#ifndef AVL_H
#define AVL_H

typedef enum{
    ATIVO = 1,
    RESOLVIDO
}StatusEvento;

typedef struct NO{
    int idEvento;
    char evento[50];
    int severidade;
    char dataHora[30];
    char regiao[50];
    StatusEvento status;
    int altura;
    struct NO *esq;
    struct NO *dir;
}NO;

extern int totalRotacoes;

//Altura nó
int altura_NO(NO *no);

//Maior valor
int maior(int a, int b);

//Fator de balanceamento
int fatorBalanceamento(NO *no);

//Atualizar altura do nó
void atualizarAltura(NO *no);

//Criar novo nó
NO *novoNO(int id, char evento[], int severidade, char dataHora[], char regiao[]);

//Rotaçao esquerda
NO *rotacaoRR(NO *raiz);

//Rotaçao direita
NO *rotacaoLL(NO *raiz);

//Rotaçao esquerda direita
NO *rotacaoLR(NO *raiz);

//Rotaçao direita esquerda
NO *rotacaoRL(NO *raiz);

//Balancear AVL
NO *balancear(NO *raiz);

//Buscar evento por ID
NO *buscar(NO *raiz, int id);

//Inserir evento na AVL
NO *inserir(NO *raiz, int id, char evento[], int severidade, char dataHora[], char regiao[]);

//Menor nó
NO *menorValor(NO *no);

//Remove nó da AVL
NO *removerInterno(NO *raiz, int id);

//Remover evento resolvido
NO *remover(NO *raiz, int id);

//Liberar memoria
void liberarArvore(NO *raiz);

#endif