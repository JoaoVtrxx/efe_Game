#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char nome[20];
    int pontos;
}Rg_jogador;

typedef struct{
    int primaria;
    int secundaria;
    int cor[6];
    bool set;
}cores_novas;

typedef struct{
    int tabuleiro[5][5];
    int tecla;
    bool resp;
    bool acabou;
    bool ganhou;
    bool linha_mexeu;
    Rg_jogador jogador_atual;
    Rg_jogador ranking[5];
    cores_novas cores;
}Rg_jogo;

void inicializa_cores(Rg_jogo *jogo){
    if(jogo->cores.set){
        jogo->cores.primaria = tela_cria_cor(0,0.172,0.168);
        jogo->cores.secundaria = tela_cria_cor(0.027 ,0.392,0.38);
        jogo->cores.cor[0] = tela_cria_cor(1, 0.239, 0);
        jogo->cores.cor[1] = tela_cria_cor(1, 0.737, 0.066);
        jogo->cores.cor[2] = tela_cria_cor(0.039, 0.513, 0.498);
        jogo->cores.cor[3] = tela_cria_cor(0.243, 0.243, 0.325);
        jogo->cores.cor[4] = tela_cria_cor(0, 0.356, 0.772);
        jogo->cores.cor[5] = tela_cria_cor(0.003, 0.14, 0.466);
        jogo->cores.set = false;
    }else{
        jogo->cores.primaria = tela_cria_cor(0.6,0.6,0.6);
        jogo->cores.secundaria = tela_cria_cor(0.7 ,0.7,0.7);
        jogo->cores.cor[0] = tela_cria_cor(1, 0.950, 0);
        jogo->cores.cor[1] = tela_cria_cor(1, 0.690, 0);
        jogo->cores.cor[2] = tela_cria_cor(1, 0.329, 0);
        jogo->cores.cor[3] = tela_cria_cor(1, 0, 0.329);
        jogo->cores.cor[4] = tela_cria_cor(0.619, 0, 0.349);
        jogo->cores.cor[5] = tela_cria_cor(0.22, 0, 0.6); 
        jogo->cores.set = true;
    }      
}

void le_arquivo(Rg_jogo *jogo){
    FILE *file;
    file = fopen("arquivo.txt", "r");

    if(file != NULL){
        fscanf(file, "%s %d %s %d %s %d %s %d %s %d", jogo->ranking[0].nome, &jogo->ranking[0].pontos, jogo->ranking[1].nome, &jogo->ranking[1].pontos, jogo->ranking[2].nome, &jogo->ranking[2].pontos, jogo->ranking[3].nome, &jogo->ranking[3].pontos, jogo->ranking[4].nome, &jogo->ranking[4].pontos);
        fclose(file);
    }
}

void escreve_arquivo(Rg_jogo jogo){
    FILE *file;
    file = fopen("arquivo.txt", "w");
    fprintf(file, "%s %d %s %d %s %d %s %d %s %d", jogo.ranking[0].nome, jogo.ranking[0].pontos, jogo.ranking[1].nome, jogo.ranking[1].pontos, jogo.ranking[2].nome, jogo.ranking[2].pontos, jogo.ranking[3].nome, jogo.ranking[3].pontos, jogo.ranking[4].nome, jogo.ranking[4].pontos);
    fclose(file);
}

void reseta_valores(Rg_jogo *jogo){
    int i, j;
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            jogo->tabuleiro[i][j] = 0;
        }
    }
    jogo->jogador_atual.pontos = 0;
    strcpy(jogo->jogador_atual.nome, "");
    jogo->acabou = false;
    jogo->ganhou = false;
}

void randomiza_tabuleiro(Rg_jogo *jogo){
    int i;
    int j;
    int h = (rand() % 4);
    bool tem_espaco = false;
    for(i = 0; i<5; i++){
       for(j = 0; j<5; j++){
            if(jogo->tabuleiro[i][j] == 0){
                tem_espaco = true;
            }
        } 
    }
    if(tem_espaco == true){
        do{
            i = (rand() % 5);
            j = (rand() % 5);
        } while(jogo->tabuleiro[i][j] != 0);
        if(h == 0){
            jogo->tabuleiro[i][j] = 3;
        }else{
            jogo->tabuleiro[i][j] = 1;
        }
    }
}

