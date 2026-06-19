#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void tambah(node ** head) {
    int num;

    printf("Masukkan ID Barang Baru: ");
    scanf("%d", &num);
    while(getchar() != '\n');

    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            printf("ID %d sudah ada!\n\n", num);
            return;
        }
        current = current->next;
    }

    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Kapasitas memori hampir habis!\n\n");
        return;
    }

    newNode->id_barang = num;
    
    printf("Masukkan Nama Barang: ");
    fgets(newNode->nama_barang, 100, stdin);
    newNode->nama_barang[strcspn(newNode->nama_barang, "\n")] = '\0'; 

    while (1) {
        printf("Masukkan Kategori (0 = Komponen, 1 = Alat, 2 = Lainnya): ");
        scanf("%hd", &newNode->kategori); 
        while(getchar() != '\n');

        if (newNode->kategori == 1 || newNode->kategori == 2 || newNode->kategori == 0) {
            break;
        } else {
            printf("Masukkan 0, 1, atau 2\n\n");
        }
    } 

    while(1){
        printf("Masukkan Jumlah Stok: ");
        scanf("%d", &newNode->jumlah_stock);
        while(getchar() != '\n'); 
        if(newNode->jumlah_stock > 0){
            break;
        } else printf("Masukkan jumlah valid! (>0)\n\n");
    }
    
    printf("Masukkan Lokasi Penyimpanan: ");
    fgets(newNode->lokasi_penyimpanan, 50, stdin);
    newNode->lokasi_penyimpanan[strcspn(newNode->lokasi_penyimpanan, "\n")] = '\0';

    while (1) {
        printf("Masukkan Status (1 = Tersedia, 0 = Habis): ");
        scanf("%hd", &newNode->status); 
        while(getchar() != '\n');

        if (newNode->status == 1 || newNode->status == 2) {
            break;
        } else {
            printf("Masukkan 1 atau 2\n\n");
        }
    } 

    printf("Masukkan PIC: ");
    fgets(newNode->PIC, 30, stdin);
    newNode->PIC[strcspn(newNode->PIC, "\n")] = '\0';

    printf("Masukkan Pemilik Barang: ");
    fgets(newNode->PemilikBarang, 30, stdin);
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

    printf("Data barang berhasil ditambahkan!\n\n");
}

void UpdateStock(node **head) { 
    // kasus data kosong
    if (*head == NULL) {
        printf("Tidak ada barang di dalam database.\n");
        return; 
    }

    // input id
    printf("Masukkan ID Barang yang ingin diupdate: ");
    int targetID;
    scanf("%d", &targetID);
    while(getchar() != '\n'); // Bersihkan buffer

    // cari id
    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == targetID) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: ID tidak ditemukan!\n");
        return;
    }
 
    printf("Barang: %s\n", current->nama_barang);
    printf("Stok Saat Ini: %d\n", current->jumlah_stock);

    printf("Opsi:\n");
    printf("1. Tambah Stok\n");
    printf("2. Kurangi Stok\n");
    printf("Pilihan Anda (1/2): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    while(getchar() != '\n');

    if (pilihan != 1 && pilihan != 2) {
        printf("Pilihan tidak valid!\n");
        return;
    }

    printf("Masukkan jumlah barang: ");
    int kuantitas;
    scanf("%d", &kuantitas);
    while(getchar() != '\n');

    if (kuantitas < 0) {
        printf("Jumlah unit tidak boleh negatif!\n");
        return;
    }

    if (pilihan == 1) {
        current->jumlah_stock += kuantitas;
        printf("Berhasil menambah stok. Stok baru: %d\n", current->jumlah_stock);
        if (current->status == 0){
            current->status == 1;
        }
    } 
    else if (pilihan == 2) {
        if (current->jumlah_stock < kuantitas) {
            printf("Stok tidak cukup!\n");
        } else {
            current->jumlah_stock -= kuantitas;
            printf("Berhasil mengurangi stok. Stok baru: %d\n", current->jumlah_stock);
            if (current->jumlah_stock == 0){
                current->status == 0;
            }
        }
    }
    printf("\n");
}