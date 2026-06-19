#ifndef RELATORIO_H
#define RELATORIO_H

#include "tipos.h"

void relatorio_frota(const Sistema *sistema);
void relatorio_motoristas(const Sistema *sistema);
void relatorio_corridas(const Sistema *sistema);
void relatorio_receita_por_motorista(const Sistema *sistema);
void relatorio_resumo_geral(const Sistema *sistema);

#endif
