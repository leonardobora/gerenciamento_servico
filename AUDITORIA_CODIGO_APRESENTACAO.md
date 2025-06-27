# � Guia de Apresentação - Sistema de Gerenciamento de Serviços
*Roteiro de Apoio para Apresentação Final*

**Data:** 17 de Junho de 2025  
**Desenvolvedores:** Leonardo Bora & Luan Constâncio  
**Disciplina:** Estruturas de Dados I  
**Professor:** Fabio Bettio  

---

## 🎯 **Abertura da Apresentação**

### 💬 **Fala Inicial Sugerida:**
> "Professor, desde a última entrega, focamos em estabilizar o sistema que já atendia aos requisitos propostos. Entendemos que o projeto estava suficiente para demonstrar a aplicação prática das estruturas de dados estudadas na disciplina."

### � **Resumo Executivo**
- **Estrutura Principal:** Lista Duplamente Encadeada
- **Linguagem:** C puro + interface GTK+
- **Funcionalidades:** CRUD completo com ordenação automática
- **Persistência:** Sistema de arquivos CSV implementado
- **Status:** Funcional e estável

---

## 🔧 **Demonstração Prática**

### � **O que mostrar funcionando:**
1. **Adicionar serviços** com diferentes prioridades
2. **Visualizar ordenação automática** (Alta → Média → Baixa)
3. **Atualizar status** de serviços existentes
4. **Excluir serviços** com confirmação
5. **Filtros dinâmicos** por status e prioridade
6. **Persistência** - fechar e reabrir programa

### 💡 **Pontos a destacar durante demo:**
- "Observe como a lista mantém a ordenação automaticamente"
- "Os dados são salvos automaticamente em arquivo CSV"
- "Interface dupla: linha de comando e gráfica"

---

## ❓ **Possíveis Perguntas do Professor - Respostas Preparadas**

### 🏗️ **"Por que escolheram Lista Duplamente Encadeada?"**
**Resposta:**
- "Precisávamos de inserção ordenada por prioridade"
- "Navegação bidirecional facilita operações de busca e remoção"
- "Memória dinâmica - cresce conforme necessário"
- "Complexidade O(n) para inserção é aceitável para o contexto"

### 💾 **"Como implementaram o gerenciamento de memória?"**
**Resposta:**
- "Verificação de malloc() antes de usar ponteiros"
- "Função liberaMemoria() percorre toda lista e faz free()"
- "Ponteiros sempre inicializados como NULL"
- "Nenhum vazamento de memória detectado"

### ⚡ **"Qual a complexidade dos algoritmos principais?"**
**Resposta:**
```
Inserção:     O(n) - precisa encontrar posição por prioridade
Busca:        O(n) - busca linear por ID
Remoção:      O(n) + O(1) - localizar + ajustar ponteiros
Atualização:  O(n) - busca + modificação
```

### 🔧 **"Como funciona a inserção ordenada?"**
**Resposta:** *(mostrar no código)*
```c
// Prioridade: A=3, M=2, B=1
if (novaPrioridadeVal > getPrioridadeValor(listaDeServicos->prioridade)) {
    // Inserir no início (maior prioridade)
} else {
    // Percorrer até encontrar posição correta
    while (atual->prox != NULL && 
           getPrioridadeValor(atual->prox->prioridade) >= novaPrioridadeVal)
}
```

### 💾 **"Como implementaram a persistência?"**
**Resposta:**
- "Arquivo CSV simples: id,descricao,status,prioridade"
- "Salvamento automático após cada operação"
- "Carregamento na inicialização do programa"
- "Tratamento de erros de I/O implementado"

---

## 🎯 **Estrutura de Dados - Explicação Técnica**

### 📋 **Definição da Estrutura:**
```c
typedef struct Servico {
    int id;                    // Chave única
    char descricao[100];       // Descrição textual  
    char status;              // P, E, C
    char prioridade;          // A, M, B
    struct Servico *ant;      // ← Ponteiro anterior
    struct Servico *prox;     // → Ponteiro próximo
} Servico;
```

### 🔗 **Vantagens da Lista Duplamente Encadeada:**
- **Inserção ordenada automática** por prioridade
- **Remoção eficiente** - O(1) após localização
- **Navegação bidirecional** para percorrer lista
- **Uso eficiente de memória** - aloca conforme necessário

### ⚙️ **Operações Principais:**
1. **Inserir:** Encontra posição por prioridade e insere mantendo ordem
2. **Buscar:** Percorre linearmente até encontrar ID
3. **Remover:** Ajusta ponteiros dos nós adjacentes
4. **Atualizar:** Localiza nó e modifica campos in-place

---

## 🎨 **Interface e Usabilidade**

### � **Duas Interfaces Implementadas:**
1. **CLI (Console):** Interface tradicional de linha de comando
2. **GTK+:** Interface gráfica moderna com widgets

### 🎯 **Funcionalidades da Interface:**
- Formulários para entrada de dados
- Validação em tempo real
- Filtros dinâmicos por status/prioridade  
- Contadores automáticos de serviços
- Confirmações para operações críticas

---

## 💡 **Justificativas Técnicas**

### 🤔 **"Por que não usaram Array/Vetor?"**
- "Arrays têm tamanho fixo, nossa solução é dinâmica"
- "Inserção ordenada em array é O(n) + realocação custosa"
- "Lista encadeada permite inserção O(1) na posição correta"

### 🤔 **"Por que não usaram Árvore/Heap?"**
- "Complexidade desnecessária para o escopo do projeto"
- "Lista atende perfeitamente aos requisitos"
- "Foco era demonstrar estruturas lineares da disciplina"

### 🤔 **"E se precisasse de performance melhor?"**
- "Hash table para busca O(1) por ID"
- "Heap para prioridades se volume fosse muito grande"
- "Mas para o contexto atual, lista é adequada"

---

## 📊 **Métricas Finais**

### ✅ **O que foi entregue:**
- Sistema funcional com todas as operações CRUD
- Interface dupla (CLI + GTK+)
- Persistência de dados implementada
- Gerenciamento de memória seguro
- Código bem estruturado e documentado

### 🎯 **Objetivos Alcançados:**
- ✅ Aplicação prática de estruturas de dados
- ✅ Demonstração de algoritmos de inserção/busca/remoção
- ✅ Projeto completo e funcional
- ✅ Código limpo seguindo boas práticas

---

## � **Encerramento da Apresentação**

### 💬 **Fala Final Sugerida:**
> "Consideramos que o projeto atende completamente aos objetivos da disciplina, demonstrando a aplicação prática das estruturas de dados estudadas. O sistema está funcional, estável e pronto para uso real. Estamos abertos para perguntas sobre implementação ou decisões técnicas."

### � **Agradecimento:**
> "Agradecemos ao Professor Fabio Bettio pela orientação durante o desenvolvimento e estamos disponíveis para esclarecimentos."
