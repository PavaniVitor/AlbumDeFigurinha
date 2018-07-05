#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXTENSION ".txt"

//-----------------A FAZER-----------------//

//-> trocar a extensao .txt pela extensao que sera utilizada nos arquivos binarios

//-> definir um algoritmo para escrever nos arquivos binarios, de forma que esses dados
//   possam ser lidos e alterados dinamicamente durante a execuçao do programa


FILE* cadastro()
{
    FILE *fp;
    char ext[] = EXTENSION;
    char usuario[24] = {};
    char senha[10]= {};
    printf("Digite o nome do usuario ate 20 caracteres\n");
    scanf("%s", &usuario[0]);
    
    if(strlen(usuario)<=20)
    {
        strcat(usuario , EXTENSION);

        if (fp)
        {
            printf("esse usuario ja existe\n");
            fclose(fp);
            return NULL;
        }
        else
        {
            fp = fopen(usuario, "w+");
            printf("novo usuario criado\n");
            printf("Digite a senha ate 10 caracteres\n");
            scanf("%s", &senha[0]);
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
void main()
{
    login();
    while(cadastro())
    {
        cadastro();
    }
}