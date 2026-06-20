#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void find(node **head) {
    uint8_t id;
    printf_P(PSTR("Masukkan ID item: "));
    scanf("%hhu", &id); 
    while(getchar() != '\n');

    node *temp = *head; 

    while (temp != NULL) {
        if (temp->id_barang == id) {
            printf_P(PSTR("ID Barang: %hu\n"), temp->id_barang);
            printf_P(PSTR("Nama Barang: %s\n"), temp->nama_barang);
            
            printf_P(PSTR("Kategori: "));
            if(temp->kategori == 0) printf_P(PSTR("Komponen\n"));
            else if(temp->kategori == 1) printf_P(PSTR("Alat\n"));
            else printf_P(PSTR("Lainnya (%hhu)\n"), temp->kategori);
            
            printf_P(PSTR("Jumlah Stock: %hu\n"), temp->jumlah_stock); 
            printf_P(PSTR("Status: %hhu\n"), temp->status);
            printf_P(PSTR("PIC: %s\n"), temp->PIC);
            printf_P(PSTR("Pemilik Barang: %s\n"), temp->PemilikBarang);
            printf_P(PSTR("Lokasi Penyimpanan: %s\n"), temp->lokasi_penyimpanan);
            return; 
        }
        temp = temp->next;
    }

    printf_P(PSTR("Item dengan ID %hhu tidak ditemukan.\n"), id);
}