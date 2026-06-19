#include "ui.h"
#include "viatura.h"
#include "motorista.h"
#include "corrida.h"
#include "tarifa.h"
#include "relatorio.h"
#include "persistencia.h"
#include "util.h"

#include <stdio.h>

static const char *resultado_texto(Resultado resultado)
{
    switch (resultado) {
        case OK: return "Operacao concluida com sucesso.";
        case ERRO_LOTACAO: return "Limite de registos atingido.";
        case ERRO_NAO_ENCONTRADO: return "Registo nao encontrado.";
        case ERRO_DUPLICADO: return "Ja existe um registo com esses dados.";
        case ERRO_INVALIDO: return "Dados invalidos.";
        case ERRO_INDISPONIVEL: return "Viatura indisponivel para esta operacao.";
        case ERRO_FICHEIRO: return "Erro ao aceder ao ficheiro de dados.";
        default: return "Erro desconhecido.";
    }
}

static void mostrar_resultado(Resultado resultado)
{
    printf("\n%s\n", resultado_texto(resultado));
}

static void accao_adicionar_viatura(Sistema *sistema)
{
    char matricula[TAM_MATRICULA];
    char modelo[TAM_MODELO];
    int novoId = 0;

    util_ler_texto("Matricula: ", matricula, TAM_MATRICULA);
    util_ler_texto("Modelo: ", modelo, TAM_MODELO);

    Resultado resultado = viatura_adicionar(sistema, matricula, modelo, &novoId);
    if (resultado == OK) {
        printf("\nViatura registada com o ID %d.\n", novoId);
    } else {
        mostrar_resultado(resultado);
    }
}

static void accao_alterar_estado_viatura(Sistema *sistema)
{
    int id = util_ler_inteiro("ID da viatura: ", 1, 1000000);
    printf("Estados: 0=Disponivel  1=Ocupada  2=Manutencao\n");
    int estado = util_ler_inteiro("Novo estado: ", 0, 2);
    mostrar_resultado(viatura_definir_estado(sistema, id, (EstadoViatura)estado));
}

static void accao_atribuir_motorista(Sistema *sistema)
{
    int viaturaId = util_ler_inteiro("ID da viatura: ", 1, 1000000);
    int motoristaId = util_ler_inteiro("ID do motorista: ", 1, 1000000);
    mostrar_resultado(viatura_atribuir_motorista(sistema, viaturaId, motoristaId));
}

static void accao_remover_viatura(Sistema *sistema)
{
    int id = util_ler_inteiro("ID da viatura a remover: ", 1, 1000000);
    mostrar_resultado(viatura_remover(sistema, id));
}

static void menu_viaturas(Sistema *sistema)
{
    for (;;) {
        util_limpar_ecra();
        printf("=== Gestao de Viaturas ===\n");
        printf("1. Registar viatura\n");
        printf("2. Listar frota\n");
        printf("3. Alterar estado\n");
        printf("4. Atribuir motorista\n");
        printf("5. Remover viatura\n");
        printf("0. Voltar\n");

        int opcao = util_ler_inteiro("Opcao: ", 0, 5);
        switch (opcao) {
            case 1: accao_adicionar_viatura(sistema); break;
            case 2: relatorio_frota(sistema); break;
            case 3: accao_alterar_estado_viatura(sistema); break;
            case 4: accao_atribuir_motorista(sistema); break;
            case 5: accao_remover_viatura(sistema); break;
            case 0: return;
            default: break;
        }
        util_pausar();
    }
}

static void accao_adicionar_motorista(Sistema *sistema)
{
    char nome[TAM_NOME];
    char carta[TAM_CARTA];
    int novoId = 0;

    util_ler_texto("Nome: ", nome, TAM_NOME);
    util_ler_texto("Numero da carta: ", carta, TAM_CARTA);
    printf("Turnos: 0=Diurno  1=Noturno\n");
    int turno = util_ler_inteiro("Turno: ", 0, 1);

    Resultado resultado = motorista_adicionar(sistema, nome, carta, (Turno)turno, &novoId);
    if (resultado == OK) {
        printf("\nMotorista registado com o ID %d.\n", novoId);
    } else {
        mostrar_resultado(resultado);
    }
}

static void accao_remover_motorista(Sistema *sistema)
{
    int id = util_ler_inteiro("ID do motorista a remover: ", 1, 1000000);
    mostrar_resultado(motorista_remover(sistema, id));
}

