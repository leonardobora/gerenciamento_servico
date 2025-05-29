# Sistema de Gerenciamento de Serviços

Sistema de gerenciamento de serviços desenvolvido em C que oferece duas interfaces: linha de comando tradicional e interface gráfica moderna com GTK+. Permite aos usuários adicionar serviços com níveis de prioridade, atualizar status e visualizar em lista ordenada.

## Funcionalidades

- ✅ Adicionar serviços com diferentes níveis de prioridade (Alta, Média, Baixa)
- ✅ Atualizar status do serviço (Pendente, Em Execução, Concluído)
- ✅ Exibir serviços em tabela formatada
- ✅ Interface de linha de comando tradicional
- ✅ Interface gráfica moderna com GTK+
- ✅ Ordenação automática baseada em prioridade
- ✅ Validação de entrada para IDs inexistentes
- ✅ Gerenciamento adequado de memória

## Como Começar

### Pré-requisitos

#### Windows

Para executar este programa no Windows, você precisa de um compilador C. Aqui estão duas opções:

1. **MinGW (Minimalist GNU for Windows)**
   - Baixe o instalador MinGW de [MinGW.org](https://mingw-w64.org/doku.php/download) ou [MSYS2](https://www.msys2.org/)
   - Execute o instalador e selecione o pacote básico
   - Adicione o diretório bin do MinGW à sua variável de ambiente PATH
   - Verifique a instalação abrindo o Prompt de Comando e digitando: `gcc --version`

2. **Visual Studio Community Edition com ferramentas C/C++**
   - Baixe [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
   - Durante a instalação, selecione a carga de trabalho "Desenvolvimento para desktop com C++"
   - Use o Prompt de Comando do Desenvolvedor para compilar

### Compilação e Execução

#### Windows com MinGW

1. Abra o Prompt de Comando
2. Navegue até o diretório do projeto:
   ```
   cd caminho\para\gerenciamento_servico
   ```
3. Compile o programa:
   ```
   gcc gerenciador_servicos.c -o gerenciador_servicos.exe
   ```
4. Execute o programa:
   ```
   gerenciador_servicos.exe
   ```

#### Windows com Visual Studio

1. Abra o Prompt de Comando do Desenvolvedor para VS
2. Navegue até o diretório do projeto
3. Compile e execute:
   ```
   cl gerenciador_servicos.c
   gerenciador_servicos.exe
   ```

#### Linux

1. Abra o Terminal
2. Navegue até o diretório do projeto
3. Compile:
   ```
   gcc gerenciador_servicos.c -o gerenciador_servicos
   ```
4. Execute:
   ```
   ./gerenciador_servicos
   ```

## Publicando no GitHub

### Configuração Inicial

1. Crie uma conta no GitHub se ainda não tiver uma
2. Instale o Git:
   - Windows: Baixe de [git-scm.com](https://git-scm.com/download/win)
   - Linux: `sudo apt-get install git` (Ubuntu/Debian) ou `sudo yum install git` (RHEL/CentOS)

3. Configure o Git:
   ```
   git config --global user.name "Seu Nome"
   git config --global user.email "seu.email@exemplo.com"
   ```

### Criando um Repositório e Enviando Código

1. Vá para [GitHub](https://github.com/) e crie um novo repositório
   - Clique no "+" no canto superior direito e selecione "New repository"
   - Nomeie como "gerenciamento_servico" ou seu nome preferido
   - Escolha visibilidade pública ou privada
   - Clique em "Create repository"

2. Inicialize o Git na pasta local do projeto (use Git Bash no Windows ou Terminal no Linux):
   ```
   cd /caminho/para/gerenciamento_servico
   git init
   ```

3. Adicione seus arquivos ao Git:
   ```
   git add .
   ```

4. Faça commit dos seus arquivos:
   ```
   git commit -m "Commit inicial: Sistema de Gerenciamento de Serviços"
   ```

5. Vincule seu repositório local ao GitHub:
   ```
   git remote add origin https://github.com/SEU-USUARIO/gerenciamento_servico.git
   ```
   (Substitua SEU-USUARIO pelo seu nome de usuário real do GitHub)

6. Envie seu código:
   ```
   git push -u origin main
   ```
   (Se estiver usando uma versão mais antiga do Git, pode precisar usar `master` em vez de `main`)

7. Digite suas credenciais do GitHub se solicitado

Seu código agora está no GitHub! Você pode compartilhar a URL do repositório com outros para colaboração.

## Como Usar

1. Quando executar o programa, você verá um menu com opções
2. Siga as instruções para adicionar serviços, atualizar seu status ou visualizar a lista
3. Os serviços são automaticamente ordenados por prioridade (Alta > Média > Baixa)
4. Use a opção 4 para ver os créditos do projeto

## Estrutura do Projeto

- **Estrutura de dados**: Lista duplamente ligada
- **Ordenação**: Automática por prioridade
- **Validação**: Verificação de IDs antes de atualização
- **Gerenciamento de memória**: Alocação e liberação adequadas

## Contexto Acadêmico

Este projeto foi desenvolvido para a disciplina de **Estrutura de Dados I** sob orientação do **Professor Fabio Bettio** para o curso de **Análise e Desenvolvimento de Sistemas (ADS2)**.

## Autores

- **Leonardo Bora** (Líder) - [github.com/leonardobora](https://github.com/leonardobora)
- **Luan Constâncio** (Desenvolvedor) - [github.com/luanconstancio](https://github.com/luanconstancio)