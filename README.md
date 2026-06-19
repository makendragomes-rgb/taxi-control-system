# Taxi Control System

Sistema de gestão de frota de táxis (modelo "Azul e Branco") desenvolvido em Linguagem C.
Permite gerir viaturas, motoristas e corridas, calcular tarifas automaticamente e gerar
relatórios de produtividade e receita.

## Funcionalidades

- Registo de viaturas com matrícula, modelo e estado
- Gestão de motoristas com número de carta e turno
- Registo de corridas com origem, destino, distância, duração e tempo de espera
- Cálculo automático de tarifas (bandeirada, preço por km e tempo de espera)
- Controlo de disponibilidade das viaturas (disponível, ocupada, manutenção)
- Relatórios de frota, motoristas, corridas, receita por motorista e resumo geral
- Persistência de dados em ficheiro binário

## Estrutura do Projeto

```
taxi-control-system/
├── include/        Cabeçalhos (.h) com as interfaces dos módulos
├── src/            Código-fonte (.c) com a implementação
├── data/           Ficheiro de dados gerado em tempo de execução
├── docs/           Documentação do projeto
├── Makefile        Script de compilação
└── README.md
```

## Compilação

Com `make`:

```
make
```

Diretamente com o `gcc`:

```
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o taxi-control-system
```

## Execução

```
make run
```

ou

```
./taxi-control-system
```

## Requisitos

- Compilador C compatível com C11 (gcc ou clang)
- `make` (opcional)
