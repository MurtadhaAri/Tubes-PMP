#include <avr/eeprom.h>
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void save(node **head) {
    uint8_t total_barang = 0;
    uint16_t alamat_eeprom = 1;
    node *current = *head;
    printf_P(PSTR("\nMenyimpan data ke EEPROM...\n"));
    while (current != NULL) {
        if (alamat_eeprom + sizeof(node) > 1023) {
            printf_P(PSTR("Kapasitas fisik EEPROM (1KB) sudah penuh!\n"));
            printf_P(PSTR("Hanya %u barang pertama yang berhasil diselamatkan.\n"), total_barang);
            break; 
        }
        eeprom_update_block((const void*)current, (void*)alamat_eeprom, sizeof(node));
        alamat_eeprom += sizeof(node); 
        total_barang++;
        current = current->next;
    }
    eeprom_update_byte((uint8_t*)0, total_barang);
    printf_P(PSTR("Berhasil %u barang tersimpan permanen.\n"), total_barang);
}
