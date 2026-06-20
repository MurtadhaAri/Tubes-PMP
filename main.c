#include <stdio.h>
#include <util/delay.h>
#include "uart.h"
#include "header.h"

int main(void) {
    uint8_t pilihan;
    node *head = NULL;
    
    uart_init(9600);
    printf_P(PSTR("\n--- Arduino Uno C Environment Ready ---\n"));
    
    // AUTO-LOAD: Ekstraksi EEPROM otomatis setiap kali Arduino menyala
    load(&head);
    
    while (1) {
        printf_P(PSTR("\n====================================\n"));
        printf_P(PSTR(" SISTEM INVENTARIS (STRESS & SAVE)  \n"));
        printf_P(PSTR("====================================\n"));
        printf_P(PSTR("[1] Tambah Barang Baru (Bot/Manual)\n"));
        printf_P(PSTR("[2] Tampilkan Semua Barang\n"));
        printf_P(PSTR("[3] Simpan Data ke EEPROM\n"));
        printf_P(PSTR("[4] Format / Kosongkan EEPROM\n"));
        printf_P(PSTR("[5] Hapus Barang\n"));
        printf_P(PSTR("====================================\n"));
        printf_P(PSTR("Masukkan nomor menu (1-5): "));
        
        // PERBAIKAN: Format uint8_t harus %hhu agar memori tidak bocor
        scanf("%hhu", &pilihan);
        while(getchar() != '\n'); 

        if (pilihan == 1) {
            tambah(&head);
        } 
        else if (pilihan == 2) {
            display(&head);
            printf_P(PSTR("\nTekan Enter untuk kembali..."));
            while(getchar() != '\n');
        } 
        else if (pilihan == 3) {
            save(&head);
        } 
        else if (pilihan == 4) {
            printf_P(PSTR("\n[WARNING] Menghapus seluruh data dari EEPROM...\n"));
            eeprom_update_byte((uint8_t*)0, 0);
            printf_P(PSTR("[SUKSES] EEPROM berhasil dikosongkan!\n"));
            printf_P(PSTR("Silakan tekan tombol RESET fisik di Arduino Anda.\n"));
            while(1); 
        }
        else if (pilihan == 5) {
            delete_node(&head);
        }
        else {
            printf_P(PSTR("\n[!] ERROR: Pilihan tidak valid!\n"));
        }
    }
    
    return 0;
}