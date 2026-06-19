#include "tipos.h"

void sistema_inicializar(Sistema *sistema)
{
    sistema->numViaturas = 0;
    sistema->numMotoristas = 0;
    sistema->numCorridas = 0;
    sistema->proximoIdViatura = 1;
    sistema->proximoIdMotorista = 1;
    sistema->proximoIdCorrida = 1;
}
