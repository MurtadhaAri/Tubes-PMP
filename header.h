#ifndef HEADER_H   /* Include guard */
#define HEADER_H

typedef struct node {
    int id_barang;
    char nama_barang[100];
    char kategori [20];
    int jumlah_stock;
    short int status;
    char PIC[30];
    char PemilikBarang[30];
    char lokasi_penyimpanan[60];
    struct node * next;
}node;

void tambah(node ** head); // tambah di butnut, parameter sesuaikan (nigo)
void Del (node **head, int num); // delete at index (moti)
void Find (node **head, int num); // find by id (bang sam)
void Display (node **head); // all (ari)
void UpdateStock (node **head); // all (nigo)
void updateStatus (node **head); // all (Update Status)
void Disp_ringkas (node **head); // all (bang sam)

#endif
