# Documentação do Projeto — Taxi Control System

Documento de apoio à defesa do projeto da disciplina de Programação 1 (Linguagem C).

---

## 1. O que é o projeto

O **Taxi Control System** é uma aplicação de consola, escrita em Linguagem C, que simula o
sistema de gestão de uma empresa de táxis convencionais (modelo "Azul e Branco"). A aplicação
centraliza, num único programa, toda a operação de uma central de táxis: o registo das
**viaturas**, a gestão dos **motoristas**, o registo das **corridas** efetuadas, o **cálculo
automático das tarifas** e a produção de **relatórios** de gestão.

Corresponde ao **Projecto 08** do enunciado da disciplina.

---

## 2. Objetivo

O objetivo é gerir de forma integrada a frota de uma empresa de táxis, controlando viaturas,
motoristas, viagens e tarifas. Em concreto, o sistema permite:

- Registar viaturas com matrícula, modelo e estado de disponibilidade.
- Gerir motoristas com número de carta e turno (diurno/noturno).
- Registar corridas com origem, destino, distância, duração e tempo de espera.
- Calcular automaticamente o valor de cada corrida com base numa tabela de tarifas.
- Controlar a disponibilidade das viaturas em tempo real.
- Gerar relatórios de receita por motorista e de produtividade da frota.

Do ponto de vista pedagógico, o projeto pratica: cálculos com fórmulas de tarifação, gestão de
estados das viaturas, relatórios estatísticos e o tratamento de turnos e disponibilidade.

---

## 3. Ideias e decisões de conceção

Durante o planeamento do projeto tomámos as seguintes decisões:

1. **Arquitetura modular.** Em vez de concentrar tudo num único ficheiro, dividimos o sistema
   em módulos independentes (viaturas, motoristas, corridas, tarifas, relatórios), cada um com
   um cabeçalho (`.h`) que define a sua interface e um ficheiro (`.c`) com a implementação. Isto
   torna o código mais legível, fácil de testar e de manter.

2. **Separação entre lógica e interface.** Os módulos de domínio (viatura, motorista, corrida,
   tarifa) **não fazem leitura nem escrita no ecrã**: limitam-se a manipular dados e a devolver
   códigos de resultado. Toda a interação com o utilizador está concentrada no módulo de
   interface (`ui.c`) e nos utilitários de entrada (`util.c`). Assim, a lógica de negócio fica
   isolada da apresentação.

3. **Estado centralizado.** Todos os dados da aplicação vivem numa única estrutura `Sistema`,
   que é passada por ponteiro às funções. Evita variáveis globais dispersas e facilita guardar e
   carregar o estado completo do programa.

4. **Tabela de tarifas configurável.** O cálculo da tarifa foi isolado num módulo próprio
   (`tarifa.c`), com uma tabela para a tarifa diurna e outra para a noturna. Alterar os preços
   não obriga a mexer no resto do código.

5. **Persistência simples e fiável.** Como a estrutura `Sistema` usa arrays de tamanho fixo,
   optámos por guardar e ler todo o estado de uma só vez num ficheiro binário, com `fwrite` e
   `fread`. É simples, rápido e garante que os dados não se perdem entre execuções.

6. **Validação de dados na entrada.** A leitura de números e texto é feita por funções
   utilitárias que validam intervalos e impedem entradas vazias ou inválidas, evitando que o
   programa entre em estados incorretos.

---

## 4. Boas práticas aplicadas

- **Modularidade e responsabilidade única:** cada ficheiro tem uma responsabilidade clara.
- **Cabeçalhos com _include guards_:** todos os `.h` usam `#ifndef/#define/#endif` para evitar
  inclusões múltiplas.
- **Nomes descritivos e consistentes:** funções e variáveis em português, com prefixo do módulo
  (`viatura_adicionar`, `motorista_remover`, `corrida_registar`), o que torna o código
  autoexplicativo e dispensa comentários.
- **`const`-correctness:** funções que apenas consultam dados recebem `const Sistema *`,
  deixando claro que não alteram o estado.
- **Códigos de resultado em vez de retornos ambíguos:** as operações devolvem um `enum Resultado`
  (`OK`, `ERRO_NAO_ENCONTRADO`, `ERRO_DUPLICADO`, ...), permitindo tratamento de erros uniforme.
- **Proteção contra _buffer overflow_:** cópias de strings feitas com `strncpy` e terminação
  manual com `'\0'`.
- **Compilação com avisos ativados:** o `Makefile` usa `-Wall -Wextra -std=c11`, garantindo
  código limpo sem avisos do compilador.
- **Encapsulamento:** funções auxiliares internas de cada módulo são declaradas `static`,
  não poluindo o espaço de nomes global.
- **Separação de dados e código:** os dados persistidos ficam na pasta `data/`, isolados do
  código-fonte.

---

## 5. Estrutura do projeto (pastas e ficheiros)

```
taxi-control-system/
├── include/
│   ├── tipos.h
│   ├── viatura.h
│   ├── motorista.h
│   ├── corrida.h
│   ├── tarifa.h
│   ├── relatorio.h
│   ├── persistencia.h
│   ├── util.h
│   └── ui.h
├── src/
│   ├── main.c
│   ├── sistema.c
│   ├── viatura.c
│   ├── motorista.c
│   ├── corrida.c
│   ├── tarifa.c
│   ├── relatorio.c
│   ├── persistencia.c
│   ├── util.c
│   └── ui.c
├── data/            (ficheiro de dados gerado em execução)
├── docs/
│   └── DOCUMENTACAO.md
├── Makefile
├── README.md
└── .gitignore
```

