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
    
    Servico *atual = listaDeServicos;
    while (atual != NULL) {
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
        
        atual = atual->prox;
    }
}

void on_adicionar_clicked(GtkWidget *widget, gpointer data) {
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

void on_atualizar_clicked(GtkWidget *widget, gpointer data) {
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

void on_window_destroy(GtkWidget *widget, gpointer data) {
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
    
    // Seção para atualizar status
    GtkWidget *update_frame = gtk_frame_new("Atualizar Status");
    gtk_box_pack_start(GTK_BOX(vbox), update_frame, FALSE, FALSE, 5);
    
    GtkWidget *update_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(update_grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(update_grid), 5);
    gtk_container_set_border_width(GTK_CONTAINER(update_grid), 10);
    gtk_container_add(GTK_CONTAINER(update_frame), update_grid);
    
    gtk_grid_attach(GTK_GRID(update_grid), gtk_label_new("ID do Serviço:"), 0, 0, 1, 1);
    entry_id_atualizar = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(update_grid), entry_id_atualizar, 1, 0, 1, 1);
    
    gtk_grid_attach(GTK_GRID(update_grid), gtk_label_new("Novo Status:"), 2, 0, 1, 1);
    combo_novo_status = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Pendente");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Em Execução");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_novo_status), "Concluído");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_novo_status), 0);
    gtk_grid_attach(GTK_GRID(update_grid), combo_novo_status, 3, 0, 1, 1);
    
    GtkWidget *btn_atualizar = gtk_button_new_with_label("Atualizar Status");
    g_signal_connect(btn_atualizar, "clicked", G_CALLBACK(on_atualizar_clicked), NULL);
    gtk_grid_attach(GTK_GRID(update_grid), btn_atualizar, 4, 0, 1, 1);
    
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
    
    // Iniciar loop principal
    gtk_main();
    
    return 0;
}