#ifndef CORRIDA_H
#define CORRIDA_H

#include "tipos.h"

Resultado corrida_registar(Sistema *sistema,
                           int viaturaId,
                           int motoristaId,
                           const char *origem,
                           const char *destino,
                           double distancia,
                           int duracaoMinutos,
                           int tempoEsperaMinutos,
                           TipoTarifa tipoTarifa,
                           int *novoId);

const Corrida *corrida_por_id_const(const Sistema *sistema, int id);

#endif
