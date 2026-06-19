#ifndef MOTORISTA_H
#define MOTORISTA_H

#include "tipos.h"

Resultado motorista_adicionar(Sistema *sistema, const char *nome, const char *carta, Turno turno, int *novoId);
Resultado motorista_remover(Sistema *sistema, int id);

Motorista *motorista_por_id(Sistema *sistema, int id);
const Motorista *motorista_por_id_const(const Sistema *sistema, int id);

const char *motorista_turno_texto(Turno turno);

#endif
