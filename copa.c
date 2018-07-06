#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXTENSION ".cup"
#define MAXFIGS 700 // trocar pelo numero correto de figurinhas que o album vai possuir

//-----------------A FAZER-----------------//

//-> trocar a extensao .txt pela extensao que sera utilizada nos arquivos binarios

//-> definir um algoritmo para escrever nos arquivos binarios, de forma que esses dados
//   possam ser lidos e alterados dinamicamente durante a execuçao do programa

typedef struct stickers
{
    unsigned int numero;
    unsigned int quantidade;
    char nome[20];
}figura;

int ArqVazio(FILE* fp)
{
    int gravando = 0;
    figura vazia;
    vazia.nome [0] = '\0';
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
    char usuario[24] = {};
    char senha[10]= {};
    printf("Digite o nome do usuario ate 20 caracteres\n");
    scanf("%s", &usuario[0]);
    
    if(strlen(usuario)<=20)
    {
        strcat(usuario , ext);
        fp = fopen(usuario, "rb");

        if (fp)
        {
            printf("esse usuario ja existe\n");
            fclose(fp);
            return NULL;
        }
        else
        {
            fp = fopen(usuario, "wb");
            printf("Digite a senha ate 10 caracteres\n");
            scanf("%s", &senha[0]);
            grav = fwrite (&senha,sizeof(senha),1,fp); //grava a senha no arquivo 
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
    FILE* fp = NULL; 
    printf("\nLogin:\n");
    printf ("Digite o nome de usuario:\n");
    scanf ("%s", &usuario[0]);
    if (strlen(usuario)>20)
    {
        printf("o nome de usuario só vai até 20 caracteres\n");
        return NULL;
    }
    else
    {
        strcat(usuario, EXTENSION);
        fp = fopen(usuario,"r");
        if (fp)
        {
            printf("Digite a senha:\n");
            scanf(" %s",&senha[0]);
            // se tudo der certo retorna fp
            // preciso defnir um padrao de leitura e escrita no arquivo, para poder ler e escrever senhas
        }
        else
        {
            printf("Usuario nao encontrado \n");
            return NULL;
        }
    }
}
void LerAlbum(FILE* fp)
{

}
void main()
{
    FILE* user = NULL;
    //login();
    while(user == NULL)
    {
        user = cadastro();
    }
}