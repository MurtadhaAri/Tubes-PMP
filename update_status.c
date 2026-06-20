#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/pgmspace.h>

void update_status(node **head) {
    // Penanganan Masalah: Jika database masih kosong
    if (*head == NULL) {
        printf_P(PSTR("Database kosong! Tidak ada data untuk diupdate.\n"));
        return;
    }

    uint16_t id; // PERBAIKAN: Menggunakan uint16_t agar cocok dengan id_barang di header.h
    printf_P(PSTR("Masukkan ID item yang mau diupdate statusnya: "));
    scanf("%u", &id); 
    while (getchar() != '\n'); // Bersihkan buffer input UART

    node *temp = *head;

    while (temp != NULL) {
        if (temp->id_barang == id) {
            // 1. Tampilkan informasi barang dan status saat ini
            printf_P(PSTR("Barang ditemukan: %s\n"), temp->nama_barang);
            printf_P(PSTR("Status saat ini : "));
            if (temp->status == 0) printf_P(PSTR("Habis\n"));
            else if (temp->status == 1) printf_P(PSTR("Tersedia\n"));
            else if (temp->status == 2) printf_P(PSTR("Dipinjam\n"));
            else if (temp->status == 3) printf_P(PSTR("Rusak\n"));
            else printf_P(PSTR("Tidak Diketahui\n"));

            // 2. Loop validasi untuk meminta input status baru dari operator
            uint16_t pilihan_status;
            while (1) {
                printf_P(PSTR("\nPilih Status Baru:\n"));
                printf_P(PSTR("0 = Habis\n"));
                printf_P(PSTR("1 = Tersedia\n"));
                printf_P(PSTR("2 = Dipinjam\n"));
                printf_P(PSTR("3 = Rusak\n"));
                printf_P(PSTR("Masukkan pilihan (0-3): "));
                
                if (scanf("%u", &pilihan_status) == 1) {
                    while (getchar() != '\n'); // Bersihkan buffer
                    
                    if (pilihan_status <= 3) {
                        temp->status = (uint8_t)pilihan_status; // Update status baru secara dinamis
                        printf_P(PSTR("\n[SUKSES] Status item ID %hu berhasil diperbarui!\n"), id);
                        return; // Keluar fungsi setelah berhasil update
                    }
                } else {
                    while (getchar() != '\n'); // Bersihkan jika input bukan angka
                }
                printf_P(PSTR("[ERROR] Masukkan angka pilihan yang valid (0-3)!\n"));
            }
        }
        temp = temp->next;
    }

    // Jika perulangan selesai dan ID tidak ditemukan
    printf_P(PSTR("Item dengan ID %hu tidak ditemukan.\n"), id);
}
