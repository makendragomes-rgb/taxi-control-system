#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

int util_ler_inteiro(const char *prompt, int minimo, int maximo);
double util_ler_double(const char *prompt, double minimo, double maximo);
void util_ler_texto(const char *prompt, char *destino, size_t tamanho);
void util_data_hora_actual(char *destino, size_t tamanho);
void util_pausar(void);
void util_limpar_ecra(void);

#endif
