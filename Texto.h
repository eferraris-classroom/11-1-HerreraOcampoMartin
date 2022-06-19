#ifndef INC_11_1_HERRERAOCAMPOMARTIN_TEXTO_H
#define INC_11_1_HERRERAOCAMPOMARTIN_TEXTO_H

typedef struct palabra {
    char *palabra;
    int vecesAparecidas;
    struct palabra *siguiente;
} Palabra;

typedef struct texto{
    Palabra *primera;
    int tam;
} Texto;

Texto *crearTexto();
Palabra *crearPalabra(char *pal);
Texto *separarCadenaPorPalabras(char *cadena);
void agregarPalabra(Texto *texto, char *nueva);
void imprimirTexto(Texto *texto);
int compararPalabras(char *palabra1, char *palabra2);
int longitudCadena(const char *cadena);
int esSeparador(char caracter, char *separadores);

#endif
