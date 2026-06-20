#include <stdio.h>
#include <util/delay.h>
#include "uart.h"
#include "header.h"

int main(void) {
    uint8_t pilihan;
    node *head = NULL;
    
    uart_init(9600);
    printf_P(PSTR("\n--- Arduino Uno C Environment Ready ---\n"));
    MenuUtama( &head);
    return 0;
}