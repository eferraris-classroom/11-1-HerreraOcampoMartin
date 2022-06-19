#include "Texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Texto *crearTexto(){
    Texto *texto = (Texto*) malloc(sizeof (Texto));

    if(texto == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    texto->tam = 0;
    texto->primera = NULL;

    return texto;
}

Palabra *crearPalabra(char *pal){
    Palabra *palabra = (Palabra*) malloc(sizeof (Palabra));

    if(palabra == NULL){
        printf("No hay memoria libre.");
        exit(-1);
    }

    palabra->palabra = pal;
    palabra->vecesAparecidas = 1;
    palabra->siguiente = NULL;

    return palabra;
}

Texto *separarCadenaPorPalabras(char *cadena){
    char separadores[] = ".,; ";
    Texto *texto = crearTexto();

    int longCandena = longitudCadena(cadena);

    char *palabraActual;
    int inicioPalabraActual = 0, longitudPalabraActual = 0;
    for(int i = 0; i <= longCandena; i++){
        // Es menor o igual porque en este caso me sirve ver el \0 (más abajo se explica)
        // Si fuera i < longCadena, no vería el \0 por como esta hecha la función longitudCadena()

        // Verifico si terminó la palabra mirando si el carácter actual es un separador de palabras
        // Algo como una coma, un punto o un espacio indican que es otra palabra, para eso me sirve
        // el carácter ' ' (similar a strtok)

        // Si está en el último carácter, entonces sale sin guardar la última palabra
        // así que además tengo que preguntar si este es el último carácter de la cadena
        if(esSeparador(cadena[i], separadores) == 0 && cadena[i] != '\0'){
            longitudPalabraActual++;
            continue;
        }

        // Si llega aca, entonces la palabra ya terminó, así que la voy a guardar;
        palabraActual = (char *) malloc(sizeof (char) * (longitudPalabraActual+1)); // i+1 para el '\0'

        if(palabraActual == NULL){
            printf("No hay memoria libre.");
            exit(-1);
        }

        int j;
        for (j = 0; j < longitudPalabraActual; j++){
            palabraActual[j] = cadena[inicioPalabraActual + j];
        }
        palabraActual[j] = '\0';
        agregarPalabra(texto, palabraActual);

        inicioPalabraActual = i+1;
        longitudPalabraActual = 0;
    }

    return texto;
}

void agregarPalabra(Texto *texto, char *nueva){
    Palabra *aux = texto->primera;

    if(aux == NULL){
        texto->primera = crearPalabra(nueva);
        return;
    }

    // Veo si existe la palabra y le sumo vecesAparecidas;
    for(; aux != NULL; aux = aux->siguiente){
        if(compararPalabras(aux->palabra, nueva) == 1){
            aux->vecesAparecidas++;
            return;
        }
    }

    // Si llega hasta aca, entonces la palabra no esta en el registro, así que la creo.
    aux = crearPalabra(nueva);
    aux->siguiente = texto->primera;
    texto->primera = aux;
    texto->tam++;
}

int compararPalabras(char *palabra1, char *palabra2){
    // 1 si son iguales 0 si no
    int long1 = longitudCadena(palabra1);

    if(long1 != longitudCadena(palabra2)){
        return 0; // Si tienen distinta longitud, entonces son distintas
    }

    for(int i = 0; i < long1; i++){
        if(palabra1[i] != palabra2[i]){
            return 0; // Si encuentro un carácter distinto, devolver 0
        }
    }

    return 1;
}

int esSeparador(char caracter, char *separadores){
    // 1 si el caracter es un separador de palabras, 0 si no
    int longitud = longitudCadena(separadores);

    for (int i = 0; i < longitud; i++) {
        if(caracter == separadores[i]){
            return 1;
        }
    }
    return 0;
}

int longitudCadena(const char *cadena){
    int i;
    for (i = 0; cadena[i] != '\0'; i++) {}

    return i;
}

void imprimirTexto(Texto *texto){
    Palabra *aux = texto->primera;

    if(aux == NULL){
        printf("El texto está vacío.\n");
        return;
    }

    for (; aux != NULL; aux = aux->siguiente){
        printf("La palabra '%s' aparece %d veces.\n", aux->palabra, aux->vecesAparecidas);
    }
}
