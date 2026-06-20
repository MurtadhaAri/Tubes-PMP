#include <stdio.h>
#include <stdlib.h>
#include "header.h"
void delete_node(node **head) {
    uint8_t id; 
    node *DelNode;
    node *temp;
    node *prev;
    if(*head == NULL) {
        printf_P(PSTR("\nDatabase kosong! Tidak ada data yang bisa dihapus.\n"));
        return;
    }
    printf_P(PSTR("Masukkan ID Barang yang ingin dihapus: "));
    scanf("%hhu", &id); 
    while(getchar() != '\n'); 
    if((*head)->id_barang == id) {
        DelNode = *head;
        (*head) = (*head)->next;
        free(DelNode);
        printf_P(PSTR("Barang dengan ID %hhu berhasil dihapus!\n"), id);
        return;
    }
    temp = *head;
    prev = *head;
    while(temp != NULL) {
        if(temp->id_barang == id) {
            prev->next = temp->next;
            free(temp);
            printf_P(PSTR("Barang dengan ID %hhu berhasil dihapus!\n"), id);
            return;    
        }
        prev = temp;
        temp = temp->next;
    }
    printf_P(PSTR("Penghapusan gagal: Barang dengan ID %hhu tidak ditemukan!\n"), id);
}
