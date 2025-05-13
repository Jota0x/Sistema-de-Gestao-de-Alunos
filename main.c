#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALUNOS 100

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

// Declaração das funções
void cadastrarAluno();
void listarAluno();
void sairComAnimacao();
void salvarDados();
void carregarDados();

int main()
{
    // Chamar funcao carregarDados
    carregarDados(); // Carrega dados do arquivo
    int opcao;

    do
    {
        printf("\n--- Sistema Aluno ---\n");
        printf("  1. Cadastrar aluno\n ");
        printf(" 2. Listar aluno\n ");
        printf(" 0. Sair\n");
        printf(" Escolha uma opcao: ");
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
            salvarDados(); // Salvar antes de sair
            sairComAnimacao();
            break;
        default:
            printf("Opcao invalida ");

        } // Fim switch
    } while (opcao != 0);

    return 0;

} // Fim main()

// Função para cadastrar aluno
void cadastrarAluno()
{
    if (totalAlunos >= MAX_ALUNOS)
    {
        printf("\nTotal de alunos atingido!\n");
        return;
    } // Fim if

    // Limpar o buffer de entrada antes de ler o nome
    while (getchar() != '\n')
        ;

    // Ler nome completo (com espaços)
    printf("\nNome: ");
    fgets(alunos[totalAlunos].nome, 50, stdin);

    // Remover a quebra de linha (\n) que o fgets captura
    alunos[totalAlunos].nome[strcspn(alunos[totalAlunos].nome, "\n")] = '\0';

    // Ler matricula
    printf("Matricula: ");
    scanf("%i", &alunos[totalAlunos].matricula);

    // Ler nota
    printf("Nota: ");
    scanf("%f", &alunos[totalAlunos].nota);

    totalAlunos++;
    printf("\nAluno cadastrado com sucesso!\n");

} // Fim cadastratAluno

// Função listar aluno
void listarAluno()
{
    if (totalAlunos == 0)
    {
        printf("\nNenhum aluno cadastrado!\n");
        return;
    } // Fim if

    printf("\n--- Lista Alunos---\n");
    for (int i = 0; i < totalAlunos; i++)
    {
        printf(" %i. %s | Matricula: %i | Nota: %.2f\n", i + 1, alunos[i].nome, alunos[i].matricula, alunos[i].nota);

    } // Fim for(i)
} // Fim aluno()

// Função para animação terminal
void sairComAnimacao()
{
    printf("\nSaindo");
    fflush(stdout); // força imprimir antes do sleep

    for (int i = 0; i < 3; i++)
    {
        sleep(1); // espera 1 segundo
        printf(".");
        fflush(stdout);
    }

    printf("\n");
} // Fim sairComAnimação()

// Função para salvar dados
void salvarDados()
{
    FILE *arquivo = fopen("dadosAlunos.txt", "w");
    if (arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
        return;
    } // Fim if

    for (int i = 0; i < totalAlunos; i++)
    {
        fprintf(arquivo, "%s|%i|%.2f\n", alunos[i].nome, alunos[i].matricula, alunos[i].nota);
    } // Fim for(i)

    fclose(arquivo);
    printf("Dados salvos em dadosAlunos.txt com sucesso! ");

} // Fim salvarDados()

#include <stdlib.h> // Adicione esta linha no início para atoi() e atof()

void carregarDados()
{
    FILE *arquivo = fopen("dadosAlunos.txt", "r");
    if (arquivo == NULL)
    {
        printf("\nArquivo de dados não encontrado. Iniciando com lista vazia.\n");
        return;
    }

    totalAlunos = 0;
    char linha[150]; // Buffer para cada linha do arquivo

    while (totalAlunos < MAX_ALUNOS && fgets(linha, sizeof(linha), arquivo))
    {
        // Remove a quebra de linha no final
        linha[strcspn(linha, "\n")] = '\0';

        char *token = strtok(linha, "|");
        if (!token)
            continue;

        // Copia o nome (com segurança)
        strncpy(alunos[totalAlunos].nome, token, 49);
        alunos[totalAlunos].nome[49] = '\0';

        // Lê matrícula
        token = strtok(NULL, "|");
        if (!token)
            continue;
        alunos[totalAlunos].matricula = atoi(token);

        // Lê nota
        token = strtok(NULL, "|");
        if (!token)
            continue;
        alunos[totalAlunos].nota = atof(token);

        totalAlunos++;
    } // Fim while

    fclose(arquivo);
    printf("\nDados carregados com sucesso! (%d alunos)\n", totalAlunos);
} // Fim carregarDados()s