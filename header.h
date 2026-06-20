#ifndef HEADER_H   /* Include guard */
#define HEADER_H
#include <stdint.h>
#include <avr/pgmspace.h>
typedef struct node {
    uint16_t id_barang;            // 2 byte
    char nama_barang[10];          // Dipangkas dari 30 -> 20 byte
    uint8_t kategori;              // 1 byte
    uint16_t jumlah_stock;         // 2 byte
    char lokasi_penyimpanan[12];   // Dipangkas dari 15 -> 12 byte
    uint8_t status;                // 1 byte
    char PIC[10];                  // Dipangkas dari 15 -> 10 byte
    char PemilikBarang[10];        // Dipangkas dari 15 -> 10 byte
    struct node *next;             // 2 byte
} node;

void tambah(node ** head); // tambah di butnut, parameter sesuaikan (nigo)
void delete_node (node **head); // delete at index (moti)
void find (node **head); // find by id (bang sam)
void display (node **head); // all (ari)
void update_stock (node **head); // all (nigo)
void update_status (node **head); // all (Update Status)
void display_ringkas (node **head); // all (bang sam)

#endif