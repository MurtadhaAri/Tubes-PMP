#ifndef HEADER_H   /* Include guard */
#define HEADER_H
#include <stdint.h>
#include <avr/pgmspace.h>
typedef struct node {
    uint16_t id_barang;            // 2 byte
    uint16_t jumlah_stock;         // 2 byte
    
    char nama_barang[10];          // 10 byte
    char lokasi_penyimpanan[12];   // 12 byte
    char PIC[10];                  // 10 byte
    char PemilikBarang[10];        // 10 byte
    
    // --- LETAKKAN BITFIELD BERSEBELAHAN ---
    uint8_t kategori:2;            // 2 bit
    uint8_t status:2;              // 2 bit
    // Keduanya kini akan di-pack sempurna ke dalam 1 byte SRAM!
    
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