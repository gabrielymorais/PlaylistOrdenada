# 🎶 Playlist de Músicas em C 🎶

Este é um programa em C para gerenciamento de playlists de músicas utilizando **listas duplamente encadeadas**. Com ele, você pode adicionar, remover, exibir, navegar entre músicas e até ordená-las por duração! 🥳

## 🎵 Menu de Opções

- Adicionar Música
- Remover Música
- Mostrar Playlist
- Avançar para a Próxima Música
- Voltar para a Música Anterior
- Ordenar Músicas por Duração
- Sair

## 📋 Funcionalidades

1. **Adicionar Músicas**  
   - Permite adicionar uma música com **título**, **artista** e **duração** (em segundos) à playlist.
   - 🎵 A música será adicionada ao **final** da playlist.

2. **Remover Músicas**  
   - Remove uma música da playlist pelo **título** informado.
   - 🔍 O programa busca a música na lista e a remove, atualizando os ponteiros das músicas adjacentes.

3. **Mostrar Playlist Completa**  
   - Exibe todas as músicas presentes na playlist.
   - 👀 Além disso, mostra a **quantidade total de músicas** e a **duração total** da playlist.

4. **Avançar para a Próxima Música**  
   - Avança para a próxima música na lista.
   - 🔜 Se não houver uma próxima música, uma mensagem será exibida.

5. **Voltar para a Música Anterior**  
   - Volta para a música anterior.
   - 🔙 Se não houver uma música anterior, uma mensagem será exibida.

6. **Ordenar Músicas por Duração**  
   - Ordena as músicas da playlist pela **duração** (em segundos) usando o algoritmo **Selection Sort**.
   - ⏳ Após a ordenação, a playlist será atualizada e exibida de acordo com a duração das músicas.

7. **Navegação Simples**  
   - Você pode navegar pelas músicas **anterior** e **próxima** dentro da lista.

## 🗂️ Estruturas de Dados Utilizadas

O programa utiliza **listas duplamente encadeadas**, onde cada nó representa uma **música** e contém os seguintes campos:
- **Título** da música (string de até 100 caracteres).
- **Artista** da música (string de até 100 caracteres).
- **Duração** da música (em segundos).
- Ponteiro para a **música anterior** (`prev`).
- Ponteiro para a **próxima música** (`next`).

Além disso, a **Playlist** contém:
- Um ponteiro para o **início** da lista.
- Um ponteiro para o **fim** da lista.
- Um ponteiro para a **música atual** (a que está sendo tocada).
- Contadores para o **número total de músicas** e a **duração total** da playlist.

## 🧠 Algoritmos Implementados

- **Inserção no Final da Lista**  
   Para adicionar uma música ao final, o algoritmo percorre a lista até encontrar o último elemento e o conecta à nova música.

- **Remoção de Música**  
   O programa busca a música pelo título e ajusta os ponteiros para remover a música da lista, lidando com as três situações possíveis:
   - Música no **início**.
   - Música no **fim**.
   - Música no **meio**.

- **Ordenação por Duração (Selection Sort)**  
   Utilizamos o algoritmo de **Selection Sort** para ordenar as músicas por duração. O programa percorre a lista, encontra a música com a menor duração e faz a troca dos dados.
  

## 🛠️ Como Usar

1. Compile o programa com o comando:
   ```bash
   gcc playlist.c -o playlist
   ```
