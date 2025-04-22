#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

Playlist* criar_playlist() {
    Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
    playlist->atual = NULL;
    playlist->tamanho = 0;
    playlist->modo_repeticao = 0;
    return playlist;
}

// ✅ Versão segura da liberação de memória (copiada da versão enviada no chat)
void liberar_playlist(Playlist* playlist) {
    if (playlist == NULL || playlist->atual == NULL) {
        free(playlist);
        return;
    }

    Musica* corrente = playlist->atual->proxima;
    Musica* temp;

    while (corrente != playlist->atual) {
        temp = corrente;
        corrente = corrente->proxima;
        free(temp);
    }

    free(playlist->atual); // Libera a última música
    free(playlist);
}

void adicionar_musica(Playlist* playlist, const char* titulo, const char* artista, int duracao) {
    Musica* nova_musica = (Musica*)malloc(sizeof(Musica));
    strncpy(nova_musica->titulo, titulo, sizeof(nova_musica->titulo) - 1);
    nova_musica->titulo[sizeof(nova_musica->titulo) - 1] = '\0';
    strncpy(nova_musica->artista, artista, sizeof(nova_musica->artista) - 1);
    nova_musica->artista[sizeof(nova_musica->artista) - 1] = '\0';
    nova_musica->duracao = duracao;

    if (playlist->atual == NULL) {
        nova_musica->proxima = nova_musica;
        playlist->atual = nova_musica;
    } else {
        Musica* ultima = playlist->atual;
        while (ultima->proxima != playlist->atual) {
            ultima = ultima->proxima;
        }
        ultima->proxima = nova_musica;
        nova_musica->proxima = playlist->atual;
    }
    playlist->tamanho++;
}

int remover_musica(Playlist* playlist, const char* titulo) {
    if (playlist->atual == NULL) return 0;

    Musica* atual = playlist->atual;
    Musica* anterior = NULL;

    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                if (atual->proxima == playlist->atual) {
                    playlist->atual = NULL;
                } else {
                    Musica* ultima = playlist->atual;
                    while (ultima->proxima != playlist->atual) {
                        ultima = ultima->proxima;
                    }
                    playlist->atual = atual->proxima;
                    ultima->proxima = playlist->atual;
                }
            } else {
                anterior->proxima = atual->proxima;
            }
            free(atual);
            playlist->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->proxima;
    } while (atual != playlist->atual);

    return 0;
}

void proxima_musica(Playlist* playlist) {
    if (playlist->atual != NULL) {
        playlist->atual = playlist->atual->proxima;
    }
}

void musica_anterior(Playlist* playlist) {
    if (playlist->atual != NULL) {
        Musica* anterior = playlist->atual;
        while (anterior->proxima != playlist->atual) {
            anterior = anterior->proxima;
        }
        playlist->atual = anterior;
    }
}

void alternar_modo_repeticao(Playlist* playlist) {
    playlist->modo_repeticao = 1 - playlist->modo_repeticao;
}

void listar_musicas(Playlist* playlist) {
    if (playlist->atual == NULL) {
        printf("A playlist esta vazia.\n");
        return;
    }

    Musica* atual = playlist->atual;
    do {
        printf("Titulo: %s | Artista: %s | Duracao: %d segundos\n",
               atual->titulo, atual->artista, atual->duracao);
        atual = atual->proxima;
    } while (atual != playlist->atual);
}

Musica* buscar_musica(Playlist* playlist, const char* titulo) {
    if (playlist->atual == NULL) return NULL;

    Musica* atual = playlist->atual;
    do {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual;
        }
        atual = atual->proxima;
    } while (atual != playlist->atual);

    return NULL;
}

void exibir_musica_atual(Playlist* playlist) {
    if (playlist->atual != NULL) {
        printf("Musica atual: %s | Artista: %s | Duracao: %d segundos\n",
               playlist->atual->titulo, playlist->atual->artista, playlist->atual->duracao);
    } else {
        printf("A playlist esta vazia.\n");
    }
}
