#ifndef UART_H
#define UART_H

#include <stdio.h>

void uart_init(unsigned long baud);
int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

#endif
