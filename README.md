# efe_Game

O jogo **efe** foi desenvolvido em C com a biblioteca gráfica allegro, funciona conforme descrito a seguir.

O jogo é constituído por um tabuleiro quadrado, de 5x5 posições.
Cada posição pode estar vazia ou preenchida por uma letra de 'A' a 'F'.
Em uma jogada, pode-se mover as peças em uma das 4 direções, usando as setas do teclado.
Ao se movimentarem, as peças podem se combinar, gerando novas letras.
O objetivo é gerar a letra 'F'.

No início do jogo, 2 casas são automaticamente preenchidas; após cada jogada, uma casa vazia é preenchida.
A casa a ser preenchida automaticamente, e a letra usada para preenchê-la são escolhidas pelo programa de forma aleatória. 
A letra usada para preencher pode ser 'A' ou 'B', com 3 vezes mais chance de ser 'A' do que de ser 'B'.

O jogo acaba quando for gerado um 'F' ou quando não houver jogada possível.

Uma jogada consiste em um movimento em uma das 4 direções. Todas as peças devem se deslocar o máximo possível na direção considerada.
Caso 3 peças iguais fiquem juntas na direção do movimento, elas são combinadas em uma peça com a letra seguinte.
Se o movimento for horizontal, somente peças de uma mesma linha podem se combinar. Se for vertical, de uma mesma coluna.
Podem acontecer várias combinações em uma mesma jogada.

Por exemplo, considerando movimento de uma linha para a direita ou esquerda:

| antes | direita | esquerda |
| :---: | :----: | :----: |
| -A--- | ----A | A---- |
| --B-A | ---BA | BA--- |
| A-AA- | ----B | B---- |
| CCBC- | -CCBC | CCBC- |
| BCCCC | --BCD | BDC-- |
| AAABB | --BBB | C---- |
| BBAAA | ----C | BBB-- |

Esses são os movimentos feitos pelo jogo 243. No nosso caso, os 2 últimos movimentos podem realizar as 2 combinações nas 2 direções, resultando em "C".

Cada letra que se mexe vale um ponto.
Cada combinação vale a soma das 3 letras combinadas (cada 'A' vale 10, combinam num 'B' vale 30; combinando 3 'B' em um 'C' vale 90 etc).

O jogo mantém arquivo as 5 maiores pontuações com a identificação de quem pontuou.
Na execução caso o arquivo não exista, o programa deve considerar que ninguém pontuou ainda.

O desenho do tabuleiro é colorido, com uma combinação de cor diferente para cada conteúdo possível em uma posição (vazia, 'A' a 'F').

O jogo é baseado no [243](https://hgentry.github.io/81/).

# Executar

Para executar o jogo é necessária a biblioteca allegro estar instalada. Após isso, baixe a pasta com os arquivos e execute no terminal com o comando:

**gcc -Wall -o jogo efe.c tela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro**
