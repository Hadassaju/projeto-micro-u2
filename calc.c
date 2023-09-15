char volatile *iostatus = (char *)0x0;
char volatile *iodata = (char *)0xC;

void int_to_string(unsigned short num, char str[]) {
  unsigned short i = 0;
  unsigned short is_negative = 0;

  // Trata o caso especial de zero
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  // Trata números negativos
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  // Cria a string reversa dos dígitos
  while (num > 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }

  // Adiciona o sinal de negativo, se necessário
  if (is_negative) {
    str[i++] = '-';
  }

  // Inverte a string
  unsigned short j;
  for (j = 0; j < i / 2; j++) {
    char temp = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = temp;
  }

  // Adiciona o caractere nulo para terminar a string
  str[i] = '\0';
}

void uart_send_string(char *str)
{
  for (unsigned short i = 0; str[i] != '\0'; i++)
  {
    while ((*iostatus & 0x20) != 0x20)
      ;
    *iodata = str[i];
  }
	
	// Adiciona o caractere nulo para terminar a string
  while ((*iostatus & 0x20) != 0x20)
    ;
  *iodata = '\0';
}

void uart_send_integer(unsigned short num)
{
  char str[20];
  int_to_string(num, str);
  uart_send_string(str);
}

// Função para calcular a média de um vetor
float calcularMedia(int vetor[], int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return (float)soma / tamanho;
}

// Função para calcular a mediana de um vetor
float calcularMediana(int vetor[], int tamanho) {
    // Primeiro, ordena o vetor
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    // Calcula a mediana
    if (tamanho % 2 == 0) {
        // Se o tamanho do vetor for par, médiana é a média dos dois valores do meio
        int meio1 = vetor[(tamanho - 1) / 2];
        int meio2 = vetor[tamanho / 2];
        return (float)(meio1 + meio2) / 2;
    } else {
        // Se o tamanho do vetor for ímpar, médiana é o valor do meio
        return (float)vetor[tamanho / 2];
    }
}

// Função para calcular a moda de um vetor
int calcularModa(int vetor[], int tamanho) {
    int moda = vetor[0];
    int modaContagem = 1;
    int contagem = 1;

    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] == vetor[i - 1]) {
            contagem++;
        } else {
            contagem = 1;
        }

        if (contagem > modaContagem) {
            moda = vetor[i];
            modaContagem = contagem;
        }
    }

    return moda;
}

int main()
{

	unsigned short array[] = {5, 2, 7, 2, 8, 3, 5, 9, 2, 6};
    unsigned short size = sizeof(array) / sizeof(array[0]);

    uart_send_string("\n\nCalcular moda\n");
    for (unsigned short i = 0; i < size; i++)
    {
        uart_send_integer(array[i]);
        if (i == size){
            break;
        }
    }

    moda = calcularModa(array, size);
    uart_send_integer(moda);
    uart_send_string("\nFim.");

    return 0;
}
