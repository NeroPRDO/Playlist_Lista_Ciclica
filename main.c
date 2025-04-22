#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "playlist.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Playlist* playlist = criar_playlist();
    int opcao;
    char titulo[100], artista[100];
    int duracao;

    adicionar_musica(playlist, "Alfathirhati", "Heilung", 5);
    adicionar_musica(playlist, "Skugge", "Ulver", 5);
    adicionar_musica(playlist, "Gra", "Myrkur", 5);
    adicionar_musica(playlist, "Elverhoy", "Wardruna", 5);
    adicionar_musica(playlist, "Hertan", "Wardruna", 5);

    do {
        printf("\n===== MENU PLAYLIST =====\n");
        printf("1. Adicionar musica\n");
        printf("2. Remover musica\n");
        printf("3. Proxima musica\n");
        printf("4. Musica anterior\n");
        printf("5. Ativar/Desativar modo repeticao\n");
        printf("6. Listar musicas\n");
        printf("7. Buscar musica pelo titulo\n");
        printf("8. Exibir musica atual\n");
        printf("9. Tocar musicas (simulacao)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                printf("Titulo: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = 0;

                printf("Duracao (segundos): ");
                scanf("%d", &duracao);
                limpar_buffer();

                adicionar_musica(playlist, titulo, artista, duracao);
                printf("Musica adicionada com sucesso!\n");
                break;

            case 2:
                printf("Titulo da musica a remover: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                if (remover_musica(playlist, titulo)) {
                    printf("Musica removida com sucesso!\n");
                } else {
                    printf("Musica nao encontrada.\n");
                }
                break;

            case 3:
                proxima_musica(playlist);
                printf("Avancou para a proxima musica.\n");
                break;

            case 4:
                musica_anterior(playlist);
                printf("Retornou para a musica anterior.\n");
                break;

            case 5:
                alternar_modo_repeticao(playlist);
                printf("Modo de repeticao %s.\n", playlist->modo_repeticao ? "ativado" : "desativado");
                break;

            case 6:
                printf("Musicas na playlist:\n");
                listar_musicas(playlist);
                break;

            case 7:
                printf("Titulo da musica a buscar: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                Musica* encontrada = buscar_musica(playlist, titulo);
                if (encontrada) {
                    printf("Musica encontrada: %s | Artista: %s | Duracao: %d segundos\n",
                           encontrada->titulo, encontrada->artista, encontrada->duracao);
                } else {
                    printf("Musica nao encontrada.\n");
                }
                break;

            case 8:
                exibir_musica_atual(playlist);
                break;
                case 9: {
                    if (playlist->atual == NULL) {
                        printf("A playlist está vazia.\n");
                        break;
                    }
                
                    printf("Iniciando reproducao automatica (pressione Ctrl+C para parar)...\n");
                
                    while (1) {
                        Musica* atual = playlist->atual;
                        for (int i = 1; i <= atual->duracao; i++) {
                            printf("\rTocando: %s [%d/%d seg]", atual->titulo, i, atual->duracao);
                            fflush(stdout);
                            sleep(1); // aguarda 1 segundo
                        }
                
                        printf("\nMusica finalizada.\n");
                
                        if (!playlist->modo_repeticao) {
                            proxima_musica(playlist);
                        }
                        exibir_musica_atual(playlist);
                    }
                
                    break;
                }                

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    liberar_playlist(playlist);
    return 0;
}