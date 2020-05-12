#include "TheOutsider.h"

u32 NombreDelVertice(Grafo G, u32 i){
    return (G->vertices[(G->orden[i])]).nombre;
};

u32 ColorDelVertice(Grafo G, u32 i){
    return (G->vertices[(G->orden[i])]).color;
};

u32 GradoDelVertice(Grafo G, u32 i){
    return (G->vertices[(G->orden[i])]).grado;
};

u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j){
    return (G->vertices[(G->vertices[(G->orden[i])]).vecinos[j]]).nombre;
};

u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j){
    return (G->vertices[(G->vertices[(G->orden[i])]).vecinos[j]]).color;
};

u32 GradoJotaesimoVecino(Grafo G, u32 i,u32 j){
    return (G->vertices[(G->vertices[(G->orden[i])]).vecinos[j]]).grado;
};


// Funciones auxiliares. 
// Obtengo el índice del vertice cuyo nombre es x.
u32 IndiceDelVertice(Grafo G, u32 x){
    u32 i = 0;
    u32 min = 0;
    u32 max = (G->nvertices)-1;
    while (min<=max){
        i = ((max-min)/2) + min;
        if ((G->vertices[i]).nombre == x)
            return i;
        else if (x < (G->vertices[i]).nombre)
            max = i - 1;
        else
            min = i + 1;
    }    
    return -1;
}


// Funcion auxiliar para ver los vertices del grafo, con sus respectivos
// nombres, índices, color, grado y vecinos.
void MostrarVertices(Grafo G){
    u32 posvertice;
    u32 k,i;
    for (i=0; i<(G->nvertices); i++){
        posvertice = G->orden[i];
            printf("Vertice %u: nombre=%u índice=%u, color=%u, grado=%u, vecinos={",posvertice,(G->vertices[posvertice]).nombre,(G->vertices[posvertice]).indice,(G->vertices[posvertice]).color,(G->vertices[posvertice]).grado);
        // Muestro vecinos
        for (k=0; (k<(G->vertices[posvertice]).grado); k++){
            printf("%u",(G->vertices[posvertice]).vecinos[k]);
            if (k!=(G->vertices[posvertice]).grado-1){
                printf(",");
            }  
        }
        printf("}\n");
    }  
}
