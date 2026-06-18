#include <stdlib.h>
#include <stdio.h>
#include "header.h"

void tambah(node ** head, int num) {
    // cek duplikat
    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            Serial.println("Error: ID duplikat!");
            return;
        }
        current = current->next;
    }

    // alokasi memori
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        Serial.println("Error: Kapasitas memori hampir habis!");
        return;
    }

    newNode->id_barang = num;
    
    Serial.print("Masukkan Nama Barang: ");
    while (Serial.available() == 0); 
    int lenNama = Serial.readBytesUntil('\n', newNode->nama_barang, 99); 
    newNode->nama_barang[lenNama] = '\0'; 
    Serial.println(newNode->nama_barang);

    Serial.print("Masukkan Kategori: ");
    while (Serial.available() == 0);
    int lenKat = Serial.readBytesUntil('\n', newNode->kategori, 19);
    newNode->kategori[lenKat] = '\0';
    Serial.println(newNode->kategori);

    Serial.print("Masukkan Jumlah Stok: ");
    while (Serial.available() == 0);
    newNode->jumlah_stock = Serial.parseInt();
    Serial.println(newNode->jumlah_stock);
    while(Serial.available() > 0) Serial.read();

    Serial.print("Masukkan Lokasi Penyimpanan: ");
    while (Serial.available() == 0);
    int lenLok = Serial.readBytesUntil('\n', newNode->lokasi_penyimpanan, 49);
    newNode->lokasi_penyimpanan[lenLok] = '\0';
    Serial.println(newNode->lokasi_penyimpanan);

    Serial.print("Masukkan Status: ");
    while (Serial.available() == 0);
    newNode->status = (short int)Serial.parseInt();
    Serial.println(newNode->status);
    while(Serial.available() > 0) Serial.read(); 

    Serial.print("Masukkan PIC: ");
    while (Serial.available() == 0);
    int lenPIC = Serial.readBytesUntil('\n', newNode->PIC, 29);
    newNode->PIC[lenPIC] = '\0';
    Serial.println(newNode->PIC);

    Serial.print("Masukkan Pemilik Barang: ");
    while (Serial.available() == 0);
    int lenPemilik = Serial.readBytesUntil('\n', newNode->PemilikBarang, 29);
    newNode->PemilikBarang[lenPemilik] = '\0';
    Serial.println(newNode->PemilikBarang);

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

    Serial.println("Data barang berhasil ditambahkan!\n");
}

// void UpdateStock (node **head){ 

// } 

void UpdateStock(node **head) { // all (nigo)
    // kasus data kosong
    if (*head == NULL) {
        Serial.println("Error: Data kosong! Tidak ada barang di dalam database.");
        return; 
    }

    // input id
    Serial.print("Masukkan ID Barang yang ingin diupdate: ");
    while (Serial.available() == 0); // Wait for input
    int targetID = Serial.parseInt();
    Serial.println(targetID); // Echo back to screen
    while(Serial.available() > 0) Serial.read(); // Clear trailing newline

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
        Serial.println("Error: ID tidak ditemukan!");
        return;
    }

    // Display stok 
    Serial.print("Barang: "); Serial.println(current->nama_barang);
    Serial.print("Stok Saat Ini: "); Serial.println(current->jumlah_stock);

    // input pilihan update
    Serial.println("Pilih Operasi:");
    Serial.println("1. Tambah Stok (Increase)");
    Serial.println("2. Kurangi Stok (Decrease)");
    Serial.print("Pilihan Anda (1/2): ");
    
    while (Serial.available() == 0);
    int pilihan = Serial.parseInt();
    Serial.println(pilihan);
    while(Serial.available() > 0) Serial.read(); // Clear trailing newline

    // Validate the menu choice
    if (pilihan != 1 && pilihan != 2) {
        Serial.println("Error: Pilihan tidak valid!");
        return;
    }

    // ---- STEP 6: Ask for the Quantity ----
    Serial.print("Masukkan jumlah unit barang: ");
    while (Serial.available() == 0);
    int kuantitas = Serial.parseInt();
    Serial.println(kuantitas);
    while(Serial.available() > 0) Serial.read(); // Clear trailing newline

    // Sanity check to make sure they didn't type a negative number here
    if (kuantitas < 0) {
        Serial.println("Error: Jumlah unit tidak boleh negatif!");
        return;
    }

    // ---- STEP 7: Process the Choice & Handle "Stok tidak mencukupi" ----
    if (pilihan == 1) {
        // Increase stock
        current->jumlah_stock += kuantitas;
        Serial.print(">> Berhasil menambah stok. Stok baru: ");
        Serial.println(current->jumlah_stock);
    } 
    else if (pilihan == 2) {
        // Decrease stock with warning check
        if (current->jumlah_stock < kuantitas) {
            Serial.println("Warning: Stok tidak mencukupi! Proses pengurangan dibatalkan.");
        } else {
            current->jumlah_stock -= kuantitas;
            Serial.print(">> Berhasil mengurangi stok. Stok baru: ");
            Serial.println(current->jumlah_stock);
        }
    }
    Serial.println();
}