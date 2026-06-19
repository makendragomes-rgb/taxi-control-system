#ifndef VIATURA_H
#define VIATURA_H

#include "tipos.h"

Resultado viatura_adicionar(Sistema *sistema, const char *matricula, const char *modelo, int *novoId);
Resultado viatura_remover(Sistema *sistema, int id);
Resultado viatura_definir_estado(Sistema *sistema, int id, EstadoViatura estado);
Resultado viatura_atribuir_motorista(Sistema *sistema, int viaturaId, int motoristaId);

Viatura *viatura_por_id(Sistema *sistema, int id);
const Viatura *viatura_por_id_const(const Sistema *sistema, int id);
Viatura *viatura_por_matricula(Sistema *sistema, const char *matricula);

const char *viatura_estado_texto(EstadoViatura estado);

#endif
