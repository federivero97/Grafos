#include "TheOutsider.h"

Grafo ConstruccionDelGrafo(void){


    Grafo G = NULL; 
    u32 n = 0;
    u32 m = 0;
    u32 poslado = 0;
    u32 x1,x2;
    char s[80];
    char c;
    // Leo informacion del grafo.
    while(stdin != NULL){
        if(fscanf(stdin, "%s\n", s) != EOF){
            if (fscanf(stdin, "edge %u %u\n", &n, &m)!=0){
                // Asigno memoria para el grafo.
                G = calloc(1,sizeof(struct GrafoSt));
                G->nvertices = n;    // Asigno a la estructura la cantidad de vertices del grafo.
                G->nlados = m;       // Asigno a la estructura la cantidad de lados del grafo.
                G->vertices = calloc(n,sizeof(struct VerticeSt));
                G->lados = calloc(2*m,sizeof(u32*));    // Armo Matriz de lados.
                for (u32 h=0;h<2*m;h++){
                    G->lados[h] = calloc(2,sizeof(u32));
                }
                G->orden = calloc(n,sizeof(u32));
                G->color = 0;
                G->colores = calloc(n+1,sizeof(u32));
                G->coloresdisponibles = calloc(n,sizeof(u32));
    
                break;
            }
        }
    }
    //Cargo lados.
    while(stdin != NULL){
        if (poslado==m){                                       
            break;  
        }
        if(fscanf(stdin, "%c",&c)!=EOF && c=='e'){
            if(fscanf(stdin, "%u %u\n", &x1, &x2) != EOF){;    // Cargo vertices a la Matriz de lados dos veces, una común  
                G->lados[poslado][0] = x1;                 // Y otra invertida para facilitar el cargado de la estructura.
                G->lados[poslado+m][1] = x1;
                G->lados[poslado][1] = x2;
                G->lados[poslado+m][0] = x2;
                poslado++;
            }
        }
    }
    // Termino de armar Matriz de lados
    // Ordeno lados.
    qsort(G->lados,(G->nlados)*2,sizeof(G->lados[0]),OrdenMatriz); 
    // Ordeno Matriz de modo de poder cargar los vertices sin repetirlos.
    // Cargo vertices leyendo la matriz generada, inicializando con un coloreo de n colores.
    
    // Completo vertices.
    // La cantidad de veces que aparece en la matriz, es el grado.

    (G->vertices[0]).nombre = G->lados[0][0];     //Agrego el primer vertices a la estructura.
    (G->vertices[0]).indice = 0;
    (G->vertices[0]).color = 1;
    (G->vertices[0]).grado = 1;
    G->orden[0] = 0;
    u32 posvertice = 1;
    u32 h = 0;
    for(h=1; h<(2*m); h++){                                 //Agrego los demás vertices a la estructura,
        if (G->lados[h][0] == G->lados[h-1][0]){            // a la vez le agrego el grado sumandole 1 cada 
            (G->vertices[posvertice-1]).grado++;            //  vez que aparece en el Matriz del aldo derecho.
        } else {
            (G->vertices[posvertice]).nombre = G->lados[h][0];
            (G->vertices[posvertice]).indice = posvertice;
            (G->vertices[posvertice]).color = posvertice + 1;
            (G->vertices[posvertice]).grado = 1;
            G->orden[posvertice] = posvertice;
            posvertice++;
        }
    }
    
    u32 totalgrado = 0;                                         //La suma de los grados de todos los vertices 
    for(h=0; h<(G->nvertices); h++){                        // es igual al doble de la cantidad de lados.
        totalgrado = totalgrado +  (G->vertices[h]).grado;
    }
    assert(totalgrado == 2*m);
    // Agrego vecinos.
    // Los numeros que aparecen en la columna derecha de la matriz son los vecinos del vertice de la columna izquierda
    u32 posvecino=0;
    for (posvertice=0; posvertice<(n); posvertice++){
        (G->vertices[posvertice]).vecinos = calloc((G->vertices[posvertice]).grado,sizeof(u32));
    }
    posvertice = 0;
    (G->vertices[posvertice]).vecinos[0] = IndiceDelVertice(G,G->lados[0][1]);
    posvecino = 1;
    for (h=1; h<(2*m); h++){ 
        if (G->lados[h][0] == G->lados[h-1][0]){
            (G->vertices[posvertice]).vecinos[posvecino] = IndiceDelVertice(G,G->lados[h][1]);
            posvecino++;
        } else {
            posvecino = 0;
            posvertice++;
            (G->vertices[posvertice]).vecinos[posvecino] = IndiceDelVertice(G,G->lados[h][1]);
            posvecino++;
        }
    }

    // El colores de este grafo tiene n colores, siendo n la cantidad de vertices.
    G->color = G->nvertices;

    return G;    
};

void DestruccionDelGrafo(Grafo G){
    for (u32 i=0;i<(G->nvertices);i++){
        free((G->vertices[i]).vecinos);        //Libero la memoria de la lista de vecinos de cada vertice.  
        (G->vertices[i]).vecinos = NULL;
    }
    free(G->vertices);      //Libero la lista de vertices.
    G->vertices = NULL;
    G->nvertices = 0;
    for (u32 i=0;i<(G->nlados)*2;i++){
       free(G->lados[i]);       
       G->lados[i] = NULL;      //Libero la Matriz.
    }
    free(G->lados);
    G->lados = NULL;
    G->nlados = 0;
    G->color = 0;            
    free(G->orden);         //Libero el array del orden.
    G->orden = NULL;
    free(G->colores);         //Libero el array auxiliar de colores.
    G->orden = NULL;
    free(G->coloresdisponibles);         //Libero el array auxiliar de colroes disponibles.
    G->orden = NULL;
    free(G);            //Libero el Grafo.
    G = NULL;
};