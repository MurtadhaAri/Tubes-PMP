#ifndef HEADER_H  
#define HEADER_H
#include <stdint.h>
#include <avr/pgmspace.h>
typedef struct node {
    uint16_t id_barang;            
    uint16_t jumlah_stock;         
    char nama_barang[10];          
    char lokasi_penyimpanan[12];   
    char PIC[10];                  
    char PemilikBarang[10];        
    uint8_t kategori:2;            
    uint8_t status:2;              
    struct node *next;             
} node;

void tambah(node ** head); 
void delete_node (node **head); 
void find (node **head); 
void display (node **head); 
void update_stock (node **head); 
void update_status (node **head); 
void display_ringkas (node **head); 
void MenuUtama(node **head);

#endif
