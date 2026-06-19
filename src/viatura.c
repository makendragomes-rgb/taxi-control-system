#include "viatura.h"
#include "motorista.h"

#include <string.h>

static int indice_por_id(const Sistema *sistema, int id)
{
    for (int i = 0; i < sistema->numViaturas; i++) {
        if (sistema->viaturas[i].id == id) {
            return i;
        }
    }
    return -1;
}

Viatura *viatura_por_id(Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    return indice >= 0 ? &sistema->viaturas[indice] : NULL;
}

const Viatura *viatura_por_id_const(const Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    return indice >= 0 ? &sistema->viaturas[indice] : NULL;
}

Viatura *viatura_por_matricula(Sistema *sistema, const char *matricula)
{
    for (int i = 0; i < sistema->numViaturas; i++) {
        if (strcmp(sistema->viaturas[i].matricula, matricula) == 0) {
            return &sistema->viaturas[i];
        }
    }
    return NULL;
}

Resultado viatura_adicionar(Sistema *sistema, const char *matricula, const char *modelo, int *novoId)
{
    if (sistema->numViaturas >= MAX_VIATURAS) {
        return ERRO_LOTACAO;
    }
    if (matricula[0] == '\0' || modelo[0] == '\0') {
        return ERRO_INVALIDO;
    }
    if (viatura_por_matricula(sistema, matricula) != NULL) {
        return ERRO_DUPLICADO;
    }

    Viatura *viatura = &sistema->viaturas[sistema->numViaturas];
    viatura->id = sistema->proximoIdViatura;
    strncpy(viatura->matricula, matricula, TAM_MATRICULA - 1);
    viatura->matricula[TAM_MATRICULA - 1] = '\0';
    strncpy(viatura->modelo, modelo, TAM_MODELO - 1);
    viatura->modelo[TAM_MODELO - 1] = '\0';
    viatura->estado = ESTADO_DISPONIVEL;
    viatura->motoristaId = 0;

    sistema->numViaturas++;
    sistema->proximoIdViatura++;

    if (novoId != NULL) {
        *novoId = viatura->id;
    }
    return OK;
}

Resultado viatura_remover(Sistema *sistema, int id)
{
    int indice = indice_por_id(sistema, id);
    if (indice < 0) {
        return ERRO_NAO_ENCONTRADO;
    }
    for (int i = indice; i < sistema->numViaturas - 1; i++) {
        sistema->viaturas[i] = sistema->viaturas[i + 1];
    }
    sistema->numViaturas--;
    return OK;
}

Resultado viatura_definir_estado(Sistema *sistema, int id, EstadoViatura estado)
{
    Viatura *viatura = viatura_por_id(sistema, id);
    if (viatura == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    viatura->estado = estado;
    return OK;
}

Resultado viatura_atribuir_motorista(Sistema *sistema, int viaturaId, int motoristaId)
{
    Viatura *viatura = viatura_por_id(sistema, viaturaId);
    if (viatura == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    if (motorista_por_id(sistema, motoristaId) == NULL) {
        return ERRO_NAO_ENCONTRADO;
    }
    viatura->motoristaId = motoristaId;
    return OK;
}

const char *viatura_estado_texto(EstadoViatura estado)
{
    switch (estado) {
        case ESTADO_DISPONIVEL: return "Disponivel";
        case ESTADO_OCUPADA: return "Ocupada";
        case ESTADO_MANUTENCAO: return "Manutencao";
        default: return "Desconhecido";
    }
}
