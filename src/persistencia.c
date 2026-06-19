#include "persistencia.h"

#include <stdio.h>

Resultado persistencia_guardar(const Sistema *sistema, const char *ficheiro)
{
    FILE *saida = fopen(ficheiro, "wb");
    if (saida == NULL) {
        return ERRO_FICHEIRO;
    }
    size_t escritos = fwrite(sistema, sizeof(Sistema), 1, saida);
    fclose(saida);
    return escritos == 1 ? OK : ERRO_FICHEIRO;
}

Resultado persistencia_carregar(Sistema *sistema, const char *ficheiro)
{
    FILE *entrada = fopen(ficheiro, "rb");
    if (entrada == NULL) {
        return ERRO_FICHEIRO;
    }
    size_t lidos = fread(sistema, sizeof(Sistema), 1, entrada);
    fclose(entrada);
    return lidos == 1 ? OK : ERRO_FICHEIRO;
}
