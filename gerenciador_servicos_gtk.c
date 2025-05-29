#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura do serviço (mesma do original)
struct Servico {
    int id;
    char descricao[100];
    char status; // 'P' (Pendente), 'E' (Em Execução), 'C' (Concluído)
    char prioridade; // 'A' (Alta), 'M' (Média), 'B' (Baixa)
    struct Servico *ant;
    struct Servico *prox;
};
typedef struct Servico Servico;

// Variáveis globais
Servico *listaDeServicos = NULL;
int proximoId = 1;

// Widgets globais
GtkWidget *window;
GtkWidget *tree_view;
GtkListStore *list_store;
GtkWidget *entry_descricao;
GtkWidget *combo_prioridade;
GtkWidget *combo_status;
GtkWidget *entry_id_atualizar;
GtkWidget *combo_novo_status;
GtkWidget *entry_id_excluir;
GtkWidget *label_contador_servicos;
GtkWidget *combo_filtro_status;
GtkWidget *combo_filtro_prioridade;

// Funções auxiliares (mesmas do original)
int getPrioridadeValor(char p) {
    if (p == 'A') return 3; // Alta
    if (p == 'M') return 2; // Média
    if (p == 'B') return 1; // Baixa
    return 0; // Desconhecida/Baixa
}

void insereServicoPrioridade(char descricao[], char prioridadeChar, char status) {
    Servico *novoServico = (Servico*)malloc(sizeof(Servico));
    if (!novoServico) {
        g_print("Erro: Falha na alocacao de memoria!\n");
        return;
    }

    novoServico->id = proximoId++;
    strcpy(novoServico->descricao, descricao);
    novoServico->status = status;
    novoServico->prioridade = prioridadeChar;
    novoServico->ant = NULL;
    novoServico->prox = NULL;

    int novaPrioridadeVal = getPrioridadeValor(prioridadeChar);

    if (listaDeServicos == NULL || novaPrioridadeVal > getPrioridadeValor(listaDeServicos->prioridade)) {
        novoServico->prox = listaDeServicos;
        if (listaDeServicos != NULL) {
            listaDeServicos->ant = novoServico;
        }
        listaDeServicos = novoServico;
    } else {
        Servico *atual = listaDeServicos;
        while (atual->prox != NULL && getPrioridadeValor(atual->prox->prioridade) >= novaPrioridadeVal) {
            atual = atual->prox;
        }
        novoServico->prox = atual->prox;
        if (atual->prox != NULL) {
            atual->prox->ant = novoServico;
        }
        atual->prox = novoServico;
        novoServico->ant = atual;
    }
}

void atualizaStatusServico(int id, char novoStatus) {
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
        if (atual->id == id) {
            atual->status = novoStatus;
            return;
        }
        atual = atual->prox;
    }
}

int contarServicos() {
    int count = 0;
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

int contarServicosPorStatus(char status) {
    int count = 0;
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
        if (atual->status == status) {
            count++;
        }
        atual = atual->prox;
    }
    return count;
}

void atualizarContadores() {
    int total = contarServicos();
    int pendentes = contarServicosPorStatus('P');
    int em_execucao = contarServicosPorStatus('E');
    int concluidos = contarServicosPorStatus('C');
    
    char texto[200];
    snprintf(texto, sizeof(texto), 
             "Total: %d | Pendentes: %d | Em Execução: %d | Concluídos: %d",
             total, pendentes, em_execucao, concluidos);
    
    gtk_label_set_text(GTK_LABEL(label_contador_servicos), texto);
}

int excluirServico(int id) {
    Servico *atual = listaDeServicos;
    
    while (atual != NULL) {
        if (atual->id == id) {
            // Atualizar ponteiros dos nós adjacentes
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                // Se é o primeiro nó, atualizar o ponteiro da lista
                listaDeServicos = atual->prox;
            }
            
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            }
            
            free(atual);
            return 1; // Sucesso
        }
        atual = atual->prox;
    }
    return 0; // Serviço não encontrado
}

void liberaMemoria() {
    Servico *atual = listaDeServicos;
    Servico *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    listaDeServicos = NULL;
}

