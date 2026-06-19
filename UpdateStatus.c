#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void UpdateStatus(node **head) {
    int id;
    printf("Masukkan ID item yang mau diupdate rusak: ");
    scanf("%d", &id);

    node *temp = *head; // Start from the head of the list

    while (temp != NULL) {
        if (temp->id_barang == id) {
            temp->status = 3;
            return; 
        }
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Item dengan ID %d tidak ditemukan.\n", id);
    }
}
