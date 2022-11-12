#include <stdio.h>
#include <stdlib.h>
#include "ABB.h"

void construirArbol(ArbolBinario *pAB){
    *pAB=NULL;
}
Nodo *crearNuevoNodo(ArbolBinario arbolIzq,ElementoArbol elemento, ArbolBinario arbolDer){
    Nodo *pNuevoNodo;
    pNuevoNodo=(Nodo*)malloc(sizeof(Nodo));
    pNuevoNodo->hizq=arbolIzq;
    pNuevoNodo->elemento=elemento;
    pNuevoNodo->hder=arbolDer;
    return pNuevoNodo;
}

void plantar(ArbolBinario *pAB,ArbolBinario arbolIzq,ElementoArbol elemento,ArbolBinario arbolDer){
    Nodo *pNuevoNodo;
    pNuevoNodo=crearNuevoNodo(arbolIzq,elemento,arbolDer);
    *pAB=pNuevoNodo;
           
}
int esArbolVacio(ArbolBinario AB){
    return AB==NULL;
}

void recorrerEnPostOrden(ArbolBinario AB){
    ArbolBinario ABI,ABD;
    if(!esArbolVacio(AB)){
        ABI=AB->hizq;
        ABD=AB->hder;
        recorrerEnPostOrden(ABI);
        recorrerEnPostOrden(ABD);
        printf("%d ",AB->elemento);
    }
}
int contarNodos(ArbolBinario AB){
    ArbolBinario ABI,ABD;
    int nodosABI,nodosABD;
    if(esArbolVacio(AB)) return 0;
    else{
        ABI=AB->hizq;
        ABD=AB->hder;
        nodosABI=contarNodos(ABI);
        nodosABD=contarNodos(ABD);
        return nodosABI+nodosABD+1;
    }
}
int esHoja(ArbolBinario AB){
    if(esArbolVacio(AB)) return 0;
    else
        return AB->hizq==NULL && AB->hder==NULL;
}
int maximo(int x,int y){
    return (x>=y)?x:y;
}
int altura(ArbolBinario AB){
    int alturaABI,alturaABD;
    if(esArbolVacio(AB)) return -1;
    else{
        alturaABI=altura(AB->hizq);
        alturaABD=altura(AB->hder);
        return maximo(alturaABI,alturaABD)+1;
    }
}
int esEquilibrado(ArbolBinario AB){
    int alturaABI,alturaABD,difAltura;
    if(esArbolVacio(AB)){
        return 1;
    }else{
        alturaABI=altura(AB->hizq);
        alturaABD=altura(AB->hder);
        difAltura=abs(alturaABI-alturaABD);
        return difAltura<=1 && esEquilibrado(AB->hizq) && esEquilibrado(AB->hder);
    }
}

int buscar(ArbolBinarioBusqueda ABB, ElementoArbol valor){
    if(esArbolVacio(ABB)) return 0;
    else{
        if(ABB->elemento==valor) return -1;
        else
            if(valor<ABB->elemento)
                return buscar(ABB->hizq,valor);
            else
                return buscar(ABB->hder,valor);
    }
}
ElementoArbol menor(ArbolBinarioBusqueda ABB){
    Nodo *p;
    p=ABB;
    while(p->hizq!=NULL)
        p=p->hizq;
    return p->elemento;
}
void eliminar(ArbolBinarioBusqueda *pABB,ElementoArbol elemento){
    Nodo *p;
    ElementoArbol menorDerecha;
    if(!esArbolVacio(*pABB)){
        if((*pABB)->elemento==elemento){
            if((*pABB)->hder==NULL){
                p=*pABB;
                *pABB=(*pABB)->hizq;
                free(p);
            }else{
                if((*pABB)->hizq==NULL){
                    p=*pABB;
                    *pABB=(*pABB)->hder;
                    free(p);
                }else{
                    menorDerecha=menor((*pABB)->hder);
                    (*pABB)->elemento=menorDerecha;
                    eliminar(&((*pABB)->hder),menorDerecha);
                }
                
            }
        }else{
            if(elemento<(*pABB)->elemento)
                eliminar(&((*pABB)->hizq),elemento);
            else
                eliminar(&((*pABB)->hder),elemento);
        }
        
    }
}
void destruir(ArbolBinarioBusqueda *pABB){
    if(!esArbolVacio(*pABB)){
        destruir(&((*pABB)->hizq));
        destruir(&((*pABB)->hder));
        free(*pABB);
        *pABB=NULL;
    }
}