// Funções GTK+
void atualizar_lista_servicos() {
    // Limpar a lista atual
    gtk_list_store_clear(list_store);
    
    // Obter filtros selecionados (se existirem)
    const char *filtro_status = NULL;
    const char *filtro_prioridade = NULL;
    
    if (combo_filtro_status) {
        filtro_status = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_filtro_status));
    }
    if (combo_filtro_prioridade) {
        filtro_prioridade = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_filtro_prioridade));
    }
    
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
        // Verificar filtros
        int mostrar = 1;
        
        // Filtro por status
        if (filtro_status && strcmp(filtro_status, "Todos") != 0) {
            char statusAtual[15];
            if (atual->status == 'P') strcpy(statusAtual, "Pendente");
            else if (atual->status == 'E') strcpy(statusAtual, "Em Execução");
            else if (atual->status == 'C') strcpy(statusAtual, "Concluído");
            else strcpy(statusAtual, "N/A");
            
            if (strcmp(filtro_status, statusAtual) != 0) {
                mostrar = 0;
            }
        }
        
        // Filtro por prioridade
        if (mostrar && filtro_prioridade && strcmp(filtro_prioridade, "Todas") != 0) {
            char prioridadeAtual[10];
            if (atual->prioridade == 'A') strcpy(prioridadeAtual, "Alta");
            else if (atual->prioridade == 'M') strcpy(prioridadeAtual, "Média");
            else if (atual->prioridade == 'B') strcpy(prioridadeAtual, "Baixa");
            else strcpy(prioridadeAtual, "N/A");
            
            if (strcmp(filtro_prioridade, prioridadeAtual) != 0) {
                mostrar = 0;
            }
        }
        
        if (mostrar) {
            GtkTreeIter iter;
            
            // Converter prioridade para string
            char prioridadeStr[10];
            if (atual->prioridade == 'A') strcpy(prioridadeStr, "Alta");
            else if (atual->prioridade == 'M') strcpy(prioridadeStr, "Média");
            else if (atual->prioridade == 'B') strcpy(prioridadeStr, "Baixa");
            else strcpy(prioridadeStr, "N/A");

            // Converter status para string
            char statusStr[15];
            if (atual->status == 'P') strcpy(statusStr, "Pendente");
            else if (atual->status == 'E') strcpy(statusStr, "Em Execução");
            else if (atual->status == 'C') strcpy(statusStr, "Concluído");
            else strcpy(statusStr, "N/A");

            gtk_list_store_append(list_store, &iter);
            gtk_list_store_set(list_store, &iter,
                              0, atual->id,
                              1, atual->descricao,
                              2, prioridadeStr,
                              3, statusStr,
                              -1);
        }
        
        atual = atual->prox;
    }
    
    // Liberar memória dos filtros
    if (filtro_status) g_free((gpointer)filtro_status);
    if (filtro_prioridade) g_free((gpointer)filtro_prioridade);
    
    // Atualizar contadores
    if (label_contador_servicos) {
        atualizarContadores();
    }
}

void on_adicionar_clicked(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    const char *descricao = gtk_entry_get_text(GTK_ENTRY(entry_descricao));
    const char *prioridade_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_prioridade));
    const char *status_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_status));
    
    if (strlen(descricao) == 0 || !prioridade_str || !status_str) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Por favor, preencha todos os campos!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Converter strings para caracteres
    char prioridade_char = 'B';
    if (strcmp(prioridade_str, "Alta") == 0) prioridade_char = 'A';
    else if (strcmp(prioridade_str, "Média") == 0) prioridade_char = 'M';
    else if (strcmp(prioridade_str, "Baixa") == 0) prioridade_char = 'B';
    
    char status_char = 'P';
    if (strcmp(status_str, "Pendente") == 0) status_char = 'P';
    else if (strcmp(status_str, "Em Execução") == 0) status_char = 'E';
    else if (strcmp(status_str, "Concluído") == 0) status_char = 'C';
    
    // Adicionar serviço
    char desc_copy[100];
    strncpy(desc_copy, descricao, 99);
    desc_copy[99] = '\0';
    
    insereServicoPrioridade(desc_copy, prioridade_char, status_char);
    
    // Limpar campos
    gtk_entry_set_text(GTK_ENTRY(entry_descricao), "");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_prioridade), 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_status), 0);
    
    // Atualizar lista
    atualizar_lista_servicos();
    
    g_free((gpointer)prioridade_str);
    g_free((gpointer)status_str);
}

void on_atualizar_clicked(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    const char *id_str = gtk_entry_get_text(GTK_ENTRY(entry_id_atualizar));
    const char *novo_status_str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_novo_status));
    
    if (strlen(id_str) == 0 || !novo_status_str) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Por favor, preencha o ID e selecione o novo status!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    int id = atoi(id_str);
    char novo_status_char = 'P';
    if (strcmp(novo_status_str, "Pendente") == 0) novo_status_char = 'P';
    else if (strcmp(novo_status_str, "Em Execução") == 0) novo_status_char = 'E';
    else if (strcmp(novo_status_str, "Concluído") == 0) novo_status_char = 'C';
    
    atualizaStatusServico(id, novo_status_char);
    
    // Limpar campos
    gtk_entry_set_text(GTK_ENTRY(entry_id_atualizar), "");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_novo_status), 0);
    
    // Atualizar lista
    atualizar_lista_servicos();
    
    g_free((gpointer)novo_status_str);
}

