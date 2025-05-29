# Makefile para o Gerenciador de Serviços

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Flags GTK+
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0 2>/dev/null || echo "-I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0")
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0 2>/dev/null || echo "-lgtk-3 -lgdk-3 -lglib-2.0 -lgobject-2.0")

# Targets
all: console gtk

console: gerenciador_servicos.c
	$(CC) $(CFLAGS) -o gerenciador_servicos gerenciador_servicos.c

gtk: gerenciador_servicos_gtk.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o gerenciador_servicos_gtk gerenciador_servicos_gtk.c $(GTK_LIBS)

clean:
	rm -f gerenciador_servicos gerenciador_servicos_gtk

install-deps:
	sudo apt update && sudo apt install -y libgtk-3-dev pkg-config

.PHONY: all console gtk clean install-deps