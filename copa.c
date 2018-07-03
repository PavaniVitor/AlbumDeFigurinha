#include <stdio.h>
#include <stdlib.h>

int cadastro()
{
    FILE *fp;
    int count = 0;
    char usuario[25] = {};
    char senha[8]= {};
    printf("Digite o nome do usuario\n");
    scanf("%s", &usuario[0]);

    while (usuario[count]!='\0')
    {
        count++;
    }
    if(count < 20)
    {
        usuario[count] = '.';
        usuario[count+1] = 't';
        usuario[count+2] = 'x';
        usuario[count+3] = 't';
        fp = fopen(usuario, "r");

        if (fp)
        {
            printf("esse usuario ja existe\n");
            return 1;
            fclose(fp);
        }
        else
        {
            fp = fopen(usuario, "w+");
            printf("novo usuario criado\n");
            printf("Digite a senha\n");
            scanf("%s", &senha[0]);
            return 0;
        }
        
    }
    else
    {
        printf("numero maximo de caracteres atingidos\n");
    }
    return 1; // retornou 1 a gente sabe que ocorreu um erro na hora de criar o usuario;
}
void main()
{
    while(cadastro())
    {
        cadastro();
    }
}