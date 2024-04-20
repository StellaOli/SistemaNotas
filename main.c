#include "funcoes.c.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
int opcao;
do {
opcao = menu();
  if (opcao == 1){
    cad_disciplina();
  }
  else if(opcao == 2){
    cad_aluno();
  }
  else if (opcao == 3){
    cad_professor();
  }
  else if (opcao == 4){
    cad_turma();
  }else if(opcao == 5){
    cad_nota();
    
  }
  else if(opcao == 6){
    relatorio();
  }else if (opcao ==7){
    
    
    char arquivo[100];
    char informacao[100];
    printf("Digite o nome do arquivo:\n ");
    fgets(arquivo, sizeof(arquivo), stdin);

    printf("Digite a informação a ser apagada: ");
    fgets(informacao, sizeof(informacao), stdin);

    apagar_dados(arquivo, informacao);
  }
}  while(opcao != 0);
  }