void tela_placar(Rg_jogo jogo){
    char txt[20];
    tela_retangulo(395,45, 590, 95, 0, jogo.cores.secundaria, jogo.cores.secundaria);
    sprintf(txt, "Pontuação: %d", jogo.jogador_atual.pontos);
    tela_texto_dir(400, 60, 20, branco, txt);
}

void switch_peca_tabuleiro(Rg_jogo jogo, int valor, int *cor, char txt[3]){
    switch (valor){
            case 1:
                strcpy(txt, "A");
                *cor = jogo.cores.cor[0];
                break;
            case 3:
                strcpy(txt, "B");
                *cor = jogo.cores.cor[1];
                break;
            case 9:
                strcpy(txt, "C");
                *cor = jogo.cores.cor[2];
                break;
            case 27:
                strcpy(txt, "D");
                *cor = jogo.cores.cor[3];
                break;
            case 81:
                strcpy(txt, "E");
                *cor = jogo.cores.cor[4];
                break;
            case 243:
                strcpy(txt, "F");
                *cor = jogo.cores.cor[5];
                break;
            default:
                strcpy(txt, "");
                *cor = branco;
                break;
    }   
}

void tela_tabuleiro(Rg_jogo jogo){
    int x, y, x1, y1, x2, y2, valor, cor;
    char txt[3];
    tela_retangulo(0, 0, 1279, 719, 0, jogo.cores.primaria, jogo.cores.primaria);
    tela_placar(jogo);

    for(x = 0; x<5; x++){
        for(y = 0; y<5; y++){   
            valor = jogo.tabuleiro[x][y];
            x1 = 390+y*100;
            y1 = 110+x*100;
            x2 = 490+y*100;
            y2 = 210+x*100;

            switch_peca_tabuleiro(jogo, valor, &cor, txt);
            tela_retangulo(x1, y1, x2, y2, 10, jogo.cores.primaria, cor);
            tela_texto(x1+50, y1+50, 30, branco, txt);
            
        }
    }
}

void move_zeros(int vetor[5]){
  int count = 0;
  for(int i =0; i < 5; i++){
    if(vetor[i] != 0){
      vetor[count] = vetor[i];
      count++;
    }
  }
  for(int i = count; i < 5; i++){
    vetor[i] = 0;
  }
}

int junta(int vetor[5]){
  for(int i = 0; i<5; i++){
       if(vetor[i] == vetor[i+1] && vetor[i] == vetor[i+2] && vetor[i] != 0){            
          vetor[i] *= 3;
          vetor[i+1] = 0;
          vetor[i+2] = 0;
          return vetor[i];
        }
  }
  return 0;
}

int compara_linha(int vetor_antes[5], int vetor_depois[5], bool *mexeu){
    int i, pontos = 0;
    for(i = 0; i<5; i++){
            if(vetor_depois[i] != 0 && vetor_antes[i] != vetor_depois[i]){
                pontos += 1;
                *mexeu = true;
        }
    }

    return pontos;
}

void desliza(int vetor[5], Rg_jogo *jogo){
    int vetor_comparador[5], i;
    for(i = 0; i<5; i++){
        vetor_comparador[i]= vetor[i];
    }

    move_zeros(vetor);
    jogo->jogador_atual.pontos += junta(vetor)*10;
    move_zeros(vetor);
    jogo->jogador_atual.pontos += junta(vetor)*10;
    move_zeros(vetor);

    jogo->jogador_atual.pontos += compara_linha(vetor_comparador, vetor, &jogo->linha_mexeu);

}

void inverte_horizontal(Rg_jogo *jogo){
    int vetor[5];

    for(int i = 0; i < 5;i++){
    
        for(int j = 0; j < 5; j++){
            vetor[j] = jogo->tabuleiro[i][j];
        }
        for(int j = 0, h = 4; j < 5 && h >= 0;j++, h--){
            jogo->tabuleiro[i][j] = vetor[h];
        }
  }
}

void inverte_vertical(Rg_jogo *jogo){
    int matriz[5][5];
    int i, j;

    for(i = 0; i<5; i++){
        for(j = 0; j<5; j++){
            matriz[i][j] = jogo->tabuleiro[i][j];
        }
    }

    for(i = 0; i<5;i++){
        for(j = 0; j<5; j++){
            jogo->tabuleiro[i][j] = matriz[j][i];
        }
    }
     
}

