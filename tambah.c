#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>       
#include <ctype.h>        
#include <avr/pgmspace.h> 

void tambah(node ** head) {
    char id_buffer[12];   
    uint16_t num = 0;     
    int temp_input;       
    uint8_t id_valid = 0;

    while (!id_valid) {
        printf_P(PSTR("Masukkan ID Barang Baru: "));
        if (fgets(id_buffer, sizeof(id_buffer), stdin) == NULL) continue;

        id_buffer[strcspn(id_buffer, "\n")] = '\0';

        if (strlen(id_buffer) == 0) {
            printf_P(PSTR("ID tidak boleh kosong\n\n"));
            continue;
        }

        id_valid = 1; 
        for (int i = 0; id_buffer[i] != '\0'; i++) {
            if (!isdigit((unsigned char)id_buffer[i])) {
                id_valid = 0;
                break;
            }
        }

        if (!id_valid) {
            printf_P(PSTR("ID harus berupa angka saja\n\n"));
        } else {
            uint32_t cek_nilai = strtoul(id_buffer, NULL, 10);

            if (cek_nilai > 65535) {
                printf_P(PSTR("Maksimal ID 65535\n\n"));
                id_valid = 0;
            } else {
                num = (uint16_t)cek_nilai;
            }
        }
    }

    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            printf_P(PSTR("ID %hu sudah ada\n\n"), num);
            return;
        }
        current = current->next;
    }

    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf_P(PSTR("Kapasitas memori hampir habis\n\n"));
        return;
    }

    newNode->id_barang = num;
    
    printf_P(PSTR("Masukkan Nama Barang: "));
    fgets(newNode->nama_barang, sizeof(newNode->nama_barang), stdin);
    newNode->nama_barang[strcspn(newNode->nama_barang, "\n")] = '\0'; 

    while (1) {
        printf_P(PSTR("Masukkan Kategori (0 = Komponen, 1 = Alat, 2 = Lainnya): "));
        scanf("%d", &temp_input); 
        while(getchar() != '\n');

        if (temp_input == 0 || temp_input == 1 || temp_input == 2) {
            newNode->kategori = (uint8_t)temp_input; 
            break;
        } else {
            printf_P(PSTR("Masukkan 0, 1, atau 2\n\n"));
        }
    } 

    while(1){
        printf_P(PSTR("Masukkan Jumlah Stok: "));
        scanf("%d", &temp_input);
        while(getchar() != '\n'); 
        if(temp_input > 0 && temp_input <= 65535){
            newNode->jumlah_stock = (uint16_t)temp_input;
            break;
        } else {
            printf_P(PSTR("Masukkan jumlah valid! (1 - 65535)\n\n"));
        }
    }
    
    printf_P(PSTR("Masukkan Lokasi Penyimpanan: "));
    fgets(newNode->lokasi_penyimpanan, sizeof(newNode->lokasi_penyimpanan), stdin);
    newNode->lokasi_penyimpanan[strcspn(newNode->lokasi_penyimpanan, "\n")] = '\0';

    while (1) {
        printf_P(PSTR("Masukkan Status (1 = Tersedia, 0 = Habis): "));
        scanf("%d", &temp_input); 
        while(getchar() != '\n');

        if (temp_input == 0 || temp_input == 1) { 
            newNode->status = (uint8_t)temp_input;
            break;
        } else {
            printf_P(PSTR("Masukkan 0 atau 1\n\n"));
        }
    } 

    printf_P(PSTR("Masukkan PIC: "));
    fgets(newNode->PIC, sizeof(newNode->PIC), stdin);
    newNode->PIC[strcspn(newNode->PIC, "\n")] = '\0';

    printf_P(PSTR("Masukkan Pemilik Barang: "));
    fgets(newNode->PemilikBarang, sizeof(newNode->PemilikBarang), stdin);
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