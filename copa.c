#include <stdio.h>
#include <stdlib.h>

void cadastro()
{
    FILE *fp;
    char usuario[20];
    char senha[8];
    printf("Digite o nome do usuario");
    scanf("%s" , &usuario[0]);
    printf("Digite a senha");
    scanf("%s", &senha[0]);
    printf("%s",senha);

    fp = fopen(usuario ,"w+");
    fclose(fp);
}
void main()
{
    cadastro();
}