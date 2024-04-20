#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu() {
  puts("");
  puts("=============");
  puts("1 - Cadastro de Disciplina ");
  // código, um nome, os pesos de cada prova e a média de aprovação;
  puts("2 - Cadastro de Aluno ");
  // numero da matricula e nome do aluno
  puts("3 - Cadastro do Professor ");
  // nome completo e senha, irá gerar um numero de identificação
  puts("4 - Cadastro de Turma ");
  // identificação,uma disciplina,o numero da turma,professor(a) e até 10
  // alunos(as)
  puts("5 - Adicionar Nota do aluno");
  // acessa a turma, busca pelo aluno e adiciona a nota, necessario
  // identificação do professor e matrciula do aluno
  puts("6 - Relatorio de Turmas ");
  // gera relatorio da turma
  puts("7 - Apagar dados: ");
  // numero do professor

  puts("0 - Sair ");
  printf("opcao => ");
  int op;
  scanf("%d", &op);

  return op;
}
//struct que salva os dados do aluno juntos
struct aluno {
  int matricula;
  char nome_aluno[50];
};
//essa função cria um arquivo binario que salva todos os alunos cadastrados
void cad_aluno() {

  struct aluno d;

  char nome_aluno[50];
  printf("\n");
  printf("Insira o nome do aluno(a): ");
  scanf("%s", nome_aluno);
  strcpy(d.nome_aluno, nome_aluno);

  printf("Insira a matricula do aluno: ");
  scanf("%d", &d.matricula);

  FILE *f = fopen("Alunos", "wb");
  fwrite(&d, 1, sizeof(struct aluno), f);
  fclose(f);

  f = fopen("Alunos", "rb");
  if (f == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }
  printf("Conteúdo do arquivo:\n");
  while (fread(&d, sizeof(struct aluno), 1, f) > 0) {
    printf("Nome: %s\n", d.nome_aluno);
    printf("Numero de Matricula: %d\n", d.matricula);

    printf("--------------------\n");
  }
  fclose(f);
}
// a struct serve para salvar as informações juntas 
struct disciplina {
  int peso_prova1;
  int peso_prova2;
  int media;
  char codigo[7];
  char nome[50];
};
//essa função recebe os dados do usuario e cria um arquivo binario com o nome da disciplina
void cad_disciplina() {

  struct disciplina d;
  printf("\n");
  puts("Cadastrar disciplinas(1),Ver disciplinas cadastradas(2): ");
  printf("Opção --> ");
  int op;
  scanf("%d", &op);

  if (op == 1) {
    char codigo[7];
    printf("\n");
    printf("Insira o codigo da disciplina: ");
    scanf("%s", codigo);
    strcpy(d.codigo, codigo);

    char nome[50];
    printf("Insira o nome da disciplina: ");
    scanf("%s", nome);
    strcpy(d.nome, nome);

    printf("Insira o peso da prova 1: ");
    scanf("%d", &d.peso_prova1);

    printf("Insira o peso da prova 2: ");
    scanf("%d", &d.peso_prova2);

    printf("Insira a media da disciplina: ");
    scanf("%d", &d.media);

    FILE *f = fopen(d.codigo, "wb");
    fwrite(&d, 1, sizeof(struct disciplina), f);
    fclose(f);
  } else {
    char codigo[7];

    printf("Digite o codigo da disciplina que deseja ver: ");
    scanf("%s", codigo);

    FILE *f = fopen(codigo, "rb");
    if (f == NULL) {
      printf("Erro ao abrir o arquivo.\n");

    } else {
      printf("Conteúdo do arquivo:\n");
      while (fread(&d, sizeof(struct disciplina), 1, f) > 0) {
        printf("Codigo: %s\n", d.codigo);
        printf("Nome: %s\n", d.nome);
        printf("Peso 1ª prova: %d\n", d.peso_prova1);
        printf("Peso 2ª prova: %d\n", d.peso_prova2);
        printf("Media: %d\n", d.media);

        printf("--------------------\n");
      }
      fclose(f);
    }
  }
}
//struct com os dados do professor e uma int id que sera gerada na funçaõ
struct professor {
  int senha;
  char professor[50];
  int id;
};
//função receb dados do usuario cadastra no sistema e gera um id que é acoplado a struct 
void cad_professor() {
  struct professor d;

  char professor[50];
  printf("\n");
  printf("Insira seu nome: ");
  scanf("%s", professor);
  strcpy(d.professor, professor);

  printf("Insira uma senha: ");
  scanf("%d", &d.senha);

  printf("Um numero de identificação será gerado \n");

  srand(time(NULL));
  int numeroIdentificacao = rand() % 9000 + 1000;

  d.id = numeroIdentificacao;

  printf("Número de Identificação: %d\n", numeroIdentificacao);

  FILE *f = fopen("Professores", "ab");
  if (f == NULL)
    printf("Arquivo não encontrado");
  else {
    fwrite(&d, 1, sizeof(struct professor), f);

    fclose(f);
  }
  f = fopen("Professores", "rb");
  if (f == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }
  printf("Conteúdo do arquivo:\n");
  while (fread(&d, sizeof(struct professor), 1, f) > 0) {
    printf("Nome: %s\n", d.professor);
    printf("senha: %d\n", d.senha);
    printf("Id: %d\n", d.id);
    printf("--------------------\n");
  }
  fclose(f);
}

