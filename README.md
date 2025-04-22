# Playlist_Lista_Ciclica

🎵 Sistema de Gerenciamento de Playlist Musical em C

✅ Introdução

Este projeto consiste em um sistema de gerenciamento de playlist musical desenvolvido na linguagem C. Ele simula o comportamento de um reprodutor de músicas básico, permitindo que o usuário:

Adicione, remova e navegue entre músicas

Visualize músicas disponíveis

Busque músicas por título

Ative ou desative o modo de repetição

Simule a reprodução automática das faixas com controle de tempo

Ideal para aprender e aplicar estruturas de dados (listas encadeadas circulares), alocação dinâmica de memória e interação via terminal.

🔧 Componentes do Projeto

1. playlist.h

Define as estruturas e protótipos das funções:

Musica: representa uma faixa musical.

Playlist: representa a lista circular com modo de repetição.

2. playlist.c

Implementa todas as funcionalidades da playlist:

Criação e liberação da lista

Adição, remoção e navegação

Listagem, busca e exibição

Controle do modo de repetição

Inclui uma versão segura e robusta da função liberar_playlist, garantindo que nenhuma memória fique alocada indevidamente.

3. main.c

Interface em linha de comando:

Apresenta menu interativo

Permite manipulação completa da playlist

Simula a reprodução de músicas com barra de tempo via sleep()

🧠 Características Técnicas

Lista Encadeada Circular: possibilita reprodução cíclica.

Gerenciamento de Memória: uso de malloc() e free() com cuidado.

Modo Repetição: opcional para manter a música tocando em loop.

Reprodução Temporizada: simula um player real com contagem de segundos.

📆 Execução do Programa

Compile os arquivos usando gcc:

gcc -o app_playlist playlist.c main.c
./app_playlist

Escolha opções no menu para interagir com o sistema.



Desenvolvido com fins educacionais para exercitar estruturas de dados em C ✨
