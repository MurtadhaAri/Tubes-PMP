#include <stdio.h>
#include <util/delay.h>
#include "uart.h"
#include "header.h"

int main(void) {
    uint8_t pilihan;
    node *head = NULL;
    
    uart_init(9600);
    MenuUtama( &head);
    return 0;
}