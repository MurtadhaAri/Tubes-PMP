#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>       
#include <ctype.h>        
#include <avr/pgmspace.h> 

#define EEPROM_SIZE 1024

void tambah(node ** head) {
    char id_buffer[12];   
    uint16_t num = 0;     

    uint8_t temp8;
    uint16_t temp16;       
    
    uint8_t id_valid = 0;
    uint8_t scan_res;
    int i;
    uint32_t cek_nilai;
    node *current;
    node *newNode;
    
    uint16_t current_count = 0;
    node *cek_node;

    cek_node = *head;
    while (cek_node != NULL) {
        current_count++;
        cek_node = cek_node->next;
    }

    if (((current_count + 1) * sizeof(node)) > EEPROM_SIZE) {
        printf_P(PSTR("Tidak dapat menyimpan data lebih dari ini\n\n"));
        return;
    }

    while (!id_valid) {
        printf_P(PSTR("Masukkan ID Barang Baru: "));
        if (fgets(id_buffer, sizeof(id_buffer), stdin) == NULL) continue;

        id_buffer[strcspn(id_buffer, "\r\n")] = '\0';

        if (strlen(id_buffer) == 0) {
            printf_P(PSTR("ID tidak boleh kosong\n\n"));
            continue;
        }

        id_valid = 1; 
        for (i = 0; id_buffer[i] != '\0'; i++) {
            if (!isdigit((unsigned char)id_buffer[i])) {
                id_valid = 0;
                break;
            }
        }

        if (!id_valid) {
            printf_P(PSTR("ID harus berupa angka saja\n\n"));
        } else {
            cek_nilai = strtoul(id_buffer, NULL, 10);

            if (cek_nilai > 65535) {
                printf_P(PSTR("Maksimal ID 65535\n\n"));
                id_valid = 0;
            } else {
                num = (uint16_t)cek_nilai;
            }
        }
    }

    current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            printf_P(PSTR("ID %hu sudah ada\n\n"), num);
            return;
        }
        current = current->next;
    }

    newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf_P(PSTR("Kapasitas memori hampir habis\n\n"));
        return;
    }

    newNode->id_barang = num;
    
    printf_P(PSTR("Masukkan Nama Barang: "));
    fgets(newNode->nama_barang, sizeof(newNode->nama_barang), stdin);
    newNode->nama_barang[strcspn(newNode->nama_barang, "\r\n")] = '\0'; 

    while (1) {
        printf_P(PSTR("Masukkan Kategori (0 = Komponen, 1 = Alat, 2 = Lainnya): "));
        scan_res = scanf("%hhu", &temp8); 
        while(getchar() != '\n');

        if (scan_res == 1 && (temp8 == 0 || temp8 == 1 || temp8 == 2)) {
            newNode->kategori = temp8; 
            break;
        } else {
            printf_P(PSTR("Masukkan 0, 1, atau 2\n\n"));
        }
    } 

    while(1){
        printf_P(PSTR("Masukkan Jumlah Stok: "));
        scan_res = scanf("%hu", &temp16);
        while(getchar() != '\n'); 
        if(scan_res == 1 && temp16 > 0 && temp16 <= 65535){
            newNode->jumlah_stock = temp16;
            break;
        } else {
            printf_P(PSTR("Masukkan jumlah valid! (1 - 65535)\n\n"));
        }
    }
    
    printf_P(PSTR("Masukkan Lokasi Penyimpanan: "));
    fgets(newNode->lokasi_penyimpanan, sizeof(newNode->lokasi_penyimpanan), stdin);
    newNode->lokasi_penyimpanan[strcspn(newNode->lokasi_penyimpanan, "\r\n")] = '\0';

    while (1) {
        printf_P(PSTR("Masukkan Status (1 = Tersedia, 0 = Habis): "));
        scan_res = scanf("%hhu", &temp8);
        while(getchar() != '\n');

        if (scan_res == 1 && (temp8 == 0 || temp8 == 1)) { 
            newNode->status = temp8;
            break;
        } else {
            printf_P(PSTR("Masukkan 0 atau 1\n\n"));
        }
    } 

    printf_P(PSTR("Masukkan PIC: "));
    fgets(newNode->PIC, sizeof(newNode->PIC), stdin);
    newNode->PIC[strcspn(newNode->PIC, "\r\n")] = '\0';

    printf_P(PSTR("Masukkan Pemilik Barang: "));
    fgets(newNode->PemilikBarang, sizeof(newNode->PemilikBarang), stdin);
    newNode->PemilikBarang[strcspn(newNode->PemilikBarang, "\r\n")] = '\0';

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