### 5.1. Pasta `include/` — interfaces dos módulos

- **`tipos.h`** — Coração do projeto. Define as constantes (limites dos arrays, tamanhos de
  texto), os tipos enumerados (`EstadoViatura`, `Turno`, `TipoTarifa`, `Resultado`) e as
  estruturas de dados principais: `Viatura`, `Motorista`, `Corrida` e a estrutura agregadora
  `Sistema`, que guarda todo o estado da aplicação.
- **`viatura.h`** — Declara as operações sobre viaturas (adicionar, remover, alterar estado,
  atribuir motorista, procurar) e o texto descritivo de cada estado.
- **`motorista.h`** — Declara as operações sobre motoristas (adicionar, remover, procurar) e o
  texto descritivo do turno.
- **`corrida.h`** — Declara o registo de corridas e a procura de uma corrida por identificador.
- **`tarifa.h`** — Declara a tabela de tarifas e a função de cálculo do valor de uma corrida.
- **`relatorio.h`** — Declara as funções que produzem os vários relatórios.
- **`persistencia.h`** — Declara as funções de gravação e leitura dos dados em ficheiro.
- **`util.h`** — Declara os utilitários de entrada de dados, data/hora e ecrã.
- **`ui.h`** — Declara o ponto de entrada da interface (menus).

### 5.2. Pasta `src/` — implementação

- **`main.c`** — Função `main`. Carrega os dados do ficheiro (ou inicializa um sistema vazio),
  arranca a interface e termina. É deliberadamente curta: apenas orquestra o programa.
- **`sistema.c`** — Inicializa a estrutura `Sistema` (contadores a zero e identificadores a
  começar em 1).
- **`viatura.c`** — Implementa toda a gestão de viaturas: validação de matrícula duplicada,
  atribuição automática de identificadores, alteração de estado e associação a um motorista.
- **`motorista.c`** — Implementa a gestão de motoristas. Ao remover um motorista, desassocia-o
  automaticamente das viaturas a que estava atribuído, mantendo a coerência dos dados.
- **`corrida.c`** — Regista corridas. Valida a existência da viatura e do motorista, impede o
  registo se a viatura estiver em manutenção, calcula o valor através do módulo de tarifas,
  regista a data/hora e atualiza o total ganho pelo motorista.
- **`tarifa.c`** — Contém as tabelas de tarifa (diurna e noturna) e a fórmula de cálculo:
  `valor = bandeirada + (distância × preço_km) + (tempo_espera × preço_espera)`.
- **`relatorio.c`** — Produz os relatórios formatados em tabela: frota, motoristas, corridas,
  receita por motorista e resumo geral com totais e estatísticas.
- **`persistencia.c`** — Grava e lê toda a estrutura `Sistema` num ficheiro binário.
- **`util.c`** — Funções de leitura robusta de inteiros, reais e texto (com validação), obtenção
  da data/hora atual e limpeza/pausa do ecrã.
- **`ui.c`** — Constrói os menus e submenus, recolhe os dados do utilizador, chama as funções dos
  módulos e apresenta os resultados. É a única camada que comunica com o utilizador.

### 5.3. Outros ficheiros

- **`Makefile`** — Automatiza a compilação (`make`), a execução (`make run`) e a limpeza
  (`make clean`), com os avisos do compilador ativados.
- **`README.md`** — Apresentação rápida, instruções de compilação e execução.
- **`.gitignore`** — Exclui do repositório os ficheiros gerados (binários, objetos e dados).

---

## 6. Modelo de dados

| Estrutura   | Campos principais                                                        |
|-------------|--------------------------------------------------------------------------|
| `Viatura`   | id, matrícula, modelo, estado, motoristaId                               |
| `Motorista` | id, nome, carta, turno, totalGanho                                       |
| `Corrida`   | id, viaturaId, motoristaId, origem, destino, distância, duração, espera, tarifa, valor, dataHora |

A estrutura `Sistema` agrega arrays destas três entidades e os contadores de identificadores.

---

## 7. Fluxo de utilização

1. O programa arranca e tenta carregar os dados de `data/taxi.dat`. Se não existir, começa vazio.
2. O utilizador navega pelo **menu principal**: Viaturas, Motoristas, Corridas, Relatórios.
3. Regista viaturas e motoristas, atribui motoristas a viaturas.
4. Regista corridas — o sistema calcula automaticamente o valor e soma-o ao motorista.
5. Consulta os relatórios de gestão.
6. Ao guardar ou sair, o estado completo é gravado no ficheiro de dados.

---

## 8. Conceitos de C demonstrados

- Estruturas (`struct`) e tipos enumerados (`enum`).
- Arrays de estruturas e gestão de coleções.
- Ponteiros e passagem por referência.
- Ficheiros binários (`fopen`, `fread`, `fwrite`).
- Manipulação de strings (`strncpy`, `strcmp`, `strlen`).
- Data e hora com a biblioteca `time.h`.
- Modularização com cabeçalhos e compilação separada.
- Tratamento de erros através de códigos de resultado.
