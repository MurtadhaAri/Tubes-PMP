#include <stdlib.h>
#include <stdio.h>
#include "header.h"

void tambah(node ** head, int num) {
    // 1. Check for Duplicate ID
    node *current = *head;
    while (current != NULL) {
        if (current->id_barang == num) {
            Serial.println("Error: ID duplikat!");
            return;
        }
        current = current->next;
    }

    // 2. Allocate Memory
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        Serial.println("Error: Kapasitas memori hampir habis!");
        return;
    }

    newNode->id_barang = num;

    // ---- READING STRINGS USING BUILT-IN ARDUINO FUNCTIONS ----
    
    Serial.print("Masukkan Nama Barang: ");
    while (Serial.available() == 0); // Wait for input
    // Read until newline, leave room for '\0' by passing 99 instead of 100
    int lenNama = Serial.readBytesUntil('\n', newNode->nama_barang, 99); 
    newNode->nama_barang[lenNama] = '\0'; // Manually null-terminate
    Serial.println(newNode->nama_barang);

    Serial.print("Masukkan Kategori: ");
    while (Serial.available() == 0);
    int lenKat = Serial.readBytesUntil('\n', newNode->kategori, 19);
    newNode->kategori[lenKat] = '\0';
    Serial.println(newNode->kategori);

    // ---- READING INTEGERS ----
    Serial.print("Masukkan Jumlah Stok: ");
    while (Serial.available() == 0);
    newNode->jumlah_stock = Serial.parseInt();
    Serial.println(newNode->jumlah_stock);
    while(Serial.available() > 0) Serial.read(); // Clear trailing newline

    Serial.print("Masukkan Status: ");
    while (Serial.available() == 0);
    newNode->status = (short int)Serial.parseInt();
    Serial.println(newNode->status);
    while(Serial.available() > 0) Serial.read(); // Clear trailing newline

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

    // 5. Link the Node
    if (*head == NULL) {
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    Serial.println(">> Data barang berhasil ditambahkan! <<\n");
}

void UpdateStock (node **head); // all (nigo)
