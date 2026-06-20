#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void delete_node(node **head) {
    // 1. DEKLARASI SEMUA VARIABEL DI ATAS (Aturan wajib C murni)
    unsigned int id; // Menggunakan unsigned int agar presisi dengan uint16_t
    node *DelNode;
    node *temp;
    node *prev;

    // 2. LOGIKA EKSEKUSI PROGRAM
    // Cek apakah database kosong sebelum meminta input
    if (*head == NULL) {
        printf("\nDatabase kosong! Tidak ada data yang bisa dihapus.\n");
        return;
    }

    // Meminta ID yang ingin dihapus
    printf("Masukkan ID Barang yang ingin dihapus: ");
    scanf("%u", &id); // Menggunakan %u karena unsigned/uint16_t
    while(getchar() != '\n'); // Wajib: Pembersih buffer setelah scanf

    // Kasus 1: Hapus di Head (Antrean pertama)
    if ((*head)->id_barang == id) {
        DelNode = *head;
        (*head) = (*head)->next;
        free(DelNode);
        printf("Barang dengan ID %u berhasil dihapus!\n", id);
        return;
    }
    
    // Kasus 2: Hapus di tengah/akhir
    temp = *head;
    prev = *head;
    
    while (temp != NULL) {
        if (temp->id_barang == id) {
            prev->next = temp->next;
            free(temp);
            printf("Barang dengan ID %u berhasil dihapus!\n", id);
            return;    
        }
        prev = temp;
        temp = temp->next;
    }
    
    // Jika loop while selesai tapi belum mengenai return (ID tidak ada)
    printf("Penghapusan gagal: Barang dengan ID %u tidak ditemukan!\n", id);
}
