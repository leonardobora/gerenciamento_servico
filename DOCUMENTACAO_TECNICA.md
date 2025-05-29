# 📚 Documentação Técnica - Sistema de Gerenciamento de Serviços

## 📋 Índice
1. [Visão Geral](#visão-geral)
2. [Arquitetura do Sistema](#arquitetura-do-sistema)
3. [Estruturas de Dados](#estruturas-de-dados)
4. [API de Funções](#api-de-funções)
5. [Interface Gráfica](#interface-gráfica)
6. [Compilação e Execução](#compilação-e-execução)
7. [Análise de Complexidade](#análise-de-complexidade)
8. [Gerenciamento de Memória](#gerenciamento-de-memória)
9. [Casos de Teste](#casos-de-teste)
10. [Troubleshooting](#troubleshooting)

---

## 🎯 Visão Geral

### Descrição
Sistema de gerenciamento de serviços desenvolvido em linguagem C com interface gráfica GTK+. O sistema permite criar, visualizar, atualizar e excluir serviços organizados por prioridade utilizando uma lista duplamente encadeada.

### Características Principais
- **Estrutura de Dados**: Lista duplamente encadeada
- **Interface**: GTK+ 3.0 (GUI) + Console (legacy)
- **Linguagem**: C (padrão C99)
- **Plataforma**: Linux/Unix/WSL2
- **Funcionalidades**: CRUD completo + filtros + validações

### Versões
- **v1.0**: Sistema console básico
- **v2.0**: Interface GTK+ completa (atual)

---

## 🏗️ Arquitetura do Sistema

### Diagrama de Componentes
```
┌─────────────────────────────────────────────────────────┐
│                    INTERFACE GTK+                      │
├─────────────────────────────────────────────────────────┤
│  Adicionar  │  Atualizar  │  Excluir  │  Filtros      │
├─────────────────────────────────────────────────────────┤
│                  LÓGICA DE NEGÓCIO                     │
├─────────────────────────────────────────────────────────┤
│ insereServico │ atualizaStatus │ excluirServico │ etc   │
├─────────────────────────────────────────────────────────┤
│               ESTRUTURA DE DADOS                       │
├─────────────────────────────────────────────────────────┤
│           LISTA DUPLAMENTE ENCADEADA                   │
│  ┌───┐    ┌───┐    ┌───┐    ┌───┐    ┌───┐           │
│  │ A │◄──►│ A │◄──►│ M │◄──►│ M │◄──►│ B │           │
│  └───┘    └───┘    └───┘    └───┘    └───┘           │
└─────────────────────────────────────────────────────────┘
```

### Padrões Arquiteturais
- **Separação de Responsabilidades**: Interface, lógica e dados separados
- **Modularidade**: Funções específicas para cada operação
- **Encapsulamento**: Estruturas e variáveis globais controladas

---

## 🔧 Estruturas de Dados

### Estrutura Principal: Serviço
```c
struct Servico {
    int id;                    // Identificador único sequencial
    char descricao[100];       // Descrição textual do serviço
    char status;               // Estado: 'P', 'E', 'C'
    char prioridade;           // Nível: 'A', 'M', 'B'
    struct Servico *ant;       // Ponteiro para nó anterior
    struct Servico *prox;      // Ponteiro para próximo nó
};
typedef struct Servico Servico;
```

### Variáveis Globais
```c
Servico *listaDeServicos = NULL;    // Ponteiro para primeiro nó
int proximoId = 1;                  // Contador de IDs únicos
```

### Estados e Prioridades
```c
// Status válidos
#define STATUS_PENDENTE     'P'
#define STATUS_EXECUCAO     'E' 
#define STATUS_CONCLUIDO    'C'

// Prioridades (ordem decrescente)
#define PRIORIDADE_ALTA     'A'    // Valor: 3
#define PRIORIDADE_MEDIA    'M'    // Valor: 2
#define PRIORIDADE_BAIXA    'B'    // Valor: 1
```

---

## 🛠️ API de Funções

### Funções Principais

#### `void insereServicoPrioridade(char descricao[], char prioridadeChar, char status)`
**Descrição**: Insere novo serviço na lista mantendo ordenação por prioridade.

**Parâmetros**:
- `descricao[]`: Texto descritivo do serviço (max 99 chars)
- `prioridadeChar`: 'A', 'M' ou 'B'
- `status`: 'P', 'E' ou 'C'

**Complexidade**: O(n)

**Algoritmo**:
1. Aloca memória para novo nó
2. Define ID sequencial automático
3. Localiza posição correta baseada na prioridade
4. Insere mantendo ponteiros anterior/próximo

#### `void atualizaStatusServico(int id, char novoStatus)`
**Descrição**: Atualiza status de serviço existente por ID.

**Parâmetros**:
- `id`: Identificador único do serviço
- `novoStatus`: Novo status ('P', 'E' ou 'C')

**Complexidade**: O(n)

#### `int excluirServico(int id)`
**Descrição**: Remove serviço da lista por ID.

**Retorno**: 1 se sucesso, 0 se não encontrado

**Complexidade**: O(n) para buscar + O(1) para remover

#### `void liberaMemoria()`
**Descrição**: Libera toda memória alocada pela lista.

**Complexidade**: O(n)

### Funções Auxiliares

#### `int getPrioridadeValor(char p)`
**Descrição**: Converte caractere de prioridade para valor numérico.

**Mapeamento**:
- 'A' → 3 (Alta)
- 'M' → 2 (Média)  
- 'B' → 1 (Baixa)

#### `int contarServicos()`
**Descrição**: Conta total de serviços na lista.

#### `int contarServicosPorStatus(char status)`
**Descrição**: Conta serviços com status específico.

#### `void atualizarContadores()`
**Descrição**: Atualiza contadores visuais na interface.

---

## 🖥️ Interface Gráfica

### Componentes GTK+

#### Widgets Principais
```c
GtkWidget *window;                    // Janela principal
GtkWidget *tree_view;                 // Tabela de serviços
GtkListStore *list_store;             // Modelo de dados
GtkWidget *entry_descricao;           // Campo descrição
GtkWidget *combo_prioridade;          // Seletor prioridade
GtkWidget *combo_status;              // Seletor status
GtkWidget *entry_id_atualizar;        // Campo ID para atualizar
GtkWidget *combo_novo_status;         // Novo status
GtkWidget *entry_id_excluir;          // Campo ID para excluir
GtkWidget *label_contador_servicos;   // Label contadores
GtkWidget *combo_filtro_status;       // Filtro por status
GtkWidget *combo_filtro_prioridade;   // Filtro por prioridade
```

#### Layout da Interface
```
┌─────────────────────────────────────────────────────────┐
│  Sistema de Gerenciamento de Serviços                  │
│  Desenvolvido por: Leonardo Bora e Luan Constancio     │
├─────────────────────────────────────────────────────────┤
│ ┌─ Adicionar Serviço ─────────────────────────────────┐ │
│ │ Descrição: [________________] [Adicionar Serviço]   │ │
│ │ Prioridade: [Alta▼] Status: [Pendente▼]            │ │
│ └─────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────┤
│ ┌─ Atualizar Status ──┐ ┌─ Excluir Serviço ──────────┐ │
│ │ ID: [___]           │ │ ID do Serviço: [___]       │ │
│ │ Novo Status: [▼]    │ │ [Excluir]                  │ │
│ │ [Atualizar]         │ │                            │ │
│ └─────────────────────┘ └────────────────────────────┘ │
├─────────────────────────────────────────────────────────┤
│ ┌─ Filtros e Ações ──────────────────────────────────┐ │
│ │ Status: [Todos▼] Prioridade: [Todas▼]             │ │
│ │                           [🗑️ Limpar] [ℹ️ Info]    │ │
│ └─────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────┤
│  Total: 5 | Pendentes: 2 | Em Execução: 2 | Concluídos: 1
├─────────────────────────────────────────────────────────┤
│ ┌─ Lista de Serviços ────────────────────────────────┐ │
│ │ ID │ Descrição              │ Prioridade │ Status  │ │
│ ├────┼────────────────────────┼────────────┼─────────┤ │
│ │  1 │ Backup servidor        │ Alta       │ Pendente│ │
│ │  3 │ Correção bug crítico   │ Alta       │ Execução│ │
│ │  2 │ Atualizar sistema      │ Média      │ Execução│ │
│ │  4 │ Documentação           │ Média      │ Concluído│ │
│ │  5 │ Limpeza arquivos       │ Baixa      │ Pendente│ │
│ └─────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
```

### Callbacks e Eventos
```c
// Callbacks principais
void on_adicionar_clicked(GtkWidget *widget, gpointer data);
void on_atualizar_clicked(GtkWidget *widget, gpointer data);
void on_excluir_clicked(GtkWidget *widget, gpointer data);
void on_filtro_changed(GtkWidget *widget, gpointer data);
void limpar_todos_servicos(GtkWidget *widget, gpointer data);
void mostrar_info_arquitetura(GtkWidget *widget, gpointer data);
void on_window_destroy(GtkWidget *widget, gpointer data);
```

---

## ⚙️ Compilação e Execução

### Dependências
```bash
# Ubuntu/Debian
sudo apt-get install build-essential libgtk-3-dev

# Red Hat/CentOS/Fedora
sudo yum install gcc gtk3-devel
# ou
sudo dnf install gcc gtk3-devel
```

### Comandos de Compilação

#### Versão GTK+ (Recomendada)
```bash
gcc gerenciador_servicos_gtk.c -o gerenciador_servicos_gtk `pkg-config --cflags --libs gtk+-3.0`
```

#### Versão Console (Legacy)
```bash
gcc gerenciador_servicos.c -o gerenciador_servicos
```

#### Makefile (Disponível)
```bash
make all        # Compila ambas versões
make gtk        # Apenas versão GTK+
make console    # Apenas versão console
make clean      # Remove executáveis
```

### Execução
```bash
# Versão GTK+
./gerenciador_servicos_gtk

# Versão Console
./gerenciador_servicos
```

---

## 📊 Análise de Complexidade

### Operações Principais

| Operação | Complexidade Temporal | Complexidade Espacial | Observações |
|----------|----------------------|----------------------|-------------|
| **Inserção** | O(n) | O(1) | Percorre lista até posição correta |
| **Busca por ID** | O(n) | O(1) | Busca linear sequencial |
| **Atualização** | O(n) | O(1) | Busca + modificação |
| **Remoção** | O(n) | O(1) | Busca + remoção em O(1) |
| **Exibição** | O(n) | O(1) | Percorre toda lista |
| **Filtros** | O(n) | O(1) | Percorre com condições |
| **Contagem** | O(n) | O(1) | Percorre contando |

### Análise Detalhada

#### Inserção por Prioridade
```c
// Melhor caso: O(1) - inserir no início (prioridade mais alta)
// Caso médio: O(n/2) - inserir no meio
// Pior caso: O(n) - inserir no final (prioridade mais baixa)
```

#### Busca Linear
```c
// Sempre O(n) - não há índice ou hash
// Otimização possível: hash table para IDs
```

#### Espaço de Memória
```c
// Cada nó: sizeof(Servico) = ~120 bytes
// n serviços: n * 120 bytes + ponteiros overhead
// Sem fragmentação significativa
```

---

## 🧠 Gerenciamento de Memória

### Estratégias de Alocação

#### Alocação Dinâmica
```c
Servico *novoServico = (Servico*)malloc(sizeof(Servico));
if (!novoServico) {
    g_print("Erro: Falha na alocação de memória!\n");
    return;
}
```

#### Liberação Segura
```c
void liberaMemoria() {
    Servico *atual = listaDeServicos;
    Servico *proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);              // Libera nó atual
        atual = proximo;          // Avança para próximo
    }
    
    listaDeServicos = NULL;       // Reset ponteiro principal
}
```

#### Remoção Individual
```c
int excluirServico(int id) {
    Servico *atual = listaDeServicos;
    
    while (atual != NULL) {
        if (atual->id == id) {
            // Atualizar ponteiros dos nós adjacentes
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                listaDeServicos = atual->prox; // Primeiro nó
            }
            
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            }
            
            free(atual);          // Libera memória
            return 1;             // Sucesso
        }
        atual = atual->prox;
    }
    return 0;                     // Não encontrado
}
```

### Prevenção de Vazamentos
- **Validação de Alocação**: Verificar retorno do malloc
- **Liberação Sistemática**: Função dedicada para cleanup
- **Ponteiros Nulos**: Reset após liberação
- **Cleanup na Saída**: Callback de destruição da janela

---

## 🧪 Casos de Teste

### Cenários de Teste Funcionais

#### Teste 1: Inserção e Ordenação
```
Entrada:
1. "Backup crítico" - Alta - Pendente
2. "Limpeza logs" - Baixa - Pendente  
3. "Atualização" - Média - Em Execução

Resultado Esperado:
ID | Descrição      | Prioridade | Status
1  | Backup crítico | Alta       | Pendente
3  | Atualização    | Média      | Em Execução
2  | Limpeza logs   | Baixa      | Pendente
```

#### Teste 2: Atualização de Status
```
Entrada:
- Atualizar serviço ID 1 para "Concluído"

Resultado Esperado:
ID 1 status muda de "Pendente" → "Concluído"
Contadores atualizam automaticamente
```

#### Teste 3: Filtros
```
Entrada:
- Filtro por Status: "Em Execução"

Resultado Esperado:
Apenas serviços com status "Em Execução" aparecem
Contadores mostram totais originais
```

#### Teste 4: Exclusão
```
Entrada:
- Excluir serviço ID 2

Resultado Esperado:
Serviço removido da lista
IDs restantes mantêm numeração original
Ponteiros da lista duplamente encadeada corretos
```

### Casos Extremos

#### Lista Vazia
- Inserir primeiro elemento
- Tentar atualizar/excluir em lista vazia
- Filtros em lista vazia

#### Lista com Um Elemento
- Excluir único elemento
- Inserir segundo elemento com prioridades diferentes

#### Entrada Inválida
- Campos vazios
- IDs inexistentes
- Caracteres especiais em descrição

---

## 🔧 Troubleshooting

### Problemas Comuns

#### Erro de Compilação: GTK+ não encontrado
```bash
# Erro
Package gtk+-3.0 was not found

# Solução
sudo apt-get install libgtk-3-dev pkg-config
```

#### Erro de Execução: Segmentation Fault
```bash
# Causas possíveis:
1. Ponteiro não inicializado
2. Acesso após free()
3. Lista corrompida

# Debug
gdb ./gerenciador_servicos_gtk
(gdb) run
(gdb) bt    # backtrace do erro
```

#### Interface não aparece
```bash
# Verificar variáveis de ambiente
echo $DISPLAY

# Para WSL2
export DISPLAY=:0
```

#### Vazamento de Memória
```bash
# Verificar com valgrind
valgrind --leak-check=full ./gerenciador_servicos_gtk
```

### Debugging

#### Prints de Debug
```c
#ifdef DEBUG
    printf("DEBUG: Inserindo serviço ID %d\n", novoServico->id);
    printf("DEBUG: Lista atual: %p\n", listaDeServicos);
#endif
```

#### Compilação com Debug
```bash
gcc -DDEBUG -g gerenciador_servicos_gtk.c -o debug_version `pkg-config --cflags --libs gtk+-3.0`
```

---

## 📈 Otimizações Futuras

### Performance
- **Hash Table**: Para busca O(1) por ID
- **Árvore Balanceada**: Para inserção/busca O(log n)
- **Pool de Memória**: Reduzir overhead de malloc/free

### Funcionalidades
- **Persistência**: Salvar/carregar de arquivo
- **Undo/Redo**: Desfazer operações
- **Busca Textual**: Filtro por descrição
- **Ordenação**: Por data, status, etc.

### Interface
- **Temas**: Dark/Light mode
- **Atalhos**: Keyboard shortcuts
- **Drag & Drop**: Reorganizar prioridades
- **Exportação**: PDF, CSV, etc.

---

## 👥 Contribuidores

### Desenvolvimento
- **Leonardo Bora** - Arquitetura e implementação técnica
- **Luan Constâncio** - Interface e testes

### Orientação Acadêmica
- **Prof. Fabio Bettio** - Disciplina Estrutura de Dados I
- **Curso ADS** - Análise e Desenvolvimento de Sistemas

---

*Documentação gerada em: 2024*  
*Versão: 2.0*  
*Última atualização: Dezembro 2024*