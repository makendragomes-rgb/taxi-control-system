#ifndef TARIFA_H
#define TARIFA_H

#include "tipos.h"

typedef struct {
    double bandeirada;
    double precoPorKm;
    double precoEsperaMinuto;
} TabelaTarifa;

TabelaTarifa tarifa_tabela(TipoTarifa tipo);
double tarifa_calcular(TipoTarifa tipo, double distancia, int tempoEsperaMinutos);
const char *tarifa_nome(TipoTarifa tipo);

#endif
