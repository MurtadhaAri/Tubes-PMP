#ifndef HEADER_H  
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

void tambah(node ** head); 
void delete_node (node **head); 
void find(node **head); 
void display(node **head); 
void update_stock (node **head); 
void update_status (node **head); 
void display_ringkas(node **head); 
void menu_utama(node **head);

#endif
