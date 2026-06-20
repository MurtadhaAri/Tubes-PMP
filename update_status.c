#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/pgmspace.h>

void update_status(node **head) {
    if(*head == NULL) {
        printf_P(PSTR("Tidak ada barang di dalam database\n\n"));
        return;
    }
    uint16_t id;
    printf_P(PSTR("Masukkan ID item yang mau diupdate statusnya: "));
    scanf("%hu", &id);
    while(getchar() != '\n');
    node *temp = *head;

    while(temp != NULL) {
        if(temp->id_barang == id) {
            printf_P(PSTR("Barang ditemukan: %s\n"), temp->nama_barang);
            printf_P(PSTR("Status saat ini : "));

            if(temp->status == 1) {
                printf_P(PSTR("Tersedia\n"));
                printf_P(PSTR("Apakah ingin mengubah status barang menjadi Rusak? (Ketik 1 jika ya): "));
            } else if(temp->status == 2) {
                printf_P(PSTR("Rusak\n"));
                printf_P(PSTR("Apakah ingin mengubah status barang menjadi Tersedia? (Ketik 1 jika ya): "));
            } else {
                printf_P(PSTR("Barang Habis\n\n"));
                return;
            }

            uint8_t pilihan_status = 0;
            uint8_t verif_scan = scanf("%d", &pilihan_status);
            while(getchar() != '\n');

            if(verif_scan == 1 && pilihan_status == 1) {
                if(temp->status == 1) {
                    temp->status = (uint8_t)2;
                } else {
                    temp->status = (uint8_t)1;
                }
                printf_P(PSTR("Status item ID %hu berhasil diperbarui!\n\n"), id);
            } else {
                printf_P(PSTR("Status tidak berubah.\n\n"));
            }
            return;
        }
        temp = temp->next;
    }

    printf_P(PSTR("Item dengan ID %hu tidak ditemukan.\n\n"), id);
}
