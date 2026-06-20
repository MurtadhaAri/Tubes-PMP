#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void delete_node(node **head) {
    unsigned int id; 
    node *DelNode;
    node *temp;
    node *prev;
    if (*head == NULL) {
        printf("\nDatabase kosong! Tidak ada data yang bisa dihapus.\n");
        return;
    }

 
    printf("Masukkan ID Barang yang ingin dihapus: ");
    scanf("%u", &id); 
    while(getchar() != '\n'); 

    if ((*head)->id_barang == id) {
        DelNode = *head;
        (*head) = (*head)->next;
        free(DelNode);
        printf("Barang dengan ID %u berhasil dihapus!\n", id);
        return;
    }
   
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
    
    printf("Penghapusan gagal: Barang dengan ID %u tidak ditemukan!\n", id);
}