//mesmo esquema das outras structs
struct turma {

  int id;
  char disciplina[7];
  char num_turma[4];
  int alunos[10];
  int total_alunos;
  float notas1[10];
  float notas2[10];
  float media[10];
};

//recebe os dados e possui um laço de repetição para cadastrar a quantidade de alunos certa 
void cad_turma() {
  struct turma d;

  printf("\n");

  printf("Insira sua identificação: ");
  scanf("%d", &d.id);

  char disciplina[7];
  printf("Insira o codigo da disciplina: ");
  scanf("%s", disciplina);
  strcpy(d.disciplina, disciplina);
  d.disciplina[strcspn(d.disciplina, "\n")] = '\0';

  char num_turma[4];
  printf("Insira o numero da turma: ");
  scanf("%s", num_turma);
  strcpy(d.num_turma, num_turma);
  d.num_turma[strcspn(d.num_turma, "\n")] = '\0';

  printf("Insira a quantidade de alunos: ");
  scanf("%d", d.alunos);

  printf("A sala tem quantos alunos: ");
  scanf("%d", &d.total_alunos);

  for (int i = 0; i < d.total_alunos; i++) {
    printf("Codigo do aluno %d:  ", i + 1);
    scanf("%d", &d.alunos[i]);
    printf("%d\n", d.alunos[i]);

    printf("Quantidade de notas para a prova 1 do aluno %d: ", i + 1);
    scanf("%f", &d.notas1[i]);
    printf("%f\n", d.notas1[i]);

    printf("Quantidade de notas para a prova 2 do aluno %d: ", i + 1);
    scanf("%f", &d.notas2[i]);
    printf("%f\n", d.notas2[i]);

    printf("Quantidade de medias do aluno %d: ", i + 1);
    scanf("%f", &d.media[i]);
    printf("%f\n", d.media[i]);
  }

  FILE *f = fopen(num_turma, "ab");
  if (f == NULL)
    printf("Arquivo não encontrado");
  else {
    fwrite(&d, 1, sizeof(struct turma), f);

    fclose(f);
  }
  f = fopen(num_turma, "rb");
  if (f == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }
  printf("Conteúdo do arquivo:\n");
  while (fread(&d, sizeof(struct turma), 1, f) > 0) {
    printf("Nome: %s\n", d.disciplina);
    printf("Turma: %s\n", d.num_turma);
    printf("Id: %d\n", d.id);
    printf("--------------------\n");
  }
  fclose(f);
}
// a funçaõ de relatorio confere se existe uma disciplina cadastrada, se houver é pedido o numero da turma e impresso todos os dados do arquivo
void relatorio() {
  FILE *arquivo;
  struct disciplina d;
  struct turma t;
  char codigo[7];
  char num_turma[4];

  printf("Digite o codigo da disciplina: ");
  scanf("%s", codigo);

  arquivo = fopen(codigo, "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");

  } else {
    fclose(arquivo);
  }
  FILE *f;

  printf("Digite o numero da turma: ");
  scanf("%s", num_turma);
  f = fopen(num_turma, "rb");
  if (f == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }
  fread(&t, sizeof(struct turma), 1, arquivo);
  printf("Turma:\n");
  printf("Número da turma: %s\n", t.num_turma);
  printf("Professor: %d\n", t.id);
  printf("Codigo da disciplina: %s\n", t.disciplina);
  for (int i = 0; i < t.total_alunos; i++) {
    printf("Matricula do Aluno: %d\n", t.alunos[i]);
    printf("Nota 1:\t%.2f\n", t.notas1[i]);
    printf("Nota 2:\t%.2f\n", t.notas2[i]);
    printf("Media:\t%.2f\n", t.media[i]);
    printf("\n");
  }
}
//Essa função abre a disciplina escolhida,c coleta os dados de valor de prova e media e usa para a tuma dessa disciplina
void cad_nota() {
  FILE *f;
  struct disciplina d;
  struct turma t;
  char codigo[7];
  char num_turma[4];

  printf("Digite o codigo da disciplina: ");
  scanf("%s", codigo);

  f = fopen(codigo, "rb");
  if (f == NULL) {
    printf("Erro ao abrir o arquivo.\n");
  }
  printf("Conteúdo do arquivo:\n");
  while (fread(&d, sizeof(struct disciplina), 1, f) > 0) {
    printf("Peso prova 1: %d\n", d.peso_prova1);
    printf("Peso prova 2: %d\n", d.peso_prova2);
    printf("Media: %d\n", d.media);
    printf("--------------------\n");
  }
  fclose(f);

  FILE *g;
  printf("Digite o numero da turma: ");
  scanf("%s", num_turma);

  g = fopen(num_turma, "rb");
  if (g == NULL) {
    printf("Erro ao abrir o arquivo.\n");

  } else {
    fread(&t, sizeof(struct turma), 1, g);
    fclose(g);
    for (int i = 0; i < t.total_alunos; i++) {
      printf("Entre com as notas do aluno %d\n", t.alunos[i]);
      printf("Nota 1: ");
      scanf("%f", &t.notas1[i]);
      printf("Nota 2: ");
      scanf("%f", &t.notas2[i]);
      t.media[i] = ((t.notas1[i] * d.peso_prova1) / 100) +
                   ((t.notas2[i] * d.peso_prova2) / 100);
      printf("%.2f\n", t.media[i] );
      if(t.media[i] >= d.media){
        printf("Aprovado");
      }else{
        printf("Reprovado");
      }
    }
  }
  g = fopen(num_turma, "wb");
  if (g == NULL) {
    printf("Erro ao abrir o arquivo.\n");

  } else {
    fwrite(&t, sizeof(struct turma), 1, g);
    fclose(g);
  }
}

