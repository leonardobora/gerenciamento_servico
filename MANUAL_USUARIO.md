# 📖 Manual do Usuário - Sistema de Gerenciamento de Serviços

## 🎯 Bem-vindo ao Sistema de Gerenciamento de Serviços!

Este manual irá guiá-lo através de todas as funcionalidades do sistema, desde a instalação até o uso avançado. O sistema foi desenvolvido para facilitar o gerenciamento de serviços organizados por prioridade de forma intuitiva e eficiente.

---

## 📋 Índice
1. [Introdução](#introdução)
2. [Instalação e Configuração](#instalação-e-configuração)
3. [Iniciando o Sistema](#iniciando-o-sistema)
4. [Interface Principal](#interface-principal)
5. [Funcionalidades Básicas](#funcionalidades-básicas)
6. [Funcionalidades Avançadas](#funcionalidades-avançadas)
7. [Filtros e Pesquisa](#filtros-e-pesquisa)
8. [Dicas e Truques](#dicas-e-truques)
9. [Solução de Problemas](#solução-de-problemas)
10. [Perguntas Frequentes](#perguntas-frequentes)

---

## 🚀 Introdução

### O que é o Sistema de Gerenciamento de Serviços?
O Sistema de Gerenciamento de Serviços é uma aplicação desktop desenvolvida em C com interface gráfica GTK+ que permite organizar e gerenciar tarefas ou serviços de forma prioritizada e eficiente.

### Principais Características:
- ✅ **Organização Automática**: Serviços organizados automaticamente por prioridade
- ✅ **Interface Intuitiva**: Fácil de usar, não requer treinamento
- ✅ **Filtros Dinâmicos**: Visualize apenas o que precisa
- ✅ **Contadores em Tempo Real**: Acompanhe o progresso instantaneamente
- ✅ **Validações Inteligentes**: Previne erros de entrada
- ✅ **Confirmações de Segurança**: Protege contra ações acidentais

### Para quem é destinado?
- **Gestores de TI**: Organizar tarefas de manutenção e suporte
- **Coordenadores de Projeto**: Gerenciar entregas e marcos
- **Estudantes**: Organizar atividades acadêmicas
- **Profissionais**: Qualquer pessoa que precise priorizar tarefas

---

## ⚙️ Instalação e Configuração

### Requisitos do Sistema
- **Sistema Operacional**: Linux (Ubuntu, Debian, CentOS, Fedora) ou WSL2
- **Memória RAM**: Mínimo 512MB disponível
- **Espaço em Disco**: 50MB livres
- **Dependências**: GTK+ 3.0, GCC

### Instalação das Dependências

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev pkg-config
```

#### CentOS/RHEL:
```bash
sudo yum install gcc gtk3-devel pkgconfig
```

#### Fedora:
```bash
sudo dnf install gcc gtk3-devel pkgconfig
```

### Compilação do Sistema
1. **Baixe ou clone o código fonte**
2. **Abra o terminal na pasta do projeto**
3. **Execute o comando de compilação**:
```bash
gcc gerenciador_servicos_gtk.c -o gerenciador_servicos_gtk `pkg-config --cflags --libs gtk+-3.0`
```

### Verificação da Instalação
```bash
./gerenciador_servicos_gtk
```
Se a interface gráfica aparecer, a instalação foi bem-sucedida! 🎉

---

## 🏁 Iniciando o Sistema

### Primeira Execução
1. **Abra o terminal**
2. **Navegue até a pasta do projeto**
3. **Execute o programa**:
```bash
./gerenciador_servicos_gtk
```

### O que esperar na primeira vez?
- Interface gráfica limpa e organizada
- Lista de serviços vazia
- Contadores zerados
- Todos os filtros em "Todos/Todas"

---

## 🖥️ Interface Principal

### Layout Geral
A interface é dividida em seções funcionais para facilitar o uso:

```
┌─────────────────────────────────────────────┐
│          TÍTULO DO SISTEMA                  │
├─────────────────────────────────────────────┤
│         ADICIONAR SERVIÇO                   │
├─────────────────────────────────────────────┤
│    ATUALIZAR STATUS  │  EXCLUIR SERVIÇO    │
├─────────────────────────────────────────────┤
│         FILTROS E AÇÕES                     │
├─────────────────────────────────────────────┤
│            CONTADORES                       │
├─────────────────────────────────────────────┤
│         LISTA DE SERVIÇOS                   │
└─────────────────────────────────────────────┘
```

### Elementos da Interface

#### 1. Cabeçalho
- **Título**: "Sistema de Gerenciamento de Serviços"
- **Créditos**: "Desenvolvido por: Leonardo Bora e Luan Constancio"

#### 2. Seção Adicionar Serviço
- **Campo Descrição**: Digite o nome do serviço
- **Prioridade**: Escolha entre Alta, Média ou Baixa
- **Status**: Defina o estado inicial (Pendente, Em Execução, Concluído)
- **Botão Adicionar**: Confirma a criação do serviço

#### 3. Seções de Operações
- **Atualizar Status**: Modifica o estado de um serviço existente
- **Excluir Serviço**: Remove um serviço da lista

#### 4. Filtros e Ações
- **Filtros**: Por status e prioridade
- **Ações**: Limpar todos os serviços e ver informações técnicas

#### 5. Contadores
- **Total**: Número total de serviços
- **Por Status**: Quantidade de cada tipo (Pendente, Em Execução, Concluído)

#### 6. Lista Principal
- **Tabela**: Visualização organizada dos serviços
- **Colunas**: ID, Descrição, Prioridade, Status
- **Ordenação**: Automática por prioridade (Alta → Média → Baixa)

---

## 🔧 Funcionalidades Básicas

### 1. Adicionando seu Primeiro Serviço

#### Passo a Passo:
1. **Digite a descrição** no campo "Descrição"
   - Exemplo: "Backup do servidor principal"
   
2. **Selecione a prioridade**:
   - **Alta**: Para tarefas urgentes e críticas
   - **Média**: Para tarefas importantes mas não urgentes
   - **Baixa**: Para tarefas de rotina e manutenção
   
3. **Escolha o status inicial**:
   - **Pendente**: Tarefa ainda não iniciada
   - **Em Execução**: Tarefa em andamento
   - **Concluído**: Tarefa já finalizada
   
4. **Clique em "Adicionar Serviço"**

#### ✅ Resultado:
- Serviço aparece na lista principal
- Contadores são atualizados automaticamente
- Lista se reorganiza por prioridade

#### ⚠️ Validações:
- Campo descrição não pode estar vazio
- Prioridade e status devem ser selecionados
- Mensagem de erro aparece se algo estiver incorreto

### 2. Visualizando Serviços

#### Lista Principal:
A lista mostra todos os serviços ordenados automaticamente:
- **Primeiro**: Serviços de prioridade ALTA
- **Segundo**: Serviços de prioridade MÉDIA  
- **Terceiro**: Serviços de prioridade BAIXA

#### Informações Mostradas:
- **ID**: Número único sequencial
- **Descrição**: Nome/descrição do serviço
- **Prioridade**: Alta, Média ou Baixa
- **Status**: Pendente, Em Execução ou Concluído

### 3. Atualizando Status de Serviços

#### Quando Usar:
- Quando iniciar trabalho em uma tarefa pendente
- Quando concluir uma tarefa em execução
- Para corrigir status incorretos

#### Passo a Passo:
1. **Identifique o ID** do serviço na lista principal
2. **Digite o ID** no campo "ID do Serviço"
3. **Selecione o novo status** no dropdown
4. **Clique em "Atualizar"**

#### Exemplo Prático:
```
Cenário: Iniciar trabalho no serviço "Backup do servidor"
ID: 1
Status Atual: Pendente
Novo Status: Em Execução

Ação: 
- Digite "1" no campo ID
- Selecione "Em Execução"
- Clique "Atualizar"
```

### 4. Excluindo Serviços

#### Quando Usar:
- Serviços cancelados ou desnecessários
- Tarefas duplicadas
- Limpeza da lista

#### Passo a Passo:
1. **Identifique o ID** do serviço a ser removido
2. **Digite o ID** no campo "ID do Serviço" (seção exclusão)
3. **Clique em "Excluir"**
4. **Confirme a ação** na janela que aparece

#### ⚠️ Cuidado:
- **Ação irreversível**: Serviço será removido permanentemente
- **Confirmação obrigatória**: Sistema sempre pergunta antes de excluir
- **ID não reutilizado**: Números de ID nunca se repetem

---

## 🎯 Funcionalidades Avançadas

### 1. Sistema de Filtros

#### Filtro por Status
Permite visualizar apenas serviços com status específico:

- **"Todos"**: Mostra todos os serviços (padrão)
- **"Pendente"**: Apenas tarefas não iniciadas
- **"Em Execução"**: Apenas tarefas em andamento
- **"Concluído"**: Apenas tarefas finalizadas

#### Filtro por Prioridade
Permite focar em prioridades específicas:

- **"Todas"**: Mostra todas as prioridades (padrão)
- **"Alta"**: Apenas serviços críticos
- **"Média"**: Apenas prioridade intermediária
- **"Baixa"**: Apenas tarefas de rotina

#### Combinando Filtros
Os filtros funcionam em conjunto:

**Exemplo**: 
- Status: "Em Execução" + Prioridade: "Alta"
- **Resultado**: Apenas tarefas críticas em andamento

### 2. Contadores Inteligentes

#### O que Mostram:
- **Total**: Número absoluto de serviços cadastrados
- **Pendentes**: Tarefas aguardando início
- **Em Execução**: Tarefas em andamento
- **Concluídos**: Tarefas finalizadas

#### Comportamento:
- **Atualização Automática**: Mudam instantaneamente com operações
- **Valores Reais**: Sempre refletem o estado atual completo
- **Independem de Filtros**: Mostram totais, não apenas itens visíveis

### 3. Limpeza Total do Sistema

#### Para que Serve:
- Reiniciar sistema do zero
- Remover todos os serviços de uma vez
- Preparar para novo projeto/período

#### Como Usar:
1. **Clique em "🗑️ Limpar Todos"**
2. **Confirme a ação** (sistema pergunta duas vezes)
3. **Sistema reseta**: Lista vazia, contadores zerados, IDs resetados

#### ⚠️ Atenção:
- **Irreversível**: Todos os serviços são perdidos permanentemente
- **Reset completo**: Próximo serviço terá ID = 1
- **Dupla confirmação**: Sistema protege contra cliques acidentais

### 4. Modal Informativo sobre Arquitetura

#### Acesso:
- Clique no botão "ℹ️ Arquitetura"

#### Conteúdo:
- Explicação detalhada sobre estruturas de dados
- Informações técnicas sobre listas duplamente encadeadas
- Análise de complexidade algorítmica
- Vantagens da implementação
- Informações educativas para estudantes

#### Para quem é útil:
- **Estudantes**: Entender conceitos de estrutura de dados
- **Desenvolvedores**: Ver implementação técnica
- **Curiosos**: Aprender sobre funcionamento interno

---

## 🔍 Filtros e Pesquisa

### Estratégias de Uso dos Filtros

#### 1. Gestão Diária
**Manhã** - Filtro: Status "Pendente"
- Veja todas as tarefas do dia
- Planeje prioridades
- Comece pelos itens de prioridade "Alta"

**Durante o Dia** - Filtro: Status "Em Execução"
- Acompanhe progresso
- Verifique o que está em andamento
- Gerencie sobrecarga

**Final do Dia** - Filtro: Status "Concluído"
- Revise realizações
- Celebrate conquistas
- Prepare relatório

#### 2. Gestão por Prioridade
**Foco Crítico** - Filtro: Prioridade "Alta"
- Apenas tarefas urgentes
- Máxima concentração
- Resolução rápida

**Planejamento** - Filtro: Prioridade "Média"
- Tarefas importantes
- Planejamento de médio prazo
- Desenvolvimento contínuo

**Manutenção** - Filtro: Prioridade "Baixa"
- Atividades de rotina
- Quando tempo disponível
- Prevenção de problemas

#### 3. Combinações Estratégicas

**🔥 Emergências**: Alta + Em Execução
- Monitorar crises em andamento
- Garantir resolução prioritária

**📋 Planejamento**: Média + Pendente  
- Próximas tarefas importantes
- Sequenciamento de atividades

**✅ Produtividade**: Todas + Concluído
- Revisão de conquistas
- Motivação e acompanhamento

---

## 💡 Dicas e Truques

### 1. Convenções de Nomenclatura

#### Descrições Eficazes:
```
✅ BOM: "Backup servidor DB01 - mensal"
❌ RUIM: "backup"

✅ BOM: "Correção bug login - módulo auth"  
❌ RUIM: "bug"

✅ BOM: "Atualizar documentação API v2.0"
❌ RUIM: "docs"
```

#### Estrutura Sugerida:
**[Ação] + [Objeto] + [Detalhes/Contexto]**

### 2. Uso Inteligente de Prioridades

#### Prioridade ALTA:
- **Emergências**: Sistemas fora do ar
- **Crítico**: Impacto em produção
- **Urgente**: Deadline hoje
- **Bloqueante**: Impede outras tarefas

#### Prioridade MÉDIA:
- **Importante**: Necessário mas não urgente
- **Planejado**: Parte do roadmap
- **Melhorias**: Otimizações significativas
- **Preventivo**: Evita problemas futuros

#### Prioridade BAIXA:
- **Manutenção**: Limpeza e organização
- **Opcional**: Nice to have
- **Aprendizado**: Estudos e testes
- **Documentação**: Atualização de manuais

### 3. Fluxo de Trabalho Recomendado

#### Início do Dia:
1. **Revisar pendências**: Filtro "Pendente"
2. **Priorizar**: Focar primeiro em "Alta"
3. **Planejar**: Estimar tempo necessário
4. **Começar**: Atualizar para "Em Execução"

#### Durante Execução:
1. **Foco**: Usar filtros para concentração
2. **Atualizar**: Mudar status conforme progresso
3. **Documentar**: Descrições claras
4. **Ajustar**: Repriorizar se necessário

#### Final da Tarefa:
1. **Concluir**: Atualizar para "Concluído"
2. **Verificar**: Revisar qualidade
3. **Celebrar**: Reconhecer conquista
4. **Próxima**: Passar para próxima prioridade

### 4. Organização por Contexto

#### Projetos Diferentes:
Use prefixos nas descrições:
- **"[PROJ-A] Implementar autenticação"**
- **"[PROJ-B] Correção de bugs"**
- **"[MANUT] Backup semanal"**

#### Tipos de Tarefa:
- **"[DEV] Desenvolvimento nova feature"**
- **"[BUG] Correção erro página login"**
- **"[DOC] Atualizar manual usuário"**
- **"[TEST] Testes unitários módulo X"**

---

## 🛠️ Solução de Problemas

### Problemas Comuns e Soluções

#### 1. Interface não Aparece

**Sintomas**: Comando executa mas janela não abre

**Possíveis Causas**:
- Variáveis de ambiente não configuradas (WSL2)
- GTK+ não instalado corretamente
- Display não configurado

**Soluções**:
```bash
# Para WSL2
export DISPLAY=:0

# Verificar instalação GTK+
pkg-config --modversion gtk+-3.0

# Reinstalar dependências
sudo apt install --reinstall libgtk-3-dev
```

#### 2. Erro de Compilação

**Sintomas**: Mensagens de erro durante compilação

**Erro Comum**:
```
Package gtk+-3.0 was not found
```

**Solução**:
```bash
# Instalar dependências
sudo apt update
sudo apt install libgtk-3-dev pkg-config

# Verificar instalação
pkg-config --cflags gtk+-3.0
```

#### 3. Interface Congela

**Sintomas**: Botões não respondem, interface trava

**Possíveis Causas**:
- Loop infinito em operação
- Problema de memória
- Corrupção de dados

**Soluções**:
1. **Fechar aplicação**: Ctrl+C no terminal ou fechar janela
2. **Reiniciar**: Executar novamente
3. **Verificar logs**: Observar mensagens no terminal

#### 4. Serviços Desaparecem

**Sintomas**: Lista fica vazia inesperadamente

**Possíveis Causas**:
- Filtros ativos ocultando serviços
- Limpeza acidental
- Corrupção de memória

**Soluções**:
1. **Verificar filtros**: Definir para "Todos/Todas"
2. **Reiniciar aplicação**: Dados são perdidos entre sessões
3. **Adicionar novamente**: Sistema não salva dados permanentemente

#### 5. Erro de Memória

**Sintomas**: Aplicação fecha inesperadamente

**Soluções**:
```bash
# Verificar memória disponível
free -h

# Executar com debug (se disponível)
gdb ./gerenciador_servicos_gtk
```

### Diagnóstico Avançado

#### Verificação do Sistema:
```bash
# Verificar versão GTK+
pkg-config --modversion gtk+-3.0

# Verificar bibliotecas
ldd ./gerenciador_servicos_gtk

# Verificar display (WSL2)
echo $DISPLAY
```

#### Logs de Debug:
```bash
# Executar com output detalhado
./gerenciador_servicos_gtk 2>&1 | tee debug.log
```

---

## ❓ Perguntas Frequentes

### Funcionalidades

**P: Os dados são salvos quando fecho o programa?**
R: Não, atualmente o sistema não salva dados automaticamente. Todos os serviços são perdidos quando a aplicação é fechada. Isso é uma limitação da versão atual.

**P: Posso mudar a prioridade de um serviço após criá-lo?**
R: Não na versão atual. Para alterar prioridade, você precisa excluir o serviço e criar novamente com a prioridade desejada.

**P: Existe limite de serviços que posso criar?**
R: Teoricamente não há limite, apenas a memória disponível do sistema. Na prática, o sistema funciona bem com centenas de serviços.

**P: Posso usar acentos e caracteres especiais nas descrições?**
R: Sim, o sistema suporta UTF-8, incluindo acentos e caracteres especiais do português.

### Uso Prático

**P: Como organizar serviços de múltiplos projetos?**
R: Use prefixos na descrição como "[PROJETO-A]", "[MANUTENÇÃO]", etc. Combine com filtros para visualizar apenas um contexto.

**P: Qual a melhor forma de usar as prioridades?**
R: 
- **Alta**: Apenas para urgências reais (máximo 20% dos serviços)
- **Média**: Tarefas importantes do dia a dia (60-70%)
- **Baixa**: Manutenção e atividades opcionais (10-20%)

**P: Como acompanhar produtividade?**
R: Use os contadores e filtro "Concluído" para ver realizações. Compare totais diários/semanais.

### Técnicas

**P: Por que a lista se reorganiza automaticamente?**
R: O sistema usa uma estrutura de dados (lista duplamente encadeada) que mantém ordenação por prioridade automaticamente para eficiência.

**P: Posso executar em Windows?**
R: Diretamente não, mas funciona perfeitamente no WSL2 (Windows Subsystem for Linux).

**P: O sistema funciona offline?**
R: Sim, é uma aplicação desktop que não requer internet.

### Problemas

**P: O que fazer se a interface não aparecer?**
R: Verifique se o GTK+ está instalado e, no WSL2, configure a variável DISPLAY. Veja seção "Solução de Problemas".

**P: Posso recuperar serviços excluídos acidentalmente?**
R: Não, exclusões são permanentes. Sempre confirme antes de excluir.

**P: Por que alguns filtros não mostram resultados?**
R: Verifique se existem serviços com as características filtradas. Lembre-se que filtros são aplicados em conjunto.

---

## 🎓 Aprendizado e Melhores Práticas

### Para Iniciantes

#### Primeiros Passos:
1. **Comece simples**: Adicione 2-3 serviços básicos
2. **Experimente filtros**: Veja como funcionam
3. **Pratique atualizações**: Mude status conforme progride
4. **Use contadores**: Observe mudanças em tempo real

#### Desenvolvendo Hábitos:
- **Descrições claras**: Pense no "eu do futuro"
- **Priorização realista**: Nem tudo é urgente
- **Atualização frequente**: Mantenha status atualizados
- **Revisão regular**: Use filtros para acompanhar progresso

### Para Usuários Avançados

#### Técnicas Avançadas:
- **Codificação por cores** (mental): Associe prioridades a urgência
- **Batching**: Agrupe tarefas similares
- **Time-boxing**: Estime e controle tempo por tarefa
- **Retrospectivas**: Use filtro "Concluído" para análises

#### Integração com Outros Métodos:
- **GTD (Getting Things Done)**: Use como inbox e sistema de ação
- **Kanban**: Simule colunas com status
- **Pomodoro**: Combine com técnica de tempo focado
- **Scrum**: Organize sprints por período

---

## 📞 Suporte e Contato

### Desenvolvimento
- **Leonardo Bora**: Arquitetura e implementação técnica
- **Luan Constâncio**: Interface e experiência do usuário

### Contexto Acadêmico
- **Disciplina**: Estrutura de Dados I
- **Professor**: Fabio Bettio
- **Curso**: Engenharia de Software

### Contribuições
Este é um projeto acadêmico open-source. Sugestões e melhorias são bem-vindas!

---

**🎉 Parabéns! Você concluiu o manual do usuário.**

Agora você está pronto para usar o Sistema de Gerenciamento de Serviços de forma eficiente e produtiva. Lembre-se: a ferramenta é simples, mas sua eficácia depende de uso consistente e organizado.

**Boa produtividade! 🚀**

---

*Manual criado em: Dezembro 2024*  
*Versão do Sistema: 2.0*  
*Última atualização: Dezembro 2024*