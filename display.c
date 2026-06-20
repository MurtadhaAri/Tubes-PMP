#include <stdio.h>
#include <stdlib.h>
#include "header.h"
void display(node **head){
    if(*head == NULL){
        printf_P(PSTR("DATA EMPTY.\n"));
        return;
    }
    node *current = *head;
    uint8_t count = 1;

    printf_P(PSTR("---------------------------------------------------------------------------\n"));
    printf_P(PSTR("        DATA INVENTARIS LABORATORIUM    \n"));
    while(current != NULL)
    {
        printf_P(PSTR("---------------------------------------------------------------------------\n"));
        printf_P(PSTR("Barang Ke-%u\n"), count);
        printf_P(PSTR("ID Barang           : %u\n"), current->id_barang);
        printf_P(PSTR("Nama Barang         : %s\n"), current->nama_barang);
        printf_P(PSTR("Kategori Barang     : "));
        if(current->kategori == 0)printf_P(PSTR("Komponen\n"));
        else if(current->kategori == 1)printf_P(PSTR("Alat\n"));
        else printf_P(PSTR("Lainnya (%u)\n"), current->kategori);

        printf_P(PSTR("Jumlah Stock barang : %u\n"), current->jumlah_stock);
        printf_P(PSTR("Lokasi Penyimpanan  : %s\n"), current->lokasi_penyimpanan);
        
        printf_P(PSTR("Status              : "));
        if(current->status==0)printf_P(PSTR("Habis\n"));
        else if(current->status==1)printf_P(PSTR("Tersedia\n"));
        else if(current->status==2)printf_P(PSTR("Rusak\n"));
        else printf_P(PSTR("Status Tidak Diketahui (%u)\n"), current->status);

        printf_P(PSTR("PIC                 : %s\n"), current->PIC);
        printf_P(PSTR("Pemilik Barang      : %s\n"), current->PemilikBarang);    
        current = current->next;
        count++;
    }
    printf_P(PSTR("---------------------------------------------------------------------------\n"));
    printf_P(PSTR("Total Jenis Barang Ditampilkan: %u\n"), count-1);
    printf_P(PSTR("---------------------------------------------------------------------------\n"));
}