void on_excluir_clicked(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    const char *id_str = gtk_entry_get_text(GTK_ENTRY(entry_id_excluir));
    
    if (strlen(id_str) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_WARNING,
                                                  GTK_BUTTONS_OK,
                                                  "Por favor, informe o ID do serviço a ser excluído!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    int id = atoi(id_str);
    
    // Confirmar exclusão
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_QUESTION,
                                              GTK_BUTTONS_YES_NO,
                                              "Tem certeza que deseja excluir o serviço ID %d?", id);
    
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        if (excluirServico(id)) {
            // Limpar campo
            gtk_entry_set_text(GTK_ENTRY(entry_id_excluir), "");
            
            // Atualizar lista
            atualizar_lista_servicos();
            
            // Mostrar confirmação
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_MODAL,
                                          GTK_MESSAGE_INFO,
                                          GTK_BUTTONS_OK,
                                          "Serviço excluído com sucesso!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                          GTK_DIALOG_MODAL,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_OK,
                                          "Serviço com ID %d não encontrado!", id);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
}

void on_filtro_changed(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    atualizar_lista_servicos();
}

void limpar_todos_servicos(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    if (listaDeServicos == NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_INFO,
                                                  GTK_BUTTONS_OK,
                                                  "Não há serviços para limpar!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Confirmar limpeza
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_QUESTION,
                                              GTK_BUTTONS_YES_NO,
                                              "Tem certeza que deseja excluir TODOS os serviços?");
    
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        liberaMemoria();
        proximoId = 1;
        
        // Atualizar lista
        atualizar_lista_servicos();
        
        // Mostrar confirmação
        dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                      GTK_DIALOG_MODAL,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      "Todos os serviços foram excluídos!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void mostrar_info_arquitetura(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Informações sobre a Arquitetura",
                                                   GTK_WINDOW(window),
                                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   "_Fechar", GTK_RESPONSE_CLOSE,
                                                   NULL);
    
    gtk_window_set_default_size(GTK_WINDOW(dialog), 600, 400);
    
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(text_view), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(text_view), 10);
    
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    
    const char *info_text = 
        "ARQUITETURA DO SISTEMA DE GERENCIAMENTO DE SERVIÇOS\n\n"
        "📋 ESTRUTURA DE DADOS PRINCIPAL\n"
        "Este sistema utiliza uma Lista Duplamente Encadeada para armazenar e gerenciar os serviços.\n\n"
        "🔗 LISTA DUPLAMENTE ENCADEADA\n"
        "• Cada nó (serviço) possui ponteiros para o próximo E anterior\n"
        "• Permite navegação bidirecional eficiente\n"
        "• Facilita inserções e remoções em qualquer posição\n"
        "• Ordenação automática por prioridade\n\n"
        "⚙️ ESTRUTURA DO NÓ (struct Servico):\n"
        "• id: Identificador único do serviço\n"
        "• descricao[100]: Descrição textual do serviço\n"
        "• status: 'P' (Pendente), 'E' (Em Execução), 'C' (Concluído)\n"
        "• prioridade: 'A' (Alta), 'M' (Média), 'B' (Baixa)\n"
        "• *ant: Ponteiro para o serviço anterior\n"
        "• *prox: Ponteiro para o próximo serviço\n\n"
        "🚀 VANTAGENS DA IMPLEMENTAÇÃO:\n"
        "• Inserção por prioridade em O(n) - mantém ordem\n"
        "• Busca por ID em O(n) - percorre lista sequencialmente\n"
        "• Remoção em O(1) - após localizar o nó\n"
        "• Atualização em O(n) - busca + modificação\n"
        "• Uso eficiente de memória - aloca conforme necessário\n\n"
        "🔧 FUNCIONALIDADES IMPLEMENTADAS:\n"
        "• Inserção com ordenação automática por prioridade\n"
        "• Atualização de status de serviços existentes\n"
        "• Exclusão segura com confirmação\n"
        "• Interface gráfica com GTK+ para facilitar uso\n"
        "• Validação de entrada e tratamento de erros\n\n"
        "📊 COMPLEXIDADES:\n"
        "• Inserção: O(n) - percorre até encontrar posição correta\n"
        "• Busca: O(n) - percorre lista linearmente\n"
        "• Remoção: O(n) para buscar + O(1) para remover\n"
        "• Exibição: O(n) - percorre toda a lista\n\n"
        "🎯 CARACTERÍSTICAS DA INTERFACE:\n"
        "• Desenvolvida com GTK+ (GIMP Toolkit)\n"
        "• Interface responsiva e intuitiva\n"
        "• Validação em tempo real\n"
        "• Feedback visual para operações\n"
        "• Confirmações para operações críticas\n\n"
        "Desenvolvido por: Leonardo Bora e Luan Constancio";
    
    gtk_text_buffer_set_text(buffer, info_text, -1);
    
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_box_pack_start(GTK_BOX(content_area), scrolled_window, TRUE, TRUE, 0);
    
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_window_destroy(GtkWidget *widget __attribute__((unused)), gpointer data __attribute__((unused))) {
    liberaMemoria();
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Criar janela principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gerenciador de Serviços");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    
    // Container principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Título
    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title_label), 
                        "<span size='large' weight='bold'>Sistema de Gerenciamento de Serviços</span>\n"
                        "<span size='small'>Desenvolvido por: Leonardo Bora e Luan Constancio</span>");
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 10);
    
    // Seção para adicionar serviços
    GtkWidget *add_frame = gtk_frame_new("Adicionar Serviço");
    gtk_box_pack_start(GTK_BOX(vbox), add_frame, FALSE, FALSE, 5);
    
    GtkWidget *add_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(add_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(add_grid), 5);
    gtk_container_set_border_width(GTK_CONTAINER(add_grid), 10);
    gtk_container_add(GTK_CONTAINER(add_frame), add_grid);
    
    // Campos para adicionar serviço
    gtk_grid_attach(GTK_GRID(add_grid), gtk_label_new("Descrição:"), 0, 0, 1, 1);
    entry_descricao = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(add_grid), entry_descricao, 1, 0, 2, 1);
    
    gtk_grid_attach(GTK_GRID(add_grid), gtk_label_new("Prioridade:"), 0, 1, 1, 1);
    combo_prioridade = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_prioridade), "Alta");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_prioridade), "Média");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_prioridade), "Baixa");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_prioridade), 0);
    gtk_grid_attach(GTK_GRID(add_grid), combo_prioridade, 1, 1, 1, 1);
    
    gtk_grid_attach(GTK_GRID(add_grid), gtk_label_new("Status:"), 2, 1, 1, 1);
    combo_status = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "Pendente");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "Em Execução");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_status), "Concluído");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_status), 0);
    gtk_grid_attach(GTK_GRID(add_grid), combo_status, 3, 1, 1, 1);
    
    GtkWidget *btn_adicionar = gtk_button_new_with_label("Adicionar Serviço");
    g_signal_connect(btn_adicionar, "clicked", G_CALLBACK(on_adicionar_clicked), NULL);
    gtk_grid_attach(GTK_GRID(add_grid), btn_adicionar, 4, 0, 1, 2);
    
    // Container para operações (atualizar e excluir)
    GtkWidget *operations_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), operations_hbox, FALSE, FALSE, 5);
    
    // Seção para atualizar status
    GtkWidget *update_frame = gtk_frame_new("Atualizar Status");
    gtk_box_pack_start(GTK_BOX(operations_hbox), update_frame, TRUE, TRUE, 0);
    
    GtkWidget *update_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(update_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(update_grid), 5);
    gtk_container_set_border_width(GTK_CONTAINER(update_grid), 10);
    gtk_container_add(GTK_CONTAINER(update_frame), update_grid);
    
    gtk_grid_attach(GTK_GRID(update_grid), gtk_label_new("ID:"), 0, 0, 1, 1);
    entry_id_atualizar = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(update_grid), entry_id_atualizar, 1, 0, 1, 1);
    
    gtk_grid_attach(GTK_GRID(update_grid), gtk_label_new("Novo Status:"), 0, 1, 1, 1);
    combo_novo_status = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Pendente");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Em Execução");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Concluído");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_novo_status), 0);
    gtk_grid_attach(GTK_GRID(update_grid), combo_novo_status, 1, 1, 1, 1);
    
    GtkWidget *btn_atualizar = gtk_button_new_with_label("Atualizar");
    g_signal_connect(btn_atualizar, "clicked", G_CALLBACK(on_atualizar_clicked), NULL);
    gtk_grid_attach(GTK_GRID(update_grid), btn_atualizar, 2, 0, 1, 2);
    
    // Seção para excluir serviço
    GtkWidget *delete_frame = gtk_frame_new("Excluir Serviço");
    gtk_box_pack_start(GTK_BOX(operations_hbox), delete_frame, TRUE, TRUE, 0);
    
    GtkWidget *delete_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(delete_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(delete_grid), 5);
    gtk_container_set_border_width(GTK_CONTAINER(delete_grid), 10);
    gtk_container_add(GTK_CONTAINER(delete_frame), delete_grid);
    
    gtk_grid_attach(GTK_GRID(delete_grid), gtk_label_new("ID do Serviço:"), 0, 0, 1, 1);
    entry_id_excluir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(delete_grid), entry_id_excluir, 1, 0, 1, 1);
    
    GtkWidget *btn_excluir = gtk_button_new_with_label("Excluir");
    g_signal_connect(btn_excluir, "clicked", G_CALLBACK(on_excluir_clicked), NULL);
    gtk_grid_attach(GTK_GRID(delete_grid), btn_excluir, 2, 0, 1, 1);
    
    // Container para filtros e ações
    GtkWidget *filter_frame = gtk_frame_new("Filtros e Ações");
    gtk_box_pack_start(GTK_BOX(vbox), filter_frame, FALSE, FALSE, 5);
    
    GtkWidget *filter_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(filter_hbox), 10);
    gtk_container_add(GTK_CONTAINER(filter_frame), filter_hbox);
    
    // Filtros
    gtk_box_pack_start(GTK_BOX(filter_hbox), gtk_label_new("Filtrar por Status:"), FALSE, FALSE, 0);
    combo_filtro_status = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_status), "Todos");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_status), "Pendente");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_status), "Em Execução");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_status), "Concluído");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_filtro_status), 0);
    g_signal_connect(combo_filtro_status, "changed", G_CALLBACK(on_filtro_changed), NULL);
    gtk_box_pack_start(GTK_BOX(filter_hbox), combo_filtro_status, FALSE, FALSE, 5);
    
    gtk_box_pack_start(GTK_BOX(filter_hbox), gtk_label_new("Filtrar por Prioridade:"), FALSE, FALSE, 10);
    combo_filtro_prioridade = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_prioridade), "Todas");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_prioridade), "Alta");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_prioridade), "Média");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_filtro_prioridade), "Baixa");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_filtro_prioridade), 0);
    g_signal_connect(combo_filtro_prioridade, "changed", G_CALLBACK(on_filtro_changed), NULL);
    gtk_box_pack_start(GTK_BOX(filter_hbox), combo_filtro_prioridade, FALSE, FALSE, 5);
    
    // Botões de ação
    GtkWidget *btn_limpar_todos = gtk_button_new_with_label("🗑️ Limpar Todos");
    g_signal_connect(btn_limpar_todos, "clicked", G_CALLBACK(limpar_todos_servicos), NULL);
    gtk_box_pack_end(GTK_BOX(filter_hbox), btn_limpar_todos, FALSE, FALSE, 5);
    
    GtkWidget *info_button = gtk_button_new_with_label("ℹ️ Arquitetura");
    g_signal_connect(info_button, "clicked", G_CALLBACK(mostrar_info_arquitetura), NULL);
    gtk_box_pack_end(GTK_BOX(filter_hbox), info_button, FALSE, FALSE, 0);
    
    // Contador de serviços
    label_contador_servicos = gtk_label_new("Total: 0 | Pendentes: 0 | Em Execução: 0 | Concluídos: 0");
    gtk_box_pack_start(GTK_BOX(vbox), label_contador_servicos, FALSE, FALSE, 5);
    
    // Lista de serviços
    GtkWidget *list_frame = gtk_frame_new("Lista de Serviços");
    gtk_box_pack_start(GTK_BOX(vbox), list_frame, TRUE, TRUE, 5);
    
    // Criar modelo para a lista
    list_store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    
    // Criar tree view
    tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
    
    // Criar colunas
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column;
    
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    column = gtk_tree_view_column_new_with_attributes("Descrição", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    column = gtk_tree_view_column_new_with_attributes("Prioridade", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    column = gtk_tree_view_column_new_with_attributes("Status", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);
    
    // Adicionar scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tree_view);
    gtk_container_add(GTK_CONTAINER(list_frame), scrolled_window);
    
    // Mostrar todos os widgets
    gtk_widget_show_all(window);
    
    // Atualizar contadores iniciais
    atualizarContadores();
    
    // Iniciar loop principal
    gtk_main();
    
    return 0;
}