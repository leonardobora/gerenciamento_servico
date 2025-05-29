# Roteiro de Apresentação - Sistema de Gerenciamento de Serviços
## 🎯 Atualização de Status do Projeto

---

## 📋 Divisão de Responsabilidades na Apresentação

### 👨‍💻 Leonardo Bora (Parte Técnica - 8-10 minutos)
- Contextualização e objetivos
- Arquitetura e estruturas de dados
- Implementação técnica detalhada
- Explicação sobre listas duplamente encadeadas
- Análise de complexidade algorítmica

### 👨‍💼 Luan Constâncio (Demo e Funcionalidades - 6-8 minutos)
- Demonstração ao vivo do sistema
- Showcase das funcionalidades
- Interface gráfica GTK
- Casos de uso práticos
- Apresentação do progresso e melhorias

---

## 🎤 **LEONARDO - PARTE 1: Contextualização e Arquitetura (3-4 min)**

### Slide 1: Apresentação da Equipe
**"Boa noite! Eu sou o Leonardo Bora e este é o Luan Constâncio. Hoje vamos apresentar nosso sistema de gerenciamento de serviços desenvolvido em C."**

- **Leonardo Bora** - Líder Técnico do Projeto
  - Foco: Arquitetura, estruturas de dados e implementação
  - GitHub: [github.com/leonardobora](https://github.com/leonardobora)
- **Luan Constâncio** - Desenvolvedor Frontend e Testes
  - Foco: Interface, validações e experiência do usuário
  - GitHub: [github.com/luanconstancio](https://github.com/luanconstancio)

### Slide 2: Objetivos e Evolução do Projeto
**"Nosso projeto evoluiu significativamente desde a concepção inicial. Começamos com um sistema console e hoje temos uma aplicação completa com interface gráfica."**

#### Objetivos Originais ✅
- Sistema de gerenciamento de serviços em C
- Implementação de lista duplamente encadeada
- Ordenação automática por prioridade
- Operações CRUD básicas

#### Evoluções Implementadas 🚀
- Interface gráfica completa com GTK+
- Sistema de filtros dinâmicos
- Contadores em tempo real
- Modal educativo sobre arquitetura
- Validações robustas e UX aprimorada

---

## 🔧 **LEONARDO - PARTE 2: Arquitetura Técnica (4-5 min)**

### Slide 3: Estrutura de Dados - Lista Duplamente Encadeada
**"O coração do nosso sistema é uma lista duplamente encadeada. Vou explicar por que escolhemos essa estrutura e como ela funciona."**

#### Por que Lista Duplamente Encadeada?
```c
struct Servico {
    int id;                    // Identificador único
    char descricao[100];       // Descrição do serviço
    char status;               // P, E, C (Pendente, Em Execução, Concluído)
    char prioridade;           // A, M, B (Alta, Média, Baixa)
    struct Servico *ant;       // Ponteiro para anterior
    struct Servico *prox;      // Ponteiro para próximo
};
```

#### Vantagens da Implementação:
- **Inserção ordenada**: O(n) com ordenação automática por prioridade
- **Navegação bidirecional**: Percorrer lista em ambas direções
- **Remoção eficiente**: O(1) após localizar o nó
- **Flexibilidade**: Inserções e remoções em qualquer posição

### Slide 4: Algoritmos Principais
**"Implementamos algoritmos eficientes para cada operação principal do sistema."**

#### Inserção por Prioridade
```c
int getPrioridadeValor(char p) {
    if (p == 'A') return 3; // Alta
    if (p == 'M') return 2; // Média
    if (p == 'B') return 1; // Baixa
    return 0;
}
```

#### Análise de Complexidade:
- **Inserção**: O(n) - percorre até encontrar posição correta
- **Busca por ID**: O(n) - busca linear
- **Atualização**: O(n) - localiza + O(1) para modificar
- **Remoção**: O(n) para localizar + O(1) para remover
- **Exibição**: O(n) - percorre toda lista

### Slide 5: Tecnologias e Ferramentas
**"Utilizamos um stack tecnológico robusto para desenvolvimento."**

#### Stack Tecnológico:
- **Linguagem Principal**: C (padrão C99)
- **Interface Gráfica**: GTK+ 3.0
- **Compilador**: GCC com flags de otimização
- **Gerenciamento de Memória**: Manual com validações
- **Controle de Versão**: Git/GitHub
- **Ambiente**: Linux/WSL2

#### Ferramentas de Desenvolvimento:
- **Build System**: Makefile personalizado
- **Debugging**: GDB e prints estratégicos
- **Testing**: Casos de teste manuais
- **Documentation**: Markdown e comentários inline

---

## 🎮 **LUAN - PARTE 3: Demonstração e Funcionalidades (6-8 min)**

### Slide 6: Interface Console vs GTK
**"Luan, agora é sua vez! Mostre como evoluímos da interface console para a interface gráfica."**

**LUAN**: *"Obrigado, Leo! Vou mostrar a evolução prática do nosso sistema. Começamos com uma interface console funcional, mas limitada. Hoje temos uma aplicação desktop completa."*

#### Demonstração Prática:
1. **Compilação do Sistema**
   ```bash
   gcc gerenciador_servicos_gtk.c -o gerenciador_servicos_gtk `pkg-config --cflags --libs gtk+-3.0`
   ./gerenciador_servicos_gtk
   ```

2. **Interface Gráfica Completa**
   - Layout profissional e intuitivo
   - Organização em seções funcionais
   - Feedback visual para todas operações

### Slide 7: Funcionalidades Principais - Live Demo
**LUAN**: *"Vou demonstrar cada funcionalidade implementada ao vivo."*

#### 1. Cadastro de Serviços
- **Campo Descrição**: Entrada livre de texto
- **Seleção de Prioridade**: Dropdown (Alta/Média/Baixa)
- **Status Inicial**: Configurável (Pendente/Em Execução/Concluído)
- **Validação**: Campos obrigatórios com mensagens de erro

*Demonstrar: Criar 3-4 serviços com prioridades diferentes*

#### 2. Visualização e Filtros
- **Lista Tabular**: ID, Descrição, Prioridade, Status
- **Filtro por Status**: Todos/Pendente/Em Execução/Concluído
- **Filtro por Prioridade**: Todas/Alta/Média/Baixa
- **Contadores Dinâmicos**: Atualização em tempo real

*Demonstrar: Aplicar diferentes filtros e mostrar contadores*

#### 3. Operações Avançadas
- **Atualização de Status**: Modificar serviços existentes
- **Exclusão Individual**: Com confirmação de segurança
- **Limpeza Total**: Reset completo do sistema
- **Modal Educativo**: Informações sobre arquitetura

*Demonstrar: Atualizar status, excluir serviço, mostrar modal*

### Slide 8: Casos de Uso Reais
**LUAN**: *"Vou demonstrar cenários práticos de uso do sistema."*

#### Cenário 1: Gestão de TI Corporativa
```
- [ALTA] Backup crítico do servidor principal
- [MÉDIA] Atualização do sistema operacional
- [BAIXA] Limpeza de arquivos temporários
```

#### Cenário 2: Gestão de Projetos
```
- [ALTA] Correção de bug crítico em produção
- [MÉDIA] Implementação de nova funcionalidade
- [BAIXA] Atualização de documentação
```

*Demonstrar: Criar estes cenários e mostrar como o sistema organiza por prioridade*

---

## 📊 **LEONARDO - PARTE 4: Progresso e Análise Técnica (2-3 min)**

### Slide 9: Evolução do Projeto
**"Luan mostrou perfeitamente o resultado final. Agora vou apresentar nossa evolução técnica."**

#### Status de Desenvolvimento:
```
✅ Versão 1.0 - Sistema Console (100%)
├── Lista duplamente encadeada implementada
├── Operações CRUD básicas
├── Menu interativo funcional
└── Gerenciamento de memória

✅ Versão 2.0 - Interface GTK (100%)
├── Interface gráfica completa
├── Sistema de filtros dinâmicos
├── Contadores em tempo real
├── Validações robustas
├── Modal educativo
└── Operações avançadas (exclusão, limpeza)
```

#### Métricas do Projeto:
- **Linhas de Código**: ~700 linhas (crescimento de 300%)
- **Funções Implementadas**: 15+ funções modulares
- **Tempo de Desenvolvimento**: 4 semanas
- **Funcionalidades**: 8 principais + 5 auxiliares

### Slide 10: Desafios Técnicos Superados
**"Durante o desenvolvimento, enfrentamos desafios interessantes:"**

#### Principais Desafios:
1. **Gerenciamento de Memória**
   - Vazamentos de memória em operações de remoção
   - Solução: Função dedicada de liberação com validações

2. **Integração GTK+**
   - Complexity de callbacks e gestão de estado
   - Solução: Estrutura modular com widgets globais

3. **Filtros Dinâmicos**
   - Performance em listas grandes
   - Solução: Algoritmo otimizado de filtrage em O(n)

4. **Sincronização de Estado**
   - Manter contadores atualizados com operações
   - Solução: Função centralizada de atualização

---

## 🎯 **AMBOS - PARTE 5: Conclusão e Próximos Passos (2 min)**

### Slide 11: Resultados Alcançados
**LEONARDO**: *"Em resumo, conseguimos criar um sistema robusto e funcional."*

**LUAN**: *"Que demonstra tanto conceitos teóricos quanto aplicação prática."*

#### Objetivos Alcançados ✅:
- ✅ Sistema completo de gerenciamento de serviços
- ✅ Implementação eficiente de lista duplamente encadeada
- ✅ Interface gráfica profissional e intuitiva
- ✅ Operações avançadas com validações
- ✅ Documentação técnica completa
- ✅ Código modular e extensível

### Slide 12: Próximos Passos e Melhorias
**LEONARDO**: *"Identificamos oportunidades de evolução:"*

#### Melhorias Futuras:
- **Persistência de Dados**: Salvar/carregar de arquivo
- **Multi-usuário**: Sistema de autenticação
- **API REST**: Integração com outros sistemas
- **Mobile**: Versão para dispositivos móveis
- **Relatórios**: Geração de estatísticas avançadas

#### Aprendizados:
- Estruturas de dados em contexto real
- Desenvolvimento de interfaces em C
- Gestão de projeto colaborativo
- Debugging e otimização de performance

### Slide 13: Agradecimentos
**AMBOS**: 
- **Professor Fabio Bettio** - Orientação técnica
- **Disciplina Estrutura de Dados I** - Base teórica
- **Curso ADS** - Suporte acadêmico
- **Colegas de Turma** - Feedback e sugestões

**"Obrigado pela atenção! Alguma pergunta?"**

---

## ⏱️ **Cronometragem Sugerida:**
- **Leonardo (Técnico)**: 8-10 minutos
- **Luan (Demo)**: 6-8 minutos  
- **Conclusão (Ambos)**: 2 minutos
- **Perguntas**: 2-3 minutos
- **Total**: 18-23 minutos

---

## 💡 **Dicas de Apresentação:**

### Para Leonardo:
- Foque nos aspectos técnicos e arquiteturais
- Use diagramas quando possível
- Explique o "porquê" das escolhas técnicas
- Mantenha linguagem técnica mas acessível

### Para Luan:
- Demonstre confiança na interface
- Teste todas funcionalidades antes da apresentação
- Prepare cenários interessantes
- Destaque a evolução visual do projeto
- Interaja naturalmente com a interface

### Para Ambos:
- Pratiquem as transições entre partes
- Tenham backup dos arquivos/códigos
- Testem o ambiente de apresentação
- Preparem respostas para possíveis perguntas técnicas