void esquerda(Rg_jogo *jogo){
    int vetor_linha[5];

    for(int i = 0; i<5; i++){

        for(int j = 0; j<5; j ++){
            vetor_linha[j] = jogo->tabuleiro[i][j];
        }

        desliza(vetor_linha, jogo);

        for(int j = 0; j<5; j ++){
            jogo->tabuleiro[i][j] = vetor_linha[j];
        }

    }
    if(jogo->linha_mexeu){
        randomiza_tabuleiro(jogo);
    }
}

void direita(Rg_jogo *jogo){
    inverte_horizontal(jogo);
    esquerda(jogo);
    inverte_horizontal(jogo);
}

void cima(Rg_jogo *jogo){
   inverte_vertical(jogo);
   esquerda(jogo);
   inverte_vertical(jogo);
}

void baixo(Rg_jogo *jogo){
    inverte_vertical(jogo);
    direita(jogo);
    inverte_vertical(jogo);
}

void verifica_tecla(Rg_jogo *jogo){
  jogo->linha_mexeu = false;
  switch (jogo->tecla){
    case c_up:
      cima(jogo);
      break;
    case c_down:
      baixo(jogo);
      break;
    case c_left:
      esquerda(jogo);
      break;
    case c_right:
      direita(jogo);
      break;
    case c_esc:
      jogo->acabou = true;
      break;
  }
    
}

bool acabou_tem_f(int tabuleiro[5][5], bool *ganhou){
    int i,j;
    for(i = 0; i<5; i++){
       for(j = 0; j<5; j++){
            if(tabuleiro[i][j] == 243){
                return true;
            }
        } 
    }
    return false;
}

bool nao_acabou_tem_espaco(int tabuleiro[5][5]){
    int i,j;
    for(i = 0; i<5; i++){
       for(j = 0; j<5; j++){
            if(tabuleiro[i][j] == 0){
                return true;
            }
        } 
    }
    return false;
}

bool nao_acabou_tem_movimento_horizontal(int tabuleiro[5][5]){
    int i,j;

    for(i = 0; i<5; i++){
       for(j = 0; j<3; j++){
            if(tabuleiro[i][j] == tabuleiro[i][j+1] && tabuleiro[i][j] == tabuleiro[i][j+2]){
                return true;
            }
        } 
    }
    return false;
}

bool nao_acabou_tem_movimento_vertical(int tabuleiro[5][5]){
    int i,j;
    for(i = 0; i<3; i++){
       for(j = 0; j<5; j++){
            if(tabuleiro[i][j] == tabuleiro[i+1][j] && tabuleiro[i][j] == tabuleiro[i+2][j]){
                return true;
            }
        } 
    }
    return false;
}

bool acabou(Rg_jogo *jogo){
    if(acabou_tem_f(jogo->tabuleiro, &jogo->ganhou)){
        jogo->ganhou = true;
        return true;
    }

    if(nao_acabou_tem_espaco(jogo->tabuleiro)){
        return false;
    }

    
    if(nao_acabou_tem_movimento_horizontal(jogo->tabuleiro)){
        return false;
    }

    if(nao_acabou_tem_movimento_vertical(jogo->tabuleiro)){
        return false;
    }

    return true;
}

void tela_de_espera(Rg_jogo jogo){
    tela_retangulo(500,320, 780, 400, 10, branco, branco);
    tela_texto_dir(600, 315, 40, jogo.cores.primaria, "Fim!");
    tela_texto_dir(505, 360, 25, jogo.cores.primaria, "Clique enter para sair");

}

void aviso_sair(Rg_jogo jogo){
    tela_retangulo(600, 45, 890, 95, 0, jogo.cores.secundaria, jogo.cores.secundaria);
    tela_texto_dir(606, 60, 20, branco, "Pressione Esc para encerrar");
}

void loop(Rg_jogo *jogo){   
  do{
    tela_tabuleiro(*jogo);
    aviso_sair(*jogo);
    jogo->tecla = tela_tecla();
    jogo->acabou = acabou(jogo);
    verifica_tecla(jogo);
    tela_atualiza();

  } while (jogo->acabou != true);
   do{
    tela_tabuleiro(*jogo);
    tela_de_espera(*jogo);
    tela_atualiza();
   }while(tela_tecla() != c_enter);

}

void partida(Rg_jogo *jogo){
    reseta_valores(jogo);
    srand(time(0));
    randomiza_tabuleiro(jogo);
    randomiza_tabuleiro(jogo);
    loop(jogo);
}

