#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void DeleteNode(node ** head, int id) {
    if(*head == NULL){
        printf("\ndatabase kosong!\n");
    }
    else{
        node * DelNode; 
        if ((*head)->id_barang == id)
        {
            DelNode = *head;
            (*head) = (*head)->next;
            free(DelNode);
        }
        else{
            node * temp; node * prev;
            while(temp != NULL){
                if(temp->id_barang == id){
                    prev->next = temp->next;
                    free(temp);
                    return;    
                }
                prev = temp;
                temp = temp->next;
            }
            
        }
        
    }
}
