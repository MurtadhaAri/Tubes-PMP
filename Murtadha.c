#include <stdio.h>
#include <stdlib.h>
#include "header.h"

  
void Display (node **head){
    if(*head == NULL){
        printf("DATA EMPTY.\n");
        return;
    }
    node *current = *head;
    int count = 1;

    printf("-------------------------------------------------------\n");
    printf("        DATA INVENTARIS LABORATORIUM    \n");
    printf("-------------------------------------------------------\n");
    while (current != NULL)
    {
        printf("Barang Ke-%d", count);
        printf("ID Barang           : %d\n", current->id_barang);
        printf("Nama Barang         : %s\n", current->nama_barang);
        printf("Kategori Barang     : %s\n", current->kategori);
        printf("Jumlah Stock barang : %d\n", current->jumlah_stock);

        printf("Status              :  ");
        switch (current->status)
        {
        case 0: printf("Habis\n");
            break;
        case 1: printf("Tersedia\n");
            break;
        case 2: printf("Dipinjam\n");
            break;
        case 3: printf("Rusak\n");
            break;            
        
        default: printf("Status Tidak Dikenal (%d)\n", current->status);
            break;
        }
        printf("PIC                 : %s\n", current->PIC);
        printf("Pemilik Barang      : %s\n", current->PemilikBarang);       
        current = current->next;
        count++;
    }
    printf("Total Jenis Barang Ditampilkan: %d\n", count-1);
    printf("-------------------------------------------------------\n");
}
