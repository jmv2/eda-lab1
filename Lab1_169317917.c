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

Nodo* agregar(Nodo* lst, int posicionFila, char tipo, int duracion);
void imprimirLista(Nodo* lst);
Nodo* filtrar(Nodo* lst_org, Nodo* lst_dst, char criterio);
Nodo* cargarContenidoEnLista(Nodo* lst, char* nombreArchivo);
Nodo* filtroTiempo(Nodo* lst);
int largoLista(Nodo* lst);
Nodo* diferencia(Nodo* lst_org, Nodo* lst_dst);

int* obtenerFila(Nodo* lst);
void escribirResultados(char* nombreArchivo, Nodo* lst_org, Nodo* lst_dst);

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
    listaResultado = filtroTiempo(listaResultado);
    imprimirLista(listaResultado);

    escribirResultados("salida.out", listaEntrada, listaResultado);

    //imprimirLista(listaEntrada);
    //printf("Largo lista: %d\n", largo(listaEntrada));

    return 0;
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
/**
 * @brief Se entrega la lista que debe ser filtrada, bajo un criterio (a, v, n).
 * Si algun nodo coincide con el criterio, el contenido de ese nodo es copiado en una nueva lista.
 * 
 * @param lst_org lista original 
 * @param lst_dst lista destino o lista nueva
 * @param criterio critero para aplicar filtro
 * @return Nodo* nueva lista creada a partir del criterio de selección
 */
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
/**
 * @brief Carga el contenido del archivo de entrada en una lista.
 * 
 * @param lst 
 * @param nombreArchivo 
 * @return Nodo* 
 */
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

    fclose(archivo);
    return lst;
}
/**
 * @brief Dada un lista, selecciona todos los turnos que pueden ser atendidos en la ventana de tiempo
 * entre las 9:00 y las 14:00 o sea 300 minutos. 
 * 
 * @param lst 
 * @return Nodo* 
 */
Nodo* filtroTiempo(Nodo* lst){
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
int largoLista(Nodo* lst){
   int i = 0;
    Nodo* indice = lst;
    
    while(indice != NULL){
        indice = indice -> siguiente;
        i++;
    }

    return i; 
}
int* obtenerFila(Nodo* lst){
    int largo = largoLista(lst), indice = 0;
    int* fila = (int*) malloc (largo * sizeof(int));
    Nodo* aux = lst;

    while (aux != aux)
    {
        fila[indice] = aux->posicionFila;
        aux = aux->siguiente;
        indice++;
    }

    return fila;
}

Nodo* diferencia(Nodo* lst_org, Nodo* lst_dst)
{
    Nodo* aux_org = lst_org;
    Nodo* aux_dst = lst_dst;
    Nodo* lst_dif = (Nodo*) malloc(sizeof(Nodo));
    lst_dif = NULL;
    int encontrado = 0;

    while (aux_org != NULL)
    {
        while (aux_dst != NULL)
        {
            if(aux_org->posicionFila == aux_dst->posicionFila)
                encontrado++;

            aux_dst = aux_dst->siguiente;
        }
   
        if(encontrado == 0)
            lst_dif = agregar(lst_dif, aux_org->posicionFila, aux_org->tipo, aux_org->duracion);
        
        aux_dst = lst_dst;
        aux_org = aux_org->siguiente;
        encontrado = 0;
    }
    
    return lst_dif;
}

void escribirResultados(char* nombreArchivo, Nodo* lst_org, Nodo* lst_dst)
{
    FILE* archivo = fopen(nombreArchivo, "a");
    int indice;
    Nodo* auxiliar = lst_org;
    Nodo* lst_dif = (Nodo*) malloc(sizeof(Nodo));
   
    char c_numero[3];
    
    fputs("Fila: \n", archivo);
    while (auxiliar != NULL)
    {
        sprintf(c_numero, "%d\n", auxiliar->posicionFila);
        fputs(c_numero, archivo);

        auxiliar = auxiliar->siguiente;
    }

    fputs("\nAtendidos: \n", archivo);
    
    auxiliar = lst_dst;

    while (auxiliar != NULL)
    {
        sprintf(c_numero, "%d\n", auxiliar->posicionFila);
        fputs(c_numero, archivo);

        auxiliar = auxiliar->siguiente;
    }
    
    fputs("\nNo atendidos: \n", archivo);
    lst_dif = diferencia(lst_org, lst_dst);
    
    auxiliar = lst_dif;
    
    while (auxiliar != NULL)
    {
        sprintf(c_numero, "%d\n", auxiliar->posicionFila);
        fputs(c_numero, archivo);

        auxiliar = auxiliar->siguiente;
    }
    
    fclose(archivo);

}