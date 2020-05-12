#include "TheOutsider.h"

int OrdenMatriz ( const void *pa, const void *pb ) { //Comparacion Para Ordenar Matriz de forma Creciente
    u32 *a =  *(u32**)pa;
    u32 *b =  *(u32**)pb;
    if (a[0] < b[0]) return -1;
    if (a[0] > b[0]) return 1;
    if(a[1] < b[1]) return -1;
    if(a[1] > b[1]) return 1;
    return 0;
}

int Creciente(const void * a, const void * b){    // Comparacion para Ordenar de forma Creciente
    return ( *(u32*)a - *(u32*)b );
}

void Aleatorizar(u32* A,u32 cantA, u32 semilla){
    u32 temp,indice;
    for (u32 j=0;j<cantA;j++){
        indice = (semilla) % cantA;
        assert(indice<cantA);
        temp = A[j];
        A[j] = A[indice];
        A[indice] = temp;
    }
}

void OrdenNatural(Grafo G){
    u32 h;
    for(h=0;h<(G->nvertices);h++){
        G->orden[h] = h;
    }
};

void OrdenWelshPowell(Grafo G){

    u32 i,j,temp;
    for(i=0;i<G->nvertices;i++){
        for(j=0;j<G->nvertices-1;j++){
            if (G->vertices[G->orden[j]].grado < G->vertices[G->orden[j+1]].grado){
                temp = G->orden[j];
                G->orden[j] = G->orden[j+1];
                G->orden[j+1] = temp;
            }
        }
    }
};


void AleatorizarVertices(Grafo G,u32 semilla){
	OrdenNatural(G); //Reinicio el orden anterior.
    Aleatorizar(G->orden,G->nvertices,semilla);	//Luego aleatorizo.
};
void ReordenManteniendoBloqueColores(Grafo G,u32 x){
    u32 i,j,temp;
    u32 ncolores = G->color;
    u32 * ncolorvertices = calloc(ncolores,sizeof(u32));
    u32 * poscolor = calloc(ncolores,sizeof(u32));
    //Array "Numero de vertices de color", donde en cada posicion esta
    //la cantidad de veces que aparece el numero de la pocision+1.
    //ncolorvertices con la cantidad de veces que aparece ese color en esa posicion.
    for(i=0; i<(G->nvertices); i++){
        ncolorvertices[(G->vertices[i].color)-1]++;
    }
    //Creo una matriz para guardar la etiqueta de cada vertice en su bloque de color correspondiente.
    u32 **BloquesColores;
    BloquesColores = calloc(ncolores,sizeof(u32*));
    for(i=0; i<ncolores; i++){
        BloquesColores[i] = calloc(ncolorvertices[i],sizeof(u32));
    }
    for(i=0; i<(G->nvertices); i++){
        BloquesColores[(G->vertices[i]).color-1][poscolor[(G->vertices[i]).color-1]] = (G->vertices[i]).indice;
        poscolor[(G->vertices[i]).color-1]++;
    }
/*
    for (i=0;i<ncolores;i++){
        printf("Bloque color %u:[",i+1);
        for (j=0;j<ncolorvertices[i];j++){
            printf("%u,", BloquesColores[i][j]);


        }
        printf("]\n" );
    }
*/

    //ordenBloques sera un array donde dirá en que orden debo ordenar los bloques.
    u32* ordenBloques = calloc(ncolores,sizeof(u32));
    //Inicializo
    for(i=0; i<ncolores; i++){
        ordenBloques[i] = i;
    }

    if ( x == 0){
        //Ordeno la estructura por color de los vertices de forma decreciente.
        for(i=0; i<ncolores; i++){
            ordenBloques[ncolores-i-1] = i;
        }

    }else if (x == 1){

        //Ordeno la estructura por cantidad de vertices de color de forma creciente.
        for (i = 0; i < ncolores; i++){
            for (j = 0; j<(ncolores)-1; j++){
                if (!(ncolorvertices[ordenBloques[j]] < ncolorvertices[ordenBloques[j+1]])){
                    temp = ordenBloques[j];
                    ordenBloques[j] = ordenBloques[j+1];
                    ordenBloques[j+1] = temp;
                }
            }
        }

    } else if (x > 1){
        //Pseudoaleatorizar Bloque de colores
        //Utilizo mi funcion pseudoaleatoria para definir el orden de los bloques.
        Aleatorizar(ordenBloques,ncolores,x);
    }

    //Modifico el orden de mi estructura, en el orden de bloque de colores que establecí.
    u32 pos = 0;
    for(i=0; i<ncolores; i++){
        for(j=0; j<ncolorvertices[ordenBloques[i]]; j++){
            G->orden[pos] = BloquesColores[ordenBloques[i]][j];
            pos++;
        }
    }
    //Libero memoria.
    for(i=0; i<ncolores; i++){
        free(BloquesColores[i]);
    }
    free(BloquesColores);
}
