#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void find(node **head) {
    uint16_t id;
    printf("Masukkan ID item: ");
    scanf("%u", &id); 
    while(getchar() != '\n');

    node *temp = *head; 

    while (temp != NULL) {
        if (temp->id_barang == id) {
            printf("ID Barang: %u\n", temp->id_barang);
            printf("Nama Barang: %s\n", temp->nama_barang);
            
            
            printf("Kategori: ");
            if(temp->kategori == 0) printf("Komponen\n");
            else if(temp->kategori == 1) printf("Alat\n");
            else printf("Lainnya (%u)\n", temp->kategori);

            printf("Jumlah Stock: %u\n", temp->jumlah_stock); 
            printf("Status: %u\n", temp->status);
            printf("PIC: %s\n", temp->PIC);
            printf("Pemilik Barang: %s\n", temp->PemilikBarang);
            printf("Lokasi Penyimpanan: %s\n", temp->lokasi_penyimpanan);
            return; 
        }
        temp = temp->next;
    }

    printf("Item dengan ID %u tidak ditemukan.\n", id);
}
