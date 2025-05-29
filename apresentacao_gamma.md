# Sistema de Gerenciamento de Serviços
*Uma implementação moderna de estruturas de dados com interfaces duplas e CI/CD*

**Autores:** Leonardo Bora & Luan Constâncio  
**Disciplina:** Estrutura de Dados I - Prof. Fabio Bettio  
**Curso:** Engenharia de Software  

---

## Agenda da Apresentação (8 min)

1. **Visão Geral do Projeto** (1 min)
2. **Arquitetura e Estruturas de Dados** (2 min)
3. **Interfaces Duplas: CLI + GTK+** (2 min)
4. **Integração Contínua (CI/CD)** (1.5 min)
5. **Demonstração e Resultados** (1 min)
6. **Perguntas & Respostas** (0.5 min)

---

## 1. Visão Geral do Projeto

### 🎯 Objetivo
Desenvolver um sistema de gerenciamento de serviços que demonstre:
- Implementação prática de **listas duplamente encadeadas**
- **Duas interfaces** de usuário (CLI + GUI)
- **DevOps** moderno com GitHub Actions
- **Qualidade de código** e boas práticas

### 📋 Funcionalidades Core
- ✅ **Adicionar** serviços com prioridades (Alta/Média/Baixa)
- ✅ **Atualizar** status (Pendente/Em Execução/Concluído)
- ✅ **Excluir** serviços com confirmação
- ✅ **Filtrar** por status e prioridade
- ✅ **Visualizar** lista ordenada automaticamente

---

## 2. Arquitetura e Estruturas de Dados

### 🔗 Lista Duplamente Encadeada
```c
typedef struct Servico {
    int id;
    char descricao[100];
    char status;      // 'P', 'E', 'C'
    char prioridade;  // 'A', 'M', 'B'
    struct Servico *ant;
    struct Servico *prox;
} Servico;
```

### ⚡ Complexidades Algorítmicas
| Operação | Complexidade | Justificativa |
|----------|-------------|---------------|
| **Inserção** | O(n) | Percorre até encontrar posição por prioridade |
| **Busca** | O(n) | Busca linear por ID |
| **Remoção** | O(n) + O(1) | Localiza + remove ponteiros |
| **Atualização** | O(n) | Busca + modificação |

### 🎯 Vantagens da Implementação
- **Ordenação automática** por prioridade
- **Navegação bidirecional** eficiente
- **Inserção/remoção** otimizada após localização
- **Uso de memória** dinâmico e eficiente

---

## 3. Interfaces Duplas: CLI + GTK+

### 🖥️ Interface CLI (Terminal)
- **Menu interativo** tradicional
- **Validação de entrada** robusta
- **Feedback** em tempo real
- **Portabilidade** total (Windows/Linux)

```bash
=== SISTEMA DE GERENCIAMENTO DE SERVIÇOS ===
1. Adicionar Serviço
2. Atualizar Status do Serviço
3. Exibir Serviços
4. Créditos
5. Sair
```

### 🎨 Interface GTK+ (Gráfica)
- **Design moderno** e intuitivo
- **Filtros visuais** por status/prioridade
- **Contadores dinâmicos** de serviços
- **Confirmações** para operações críticas
- **Dialog informativo** sobre arquitetura

### 🔄 Arquiteturas Compartilhadas
- **Mesmo core** de estruturas de dados
- **Funções reutilizadas** entre interfaces
- **Consistência** de comportamento
- **Manutenibilidade** simplificada

---

## 4. Integração Contínua (CI/CD)

### 🤖 GitHub Actions Workflow
**Trigger:** A cada `git push` ou Pull Request

```yaml
jobs:
  build-and-test:
    - Instala dependências (gcc, GTK+)
    - Compila versão CLI
    - Compila versão GTK+
    - Valida executáveis
    - Upload de artifacts
  
  documentation-check:
    - Verifica arquivos de documentação
    - Valida Makefile
```

