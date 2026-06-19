#include <string.h>
#include <stdio.h>
#include "header.h"

void Disp_ringkas (node **head){
    if (*head==NULL){
        printf("DATA EMPTY.\n");
        return;
    }
    node *current = *head;

    int input_kategori;
    printf("\nPilih Kategori:\n");
    printf("0 = Komponen\n");
    printf("1 = Alat\n");
    printf("2 = Lainnya\n");
    printf("Masukkan Kategori: ");
    scanf("%d", &input_kategori);
    while(getchar() != '\n');

    if (input_kategori < 0 || input_kategori > 2){
        printf("KATEGORI TIDAK VALID!\n");
        return;
    }

    printf("-------------------------------------------------------\n");
    printf("   DATA INVENTARIS KATEGORI LABORATORIUM ");
    if(input_kategori == 0) printf("KOMPONEN\n");
    else if(input_kategori == 1) printf("ALAT\n");
    else printf("LAINNYA\n");
    printf("-------------------------------------------------------\n");

    int count = 0;
    while (current != NULL){
        if(current->kategori == input_kategori){
            count++;
            printf("[%d]. ID: %d | Nama: %s | Stok: %d | Lokasi Penyimpanan: %s\n", count, current->id_barang, current->nama_barang, current->jumlah_stock, current->lokasi_penyimpanan);
            printf(" Status: ");
            if(current->status == 0) printf("Habis");
            else if(current->status == 1) printf("Tersedia");
            else if(current->status == 2) printf("Dipinjam");
            else if(current->status ==3)printf("Rusak");
            else printf("Status Tidak Diketahui");
            printf(" | PIC: %s | Pemilik: %s\n", current->PIC, current->PemilikBarang);
            printf("-------------------------------------------------------\n");
        }
        current = current->next;
    }

    if(count==0) printf("Tidak ada barang di dalam kategori ini.\n");
    else printf("Total Barang dalam kategori ini: %d\n", count);
    printf("-------------------------------------------------------\n");
}
