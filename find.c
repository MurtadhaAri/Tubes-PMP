#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void Find(node **head) {
    int id;
    printf("Masukkan ID item: ");
    scanf("%d", &id);

    node *temp = *head; // Start from the head of the list

    while (temp != NULL) {
        if (temp->id_barang == id) {
            printf("ID Barang: %d\n", temp->id_barang);
            printf("Nama Barang: %s\n", temp->nama_barang);
            printf("Kategori: %s\n", temp->kategori);
            printf("Jumlah Stock: %d\n", temp->jumlah_stock);
            printf("Status: %d\n", temp->status);
            printf("PIC: %s\n", temp->PIC);
            printf("Pemilik Barang: %s\n", temp->PemilikBarang);
            printf("Lokasi Penyimpanan: %s\n", temp->lokasi_penyimpanan);
            return; 
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Item dengan ID %d tidak ditemukan.\n", id);
    }
}
