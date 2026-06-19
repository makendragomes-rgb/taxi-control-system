#ifndef TIPOS_H
#define TIPOS_H

#define MAX_VIATURAS 200
#define MAX_MOTORISTAS 200
#define MAX_CORRIDAS 2000

#define TAM_MATRICULA 16
#define TAM_MODELO 50
#define TAM_NOME 80
#define TAM_CARTA 24
#define TAM_LOCAL 80
#define TAM_DATAHORA 32

typedef enum {
    OK,
    ERRO_LOTACAO,
    ERRO_NAO_ENCONTRADO,
    ERRO_DUPLICADO,
    ERRO_INVALIDO,
    ERRO_INDISPONIVEL,
    ERRO_FICHEIRO
} Resultado;

typedef enum {
    ESTADO_DISPONIVEL,
    ESTADO_OCUPADA,
    ESTADO_MANUTENCAO
} EstadoViatura;

typedef enum {
    TURNO_DIURNO,
    TURNO_NOTURNO
} Turno;

typedef enum {
    TARIFA_DIURNA,
    TARIFA_NOTURNA
} TipoTarifa;

typedef struct {
    int id;
    char matricula[TAM_MATRICULA];
    char modelo[TAM_MODELO];
    EstadoViatura estado;
    int motoristaId;
} Viatura;

typedef struct {
    int id;
    char nome[TAM_NOME];
    char carta[TAM_CARTA];
    Turno turno;
    double totalGanho;
} Motorista;

typedef struct {
    int id;
    int viaturaId;
    int motoristaId;
    char origem[TAM_LOCAL];
    char destino[TAM_LOCAL];
    double distancia;
    int duracaoMinutos;
    int tempoEsperaMinutos;
    TipoTarifa tipoTarifa;
    double valor;
    char dataHora[TAM_DATAHORA];
} Corrida;

typedef struct {
    Viatura viaturas[MAX_VIATURAS];
    int numViaturas;
    Motorista motoristas[MAX_MOTORISTAS];
    int numMotoristas;
    Corrida corridas[MAX_CORRIDAS];
    int numCorridas;
    int proximoIdViatura;
    int proximoIdMotorista;
    int proximoIdCorrida;
} Sistema;

void sistema_inicializar(Sistema *sistema);

#endif
