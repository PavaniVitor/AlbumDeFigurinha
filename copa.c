#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXTENSION ".cup"
#define MAXFIGS 640    
#define PAGES 64       
#define FIGSPAGE 10    

#ifdef __linux__
#define LIMPAR "clear"
#elif _WIN32
#define LIMPAR "cls"
#endif

typedef struct stickers
{
    unsigned int numero;
    unsigned int quantidade;
    char nome[20];
} figura;

typedef struct users
{
    char usuario[20];
    char password[10];
} user;

int ArqVazio(FILE *fp)
{
    int gravando = 0;
    figura vazia;
    vazia.nome[0] = '\0';
    vazia.quantidade = 0;
    int i;
    for (i = 1; i <= MAXFIGS; i++)
    {
        vazia.numero = i;
        gravando += fwrite(&vazia, sizeof(figura), 1, fp);
    }
    if (gravando == MAXFIGS)
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
FILE *cadastro()
{
    FILE *fp = NULL;
    int grav;
    char ext[] = EXTENSION;
    user novo;
    printf("Digite o nome do usuario ate 20 caracteres\n");
    scanf("%s", &novo.usuario[0]);

    if (strlen(novo.usuario) <= 20)
    {
        strcat(novo.usuario, ext);
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
            fp = fopen(novo.usuario, "rb+");
            printf("Digite a senha ate 10 caracteres\n");
            scanf(" %s", &novo.password[0]);
            rewind(fp);
            grav = fwrite(&novo, sizeof(user), 1, fp);
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
void GravString(FILE *fp, unsigned int numFig)
{
    int figPos = numFig - 1;
    char resp;
    char nomeFig[20];
    figura lida;
    fseek(fp, sizeof(user), SEEK_SET);
    if (numFig == 1)
    {
        fread(&lida, sizeof(figura), 1, fp);
    }
    else
    {
        fseek(fp, figPos * sizeof(figura), SEEK_CUR);
        fread(&lida, sizeof(figura), 1, fp);
    }
    if (strlen(lida.nome) == 0)
    {
        printf("Deseja inserir o nome na figura %d?[s/n]", lida.numero);
        scanf(" %c", &resp);
        if (resp == 's')
        {
            printf("Digite o nome da figura\n");
            scanf(" %s", &nomeFig[0]);
            strcpy(lida.nome, nomeFig);
            fseek(fp, sizeof(user), SEEK_SET);
            if (numFig == 1)
            {
                fwrite(&lida, sizeof(figura), 1, fp);
            }
            else
            {
                fseek(fp, figPos * sizeof(figura), SEEK_CUR);
                fwrite(&lida, sizeof(figura), 1, fp);
            }
        }
    }
}
void GravFig(int unsigned NumFig, int QuantFig, FILE *fp)
{
    int FigPos;
    figura grav;
    FigPos = NumFig - 1;
    fseek(fp, sizeof(user), SEEK_SET);
    if (NumFig == 1)
    {
        fread(&grav, sizeof(figura), 1, fp);
        grav.quantidade = grav.quantidade + QuantFig;
        fseek(fp, sizeof(user), SEEK_SET);
        fwrite(&grav, sizeof(figura), 1, fp);
    }
    else
    {
        fseek(fp, FigPos * sizeof(figura), SEEK_CUR);
        fread(&grav, sizeof(figura), 1, fp);
        grav.quantidade = grav.quantidade + QuantFig;
        fseek(fp, sizeof(user), SEEK_SET);
        fseek(fp, FigPos * sizeof(figura), SEEK_CUR);
        fwrite(&grav, sizeof(figura), 1, fp);
    }
    GravString(fp, NumFig);
}
FILE *login()
//funçao de login: retorna o ponteiro para o arquivo que o usuario abriu, dessa forma podemos identificar se o usuario ja esta logado por exemplo
{ //colocar a extensao que vai ser utilizada pelos arquivos binarios

    user usuario;
    user userLido;
    FILE *fp = NULL;
    printf("\nLogin:\n");
    printf("Digite o nome de usuario:\n");
    scanf("%s", &usuario.usuario[0]);
    if (strlen(usuario.usuario) > 20)
    {
        printf("o nome de usuario vai até 20 caracteres\n");
        return NULL;
    }
    else
    {
        strcat(usuario.usuario, EXTENSION);
        fp = fopen(usuario.usuario, "rb");
        if (fp)
        {

            fp = fopen(usuario.usuario, "rb+");
            printf("Digite a senha:\n");
            scanf(" %s", &usuario.password[0]);
            rewind(fp);
            fread(&userLido, sizeof(user), 1, fp);
            if (strcmp(userLido.password, usuario.password) == 0)
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
void ImprimirPag(FILE *fp, unsigned int page)
{
    if (page <= PAGES)
    {
        printf("Pagina: %d\n", page);
        figura leitura;
        page = page - 1;
        fseek(fp, sizeof(user), SEEK_SET); //pula a senha com o cursor
        if (page == 0)
        {
            int i;
            for (i = 0; i < FIGSPAGE; i++)
            {
                fread(&leitura, sizeof(figura), 1, fp);
                printf(" %3d %d %s\n", leitura.numero, leitura.quantidade, leitura.nome);
            }
        }
        else
        {
            int i;
            fseek(fp, FIGSPAGE * sizeof(figura) * page, SEEK_CUR);
            for (i = 0; i < FIGSPAGE; i++)
            {
                fread(&leitura, sizeof(figura), 1, fp);
                printf(" %3d %d %s\n", leitura.numero, leitura.quantidade, leitura.nome);
            }
        }
    }
    else
    {
        printf("O Album so vai ate a pagina %d\n" , PAGES);
    }
}

int CmpArqv(FILE *fp1, FILE *fp2)
{
    user logados[2];
    rewind(fp1);
    rewind(fp2);
    fread(&logados[0], sizeof(user), 1, fp1);
    fread(&logados[1], sizeof(user), 1, fp2);

    if (strcmp(logados[0].usuario, logados[1].usuario) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void compra(FILE *fp)
{
    char escolha;
    int num, i;
    printf("deseja comprar um pacote?\ns para sim / n para Nao  "); //adicionar probabilidade de vir figurinhas novas
    scanf(" %c", &escolha);
    if (escolha == 's')
    {
        srand(time(NULL));
        for (i = 0; i < 5; i++)
        {
            printf("A %dº figura que veio no pacote foi: ", i + 1);
            /* gerando valores aleat�rios entre 1 e o num da ultima figurinha */
            num = rand() % MAXFIGS;
            printf("%d \n", num);
            GravFig(num, 1, fp);
        }
        printf("\n");
    }
}
int PrintRepetidas(FILE *fp)
{
    int i, contador = 0;
    figura leitura;
    fseek(fp, sizeof(user), SEEK_SET);
    printf("Figuras repetidas:\n");
    for (i = 0; i < MAXFIGS; i++)
    {
        fread(&leitura, sizeof(figura), 1, fp);
        if (leitura.quantidade > 1)
        {
            contador++;
            printf("%3d ", leitura.numero);
        }
        if (contador == 10)
        {
            printf("\n");
            contador = 0;
        }
    }
    printf("\n");
}
int CheckRepetidas(FILE *fp, int NumFig)
{
    figura lida;
    int FigPos = NumFig - 1;
    fseek(fp, sizeof(user), SEEK_SET);
    if (NumFig == 1)
    {
        fread(&lida, sizeof(figura), 1, fp);
    }
    else
    {
        fseek(fp, FigPos * sizeof(figura), SEEK_CUR);
        fread(&lida, sizeof(figura), 1, fp);
    }
    if (lida.quantidade > 1)
        return 1;
    else
        return 0;
}
void troca(FILE *fp1)
{
    FILE *fp2 = NULL;
    int resp = 1;
    int escolha1, escolha2;
    printf("Troca de Figurinhas!\n");
    printf("solicite o login do outro usuario:\n");
    while (fp2 == NULL)
    {
        fp2 = login();
        if (fp2 != NULL)
        {
            if (CmpArqv(fp1, fp2) == 0)
            {
                printf("Os dois usuarios logados sao iguais\n");
                printf("Logue com outro usuario\n");
                fp2 = NULL;
            }
        }
        else
        {
            printf("tente novamente com outro usuario\n");
        }
    }
    while (resp == 1)
    {
        printf("usuario 1: escolha uma figura do usuario 2\n");
        PrintRepetidas(fp2);
        scanf("%d", &escolha1);
        if (CheckRepetidas(fp2, escolha1) == 0)
        {
            printf("o usuario nao possui essa figura repetida\n");
            printf("escolha outra figura\n");
        }
        else
        {
            resp = 0;
        }
    }
    resp = 1;
    while (resp == 1)
    {
        printf("usuario 2: escolha uma figura do usuario 1\n");
        PrintRepetidas(fp1);
        scanf("%d", &escolha2);
        if (CheckRepetidas(fp1, escolha2) == 0)
        {
            printf("o usuario nao possui essa figura repetida\n");
            printf("escolha outra figura\n");
        }
        else
        {
            resp = 0;
        }
    }
    GravFig(escolha1, 1, fp1);
    GravFig(escolha2, -1, fp1);
    GravFig(escolha2, 1, fp2);
    GravFig(escolha1, -1, fp2);
    fclose(fp2);
    printf("troca realizada com sucesso\n");
}
float CheckStatus(FILE *fp)
{
    int i;
    float contador = 0;
    float porc;
    figura lida;
    fseek(fp, sizeof(user), SEEK_SET);
    for (i = 0; i < MAXFIGS; i++)
    {
        fread(&lida, sizeof(figura), 1, fp);
        if (lida.quantidade > 0)
        {
            contador++;
        }
    }
    porc = ((contador / MAXFIGS) * 100);
    return porc;
}
void EncomendaCarta(float porcentagem, FILE *fp)
{
    int num;
    if (porcentagem >= 95)
    {
        printf("escolha as 35 figurinhas\n");
        for (int i = 0; i < 35; i++)
        {
            scanf("%d", &num);
            GravFig(num, 1, fp); //numero, qtd, arquivo
        }
        printf("figurinhas adicionadas no album com sucesso\n");
    }
    else
    {
        printf("Necessario ter 95%% do album completo para pedir a carta\n");
    }
}
int main()
{
    int opfuncao = 0, opinicio = 0;
    unsigned int page;
    FILE *user = NULL;
    while (user == NULL && opinicio != 3)
    {
        printf("Bem vindo ao album da copa!\nDigite 1 para cadastrar\nDigite 2 para fazer o login\nDigite 3 para sair");
        scanf("%d", &opinicio);
        if (opinicio == 1)
        {
            user = cadastro();
        }
        else if (opinicio == 2)
        {
            user = login();
        }
    }
    if (user != NULL)
    {
        while (opfuncao != 7)
        { //adicionar num certo
            printf("O que dezeja fazer:\n1-comprar pacotinho\n2-visualizar uma pagina\n3-trocar figurinhas com outro usurio\n4-enviar uma carta para pedir as ultimas 35 figurinhas\n5-ver o estado do album\n6-Ver Repetidas\n7-sair\n");
            scanf("%d", &opfuncao);
            switch (opfuncao)
            {
            case 1:
                compra(user);
                break;
            case 2:
                printf("Digite a pagina que deseja visualizar:");
                scanf("%d", &page);
                ImprimirPag(user, page);
                break;
            case 3:
                troca(user);
                break;
            case 4:
                EncomendaCarta(CheckStatus(user), user);
                break;
            case 5:
                printf("O album esta %% %d completo",CheckStatus(user));
                break;
            case 6:
                PrintRepetidas(user);
                break;
            case 7:
                break;
            default:
                printf("erro\n");
                break;
            }
        }
        fclose(user);
    }
    return 0;
}