void jogar_novamente(Rg_jogo jogo){
    if(jogo.ganhou == true){
      tela_texto_dir(400, 620, 20, branco, "Ganhou! Jogar novamente?");
    }else{
      tela_texto_dir(400, 620, 20, branco, "Perdeu! Jogar novamente?");
    }
    tela_retangulo(700, 620, 780, 660, 5, jogo.cores.cor[2], jogo.cores.cor[2]);
    tela_retangulo(800, 620, 880, 660, 5, jogo.cores.cor[0], jogo.cores.cor[0]);
    tela_texto_dir(715, 625, 25, branco, "Sim");
    tela_texto_dir(815, 625, 25, branco, "Não");
    tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, branco);
}

void caixa_texto_nome(Rg_jogo jogo){
    char txt[21];
    strcpy(txt, jogo.jogador_atual.nome);
    strcat(txt, "|");

    tela_texto_dir(320, 360, 30, branco, "Digite seu nome:");
    tela_retangulo(320, 400, 960, 480, 5, jogo.cores.secundaria, jogo.cores.primaria);
    tela_texto_dir(330, 420, 30, branco, txt);
}

bool letra_valida(int letra){
    if((letra > 47 && letra < 58) || (letra > 64 && letra < 91) || (letra > 96 && letra < 123)){
        return true;
    }
    return false;
}

void verifica_letra(Rg_jogo *jogo, int letra_int){
    char string_concat[2];
    int tamanho_nome;
    bool valida = false;
    tamanho_nome = strlen(jogo->jogador_atual.nome);

    if(letra_valida(letra_int)){
        valida = true;
    }
    switch (letra_int){
        case c_back:
            if(tamanho_nome > 0){
                jogo->jogador_atual.nome[tamanho_nome-1] = '\0';
            }
            break;
        case c_none:
            break;
        default:
            if(valida == true){
                string_concat[0] = letra_int;
                string_concat[1] = '\0';
                if(tamanho_nome < 20){
                    strcat(jogo->jogador_atual.nome, string_concat);
                }
            }
            break;
    }
}

void tela_pergunta_nome(Rg_jogo *jogo){
    tela_retangulo(0, 0, 1279, 719, 0, jogo->cores.primaria, jogo->cores.primaria);
    tela_placar(*jogo);
    caixa_texto_nome(*jogo);
}

void pergunta_nome(Rg_jogo *jogo){
    int letra;
    do{
        letra = tela_tecla();
        verifica_letra(jogo, letra);
        tela_pergunta_nome(jogo);
        tela_atualiza();
    } while(letra != c_enter);
}

void verifica_ranking(Rg_jogo *jogo){
    int pontos_jogador = jogo->jogador_atual.pontos;
    int ranking[5] = {jogo->ranking[0].pontos, jogo->ranking[1].pontos, jogo->ranking[2].pontos, jogo->ranking[3].pontos, jogo->ranking[4].pontos};

    for(int i=0; i<5; i++){
        if(pontos_jogador > ranking[i]){
            if(i<4){
                jogo->ranking[4] = jogo->ranking[3];
            }
            if(i<3){
                jogo->ranking[3] = jogo->ranking[2];
            }
            if(i<2){
                jogo->ranking[2] = jogo->ranking[1];
            }
            if(i < 1){
                jogo->ranking[1] = jogo->ranking[0];
            }
            jogo->ranking[i] = jogo->jogador_atual;
            break;
        }
    }
}

void imprime_ranking(Rg_jogo jogo){
    char txt[50];
    int i;

    tela_texto_dir(520, 400, 20, branco, "MELHORES PLAYERS");
    for(i = 0; i<5; i++){
        tela_retangulo(400, 110+i*50, 500, 160+i*50, 5, branco, jogo.cores.primaria);
        tela_retangulo(500, 110+i*50, 880, 160+i*50, 5, branco, jogo.cores.primaria);
        sprintf(txt, "%d", jogo.ranking[i].pontos);
        tela_texto_dir(410, 120+i*50, 27, branco, txt);
        tela_texto_dir(510, 120+i*50, 30, branco, jogo.ranking[i].nome);
    }
}

void tela_fim_jogo(Rg_jogo *jogo){
    tela_retangulo(0, 0, 1279, 719, 0, jogo->cores.primaria, jogo->cores.primaria);
    tela_placar(*jogo);
    imprime_ranking(*jogo);
    jogar_novamente(*jogo);
}

