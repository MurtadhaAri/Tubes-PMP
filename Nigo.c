#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void tambah(node ** head, int num) {
    // cek duplikat
    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            printf("Error: ID duplikat!\n");
            return;
        }
        current = current->next;
    }

    // alokasi memori
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Error: Kapasitas memori hampir habis!\n");
        return;
    }

    newNode->id_barang = num;
    
    // Asumsi: Jika fungsi tambah() dipanggil tepat setelah input scanf di menu utama,
    // mungkin perlu membersihkan buffer input (sisa '\n') terlebih dahulu sebelum pemanggilan fungsi ini.

    printf("Masukkan Nama Barang: ");
    fgets(newNode->nama_barang, 100, stdin);
    newNode->nama_barang[strcspn(newNode->nama_barang, "\n")] = '\0'; // Hapus enter bawaan fgets

    printf("Masukkan Kategori: ");
    fgets(newNode->kategori, 20, stdin);
    newNode->kategori[strcspn(newNode->kategori, "\n")] = '\0';

    printf("Masukkan Jumlah Stok: ");
    scanf("%d", &newNode->jumlah_stock);
    while(getchar() != '\n'); // Bersihkan sisa karakter enter di buffer setelah scanf

    printf("Masukkan Lokasi Penyimpanan: ");
    fgets(newNode->lokasi_penyimpanan, 50, stdin);
    newNode->lokasi_penyimpanan[strcspn(newNode->lokasi_penyimpanan, "\n")] = '\0';

    printf("Masukkan Status: ");
    scanf("%hd", &newNode->status); // %hd untuk short int
    while(getchar() != '\n'); // Bersihkan sisa karakter enter di buffer

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
        printf("Error: Data kosong! Tidak ada barang di dalam database.\n");
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
            break; // Found it!
        }
        current = current->next;
    }

    // kasus id tidak ada
    if (current == NULL) {
        printf("Error: ID tidak ditemukan!\n");
        return;
    }

    // Display stok 
    printf("Barang: %s\n", current->nama_barang);
    printf("Stok Saat Ini: %d\n", current->jumlah_stock);

    // input pilihan update
    printf("Pilih Operasi:\n");
    printf("1. Tambah Stok (Increase)\n");
    printf("2. Kurangi Stok (Decrease)\n");
    printf("Pilihan Anda (1/2): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    while(getchar() != '\n'); // Bersihkan buffer

    // Validate the menu choice
    if (pilihan != 1 && pilihan != 2) {
        printf("Error: Pilihan tidak valid!\n");
        return;
    }

    // ---- STEP 6: Ask for the Quantity ----
    printf("Masukkan jumlah unit barang: ");
    int kuantitas;
    scanf("%d", &kuantitas);
    while(getchar() != '\n'); // Bersihkan buffer

    // Sanity check to make sure they didn't type a negative number here
    if (kuantitas < 0) {
        printf("Error: Jumlah unit tidak boleh negatif!\n");
        return;
    }

    // ---- STEP 7: Process the Choice & Handle "Stok tidak mencukupi" ----
    if (pilihan == 1) {
        // Increase stock
        current->jumlah_stock += kuantitas;
        printf(">> Berhasil menambah stok. Stok baru: %d\n", current->jumlah_stock);
    } 
    else if (pilihan == 2) {
        // Decrease stock with warning check
        if (current->jumlah_stock < kuantitas) {
            printf("Warning: Stok tidak mencukupi! Proses pengurangan dibatalkan.\n");
        } else {
            current->jumlah_stock -= kuantitas;
            printf(">> Berhasil mengurangi stok. Stok baru: %d\n", current->jumlah_stock);
        }
    }
    printf("\n");
}