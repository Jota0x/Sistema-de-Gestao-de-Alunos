#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALUNOS 100

void cadastratAluno();
void listarAluno();
void sairComAnimacao();
void salvarDados();
void carregarDados();

int main()
{
    // Chamar funcao carregarDados
    carregarDados(); // Gera arquivo dadosAlunos.txt
    int opcao;

    do
    {
        printf("--- Sistema Aluno ---");
        printf(" 1. Cadastrar aluno ");
        printf(" 2. Listar aluno ");
        printf(" 0. Sair");
        printf(" Escolha uma opcao ");
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            // Chamar função cadastrarAluno
            cadastrarAluno();
            break;
        case 2:
            // Chamar função listarAluno
            listarAluno();
            break;
        case 0:
            // Chamar função sairComAnimacao e salvarDados
            sairComAnimacao();
            salvarDados();
            break;
        default:
            printf("Opcao invalida ");

        } // Fim switch
    } while (opcao != 0);

    return 0;

} // Fim main

// Struct para definir oque será pedido do aluno
typedef struct
{
    char nome[50];
    int matricula;
    float nota;
} Aluno;

// Vetor para controle de alunos cadastrados
Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

// Função para cadastrar aluno
void cadastrarAluno()
{
    if (totalAlunos >= MAX_ALUNOS)
    {
        printf("\n Total de alunos atingido! ");
        return;
    } // Fim if

    // Ler nome
    printf("Nome: ");
    scanf("% c", alunos[totalAlunos].nome);

    // Ler matricula
    printf("Matricula: ");
    scanf("% c", alunos[totalAlunos].matricula);
    // Ler nota
    printf("Nota: ");
    scanf("% c", alunos[totalAlunos].nota);

    totalAlunos++;

    printf("Aluno cadastrado com sucesso");

} // Fim cadastratAluno

// Função listar aluno
void listarAluno()
{
    if (totalAlunos == 0)
    {
        printf("Nenhum aluno cadastrado");
        return;
    } // Fim if

    printf("--- Lista Alunos---");
    for (int i = 0; i < totalAlunos; i++)
    {
        printf(" %s | Matricula: %i | Nota: %f ", i + 1, alunos[i].nome, alunos[i].matricula, alunos[i].nota);

    } // Fim for(i)
} // Fim aluno

// Função para animação terminal
void sairComAnimacao()
{
    printf("Saindo");
    fflush(stdout); // força imprimir antes do sleep

    for (int i = 0; i < 3; i++)
    {
        sleep(1); // espera 1 segundo
        printf(".");
        fflush(stdout);
    }

    printf("\n");
} // Fim sairComAnimação

// Função para salvar dados
void salvarDados()
{
    FILE *arquivo = fopen("dadosAlunos.txt", 'w');
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo");
        return;
    } // Fim if

    for (int i = 0; i < totalAlunos; i++)
    {
        fprintf(arquivo, "%s;%d;%.2f\n", alunos[i].nome, alunos[i].matricula, alunos[i].nota);
    } // Fim for(i)

    fclose(arquivo);
    printf("Dados salvos em dadosAlunos.txt com sucesso! ");

} // Fim salvarDados

// Função para carregar dados
void carregarDados()
{
    FILE *arquivo = fopen("dadosAlunos.txt", "r");
    if (arquivo == NULL)
    {
        return;
    } // Fim if

    while (fscanf(arquivo, "% c, %d,%f", alunos[totalAlunos].nome, alunos[totalAlunos].matricula, alunos[totalAlunos].nota) == 3)
    {
        totalAlunos++;
    } // Fim while

    fclose(arquivo);
    printf("Dados carregados ded dadosAlunos.txt com sucesso!");

} // Fim carregarDados