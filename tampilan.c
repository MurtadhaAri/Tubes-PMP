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
    while (current != NULL)
    {
        printf("-------------------------------------------------------\n");
        printf("Barang Ke-%d\n", count);
        printf("ID Barang           : %d\n", current->id_barang);
        printf("Nama Barang         : %s\n", current->nama_barang);
        printf("Kategori Barang     : ");
        if(current->kategori == 0)printf("Komponen\n");
        else if(current->kategori == 1)printf("Alat\n");
        else printf("Lainnya (%d)\n", current->kategori);

        printf("Jumlah Stock barang : %d\n", current->jumlah_stock);
        
        printf("Status              : ");
        if(current->status==0)printf("Habis\n");
        else if(current->status==1)printf("Tersedia\n");
        else if(current->status==2)printf("Dipinjam\n");
        else if(current->status==3)printf("Rusak\n");
        else printf("Status Tidak Diketahui (%d)\n", current->status);

        printf("PIC                 : %s\n", current->PIC);
        printf("Pemilik Barang      : %s\n", current->PemilikBarang);    
        current = current->next;
        count++;
    }
    printf("-------------------------------------------------------\n");
    printf("Total Jenis Barang Ditampilkan: %d\n", count-1);
    printf("-------------------------------------------------------\n");
}
