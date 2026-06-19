#include "tipos.h"
#include "persistencia.h"
#include "seed.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>

#define FICHEIRO_DADOS "data/taxi.dat"
#define FICHEIRO_DEMO "data/taxi-demo.dat"

int main(int argc, char **argv)
{
    static Sistema sistema;
    int modoDemo = (argc > 1 && strcmp(argv[1], "--demo") == 0);
    const char *ficheiro = modoDemo ? FICHEIRO_DEMO : FICHEIRO_DADOS;

    if (modoDemo) {
        seed_povoar(&sistema);
    } else if (persistencia_carregar(&sistema, ficheiro) != OK) {
        sistema_inicializar(&sistema);
    }

    ui_executar(&sistema, ficheiro);

    printf("\nDados guardados. Ate breve!\n");
    return 0;
}
