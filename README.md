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

## Demonstração rápida (dados de exemplo)

O programa aceita o argumento `--demo`, que arranca já com dados de exemplo carregados
(3 viaturas, 2 motoristas e 3 corridas), ideal para uma demonstração imediata. Os dados de
demonstração são gravados num ficheiro separado (`data/taxi-demo.dat`) e não afetam os dados
reais (`data/taxi.dat`).

Com `make`:

```
make demo
```

Comando único (compila e arranca em modo demonstração):

```
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o taxi-control-system && ./taxi-control-system --demo
```

No Windows (PowerShell):

```
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o taxi-control-system.exe ; ./taxi-control-system.exe --demo
```

## Como testar

1. Arranca em modo demonstração (`make demo` ou `--demo`).
2. Abre o menu **4 (Relatórios)**:
   - **1 (Resumo geral)** deve mostrar 3 viaturas (2 disponíveis, 1 em manutenção),
     2 motoristas, 3 corridas e receita total **27.39**.
   - **2 (Frota)** mostra a viatura "Nissan Leaf" em **Manutencao** e sem motorista.
   - **5 (Receita por motorista)** mostra João Silva com 2 corridas (18.05) e Maria Costa
     com 1 corrida (9.34).
3. Testa as validações: tenta registar uma viatura com matrícula repetida, ou registar uma
   corrida para a viatura em manutenção (ID 3) — ambas devem ser recusadas.
4. Sai com **0 (Guardar e sair)**, volta a arrancar normalmente (`make run`) e confirma que
   os dados reais permanecem independentes dos de demonstração.

Para uma verificação automática (sem digitar), é possível encaminhar as respostas por `stdin`.
Exemplo que arranca em demo e imprime o resumo geral:

```
printf '4\n1\n\n0\n0\n' | ./taxi-control-system --demo
```

## Requisitos

- Compilador C compatível com C11 (gcc ou clang)
- `make` (opcional)
