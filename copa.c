#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXTENSION ".cup"
#define MAXFIGS 700     // trocar pelo numero correto de figurinhas que o album vai possuir
#define PAGES 50        // trocar pelo numero correto de paginas do album
#define FIGSPAGE 10     // trocar pelo numero correto de figurinhas por pagina

//-----------------A FAZER-----------------//

//-> trocar a extensao .txt pela extensao que sera utilizada nos arquivos binarios

//-> definir um algoritmo para escrever nos arquivos binarios, de forma que esses dados
//   possam ser lidos e alterados dinamicamente durante a execuçao do programa

//-------------LEMBRAR:-------------------//
// usar wb+ para criar arquivos, mas as funçoes devem retornar ponteiros RB+ para ediçao!!!!

typedef struct stickers
{
    unsigned int numero;
    unsigned int quantidade;
    char nome[20];
}figura;

typedef struct users
{
    char usuario[20];
    char password[10];
}user;

int ArqVazio(FILE* fp)
{
    int gravando = 0;
    figura vazia;
    vazia.nome [0] = '\0';
    vazia.quantidade = 0;
    int i;
    for (i = 1; i <= MAXFIGS; i++)
    {
        vazia.numero = i;
        gravando += fwrite(&vazia , sizeof(figura), 1 , fp);
    }
    if(gravando == MAXFIGS)
    {
        printf("usuario criado com sucesso\n");
        return 1;
    }
    else
    {
        printf("falha ao criar usuario %d", gravando);
        return 0;
    }
}

FILE* cadastro()
{
    FILE *fp = NULL;
    int grav;
    char ext[] = EXTENSION;
    user novo;
    printf("Digite o nome do usuario ate 20 caracteres\n");
    scanf("%s", &novo.usuario[0]);
    
    if(strlen(novo.usuario)<=20)
    {
        strcat(novo.usuario , ext);
        fp = fopen(novo.usuario, "rb");

        if (fp)
        {
            printf("esse usuario ja existe\n");
            fclose(fp);
            return NULL;
        }
        else
        {
            fp = fopen(novo.usuario, "wb+");
            fclose(fp);
            fp = fopen(novo.usuario,  "rb+");
            printf("Digite a senha ate 10 caracteres\n");
            scanf(" %s", &novo.password[0]);
            rewind(fp);
            grav = fwrite (&novo,sizeof(user),1,fp); //grava a senha no arquivo 
            ArqVazio(fp);
            return fp;
        }
    }
    else
    {
        printf("Digite um nome de usuario de ate 20 caracteres\n");
    }
    return NULL; // retornou NULL a gente sabe que ocorreu um erro na hora de criar o usuario;
}
FILE* login()
//funçao de login: retorna o ponteiro para o arquivo que o usuario abriu, dessa forma podemos identificar se o usuario ja esta logado por exemplo
{ //colocar a extensao que vai ser utilizada pelos arquivos binarios

    char usuario[24];
    char senha[10];
    char senhaLida[10];
    FILE* fp = NULL; 
    printf("\nLogin:\n");
    printf ("Digite o nome de usuario:\n");
    scanf ("%s", &usuario[0]);
    if (strlen(usuario)>20)
    {
        printf("o nome de usuario vai até 20 caracteres\n");
        return NULL;
    }
    else
    {
        strcat(usuario, EXTENSION);
        fp = fopen(usuario,"rb");
        if (fp)
        {

            fp = fopen(usuario,"rb+");
            printf("Digite a senha:\n");
            scanf(" %s",&senha[0]);
            rewind(fp);
            fread(&senhaLida[0],10*sizeof(char),1,fp);
            if(strcmp(senha, senhaLida) == 0)
            {
                printf("Senha digitada com sucesso\n");
                return fp;
            }
            else
            {
                printf("Senha incorreta\n");
                return NULL;
            }
        }
        else
        {
            printf("Usuario nao encontrado \n");
            return NULL;
        }
    }
}
void PrintPage(FILE* fp, unsigned int page)
{
    printf ("Pagina: %d\n" ,page);
    figura leitura;
    page  = page - 1;
    fseek(fp ,sizeof(user),SEEK_SET); //pula a senha com o cursor
    if (page == 0)
    {
        int i;
        for(i = 0 ; i < FIGSPAGE ; i++)
        {
            fread(&leitura , sizeof (figura), 1 , fp);
            printf (" %d %s %d\n", leitura.numero, leitura.nome , leitura.quantidade);
        }
    }
    else
    {
        int i;
        fseek(fp, FIGSPAGE*sizeof(figura)*page,SEEK_CUR);
        for (i = 0 ; i<FIGSPAGE ; i++)
        {
            fread(&leitura , sizeof (figura), 1 , fp);
            printf (" %d %s %d\n", leitura.numero, leitura.nome , leitura.quantidade);
        }
    }
}
void troca(FILE* fp1)
{
    char respLog = 's';
    FILE* fp2 = NULL;
    printf("Troca de Figurinhas!\n");
    printf("solicite o login do outro usuario:\n");
    while (respLog == 's')
    {
        fp2 = login();
    }
}
int CmpArqv(FILE* fp1, FILE* fp2)
{

}
void main()
{
    int page;
    FILE* user = NULL;
    //user = login();
    //troca(user);
    user = cadastro();
    printf("Digite a pagina que deseja visualizar\n");
    scanf(" %d", &page);
    PrintPage(user , page);
}