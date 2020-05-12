// Rivero, Federico Joaquín: fedeerivero@gmail.com
// Rivero, Gonzalo Nicolás: gon.rivero10@gmail.com

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
typedef unsigned int u32;

struct GrafoSt
{
    u32 nvertices;      //Cantidad de vertices.
    u32 nlados;         //Cantidad de lados.
    struct VerticeSt{
        u32 nombre;         //Nombre posicion Real del vertice (cualquier u32).
        u32 indice;         //Índice del vertice (u32 entre 0 y n-1).
        u32 color;          //Color del vertice.
        u32 grado;          //Numero de vecinos.
        u32* vecinos;       //Lista de los índices de los vecinos del vertice.
    } *vertices;        //Lista de vertices.
    u32** lados;        //Matriz de lados leida del archivo.
    u32* orden;         //Orden de los índices en el cual se realizara el coloreo.
    u32 color;           //Guarda el número de colores del coloreo actual del grafo.
    u32* colores;               //Array auxiliar para calcular el coloreo.
    u32* coloresdisponibles;    //Array auxiliar para calcular el coloreo.
};

typedef struct GrafoSt* Grafo;

//graph.c
Grafo ConstruccionDelGrafo(void);
void DestruccionDelGrafo(Grafo G);

//data.c
u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 NumeroDeColores(Grafo G);
void MostrarOrden(Grafo G);
void MostrarColoresEnOrden(Grafo G);

//vert.c
u32 NombreDelVertice(Grafo G, u32 i);
u32 IndiceDelVertice(Grafo G, u32 i);
u32 ColorDelVertice(Grafo G, u32 i);
u32 GradoDelVertice(Grafo G, u32 i);
u32 NombreJotaesimoVecino(Grafo G, u32 i,u32 j);
u32 ColorJotaesimoVecino(Grafo G, u32 i,u32 j);
u32 GradoJotaesimoVecino(Grafo G, u32 i,u32 j);
void MostrarVertices(Grafo G);

//color.c
u32 NotSoGreedy(Grafo G,u32 semilla);
u32 Propio(Grafo G);
int Bipartito(Grafo G);

//sort.c
int OrdenMatriz ( const void *pa, const void *pb);
int Creciente (const void * a, const void * b);
void Aleatorizar(u32* A,u32 cantA, u32 semilla);
void OrdenNatural(Grafo G);
void OrdenWelshPowell(Grafo G);
void AleatorizarVertices(Grafo G,u32 semilla);
void ReordenManteniendoBloqueColores(Grafo G,u32 x);
