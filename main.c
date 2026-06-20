#include <stdio.h>
#include <util/delay.h>
#include "uart.h"
#include "header.h"

int main(void) {
    uart_init(9600);
    node *head = NULL; 
    menu_utama(&head); 
    return 0;
}
