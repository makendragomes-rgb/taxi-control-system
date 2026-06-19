#include "tipos.h"
#include "persistencia.h"
#include "ui.h"

#include <stdio.h>

#define FICHEIRO_DADOS "data/taxi.dat"

int main(void)
{
    static Sistema sistema;

    if (persistencia_carregar(&sistema, FICHEIRO_DADOS) != OK) {
        sistema_inicializar(&sistema);
    }

    ui_executar(&sistema, FICHEIRO_DADOS);

    printf("\nDados guardados. Ate breve!\n");
    return 0;
}
