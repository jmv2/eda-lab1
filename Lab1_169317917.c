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

Nodo* filtrar(Nodo* lst_org, Nodo* lst_dst, char criterio){
    Nodo* auxiliar;
    auxiliar = lst_org;

    if (criterio == 'v')
    {
        while (auxiliar != NULL) {
            if (auxiliar->tipo == criterio){
                lst_dst = agregar(lst_dst, auxiliar->posicionFila, auxiliar->tipo, auxiliar->duracion);
            }
            auxiliar = auxiliar->siguiente;
        }
    }else if (criterio == 'a')
    {
        while (auxiliar != NULL) 
        {
            if (auxiliar->tipo == criterio)
            {
                lst_dst = agregar(lst_dst, auxiliar->posicionFila, auxiliar->tipo, auxiliar->duracion);
            }
        auxiliar = auxiliar->siguiente;
        }
    }else if (criterio == 'n')
    {
        while (auxiliar != NULL) 
        {
            if (auxiliar->tipo == criterio)
            {
                lst_dst = agregar(lst_dst, auxiliar->posicionFila, auxiliar->tipo, auxiliar->duracion);
            }
        auxiliar = auxiliar->siguiente;
        }
    }
    return lst_dst;
}

Nodo* cargarContenidoEnLista(Nodo* lst, char* nombreArchivo){

    FILE* archivo = fopen(nombreArchivo, "r");
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

    while(!feof(archivo)){
    
        fgets(lineaArchivo, 15, archivo);
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
        lst = agregar(lst, n_PosicionFila, tipoPublico[0], duracion);
        posicionLista++; 
    }
    return lst;
}

Nodo* calculoTiempo(Nodo* lst){
    Nodo* auxiliar;
    auxiliar = lst;
    int tiempoTotal = 0;
    lst = NULL;

    while ((auxiliar != NULL) && (tiempoTotal <= 300)){
        tiempoTotal = tiempoTotal + auxiliar->duracion;
        lst = agregar(lst, auxiliar->posicionFila, auxiliar->tipo, auxiliar->duracion);
        auxiliar = auxiliar->siguiente;
    }
    return lst;
}

int main(int argc, char const *argv[])
{
    Nodo* listaEntrada = (Nodo*) malloc(sizeof(Nodo));
    Nodo* listaResultado = (Nodo*) malloc(sizeof(Nodo));
    listaEntrada = NULL;
    listaResultado = NULL;

    listaEntrada = cargarContenidoEnLista(listaEntrada, "entrada.in");
    listaResultado = filtrar(listaEntrada, listaResultado, 'a');
    listaResultado = filtrar(listaEntrada, listaResultado, 'v');
    listaResultado = filtrar(listaEntrada, listaResultado, 'n');
    listaResultado = calculoTiempo(listaResultado);
    imprimirLista(listaResultado);

    //imprimirLista(listaEntrada);
    //printf("Largo lista: %d\n", largo(listaEntrada));

    return 0;
}
