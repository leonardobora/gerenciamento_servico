# Roteiro de Apresentação - Sistema de Gerenciamento de Serviços

## Slide 1: Apresentação dos Integrantes
- **Leonardo Bora** - Líder do Projeto
  - GitHub: [github.com/leonardobora](https://github.com/leonardobora)
- **Luan Constâncio** - Desenvolvedor
  - GitHub: [github.com/luanconstancio](https://github.com/luanconstancio)

## Slide 2: Contextualização e Objetivos do Projeto
### Objetivo Principal
Desenvolver um sistema de gerenciamento de serviços em linguagem C que permite:
- Cadastrar serviços com diferentes níveis de prioridade
- Atualizar status dos serviços
- Visualizar lista ordenada por prioridade
- Gerenciar memoria de forma eficiente

### Tecnologias Utilizadas
- Linguagem C
- Estrutura de dados: Lista duplamente ligada
- Compilação com GCC

## Slide 3: Cronograma e Status do Projeto

### ✅ Funcionalidades Concluídas
- **Estrutura de dados**: Lista duplamente ligada implementada
- **Inserção por prioridade**: Serviços ordenados automaticamente (Alta → Média → Baixa)
- **Sistema de IDs**: Geração automática e sequencial
- **Menu interativo**: Interface de usuário funcional
- **Atualização de status**: Modificação do estado dos serviços
- **Exibição formatada**: Lista tabular com informações completas
- **Gerenciamento de memória**: Liberação adequada de recursos

### 🔄 Melhorias Identificadas
- **Validação de ID**: Verificar existência antes de atualizar status
- **Sistema de créditos**: Adicionar informações acadêmicas

### 📊 Status Geral: **85% Concluído**
- Core do sistema: **100%** ✅
- Interface do usuário: **100%** ✅
- Validações de entrada: **80%** 🔄
- Documentação: **90%** ✅

## Slide 4: Demonstração Funcional

### Fluxo de Demonstração
1. **Compilação e execução**
   ```bash
   gcc gerenciador_servicos.c -o gerenciador_servicos
   ./gerenciador_servicos
   ```

2. **Cadastro de serviços** (Opção 1)
   - Demonstrar inserção com diferentes prioridades
   - Mostrar ordenação automática

3. **Visualização da lista** (Opção 3)
   - Exibir tabela formatada
   - Mostrar ordenação por prioridade

4. **Atualização de status** (Opção 2)
   - Demonstrar mudança de status
   - Mostrar validação de entrada

5. **Encerramento do sistema** (Opção 0)
   - Demonstrar liberação de memória

### Casos de Teste
- Serviço de alta prioridade: "Backup crítico do servidor"
- Serviço de média prioridade: "Atualização de software"
- Serviço de baixa prioridade: "Limpeza de arquivos temporários"

## Slide 5: Créditos e Informações Acadêmicas

### Contexto Acadêmico
- **Disciplina**: Estrutura de Dados I
- **Professor Orientador**: Fabio Bettio
- **Curso**: Engenharia de Software

### Equipe de Desenvolvimento
- **Leonardo Bora** (Líder)
  - Responsável pela arquitetura e coordenação
  - GitHub: [github.com/leonardobora](https://github.com/leonardobora)
- **Luan Constâncio** (Desenvolvedor)
  - Implementação e testes
  - GitHub: [github.com/luanconstancio](https://github.com/luanconstancio)

### Tecnologias e Conceitos Aplicados
- Estruturas de dados dinâmicas
- Ponteiros e gerenciamento de memória
- Algoritmos de ordenação
- Programação modular em C