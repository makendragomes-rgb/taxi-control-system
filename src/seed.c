#include "seed.h"
#include "viatura.h"
#include "motorista.h"
#include "corrida.h"

void seed_povoar(Sistema *sistema)
{
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int m1 = 0;
    int m2 = 0;
    int corridaId = 0;

    sistema_inicializar(sistema);

    viatura_adicionar(sistema, "AB-12-CD", "Toyota Prius", &v1);
    viatura_adicionar(sistema, "EF-34-GH", "Mercedes E220", &v2);
    viatura_adicionar(sistema, "IJ-56-KL", "Nissan Leaf", &v3);

    motorista_adicionar(sistema, "Joao Silva", "C-123456", TURNO_DIURNO, &m1);
    motorista_adicionar(sistema, "Maria Costa", "C-654321", TURNO_NOTURNO, &m2);

    viatura_atribuir_motorista(sistema, v1, m1);
    viatura_atribuir_motorista(sistema, v2, m2);

    corrida_registar(sistema, v1, m1, "Aeroporto", "Baixa", 12.5, 20, 5, TARIFA_DIURNA, &corridaId);
    corrida_registar(sistema, v2, m2, "Estacao", "Hospital", 8.0, 15, 0, TARIFA_NOTURNA, &corridaId);
    corrida_registar(sistema, v1, m1, "Baixa", "Universidade", 6.2, 12, 2, TARIFA_DIURNA, &corridaId);

    viatura_definir_estado(sistema, v3, ESTADO_MANUTENCAO);
}
