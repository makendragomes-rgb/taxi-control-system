#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_LINHA 256

static void remover_nova_linha(char *texto)
{
    size_t comprimento = strlen(texto);
    while (comprimento > 0 && (texto[comprimento - 1] == '\n' || texto[comprimento - 1] == '\r')) {
        texto[comprimento - 1] = '\0';
        comprimento--;
    }
}

static int ler_linha(char *destino, size_t tamanho)
{
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        return 0;
    }
    remover_nova_linha(destino);
    return 1;
}

int util_ler_inteiro(const char *prompt, int minimo, int maximo)
{
    char linha[TAM_LINHA];
    char *fim = NULL;
    long valor = 0;

    for (;;) {
        printf("%s", prompt);
        if (!ler_linha(linha, sizeof(linha)) || linha[0] == '\0') {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        valor = strtol(linha, &fim, 10);
        if (*fim != '\0' || valor < (long)minimo || valor > (long)maximo) {
            printf("Valor fora do intervalo permitido (%d a %d).\n", minimo, maximo);
            continue;
        }
        return (int)valor;
    }
}

double util_ler_double(const char *prompt, double minimo, double maximo)
{
    char linha[TAM_LINHA];
    char *fim = NULL;
    double valor = 0.0;

    for (;;) {
        printf("%s", prompt);
        if (!ler_linha(linha, sizeof(linha)) || linha[0] == '\0') {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        valor = strtod(linha, &fim);
        if (*fim != '\0' || valor < minimo || valor > maximo) {
            printf("Valor fora do intervalo permitido (%.2f a %.2f).\n", minimo, maximo);
            continue;
        }
        return valor;
    }
}

void util_ler_texto(const char *prompt, char *destino, size_t tamanho)
{
    char linha[TAM_LINHA];

    for (;;) {
        printf("%s", prompt);
        if (!ler_linha(linha, sizeof(linha))) {
            destino[0] = '\0';
            return;
        }
        if (linha[0] == '\0') {
            printf("O campo nao pode ficar vazio.\n");
            continue;
        }
        strncpy(destino, linha, tamanho - 1);
        destino[tamanho - 1] = '\0';
        return;
    }
}

void util_data_hora_actual(char *destino, size_t tamanho)
{
    time_t agora = time(NULL);
    struct tm *local = localtime(&agora);
    strftime(destino, tamanho, "%Y-%m-%d %H:%M", local);
}

void util_pausar(void)
{
    char linha[TAM_LINHA];
    printf("\nPrima Enter para continuar...");
    ler_linha(linha, sizeof(linha));
}

void util_limpar_ecra(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
