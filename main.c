#include "Texto.h"

int main() {
    char *cadena = "Hola que tal me llamo Martin me tal llamo me Martin Hola";

    Texto *texto = separarCadenaPorPalabras(cadena);
    imprimirTexto(texto);

    return 0;
}
