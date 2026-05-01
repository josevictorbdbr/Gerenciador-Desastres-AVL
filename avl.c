#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int totalRotacoes = 0;

//Altura nó
int altura_NO(NO *no){
    if(no == NULL)
        return -1;

    return no->altura;
}

//Maior valor
int maior(int a, int b){
    return (a > b) ? a : b;
}

//Fator de balanceamento
int fatorBalanceamento(NO *no){
    if(no == NULL)
        return 0;

    return altura_NO(no->esq) - altura_NO(no->dir);
}

//Atualizar altura do nó
void atualizarAltura(NO *no){
    if(no != NULL)
        no->altura = maior(altura_NO(no->esq), altura_NO(no->dir)) + 1;
}

//Criar novo nó
NO *novoNO(int id, char evento[], int severidade, char dataHora[], char regiao[]){
    NO *no = (NO*)malloc(sizeof(NO));

    if(no == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    no->idEvento = id;
    strcpy(no->evento, evento);
    no->severidade = severidade;
    strcpy(no->dataHora, dataHora);
    strcpy(no->regiao, regiao);
    no->status = ATIVO;
    no->altura = 0;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

//Rotaçao esquerda
NO *rotacaoRR(NO *raiz){
    NO *no = raiz->dir;

    raiz->dir = no->esq;
    no->esq = raiz;

    atualizarAltura(raiz);
    atualizarAltura(no);

    totalRotacoes++;

    return no;
}

//Rotaçao direita
NO *rotacaoLL(NO *raiz){
    NO *no = raiz->esq;

    raiz->esq = no->dir;
    no->dir = raiz;

    atualizarAltura(raiz);
    atualizarAltura(no);

    totalRotacoes++;

    return no;
}

//Rotaçao esquerda direita
NO *rotacaoLR(NO *raiz){
    raiz->esq = rotacaoRR(raiz->esq);
    return rotacaoLL(raiz);
}

//Rotaçao direita esquerda
NO *rotacaoRL(NO *raiz){
    raiz->dir = rotacaoLL(raiz->dir);
    return rotacaoRR(raiz);
}

//Balancear AVL
NO *balancear(NO *raiz){
    int fb;

    if(raiz == NULL)
        return NULL;

    atualizarAltura(raiz);
    fb = fatorBalanceamento(raiz);

    if(fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoLL(raiz);

    if(fb > 1 && fatorBalanceamento(raiz->esq) < 0)
        return rotacaoLR(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoRR(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) > 0)
        return rotacaoRL(raiz);

    return raiz;
}

//Buscar evento por ID
NO *buscar(NO *raiz, int id){
    if(raiz == NULL)
        return NULL;

    if(id < raiz->idEvento)
        return buscar(raiz->esq, id);

    if(id > raiz->idEvento)
        return buscar(raiz->dir, id);

    return raiz;
}

//Inserir evento na AVL
NO *inserir(NO *raiz, int id, char evento[], int severidade, char dataHora[], char regiao[]){
    if(raiz == NULL)
        return novoNO(id, evento, severidade, dataHora, regiao);

    if(id < raiz->idEvento)
        raiz->esq = inserir(raiz->esq, id, evento, severidade, dataHora, regiao);
    else if(id > raiz->idEvento)
        raiz->dir = inserir(raiz->dir, id, evento, severidade, dataHora, regiao);
    else{
        printf("Erro: ID ja cadastrado.\n");
        return raiz;
    }

    return balancear(raiz);
}

//Menor nó da subárvore
NO *menorValor(NO *no){
    NO *atual = no;

    while(atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

//Remover nó
NO *removerInterno(NO *raiz, int id){
    if(raiz == NULL)
        return NULL;

    if(id < raiz->idEvento)
        raiz->esq = removerInterno(raiz->esq, id);
    else if(id > raiz->idEvento)
        raiz->dir = removerInterno(raiz->dir, id);
    else{
        if(raiz->esq == NULL || raiz->dir == NULL){
            NO *temp = raiz->esq ? raiz->esq : raiz->dir;

            if(temp == NULL){
                temp = raiz;
                raiz = NULL;
            }else{
                *raiz = *temp;
            }

            free(temp);
        }else{
            NO *temp = menorValor(raiz->dir);

            raiz->idEvento = temp->idEvento;
            strcpy(raiz->evento, temp->evento);
            raiz->severidade = temp->severidade;
            strcpy(raiz->dataHora, temp->dataHora);
            strcpy(raiz->regiao, temp->regiao);
            raiz->status = temp->status;

            raiz->dir = removerInterno(raiz->dir, temp->idEvento);
        }
    }

    if(raiz == NULL)
        return NULL;

    return balancear(raiz);
}

//Remover evento resolvido
NO *remover(NO *raiz, int id){
    NO *evento = buscar(raiz, id);

    if(evento == NULL){
        printf("Evento nao encontrado.\n");
        return raiz;
    }

    if(evento->status != RESOLVIDO){
        printf("Apenas eventos resolvidos podem ser removidos.\n");
        return raiz;
    }

    raiz = removerInterno(raiz, id);
    printf("Evento removido.\n");

    return raiz;
}

//Liberar memoria
void liberarArvore(NO *raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}