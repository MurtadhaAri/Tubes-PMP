#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <avr/pgmspace.h>

void update_stock(node **head) { 
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
        printf_P(PSTR("ID tidak ditemukan!\n"));
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
    uint16_t jumlah; 
    scanf("%hd", &jumlah);
    while(getchar() != '\n');

    if (kuantitas < 0) {
        printf_P(PSTR("Jumlah unit tidak boleh negatif\n"));
        return;
    }

    if (pilihan == 1) {
        current->jumlah_stock += jumlah;
        printf_P(PSTR("Berhasil menambah stok. Stok baru: %hu\n"), current->jumlah_stock);
        if (current->status == 0){
            current->status = 1; 
        }
    } 
    else if (pilihan == 2) {
        if (current->jumlah_stock < (uint16_t)jumlah) {
            printf_P(PSTR("Stok tidak cukup\n"));
        } else {
            current->jumlah_stock -= jumlah;
            printf_P(PSTR("Berhasil mengurangi stok. Stok baru: %hu\n"), current->jumlah_stock);
            if (current->jumlah_stock == 0){
                current->status = 0; 
            }
        }
    }
    printf_P(PSTR("\n"));
}
