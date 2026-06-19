#include "corrida.h"
#include "viatura.h"
#include "motorista.h"
#include "tarifa.h"
#include "util.h"

#include <string.h>

const Corrida *corrida_por_id_const(const Sistema *sistema, int id)
{
    for (int i = 0; i < sistema->numCorridas; i++) {
        if (sistema->corridas[i].id == id) {
            return &sistema->corridas[i];
        }
    }
    return NULL;
}

Resultado corrida_registar(Sistema *sistema,
                           int viaturaId,
                           int motoristaId,
                           const char *origem,
                           const char *destino,
                           double distancia,
                           int duracaoMinutos,
                           int tempoEsperaMinutos,
                           TipoTarifa tipoTarifa,
                           int *novoId)
{
    if (sistema->numCorridas >= MAX_CORRIDAS) {
        return ERRO_LOTACAO;
    }
    if (origem[0] == '\0' || destino[0] == '\0' || distancia <= 0.0) {
        return ERRO_INVALIDO;
    }

    Viatura *viatura = viatura_por_id(sistema, viaturaId);
    if (viatura == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    Motorista *motorista = motorista_por_id(sistema, motoristaId);
    if (motorista == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (viatura->estado == ESTADO_MANUTENCAO) {
        return ERRO_INDISPONIVEL;
    }

    Corrida *corrida = &sistema->corridas[sistema->numCorridas];
    corrida->id = sistema->proximoIdCorrida;
    corrida->viaturaId = viaturaId;
    corrida->motoristaId = motoristaId;
    strncpy(corrida->origem, origem, TAM_LOCAL - 1);
    corrida->origem[TAM_LOCAL - 1] = '\0';
    strncpy(corrida->destino, destino, TAM_LOCAL - 1);
    corrida->destino[TAM_LOCAL - 1] = '\0';
    corrida->distancia = distancia;
    corrida->duracaoMinutos = duracaoMinutos;
    corrida->tempoEsperaMinutos = tempoEsperaMinutos;
    corrida->tipoTarifa = tipoTarifa;
    corrida->valor = tarifa_calcular(tipoTarifa, distancia, tempoEsperaMinutos);
    util_data_hora_actual(corrida->dataHora, TAM_DATAHORA);

    motorista->totalGanho += corrida->valor;

    sistema->numCorridas++;
    sistema->proximoIdCorrida++;

    if (novoId != NULL) {
        *novoId = corrida->id;
    }
    return OK;
}
