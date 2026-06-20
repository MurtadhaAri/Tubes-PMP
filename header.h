#ifndef HEADER_H   /* Include guard */
#define HEADER_H
#include <stdint.h>

typedef struct node {
    uint16_t id_barang;          
    char nama_barang[30];        
    uint8_t kategori;            
    uint16_t jumlah_stock;       
    uint8_t status;              
    char PIC[15];                
    char PemilikBarang[15];      
    char lokasi_penyimpanan[15]; 
    struct node * next;
} node;

void tambah(node ** head); // tambah di butnut, parameter sesuaikan (nigo)
void Del (node **head, int num); // delete at index (moti)
void Find (node **head, int num); // find by id (bang sam)
void Display (node **head); // all (ari)
void UpdateStock (node **head); // all (nigo)
void updateStatus (node **head); // all (Update Status)
void Disp_ringkas (node **head); // all (bang sam)

#endif
