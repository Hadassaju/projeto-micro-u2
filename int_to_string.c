void int_to_string(unsigned short num, char str[]) {
    int i = 0;
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

    // Inverte a string enquanto converte
    while (num > 0) {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    }

    // Adiciona o sinal de negativo, se necessário
    if (is_negative) {
        str[i++] = '-';
    }

    // Inverte a string
    int start = 0;
    if (is_negative) {
        start = 1;  // Ignora o sinal de negativo temporariamente
    }

    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    // Adiciona o caractere nulo para terminar a string
    str[i] = '\0';
}