### 📊 Benefícios Demonstrados
- ✅ **Build automático** em ~50 segundos
- ✅ **Binários prontos** para download
- ✅ **Feedback imediato** sobre problemas
- ✅ **Qualidade garantida** em cada commit
- ✅ **Colaboração facilitada** com status visual

### 🎯 DevOps na Prática
**Antes:** "Funciona na minha máquina" 🤷‍♂️  
**Depois:** Validação automática em ambiente limpo ✅

---

## 5. Demonstração e Resultados

### 📈 Métricas do Projeto
- **2 interfaces** funcionais (CLI + GTK+)
- **15+ funcionalidades** implementadas
- **100% build success** no GitHub Actions
- **~1500 linhas** de código C
- **Documentação completa** (README, MANUAL, DOCS)

### 🎮 Demo Highlights
1. **Adicionar serviços** com diferentes prioridades
2. **Ordenação automática** por prioridade
3. **Filtros dinâmicos** na interface GTK+
4. **Contadores em tempo real**
5. **GitHub Actions** em funcionamento

### 🔍 Aspectos Técnicos Demonstrados
- **Gerenciamento de memória** adequado
- **Validação de entrada** robusta
- **Interface responsiva** com GTK+
- **Integração contínua** funcional
- **Estrutura de dados** eficiente

---

## 6. Conclusões e Aprendizados

### 🎓 Competências Desenvolvidas
- **Estruturas de dados** avançadas na prática
- **Programação em C** com duas interfaces
- **DevOps** e automação com GitHub Actions
- **Design de software** modular e reutilizável
- **Documentação técnica** profissional

### 🚀 Diferenciais do Projeto
- **Duas interfaces** completas
- **CI/CD** implementado
- **Código open-source** disponível
- **Documentação completa**
- **Boas práticas** de desenvolvimento

### 🔮 Próximos Passos
- **Persistência** em arquivo/banco de dados
- **Interface web** com frameworks modernos
- **API REST** para integração
- **Testes unitários** automatizados
- **Deploy automatizado**

---

## Recursos do Projeto

### 🔗 Links Importantes
- **GitHub:** https://github.com/leonardobora/gerenciamento_servico
- **Actions:** Build automático a cada commit
- **Releases:** Binários compilados disponíveis
- **Documentação:** README, Manual do Usuário, Docs Técnicas

### 📚 Estrutura de Arquivos
```
gerenciamento_servico/
├── gerenciador_servicos.c      # Versão CLI
├── gerenciador_servicos_gtk.c  # Versão GTK+
├── .github/workflows/          # GitHub Actions
├── README.md                   # Documentação principal
├── MANUAL_USUARIO.md          # Manual do usuário
├── DOCUMENTACAO_TECNICA.md    # Docs técnicas
└── CLAUDE.md                  # Instruções para IA
```

---

## Perguntas & Respostas

### ❓ Perguntas Esperadas

**P: Por que lista duplamente encadeada?**  
**R:** Permite navegação bidirecional eficiente e facilita inserção ordenada por prioridade.

**P: Vantagem de ter duas interfaces?**  
**R:** Demonstra versatilidade técnica e atende diferentes tipos de usuários.

**P: Benefício do GitHub Actions?**  
**R:** Garante qualidade, automatiza builds e facilita colaboração.

**P: Complexidade do projeto?**  
**R:** Equilibra simplicidade didática com práticas profissionais reais.

---

## Obrigado!

### 👥 Equipe
**Leonardo Bora** - Líder de Desenvolvimento  
**Luan Constâncio** - Desenvolvedor  

### 🙏 Agradecimentos
**Professor Fabio Bettio** - Orientação técnica  
**Estrutura de Dados I** - Base conceitual sólida

**GitHub:** leonardobora/gerenciamento_servico  
**Tempo de apresentação:** 8 minutos ⏱️