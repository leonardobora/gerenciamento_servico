# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This repository contains a C-based service management system ("gerenciamento_servico" in Portuguese). It's a command-line application that allows users to add services with priority levels, update their status, and display them in a list.

## Build and Run Commands

### Compile the Program
```bash
gcc gerenciador_servicos.c -o gerenciador_servicos
```

### Run the Program
```bash
./gerenciador_servicos
```

## Architecture Overview

The system is built around a doubly-linked list implementation with the following key components:

1. **Service Structure**: Each service contains an ID, description, priority level, status, and pointers to the previous and next services in the list.

2. **Priority Levels**: 
   - 'A' (Alta/High)
   - 'M' (Media/Medium)
   - 'B' (Baixa/Low)

3. **Status Types**:
   - 'P' (Pendente/Pending)
   - 'E' (Em Execução/In Progress)
   - 'C' (Concluído/Completed)

4. **Core Functions**:
   - `insereServicoPrioridade`: Inserts services into the list based on their priority
   - `atualizaStatusServico`: Updates the status of a service by ID
   - `exibeServicos`: Displays all services in a formatted table
   - `liberaMemoria`: Frees all allocated memory when the program exits

## Development Notes

- Services are stored in a priority-ordered doubly-linked list
- The system maintains services in order of priority (high to low)
- Memory management is handled with proper allocation and deallocation
- Input validation ensures only valid status and priority values are accepted