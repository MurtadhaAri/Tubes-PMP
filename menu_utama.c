#include <stdio.h>
#include <string.h>
#include <util/delay.h> 
#include <avr/pgmspace.h>
#include "header.h"

void TampilkanMenuAplikasi(void) {
    printf_P(PSTR("\n=======================================\n"));
    printf_P(PSTR("       SISTEM INVENTARIS LAB           \n"));
    printf_P(PSTR("=======================================\n"));
    printf_P(PSTR("1. Tambah Barang Baru\n"));
    printf_P(PSTR("2. Tampilkan Semua Barang\n"));
    printf_P(PSTR("3. Tampilkan Berdasarkan Kategori\n"));
    printf_P(PSTR("4. Update Stok Barang\n"));
    printf_P(PSTR("5. Update Status Barang Rusak\n"));
    printf_P(PSTR("6. Hapus Barang dari Database\n"));
    printf_P(PSTR("7. Keluar (Exit)\n"));
    printf_P(PSTR("Masukkan pilihan Anda (1-7): "));
}

void MenuUtama(node **head) {
    int pilihan;
    int id_target;

    printf_P(PSTR("\n--- Arduino Uno C Environment Ready ---\n"));

    while(1) {
        
        TampilkanMenuAplikasi();

        if(scanf("%d", &pilihan) != 1) {
            while(getchar() != '\n'); 
            printf_P(PSTR("Input harus berupa angka!\n"));
            _delay_ms(1000);
            continue;
        }
        while(getchar() != '\n'); 

        printf_P(PSTR("\n"));

        
        if(pilihan == 1) {
            tambah(head);
        } 
        else if(pilihan == 2) {
            Display(head);
        } 
        else if(pilihan == 3) {
            Disp_ringkas(head);
        } 
        else if(pilihan == 4) {
            UpdateStock(head);
        } 
        else if(pilihan == 5) {
            update_status_rusak(head);
        } 
        else if(pilihan == 6) {
            printf_P(PSTR("Masukkan ID Barang yang ingin dihapus: "));
            if(scanf("%d", &id_target) == 1) {
                while(getchar() != '\n');
                DeleteNode(head, id_target);
            } else{
                while(getchar() != '\n');
                printf_P(PSTR("ID tidak valid!\n"));
            }
        } 
        else if(pilihan == 7) {
            printf_P(PSTR("Keluar dari sistem. Terima kasih!\n"));
            _delay_ms(500);
            return;
        } 
        else{
            printf_P(PSTR("Pilihan menu tidak tersedia!\n"));
        }
        
        _delay_ms(500);
    }
}