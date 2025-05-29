#!/bin/bash

echo "Instalando dependências GTK+ para desenvolvimento..."

# Atualizar repositórios
sudo apt update

# Instalar dependências GTK+ e desenvolvimento
sudo apt install -y \
    libgtk-3-dev \
    pkg-config \
    build-essential \
    libglib2.0-dev \
    libpango1.0-dev \
    libcairo2-dev \
    libgdk-pixbuf2.0-dev \
    libatk1.0-dev

echo "Instalação concluída!"
echo "Para testar, execute: make gtk"