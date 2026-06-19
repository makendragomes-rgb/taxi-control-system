#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "tipos.h"

Resultado persistencia_guardar(const Sistema *sistema, const char *ficheiro);
Resultado persistencia_carregar(Sistema *sistema, const char *ficheiro);

#endif
