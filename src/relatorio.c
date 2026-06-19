#include "relatorio.h"
#include "viatura.h"
#include "motorista.h"
#include "tarifa.h"

#include <stdio.h>

static void linha_separadora(void)
{
    printf("------------------------------------------------------------\n");
}

void relatorio_frota(const Sistema *sistema)
{
    printf("\n=== Frota de Viaturas ===\n");
    if (sistema->numViaturas == 0) {
        printf("Nao existem viaturas registadas.\n");
        return;
    }
    linha_separadora();
    printf("%-4s %-12s %-20s %-12s %-10s\n", "ID", "Matricula", "Modelo", "Estado", "Motorista");
    linha_separadora();
    for (int i = 0; i < sistema->numViaturas; i++) {
        const Viatura *viatura = &sistema->viaturas[i];
        const Motorista *motorista = motorista_por_id_const(sistema, viatura->motoristaId);
        printf("%-4d %-12s %-20s %-12s %-10s\n",
               viatura->id,
               viatura->matricula,
               viatura->modelo,
               viatura_estado_texto(viatura->estado),
               motorista != NULL ? motorista->nome : "(sem)");
    }
    linha_separadora();
}

void relatorio_motoristas(const Sistema *sistema)
{
    printf("\n=== Motoristas ===\n");
    if (sistema->numMotoristas == 0) {
        printf("Nao existem motoristas registados.\n");
        return;
    }
    linha_separadora();
    printf("%-4s %-24s %-14s %-10s %-12s\n", "ID", "Nome", "Carta", "Turno", "Ganho");
    linha_separadora();
    for (int i = 0; i < sistema->numMotoristas; i++) {
        const Motorista *motorista = &sistema->motoristas[i];
        printf("%-4d %-24s %-14s %-10s %10.2f\n",
               motorista->id,
               motorista->nome,
               motorista->carta,
               motorista_turno_texto(motorista->turno),
               motorista->totalGanho);
    }
    linha_separadora();
}

void relatorio_corridas(const Sistema *sistema)
{
    printf("\n=== Corridas Registadas ===\n");
    if (sistema->numCorridas == 0) {
        printf("Nao existem corridas registadas.\n");
        return;
    }
    linha_separadora();
    printf("%-4s %-16s %-16s %-8s %-8s %-9s %-10s\n",
           "ID", "Origem", "Destino", "Km", "Tarifa", "Valor", "Data");
    linha_separadora();
    for (int i = 0; i < sistema->numCorridas; i++) {
        const Corrida *corrida = &sistema->corridas[i];
        printf("%-4d %-16s %-16s %-8.1f %-8s %9.2f %-10s\n",
               corrida->id,
               corrida->origem,
               corrida->destino,
               corrida->distancia,
               tarifa_nome(corrida->tipoTarifa),
               corrida->valor,
               corrida->dataHora);
    }
    linha_separadora();
}

void relatorio_receita_por_motorista(const Sistema *sistema)
{
    printf("\n=== Receita por Motorista ===\n");
    if (sistema->numMotoristas == 0) {
        printf("Nao existem motoristas registados.\n");
        return;
    }
    linha_separadora();
    printf("%-4s %-24s %-8s %-12s\n", "ID", "Nome", "Corridas", "Receita");
    linha_separadora();
    for (int i = 0; i < sistema->numMotoristas; i++) {
        const Motorista *motorista = &sistema->motoristas[i];
        int totalCorridas = 0;
        for (int j = 0; j < sistema->numCorridas; j++) {
            if (sistema->corridas[j].motoristaId == motorista->id) {
                totalCorridas++;
            }
        }
        printf("%-4d %-24s %-8d %10.2f\n",
               motorista->id,
               motorista->nome,
               totalCorridas,
               motorista->totalGanho);
    }
    linha_separadora();
}

void relatorio_resumo_geral(const Sistema *sistema)
{
    int disponiveis = 0;
    int ocupadas = 0;
    int manutencao = 0;
    double receitaTotal = 0.0;
    double distanciaTotal = 0.0;

    for (int i = 0; i < sistema->numViaturas; i++) {
        switch (sistema->viaturas[i].estado) {
            case ESTADO_DISPONIVEL: disponiveis++; break;
            case ESTADO_OCUPADA: ocupadas++; break;
            case ESTADO_MANUTENCAO: manutencao++; break;
        }
    }
    for (int i = 0; i < sistema->numCorridas; i++) {
        receitaTotal += sistema->corridas[i].valor;
        distanciaTotal += sistema->corridas[i].distancia;
    }

    printf("\n=== Resumo Geral ===\n");
    linha_separadora();
    printf("Viaturas registadas .......: %d\n", sistema->numViaturas);
    printf("  Disponiveis .............: %d\n", disponiveis);
    printf("  Ocupadas ................: %d\n", ocupadas);
    printf("  Em manutencao ...........: %d\n", manutencao);
    printf("Motoristas registados .....: %d\n", sistema->numMotoristas);
    printf("Corridas registadas .......: %d\n", sistema->numCorridas);
    printf("Distancia total (km) ......: %.1f\n", distanciaTotal);
    printf("Receita total .............: %.2f\n", receitaTotal);
    linha_separadora();
}
