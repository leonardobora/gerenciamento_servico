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
- ✅ Exclusão de serviços com confirmação
- ✅ Contadores de serviços por status
- ✅ Filtros por status e prioridade
- ✅ Integração contínua com GitHub Actions
- ✅ Build automático e distribuição de binários

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

**Para a versão CLI:**
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

**Para a versão GTK+ (Interface Gráfica):**
1. Instale as dependências GTK+:
   ```
   # Ubuntu/Debian
   sudo apt-get install libgtk-3-dev pkg-config
   
   # Fedora/RHEL
   sudo dnf install gtk3-devel pkgconfig
   
   # Arch Linux
   sudo pacman -S gtk3 pkgconfig
   ```
2. Compile:
   ```
   gcc gerenciador_servicos_gtk.c -o gerenciador_servicos_gtk `pkg-config --cflags --libs gtk+-3.0`
   ```
3. Execute:
   ```
   ./gerenciador_servicos_gtk
   ```

## Integração Contínua (CI/CD)

Este projeto utiliza **GitHub Actions** para automatizar builds e testes:

### 🤖 Build Automático
- **Compilação automática** nas versões CLI e GTK+ a cada push
- **Testes de integridade** em ambiente Ubuntu limpo
- **Artifacts disponíveis** para download após build bem-sucedido
- **Feedback imediato** sobre problemas de compilação

### 📋 Workflow Details
O workflow executa automaticamente:
1. **Instalação de dependências** (gcc, make, GTK+ dev libraries)
2. **Compilação das duas versões** do programa
3. **Validação dos executáveis** gerados
4. **Upload dos binários** como artifacts
5. **Verificação da documentação**

### 📦 Download de Binários
Após cada build bem-sucedido:
- Vá para a aba **Actions** no GitHub
- Clique no workflow run mais recente
- Baixe o artifact **"compiled-binaries"**
- Contém ambas as versões: CLI e GTK+

## Contribuindo

Contribuições são bem-vindas! Para contribuir:

1. **Fork** o repositório
2. Crie uma **branch** para sua feature (`git checkout -b feature/nova-funcionalidade`)
3. **Commit** suas mudanças (`git commit -m 'Adicionar nova funcionalidade'`)
4. **Push** para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um **Pull Request**

### 📋 Checklist antes do PR
- [ ] Código compila sem warnings
- [ ] Funcionalidade testada manualmente
- [ ] Documentação atualizada se necessário
- [ ] GitHub Actions passando ✅

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

Este projeto foi desenvolvido para a disciplina de **Estrutura de Dados I** sob orientação do **Professor Fabio Bettio** para o curso de **Engenharia de Software**.

## Autores

- **Leonardo Bora** (Líder) - [github.com/leonardobora](https://github.com/leonardobora)
- **Luan Constâncio** (Desenvolvedor) - [github.com/luanconstancio](https://github.com/luanconstancio)
