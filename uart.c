#include "uart.h"
#include <avr/io.h>

void uart_init(unsigned long baud) {
    unsigned int ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    static FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
}
int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}
int uart_getchar(FILE *stream) {
    while (!(UCSR0A & (1 << RXC0)));
    char c = UDR0;
    if (c == '\r') {
        uart_putchar('\n', stdout);
    } else {
        uart_putchar(c, stdout);
    }
    return c;
}
