# Guião de Demonstração — Taxi Control System

Roteiro para apresentar e defender o projeto ao vivo. Segue os passos pela ordem indicada;
os valores estão prontos a introduzir e os resultados esperados estão assinalados.

---

## 1. Preparação (antes de começar)

Compilar e arrancar a aplicação:

```
make
make run
```

ou, sem `make`:

```
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o taxi-control-system
./taxi-control-system
```

> Dica: começa com a aplicação já compilada. Se quiseres uma demonstração "limpa",
> apaga o ficheiro `data/taxi.dat` antes de arrancar para começar sem dados.

---

## 2. Roteiro da demonstração

### Passo 1 — Registar duas viaturas
No menu principal escolhe **1 (Viaturas)** → **1 (Registar viatura)**.

| Campo     | Viatura A      | Viatura B       |
|-----------|----------------|-----------------|
| Matrícula | `AB-12-CD`     | `EF-34-GH`      |
| Modelo    | `Toyota Prius` | `Mercedes E220` |

Resultado esperado: *"Viatura registada com o ID 1"* e *"... ID 2"*.

Escolhe **2 (Listar frota)** para mostrar a tabela com as duas viaturas a "Disponivel".

### Passo 2 — Registar dois motoristas
Volta ao menu principal → **2 (Motoristas)** → **1 (Registar motorista)**.

| Campo  | Motorista 1   | Motorista 2    |
|--------|---------------|----------------|
| Nome   | `Joao Silva`  | `Maria Costa`  |
| Carta  | `C-123456`    | `C-654321`     |
| Turno  | `0` (Diurno)  | `1` (Noturno)  |

Resultado esperado: IDs 1 e 2 atribuídos.

### Passo 3 — Atribuir motoristas às viaturas
Menu **1 (Viaturas)** → **4 (Atribuir motorista)**:
- Viatura `1` → Motorista `1`
- Viatura `2` → Motorista `2`

Mostra **2 (Listar frota)**: a coluna "Motorista" passa a indicar os nomes.

### Passo 4 — Registar corridas (cálculo automático da tarifa)
Menu **3 (Corridas)** → **1 (Registar corrida)**.

**Corrida 1 (tarifa diurna):**

| Campo               | Valor       |
|---------------------|-------------|
| ID da viatura       | `1`         |
| ID do motorista     | `1`         |
| Origem              | `Aeroporto` |
| Destino             | `Baixa`     |
| Distância (km)      | `12.5`      |
| Duração (minutos)   | `20`        |
| Tempo de espera     | `5`         |
| Tipo de tarifa      | `0` (Diurna)|

Resultado esperado: **Valor calculado: 11.03**
(cálculo: 3,25 de bandeirada + 12,5 × 0,55 + 5 × 0,18 = 11,03)

**Corrida 2 (tarifa noturna):**

| Campo               | Valor          |
|---------------------|----------------|
| ID da viatura       | `2`            |
| ID do motorista     | `2`            |
| Origem              | `Estacao`      |
| Destino             | `Hospital`     |
| Distância (km)      | `8`            |
| Duração (minutos)   | `15`           |
| Tempo de espera     | `0`            |
| Tipo de tarifa      | `1` (Noturna)  |

Resultado esperado: **Valor calculado: 9.34**
(cálculo: 3,90 + 8 × 0,68 + 0 = 9,34)

### Passo 5 — Mostrar os relatórios
Menu **4 (Relatórios)**:
- **1 (Resumo geral)** — mostra totais: 2 viaturas, 2 motoristas, 2 corridas, distância total
  20,5 km e receita total **20,37**.
- **5 (Receita por motorista)** — mostra cada motorista com o número de corridas e a receita.

### Passo 6 — Demonstrar a persistência
Escolhe **0 (Guardar e sair)**. Arranca novamente (`make run`) e vai a
**4 (Relatórios) → 1 (Resumo geral)**: os dados continuam lá, provando que foram gravados
em `data/taxi.dat` e relidos.

### Passo 7 (opcional) — Validações
Mostra a robustez do sistema:
- Tenta registar uma viatura com matrícula repetida (`AB-12-CD`) → *"Ja existe um registo..."*.
- Tenta uma opção inválida no menu (ex.: `9`) → o sistema rejeita e repete o pedido.
- Coloca uma viatura em **Manutenção** (Viaturas → 3) e tenta registar-lhe uma corrida →
  *"Viatura indisponivel para esta operacao."*.

---

## 3. O que destacar durante a defesa

- **Arquitetura modular**: cada módulo (`viatura`, `motorista`, `corrida`, `tarifa`,
  `relatorio`) tem o seu `.h` (interface) e `.c` (implementação).
- **Separação lógica/interface**: os módulos de domínio não imprimem nada; só o `ui.c` fala
  com o utilizador. Isto facilita testar e reutilizar a lógica.
- **Cálculo de tarifas isolado** em `tarifa.c`, com tabela configurável.
- **Persistência binária** de toda a estrutura `Sistema` num único ficheiro.
- **Sem comentários, mas legível**: o código é claro graças aos nomes descritivos.
- **Compila sem avisos** com `-Wall -Wextra`.

---

## 4. Perguntas prováveis do júri (e respostas)

**Porque não usaram comentários?**
O código foi escrito para ser autoexplicativo através de nomes claros e funções pequenas com
uma única responsabilidade. A explicação de alto nível está na documentação. Foi também um
requisito assumido do projeto.

**Como é calculada a tarifa?**
`valor = bandeirada + (distância × preço_km) + (tempo_espera × preço_min)`. Há duas tabelas
(diurna e noturna) definidas em `tarifa.c`; mudar de tabela não afeta o resto do código.

**Onde ficam guardados os dados?**
Em `data/taxi.dat`, um ficheiro binário onde gravamos a estrutura `Sistema` completa com
`fwrite` e que lemos no arranque com `fread`.

**O que acontece se o ficheiro de dados não existir?**
No arranque, se a leitura falhar, o sistema é inicializado vazio com `sistema_inicializar`.

**Porque é que a estrutura `Sistema` é passada por ponteiro?**
Para evitar variáveis globais e cópias desnecessárias da estrutura, e para que todas as
funções operem sobre o mesmo estado central.

**Como garantem que não há matrículas repetidas?**
Antes de adicionar, `viatura_adicionar` procura a matrícula com `viatura_por_matricula`;
se já existir, devolve `ERRO_DUPLICADO`.

**E se removerem um motorista que está atribuído a uma viatura?**
`motorista_remover` percorre as viaturas e desassocia o motorista (coloca `motoristaId` a 0),
mantendo a coerência dos dados.

**Quais os limites do sistema?**
Definidos em `tipos.h`: até 200 viaturas, 200 motoristas e 2000 corridas. São constantes
fáceis de ajustar.