//Essa função recebe duas informações na main e as usa para conferir que arquivo será alterado e que informação dentro do arquivo sera apagada, ele faz isso lendo o arquivo original e gerando um temporario onde a modificação será feita, o arquivo original então é apagado e o temporario vira o atual
void apagar_dados(const char *arquivo, const char *informacao) {
  FILE *arquivoOrigem, *arquivoTemp;
  char linha[1000];

  arquivoOrigem = fopen(arquivo, "rb");
  if (arquivoOrigem == NULL) {
    printf("Erro ao abrir o arquivo de origem.\n");
    return;
  }

  arquivoTemp = fopen("temp.txt", "wb");
  if (arquivoTemp == NULL) {
    printf("Erro ao abrir o arquivo temporário.\n");
    fclose(arquivoOrigem);
    return;
  }
  while (fgets(linha, sizeof(linha), arquivoOrigem) != NULL) {
    if (strstr(linha, informacao) == NULL) {
      fputs(linha, arquivoTemp);
    }
  }

  fclose(arquivoOrigem);
  fclose(arquivoTemp);

  if (remove(arquivo) != 0) {
    printf("Erro ao apagar o arquivo de origem.\n");
    return;
  }

  if (rename("temp.txt", arquivo) != 0) {
    printf("Erro ao renomear o arquivo temporário.\n");
    return;
  }

  printf("Informação apagada com sucesso.\n");
}
