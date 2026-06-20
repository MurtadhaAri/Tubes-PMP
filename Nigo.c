#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/pgmspace.h>

void tambah(node ** head) {
    uint16_t num;

    printf_P(PSTR("Masukkan ID Barang Baru: "));
    scanf("%hu", &num);
    while(getchar() != '\n');

    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            printf_P(PSTR("ID %hu sudah ada!\n\n"), num);
            return;
        }
        current = current->next;
    }

    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf_P(PSTR("Kapasitas memori hampir habis!\n\n"));
        return;
    }

    newNode->id_barang = num;
    
    printf_P(PSTR("Masukkan Nama Barang: "));
    fgets(newNode->nama_barang, 30, stdin); 
    newNode->nama_barang[strcspn(newNode->nama_barang, "\n")] = '\0'; 

    while (1) {
        printf_P(PSTR("Masukkan Kategori (0 = Komponen, 1 = Alat, 2 = Lainnya): "));
        scanf("%hhu", &newNode->kategori); 
        while(getchar() != '\n');

        if (newNode->kategori == 0 || newNode->kategori == 1 || newNode->kategori == 2) {
            break;
        } else {
            printf_P(PSTR("Masukkan 0, 1, atau 2\n\n"));
        }
    } 

    while(1){
        printf_P(PSTR("Masukkan Jumlah Stok: "));
        scanf("%hu", &newNode->jumlah_stock);
        while(getchar() != '\n'); 
        if(newNode->jumlah_stock > 0){
            break;
        } else {
            printf_P(PSTR("Masukkan jumlah valid! (>0)\n\n"));
        }
    }
    
    printf_P(PSTR("Masukkan Lokasi Penyimpanan: "));
    fgets(newNode->lokasi_penyimpanan, 15, stdin); 
    newNode->lokasi_penyimpanan[strcspn(newNode->lokasi_penyimpanan, "\n")] = '\0';

    while (1) {
        printf_P(PSTR("Masukkan Status (1 = Tersedia, 0 = Habis): "));
        scanf("%hhu", &newNode->status); 
        while(getchar() != '\n');

        if (newNode->status == 0 || newNode->status == 1) {
            break;
        } else {
            printf_P(PSTR("Masukkan 0 atau 1\n\n"));
        }
    } 

    printf_P(PSTR("Masukkan PIC: "));
    fgets(newNode->PIC, 15, stdin); 
    newNode->PIC[strcspn(newNode->PIC, "\n")] = '\0';

    printf_P(PSTR("Masukkan Pemilik Barang: "));
    fgets(newNode->PemilikBarang, 15, stdin); 
    newNode->PemilikBarang[strcspn(newNode->PemilikBarang, "\n")] = '\0';

    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf_P(PSTR("Data barang berhasil ditambahkan!\n\n"));
}

void UpdateStock(node **head) { 
    if (*head == NULL) {
        printf_P(PSTR("Tidak ada barang di dalam database.\n"));
        return; 
    }

    printf_P(PSTR("Masukkan ID Barang yang ingin diupdate: "));
    uint16_t targetID; 
    scanf("%hu", &targetID);
    while(getchar() != '\n'); 

    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == targetID) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf_P(PSTR("Error: ID tidak ditemukan!\n"));
        return;
    }
 
    printf_P(PSTR("Barang: %s\n"), current->nama_barang);
    printf_P(PSTR("Stok Saat Ini: %hu\n"), current->jumlah_stock);

    printf_P(PSTR("Opsi:\n1. Tambah Stok\n2. Kurangi Stok\nPilihan Anda (1/2): "));
    
    uint8_t pilihan;
    scanf("%hhu", &pilihan);
    while(getchar() != '\n');

    if (pilihan != 1 && pilihan != 2) {
        printf_P(PSTR("Pilihan tidak valid!\n"));
        return;
    }

    printf_P(PSTR("Masukkan jumlah barang: "));
    int16_t kuantitas; 
    scanf("%hd", &kuantitas);
    while(getchar() != '\n');

    if (kuantitas < 0) {
        printf_P(PSTR("Jumlah unit tidak boleh negatif!\n"));
        return;
    }

    if (pilihan == 1) {
        current->jumlah_stock += kuantitas;
        printf_P(PSTR("Berhasil menambah stok. Stok baru: %hu\n"), current->jumlah_stock);
        if (current->status == 0){
            current->status = 1; 
        }
    } 
    else if (pilihan == 2) {
        if (current->jumlah_stock < (uint16_t)kuantitas) {
            printf_P(PSTR("Stok tidak cukup!\n"));
        } else {
            current->jumlah_stock -= kuantitas;
            printf_P(PSTR("Berhasil mengurangi stok. Stok baru: %hu\n"), current->jumlah_stock);
            if (current->jumlah_stock == 0){
                current->status = 0; 
            }
        }
    }
    printf_P(PSTR("\n"));
}