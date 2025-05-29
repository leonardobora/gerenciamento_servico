# Configuração de Interface Gráfica no WSL

## Opção 1: X11 Forwarding (Recomendado)

### 1. Instalar X Server no Windows
- Baixe e instale VcXsrv: https://sourceforge.net/projects/vcxsrv/
- Ou Xming: https://sourceforge.net/projects/xming/

### 2. Configurar VcXsrv
- Execute "XLaunch"
- Selecione "Multiple windows"
- Display number: -1
- Marque "Disable access control"

### 3. Configurar WSL
```bash
# Adicionar ao ~/.bashrc ou ~/.zshrc
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
export LIBGL_ALWAYS_INDIRECT=1
```

### 4. Instalar dependências GTK+ (executar como sudo)
```bash
./install_gtk.sh
```

### 5. Compilar e executar
```bash
make gtk
./gerenciador_servicos_gtk
```

## Opção 2: WSLg (Windows 11)

Se você tem Windows 11, pode usar WSLg que já vem integrado:

### 1. Atualizar WSL
```bash
wsl --update
```

### 2. Instalar dependências
```bash
./install_gtk.sh
```

### 3. Executar
```bash
make gtk
./gerenciador_servicos_gtk
```

## Opção 3: Terminal apenas (Sempre funciona)
```bash
make console
./gerenciador_servicos
```

## Troubleshooting

### Erro: "cannot connect to X server"
- Verifique se o X Server está rodando no Windows
- Verifique a variável DISPLAY: `echo $DISPLAY`
- Reinicie o WSL: `wsl --shutdown` (no PowerShell do Windows)

### Erro: "No such file or directory" para gtk/gtk.h
- Execute: `./install_gtk.sh`
- Se não funcionar, instale manualmente: `sudo apt install libgtk-3-dev`