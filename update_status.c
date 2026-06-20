#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/pgmspace.h>

void update_status(node **head) {
    uint8_t id; 
    printf_P(PSTR("Masukkan ID item yang mau diupdate rusak: "));
    scanf("%hhu", &id); 

    node *temp = *head;

    while (temp != NULL) {
        if (temp->id_barang == id) {
            temp->status = 3; 
            return; 
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        printf_P(PSTR("Item dengan ID %hhu tidak ditemukan.\n"), id);
    }
}