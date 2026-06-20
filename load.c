#include <avr/eeprom.h>
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load(node **head) {
    uint8_t total_barang;
    uint16_t alamat_eeprom;
    uint8_t i;
    node *newNode;
    node *current;

    total_barang = eeprom_read_byte((const uint8_t*)0);
    
    if(total_barang == 255 || total_barang == 0) {
        printf_P(PSTR("EEPROM kosong. Memulai sistem dari awal.\n"));
        return;
    }

    alamat_eeprom = 1;
    printf_P(PSTR("Menemukan %u barang di EEPROM. Memuat data...\n"), total_barang);

    for(i = 0; i < total_barang; i++) {
        newNode = (node*)malloc(sizeof(node));
        if(newNode == NULL) {
            // PERBAIKAN: Typo printfP diubah menjadi printf_P
            printf_P(PSTR("Memori SRAM penuh saat memuat data!\n"));
            return;
        }
        eeprom_read_block((void*)newNode, (const void*)alamat_eeprom, sizeof(node));
        
        newNode->next = NULL;

        if(*head == NULL) 
        {
            *head = newNode;
        } 
        else {
            current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        alamat_eeprom += sizeof(node);
    }
    printf_P(PSTR("Semua data berhasil dipulihkan!\n"));
}
