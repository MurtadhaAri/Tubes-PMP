#include <string.h>
#include <stdio.h>
#include "header.h"

void display_ringkas(node **head){
    if (*head==NULL){
        printf_P(PSTR("DATA EMPTY.\n"));
        return;
    }
    node *current = *head;

    uint8_t input_kategori;
    printf_P(PSTR("\nPilih Kategori:\n"));
    printf_P(PSTR("0 = Komponen\n"));
    printf_P(PSTR("1 = Alat\n"));
    printf_P(PSTR("2 = Lainnya\n"));
    printf_P(PSTR("Masukkan Kategori: "));
    scanf("%hhu", &input_kategori);
    while(getchar() != '\n');

    if (input_kategori > 2){
        printf_P(PSTR("KATEGORI TIDAK VALID!\n"));
        return;
    }

    printf_P(PSTR("---------------------------------------------------------------------------\n"));
    printf_P(PSTR("   DATA INVENTARIS KATEGORI LABORATORIUM "));
    if(input_kategori == 0) printf_P(PSTR("KOMPONEN\n"));
    else if(input_kategori == 1) printf_P(PSTR("ALAT\n"));
    else printf_P(PSTR("LAINNYA\n"));
    printf_P(PSTR("---------------------------------------------------------------------------\n"));

    uint8_t count = 0;
    while (current != NULL){
        if(current->kategori == input_kategori){
            count++;
            printf_P(PSTR("[%u]. ID: %u | Nama: %s | Stok: %u | Lokasi Penyimpanan: %s\n"), count, current->id_barang, current->nama_barang, current->jumlah_stock, current->lokasi_penyimpanan);
            printf_P(PSTR(" Status: "));
            if(current->status == 0) printf_P(PSTR("Habis"));
            else if(current->status == 1) printf_P(PSTR("Tersedia"));
            else if(current->status == 2) printf_P(PSTR("Dipinjam"));
            else if(current->status ==3) printf_P(PSTR("Rusak"));
            else printf_P(PSTR("Status Tidak Diketahui"));
            printf_P(PSTR(" | PIC: %s | Pemilik: %s\n"), current->PIC, current->PemilikBarang);
            printf_P(PSTR("---------------------------------------------------------------------------\n"));
        }
        current = current->next;
    }

    if(count==0) printf_P(PSTR("Tidak ada barang di dalam kategori ini.\n"));
    else printf_P(PSTR("Total Barang dalam kategori ini: %u\n"), count);
    printf_P(PSTR("---------------------------------------------------------------------------\n"));
}