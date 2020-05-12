#include "TheOutsider.h"
//Limpio los colores anteriores.
//Coloreo los vertices en el orden guardado en la estrucura.
//Creo una lista ordenada de los colores que poseen los vecinos de cada vertice.
//Creo otra lista pseudoaleatoreamente ordenada de los colores posibles del vertice actual.


u32 NotSoGreedy(Grafo G,u32 semilla){
    u32 i, j, h, disponibles, posngb, id, ncolores;
    //Elimino el coloreo anterior.
    G->color = 0;
    for (i=0;i<(G->nvertices);i++){
        (G->vertices[i]).color = 0;
    }
    //Pinto el primer vertice.
    G->vertices[G->orden[0]].color = 1;
    ncolores = 1;


    for (i=1; i<(G->nvertices); i++){
        // Reinicio los colores de los vecinos y los colores disponibles.
        for (h=0;(h<ncolores+1);h++){
            G->coloresdisponibles[h] = 0;
            G->colores[h] = 0;
        }
        id = G->orden[i];
        // Pongo el valor del indice en las posiciones de los colores que poseen los vecinos.
        for (j=0; j<((G->vertices[id]).grado); j++){
            posngb = (G->vertices[id]).vecinos[j];
            G->colores[(G->vertices[posngb]).color] = id;
        }
        disponibles = 0;
        // Veo cuantos coloresdisponibles tengo para ese vertice.

        for (j=1;j<ncolores+1;j++){
            if (G->colores[j]!=id){
                G->coloresdisponibles[disponibles]=j;
                disponibles++;
            }
        }

        // Si no tiene colores disponibles coloreo con ncolores+1.
        if (disponibles==0){
            ncolores = ncolores + 1;
            (G->vertices[id]).color = ncolores;
          //  printf("Nuevo color: %u\n",ncolores );
        } else {
            // Sino selecciono pseudoaleatoreamente un color de los disponibles que tendrá el vertice.
            Aleatorizar(G->coloresdisponibles,disponibles,semilla);
            (G->vertices[id]).color = G->coloresdisponibles[(semilla*i)% disponibles];
            //printf("Elijo %u\n",(G->vertices[id]).color);
        }
        assert((G->vertices[id]).color != 0);
    }
    G->color = ncolores;
    return G->color;
}


u32 Propio(Grafo G){
    u32 propio = 1;
    for (u32 i=0; i<G->nvertices; i++){
        for (u32 j=0; j<(G->vertices[i]).grado;j++){
            if (G->vertices[i].color == G->vertices[((G->vertices[i]).vecinos[j])].color){
                propio = 0;
            }
        }
    }
    return propio;
}

// Creo una cola para hacer BFS
// Si la posicion de la cola esta vacia, busco el primer vertice que no ha sido coloreado, cuando esto sucede,
// es porque este se ubica en una componente conexa distinta y agrego el vertice a la cola y prosigo.
// Luego agrego a una cola los vecinos coloreándolos con el color opuesto.
// Si deseo colorear un vecino coloreado, comparo con el color del vertice actual, si es igual, el grafo no es Bipartito.
// Finalmente comparo si el coloreo es propio.
// Si el Grafo no es bipartito, lo coloreo con otro coloreo propio y devuelvo -k, donde k es numero de componentes conexas.

int Bipartito(Grafo G){
    u32  i, j, h, coloreo;
    int k;
    bool bipartito;
    int* cola = calloc(G->nvertices,sizeof(int));
    //Elimino coloreo anterior
    for (i=0; i<G->nvertices; i++){
        G->vertices[i].color = 0;
        cola[i] = -1;
    }
    coloreo = 0;
    bipartito = true;
    k = 0;
    h = 0;
    i = 0;
    while (G->nvertices>coloreo){
        // Si la posicion de la cola esta vacia, busco el primer vertice que no ha sido coloreado, cuando esto sucede,
        // es porque este se ubica en una componente conexa distinta. Coloreo y agrego el vertice a la cola y prosigo.
        while (cola[i]<0){
            j = 0;
            while (G->vertices[j].color!=0){
                j++;
            }
            k++;
            cola[i] = j;
            h++;
            G->vertices[cola[i]].color = 1;
            coloreo++;
        }
        // Luego agrego a una cola los vecinos coloreándolos con el color opuesto.
        // Si deseo colorear un vecino coloreado, comparo con el color del vertice actual, si es igual, el grafo no es Bipartito.
        for (j=0;j<G->vertices[cola[i]].grado;j++){
            if (G->vertices[G->vertices[cola[i]].vecinos[j]].color==0){
                G->vertices[G->vertices[cola[i]].vecinos[j]].color = 3 - G->vertices[cola[i]].color;
                cola[h]=G->vertices[i].vecinos[j];
                h++;
                coloreo++;
            } else {
                if (G->vertices[G->vertices[cola[i]].vecinos[j]].color==G->vertices[cola[i]].color){
                    bipartito = false;
                }
            }
        }
        i++;
    }
    // Finalmente compruebo que haya un coloreo propio.
    if (bipartito){
        for (i=0; i<G->nvertices; i++){
            for (j=0; j<G->vertices[i].grado;j++){
                if (G->vertices[i].color == G->vertices[G->vertices[i].vecinos[j]].color){
                    bipartito = false;
                }
            }
        }
    }
    free(cola);
    cola = NULL;
    // Si no es Bipartito coloreo el grafo con un coloreo propio, donde el color de cada vertice es igual a su indice.
    if (!bipartito){
        for (i=0; i<G->nvertices; i++){
            G->vertices[i].color = i;
        }
        return (-1)*k;
    }
    return k;
}
