#include <stdlib.h>
#include <stdio.h>

#define ARQ "teste.b" // (onte tem ARQ vai ser lido pelo programa como teste.b)
//teste.b e o arquivo binario onde os dados ficaram salvos
typedef struct data
{
    int i;
    char nome[10];
} dados;

int main()
{
    dados VecDados[10];  //VecDados e Read dados são a mesma coisa, com nomes diferentes
    dados ReadDados[10]; //poderia ser usado so um dos dois.
    dados EditDados;     //o mesmo vale para edit dados, poderia ter sido usado uma posição desses arrays de cima

    int grav;
    int lidos;
    char resp;
    char senha[10];
    char senhaLida[10];
    int pos;
    FILE *fp = NULL;
    printf("w para escrever r para ler e para editar\n");
    scanf(" %c", &resp);
    if (resp == 'w') // grava as entradas em um vetor de estruturas do tipo dados e depois escreve esse vetor no arquivo{
        fp = fopen(ARQ, "wb");
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        printf("Digite um numero\n");
        scanf("%d", &VecDados[i].i);
        printf("Digite um nome\n");
        scanf(" %s", &VecDados[i].nome[0]);
    }
    printf("digite uma senha\n");
    scanf(" %s", &senha[0]);
    grav = fwrite(&senha[0], sizeof(senha), 1, fp);
    grav = fwrite(&VecDados[0], sizeof(dados), 10, fp);
    // grav(numero de itens gravados) = fwrite(&endereçoDoVetor, tamanho do elemento, qnt de elementos, ponteiro para o arquivo)
    fclose(fp);

    else if (resp == 'r') //ler o arquivo: grava as informações em um vetor de estruturas do tipo dados e depois imprime esse vetor
    {
        fp = fopen(ARQ, "rb");
        lidos = fread(&senhaLida[0], sizeof(senhaLida), 1, fp);
        lidos = fread(&ReadDados[0], sizeof(dados), 10, fp);
        printf("%d dados lidos\n", lidos);
        printf("senha lida: %s\n", senhaLida);
        int i;
        for (i = 0; i < lidos; i++)
        {
            printf("%d  %s\n", ReadDados[i].i, ReadDados[i].nome);
        }
        fclose(fp);
    }
    else if (resp == 'e') // editar arquivo: coloca o cursor no local que vai ser editado, depois sobreescreve a quantidade de bytes referentes a uma struct dados com a nova informação (no caso outra struct dados, com dados diferentes);
    {
        fp = fopen(ARQ, "rb+");
        printf("digite a posição que deseja editar\n");
        scanf("%d", &pos);
        pos = (pos - 1);
        fseek(fp, 10 * sizeof(char), SEEK_SET);   //pra pular a senha que esta no inicio do arquivo, onde esta a senha
        fseek(fp, pos * sizeof(dados), SEEK_CUR); //
        fread(&EditDados, pos * sizeof(dados), 1, fp);
        fseek(fp, 10 * sizeof(char), SEEK_SET);   //pra pular a senha que esta no inicio do arquivo, onde esta a senha
        fseek(fp, pos * sizeof(dados), SEEK_CUR); //
        printf(" numero: %d \nnome: %s\n", EditDados.i, EditDados.nome);

        printf("Digite o novo numero\n");
        scanf(" %d", &EditDados.i);
        printf("entre o novo nome:\n");
        scanf(" %s", &EditDados.nome[0]);
        grav = fwrite(&EditDados, sizeof(dados), 1, fp);
    }

    else

    {
        printf("resposta invalida digite w ou r\n");
    }
    return 0;
}
/* 

fseek (ponteiro arquivo, quantosbytes vai pular, constante que e o lugar do cursor no arquivo);
constantes:
 SEEK_CUR -> local atual do ponteiro
 SEEK_SET -> local inicial do ponteiro
 SEEK_END -> final do arquivo

outros comandos uteis: 

rewind(ponteiro para arquivo); -> move o cursor para o inicio do arquivo 

fread(); e fwrite() saoo as funções para ler e escrever no arquivo respectivamente
 usei esse link como referencia para escrever todo esse programa:
 https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/ArquivosBinarios.htm


vale lembrar que as funções fread e fwrite retornam numeros inteiros, que sao a 
quantidade de tamanhos predefinidos (que foram passados para essas funções) lidos, 
por isso no programa tempos "int lidos = fread()" assim podemos saber se foram lidos a 
quantidade correta de dados por exemplo o mesmo vale para fwrite() 

*/