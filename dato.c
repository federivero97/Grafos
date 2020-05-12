#include "TheOutsider.h"

u32 NumeroDeVertices(Grafo G){
	return G->nvertices;
};

u32 NumeroDeLados(Grafo G){
	return G->nlados;
};

u32 NumeroDeColores(Grafo G){
	return G->color;
};

//Funcion Auxiliar para ver el orden de los vertices del grafo, con el cual se realizará Greedy.
void MostrarOrden(Grafo G){
    u32 h;
    printf("Orden:{");
    for (h=0; h<(G->nvertices); h++){
        printf("%u",G->orden[h]);
        if (h!=(G->nvertices)-1){
            printf(",");
        }  
    }
    printf("}\n");
}


void MostrarColoresEnOrden(Grafo G){
    u32 h,indice;
    printf("Colores:{");
    for (h=0; h<(G->nvertices); h++){
        indice = G->orden[h];
        printf("%u",(G->vertices[G->orden[indice]]).color);
        if (h!=(G->nvertices)-1){
            printf(",");
        }  
    }
    printf("}\n");
}