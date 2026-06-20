#include <stdio.h>
#include <string.h>
#include <util/delay.h> 
#include <avr/pgmspace.h>
#include "header.h"

void MenuUtama(node **head) {
    uint8_t pilihan;        

    printf_P(PSTR("\n--- Arduino Uno C Environment Ready ---\n"));
    load(head);
    while(1) {
        printf_P(PSTR("\n=======================================\n"));
        printf_P(PSTR("       SISTEM INVENTARIS LAB           \n"));
        printf_P(PSTR("=======================================\n"));
        printf_P(PSTR("1. Tambah Barang Baru\n"));
        printf_P(PSTR("2. Tampilkan Semua Barang\n"));
        printf_P(PSTR("3. Tampilkan Berdasarkan Kategori\n"));
        printf_P(PSTR("4. Update Stok Barang\n"));
        printf_P(PSTR("5. Update Status Barang Rusak\n"));
        printf_P(PSTR("6. Hapus Barang dari Database\n"));
        printf_P(PSTR("7. Cari Barang\n"));
        printf_P(PSTR("8. Keluar (Exit)\n"));
        printf_P(PSTR("Masukkan pilihan Anda (1-7): "));

        if(scanf("%hhu", &pilihan) != 1) {
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
            display(head);
        } 
        else if(pilihan == 3) {
            display_ringkas(head);
        } 
        else if(pilihan == 4) {
            update_stock(head);
        } 
        else if(pilihan == 5) {
            update_status(head);
        } 
        else if(pilihan == 6) {
            delete_node(head);
        }
        else if(pilihan == 7) {
            find(head);
        } 
        else if(pilihan == 8) {
            printf_P(PSTR("Keluar dari sistem. Terima kasih!\n"));
            save(head);
            _delay_ms(500);
            return;
        } 
        else{
            printf_P(PSTR("Pilihan menu tidak tersedia!\n"));
        }
        
        _delay_ms(500);
    }
}