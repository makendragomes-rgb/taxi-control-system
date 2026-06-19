#include "motorista.h"

#include <string.h>

static int indice_por_id(const Sistema *sistema, int id)
{
    for (int i = 0; i < sistema->numMotoristas; i++) {
        if (sistema->motoristas[i].id == id) {
            return i;
        }
    }
    return -1;
}

Motorista *motorista_por_id(Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    return indice >= 0 ? &sistema->motoristas[indice] : NULL;
}

const Motorista *motorista_por_id_const(const Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    return indice >= 0 ? &sistema->motoristas[indice] : NULL;
}

Resultado motorista_adicionar(Sistema *sistema, const char *nome, const char *carta, Turno turno, int *novoId)
{
    if (sistema->numMotoristas >= MAX_MOTORISTAS) {
        return ERRO_LOTACAO;
    }
    if (nome[0] == '\0' || carta[0] == '\0') {
        return ERRO_INVALIDO;
    }

    Motorista *motorista = &sistema->motoristas[sistema->numMotoristas];
    motorista->id = sistema->proximoIdMotorista;
    strncpy(motorista->nome, nome, TAM_NOME - 1);
    motorista->nome[TAM_NOME - 1] = '\0';
    strncpy(motorista->carta, carta, TAM_CARTA - 1);
    motorista->carta[TAM_CARTA - 1] = '\0';
    motorista->turno = turno;
    motorista->totalGanho = 0.0;

    sistema->numMotoristas++;
    sistema->proximoIdMotorista++;

    if (novoId != NULL) {
        *novoId = motorista->id;
    }
    return OK;
}

Resultado motorista_remover(Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    if (indice < 0) {
        return ERRO_NAO_ENCONTRADO;
    }
    for (int i = 0; i < sistema->numViaturas; i++) {
        if (sistema->viaturas[i].motoristaId == id) {
            sistema->viaturas[i].motoristaId = 0;
        }
    }
    for (int i = indice; i < sistema->numMotoristas - 1; i++) {
        sistema->motoristas[i] = sistema->motoristas[i + 1];
    }
    sistema->numMotoristas--;
    return OK;
}

const char *motorista_turno_texto(Turno turno)
{
    switch (turno) {
        case TURNO_DIURNO: return "Diurno";
        case TURNO_NOTURNO: return "Noturno";
        default: return "Desconhecido";
    }
}
