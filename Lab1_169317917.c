#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
    int posicionFila; 
    int duracion;
    char tipo;
    struct nodo *siguiente;
}Nodo;


Nodo* crearNodo(int posicionFila, char tipo, int duracion){
    
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    nuevo->posicionFila = posicionFila;
    nuevo->tipo = tipo;
    nuevo->duracion = duracion;
    nuevo->siguiente = NULL;
    return nuevo;
}

Nodo* agregar(Nodo* lst, int posicionFila, char tipo, int duracion){
    
    if(lst == NULL){
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->posicionFila = posicionFila;
        nuevo->tipo = tipo;
        nuevo->duracion = duracion;
        nuevo->siguiente = NULL;
        lst = nuevo;
        return lst;
    }
    else{
        Nodo* auxiliar = lst;
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        nuevo->posicionFila = posicionFila;
        nuevo->tipo = tipo;
        nuevo->duracion = duracion;

        while(auxiliar->siguiente != NULL){ 
            auxiliar = auxiliar->siguiente;
        }
        auxiliar->siguiente = nuevo;
        return lst;
    }
}

Nodo* insertar(Nodo* lista, int posicion, int posicionFila, char tipo, int duracion){
    if(posicion < 0){
        return lista;
    }

    if(posicion == 0){
        Nodo* nuevo = crearNodo(posicionFila, tipo, duracion);
        nuevo->siguiente = lista;
        return nuevo;
    }

    int i = 0;
    Nodo* indice = lista;

    while(indice != NULL && i < posicion - 1){
        indice = indice->siguiente;
        i++;
    }

    if(indice != NULL){
        Nodo* nuevo = crearNodo(posicionFila, tipo, duracion);
        nuevo->siguiente = indice->siguiente; // 
        indice->siguiente = nuevo;  // dirección de nuevo en indice->siguente
    }
    return lista;
}

void imprimirLista(Nodo* lst){
    Nodo* auxiliar;
    auxiliar = lst;
    while (auxiliar != NULL){
        printf("%d\t", auxiliar->posicionFila);
        printf("%c\t", auxiliar->tipo);
        printf("%d\n", auxiliar->duracion);

        auxiliar = auxiliar->siguiente;
    }
}

int largo(Nodo* lista){
    int i = 0;
    Nodo* indice = lista;
    
    while(indice != NULL){
        indice = indice -> siguiente;
        i++;
    }

    return i;
}

Nodo* filtrar_vip(Nodo* lst_org, Nodo* lst_dst){
    Nodo* auxiliar;
    auxiliar = lst_org;

    while (auxiliar != NULL){
        if (auxiliar->tipo == 'v'){
            lst_dst = insertar(lst_dst, largo(lst_dst),auxiliar->posicionFila, 'v', auxiliar->duracion);
        }
        auxiliar = auxiliar->siguiente;
    }

    return lst_dst;
}

int main(int argc, char const *argv[])
{
    Nodo* listaEntrada = (Nodo*) malloc(sizeof(Nodo));
    Nodo* listaResultado = (Nodo*) malloc(sizeof(Nodo));
    FILE* a_entrada =  fopen("entrada.in", "r");
    
    char lineaArchivo[15];
    char *posicionFila; 
    char *tipoPublico;
    char *duracionAtencion;
    char *token; 
    char *delimitador = " ";
    int duracion;
    int n_PosicionFila;
    int posicionLista = 0;
    int acumulador_tiempo;
    
    listaEntrada = NULL;
    listaResultado = NULL;
    
    rewind(a_entrada);

    while(!feof(a_entrada)){
    
        fgets(lineaArchivo, 15, a_entrada);
        token = strtok(lineaArchivo, delimitador);
        posicionFila = (char*) malloc(strlen(token)*sizeof(char));
        strcpy(posicionFila, token);
        n_PosicionFila = atoi(posicionFila);
        //Tipo de publico
        token = strtok(NULL, delimitador);
        tipoPublico = (char*) malloc(strlen(token)*sizeof(char));
        strcpy(tipoPublico, token);
        //Duración de la atención
        token = strtok(NULL, delimitador);
        duracionAtencion = (char*) malloc(strlen(token)*sizeof(char));  
        strcpy(duracionAtencion, token);
        duracion = atoi(duracionAtencion);
        listaEntrada = agregar(listaEntrada, n_PosicionFila, tipoPublico[0], duracion);
        //listaEntrada = insertar(listaEntrada, posicionLista, n_PosicionFila, tipoPublico[0], duracion);
        posicionLista++; 
    }
    fclose(a_entrada);

    //filtrar_vip(listaEntrada, listaResultado);
    //imprimirLista(listaResultado);

    //printf("Largo lista: %d\n", largo(listaEntrada));


    imprimirLista(listaEntrada);

    return 0;
}
