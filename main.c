#include "TheOutsider.h"


/*Con un main que hace OrdenNatural mas NotSoGreedy mas chequeo de propio,
 luego una cierta cantidad (a elección) de AleatorizarVertices (
 también seguidos de NotSoGreedy mas chequeo de propio)
 luego WelshPowell (también seguido de NotSoGreedy mas chequeo de propio),
 luego elije el mejor de todos ellos, luego una cierta cantidad (a elección) de ReordenManteniendoBloqueColores
 (también seguidos de NotSoGreedy mas chequeo de propio) y finalmente Bipartito mas destrucción del grafo, pasa lo siguiente:*/
int main(void){
    Grafo G = ConstruccionDelGrafo();
    printf("Cargando Grafo...\n");

    u32 t;
    u32* OrdenGuardado= calloc(G->nvertices,sizeof(u32));
    OrdenGuardado = G->orden;
    printf("Orden Guardado:[" );
    for(t=0;t<G->nvertices;t++){
      printf("%u, ",OrdenGuardado[t]);
    }
    printf("]\n" );
    u32 Menor = G->nvertices;
    OrdenNatural(G);
    u32 g = NotSoGreedy(G,1);
    if (g< Menor){
      OrdenGuardado = G->orden;
      Menor = g;
    }
    u32 p = Propio(G);
    assert(p==1);
    OrdenWelshPowell(G);
    g = NotSoGreedy(G,1);

    if (g< Menor){
    OrdenGuardado = G->orden;
    Menor = g;
    }
    p = Propio(G);
    assert(p==1);

    for (u32 i=0;i<100;i++){

        AleatorizarVertices(G,i);

        g = NotSoGreedy(G,i);
        //printf("%u\n",g);
        if (g< Menor){
          OrdenGuardado = G->orden;
          Menor = g;
        }
        if (!Propio(G)){
            printf("Mal Coloreo %u\n",i);
            break;
        }

    }
    G->orden = OrdenGuardado;

    printf("Reordenamiento de Bloques...\n");
    for (u32 i=0;i<100;i++){

        ReordenManteniendoBloqueColores(G,i);
        g = NotSoGreedy(G,i);
        //printf("%u\n",g);

        if (!Propio(G)){
            printf("Mal Coloreo %u\n",i);
            break;
        }

    }

    printf("Bipartito:%i\n",Bipartito(G));
    p = Propio(G);
    assert(p==1);

    DestruccionDelGrafo(G);
    printf("Destruyendo Grafo\n" );
};