void config_fim_jogo(Rg_jogo *jogo){
    int x = 0, y = 0;
    if(jogo->jogador_atual.pontos > 0){
        pergunta_nome(jogo);
        verifica_ranking(jogo);
    }
    while(true){
        tela_fim_jogo(jogo);
        tela_atualiza();
        if(tela_rato_clicado() == true){    
            x = tela_rato_x_clique();
            y = tela_rato_y_clique();
        }
        if(x >= 700 && x <= 780 && y >= 620 && y <=660){
            jogo->resp = true;
            break;  
        }else if(x >= 800 && x <= 880 && y >= 620 && y <=660 ){
            jogo->resp = false;  
            break;
        }
    } 
}

void botao_voltar(Rg_jogo jogo){
    tela_retangulo(800, 620, 880, 660, 5, jogo.cores.secundaria, jogo.cores.secundaria);
    tela_texto_dir(805, 625, 25, branco, "Voltar");
    tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, branco);
}

void botao_reseta_recordes(){
    tela_retangulo(400, 620, 500, 660, 5, vermelho, vermelho);
    tela_texto_dir(405, 625, 25, branco, "Resetar");
}

void reseta_recordes(Rg_jogo *jogo){
    for(int i = 0 ;i < 5 ;i++){
        strcpy(jogo->ranking[i].nome, "-");
        jogo->ranking[i].pontos = 0;
    }
}

void config_tela_recordes(Rg_jogo *jogo){
    int x = 0;
    int y = 0;
    while(true){        
        tela_retangulo(0, 0, 1279, 719, 0, jogo->cores.primaria, jogo->cores.primaria);
        imprime_ranking(*jogo);
        botao_reseta_recordes();
        botao_voltar(*jogo);
        tela_atualiza();
            
        if(tela_rato_clicado() == true){    
            x = tela_rato_x_clique();
            y = tela_rato_y_clique();
        }     
        if(x >= 800 && x <= 880 && y >= 620 && y <=660 ){
            break;
        }else if(x >= 400 && x <= 500 && y >= 620 && y <=660 ){
            reseta_recordes(jogo);
        }
    } 
}

void tela_menu(Rg_jogo jogo){
    tela_retangulo(0, 0, 1279, 719, 0, jogo.cores.primaria, jogo.cores.primaria);
    tela_retangulo(500, 320, 650, 360, 5, jogo.cores.cor[0], jogo.cores.cor[0]);
    tela_retangulo(500, 380, 650, 420, 5, jogo.cores.cor[1], jogo.cores.cor[1]);
    tela_retangulo(500, 440, 650, 480, 5, jogo.cores.cor[2], jogo.cores.cor[2]);
    tela_retangulo(500, 500, 650, 540, 5, branco, branco);
    tela_texto_dir(520, 325, 25, branco, "Jogar");
    tela_texto_dir(520, 385, 25, branco, "Recordes");
    tela_texto_dir(520, 445, 25, branco, "Sair");
    tela_texto_dir(520, 505, 25, preto, "Troca cor");
    tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, branco);
}

void config_tela_menu(Rg_jogo *jogo){
    int x, y;
    le_arquivo(jogo);
    while(true){
        x=0;
        tela_menu(*jogo);
        if(tela_rato_clicado() == true){    
            x = tela_rato_x_clique();
            y = tela_rato_y_clique();
        }
        if(x >= 500 && x <= 650 && y >= 320 && y <=360){
            do{        
                partida(jogo);
                config_fim_jogo(jogo);
            }while(jogo->resp == true);
        }else if(x >= 500 && x <= 650 && y >= 380 && y <=420 ){
            config_tela_recordes(jogo);
        }else if(x >= 500 && x <= 650 && y >= 440 && y <=480 ){
            break;
        }else if(x >= 500 && x <= 650 && y >= 500 && y <=540 ){
            inicializa_cores(jogo);
        }
        tela_atualiza();
    } 
   escreve_arquivo(*jogo);
}

int main() {
   Rg_jogo jogo = {
    .tabuleiro = {{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}},
    .tecla = 0,
    .resp = true,
    .acabou = false,
    .ganhou = false,
    .jogador_atual.pontos = 0,
    .jogador_atual.nome = "",
    .ranking = {{"-", 0}, {"-", 0}, {"-", 0}, {"-", 0}, {"-", 0}},
    .cores.set = true
   };

   tela_inicio(1280, 720, "jogo");
   inicializa_cores(&jogo);
   config_tela_menu(&jogo);

   tela_fim();
   return 0;
}