static void menu_motoristas(Sistema *sistema)
{
    for (;;) {
        util_limpar_ecra();
        printf("=== Gestao de Motoristas ===\n");
        printf("1. Registar motorista\n");
        printf("2. Listar motoristas\n");
        printf("3. Remover motorista\n");
        printf("0. Voltar\n");

        int opcao = util_ler_inteiro("Opcao: ", 0, 3);
        switch (opcao) {
            case 1: accao_adicionar_motorista(sistema); break;
            case 2: relatorio_motoristas(sistema); break;
            case 3: accao_remover_motorista(sistema); break;
            case 0: return;
            default: break;
        }
        util_pausar();
    }
}

static void accao_registar_corrida(Sistema *sistema)
{
    char origem[TAM_LOCAL];
    char destino[TAM_LOCAL];
    int novoId = 0;

    int viaturaId = util_ler_inteiro("ID da viatura: ", 1, 1000000);
    int motoristaId = util_ler_inteiro("ID do motorista: ", 1, 1000000);
    util_ler_texto("Origem: ", origem, TAM_LOCAL);
    util_ler_texto("Destino: ", destino, TAM_LOCAL);
    double distancia = util_ler_double("Distancia (km): ", 0.1, 100000.0);
    int duracao = util_ler_inteiro("Duracao (minutos): ", 0, 100000);
    int espera = util_ler_inteiro("Tempo de espera (minutos): ", 0, 100000);
    printf("Tarifa: 0=Diurna  1=Noturna\n");
    int tarifa = util_ler_inteiro("Tipo de tarifa: ", 0, 1);

    Resultado resultado = corrida_registar(sistema, viaturaId, motoristaId, origem, destino,
                                            distancia, duracao, espera, (TipoTarifa)tarifa, &novoId);
    if (resultado == OK) {
        const Corrida *corrida = corrida_por_id_const(sistema, novoId);
        printf("\nCorrida registada com o ID %d.\n", novoId);
        printf("Valor calculado: %.2f\n", corrida->valor);
    } else {
        mostrar_resultado(resultado);
    }
}

static void menu_corridas(Sistema *sistema)
{
    for (;;) {
        util_limpar_ecra();
        printf("=== Gestao de Corridas ===\n");
        printf("1. Registar corrida\n");
        printf("2. Listar corridas\n");
        printf("0. Voltar\n");

        int opcao = util_ler_inteiro("Opcao: ", 0, 2);
        switch (opcao) {
            case 1: accao_registar_corrida(sistema); break;
            case 2: relatorio_corridas(sistema); break;
            case 0: return;
            default: break;
        }
        util_pausar();
    }
}

static void menu_relatorios(Sistema *sistema)
{
    for (;;) {
        util_limpar_ecra();
        printf("=== Relatorios ===\n");
        printf("1. Resumo geral\n");
        printf("2. Frota de viaturas\n");
        printf("3. Motoristas\n");
        printf("4. Corridas\n");
        printf("5. Receita por motorista\n");
        printf("0. Voltar\n");

        int opcao = util_ler_inteiro("Opcao: ", 0, 5);
        switch (opcao) {
            case 1: relatorio_resumo_geral(sistema); break;
            case 2: relatorio_frota(sistema); break;
            case 3: relatorio_motoristas(sistema); break;
            case 4: relatorio_corridas(sistema); break;
            case 5: relatorio_receita_por_motorista(sistema); break;
            case 0: return;
            default: break;
        }
        util_pausar();
    }
}

void ui_executar(Sistema *sistema, const char *ficheiroDados)
{
    for (;;) {
        util_limpar_ecra();
        printf("====================================\n");
        printf("  Sistema de Controle de Taxis\n");
        printf("        Azul e Branco\n");
        printf("====================================\n");
        printf("1. Viaturas\n");
        printf("2. Motoristas\n");
        printf("3. Corridas\n");
        printf("4. Relatorios\n");
        printf("5. Guardar dados\n");
        printf("0. Guardar e sair\n");

        int opcao = util_ler_inteiro("Opcao: ", 0, 5);
        switch (opcao) {
            case 1: menu_viaturas(sistema); break;
            case 2: menu_motoristas(sistema); break;
            case 3: menu_corridas(sistema); break;
            case 4: menu_relatorios(sistema); break;
            case 5:
                mostrar_resultado(persistencia_guardar(sistema, ficheiroDados));
                util_pausar();
                break;
            case 0:
                mostrar_resultado(persistencia_guardar(sistema, ficheiroDados));
                return;
            default:
                break;
        }
    }
}
