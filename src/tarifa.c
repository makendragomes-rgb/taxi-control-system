#include "tarifa.h"

static const TabelaTarifa TABELAS[] = {
    { 3.25, 0.55, 0.18 },
    { 3.90, 0.68, 0.22 }
};

TabelaTarifa tarifa_tabela(TipoTarifa tipo)
{
    return TABELAS[tipo];
}

double tarifa_calcular(TipoTarifa tipo, double distancia, int tempoEsperaMinutos)
{
    TabelaTarifa tabela = TABELAS[tipo];
    double valor = tabela.bandeirada
                 + distancia * tabela.precoPorKm
                 + tempoEsperaMinutos * tabela.precoEsperaMinuto;
    return valor;
}

const char *tarifa_nome(TipoTarifa tipo)
{
    switch (tipo) {
        case TARIFA_DIURNA: return "Diurna";
        case TARIFA_NOTURNA: return "Noturna";
        default: return "Desconhecida";
    }
}
