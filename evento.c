#include <stdio.h>
#include <string.h>
#include "evento.h"

//Mostrar texto do status
char *statusTexto(StatusEvento status){
    if(status == ATIVO)
        return "Ativo";

    return "Resolvido";
}

//Exibir um evento
void exibirEvento(NO *no){
    if(no == NULL)
        return;

    printf("\nID: %d\n", no->idEvento);
    printf("Evento: %s\n", no->evento);
    printf("Severidade: %d\n", no->severidade);
    printf("Data/Hora: %s\n", no->dataHora);
    printf("Regiao: %s\n", no->regiao);
    printf("Status: %s\n", statusTexto(no->status));
}

//Listar eventos em ordem
void listarEmOrdem(NO *raiz){
    if(raiz != NULL){
        listarEmOrdem(raiz->esq);
        exibirEvento(raiz);
        listarEmOrdem(raiz->dir);
    }
}

//Listar ativos por severidade
void listarAtivosPorSeveridade(NO *raiz, int min, int max){
    if(raiz != NULL){
        listarAtivosPorSeveridade(raiz->esq, min, max);

        if(raiz->status == ATIVO && raiz->severidade >= min && raiz->severidade <= max)
            exibirEvento(raiz);

        listarAtivosPorSeveridade(raiz->dir, min, max);
    }
}

//Gerar relatorio por região
void relatorioPorRegiao(NO *raiz, char regiao[]){
    if(raiz != NULL){
        relatorioPorRegiao(raiz->esq, regiao);

        if(raiz->status == ATIVO && strcmp(raiz->regiao, regiao) == 0)
            exibirEvento(raiz);

        relatorioPorRegiao(raiz->dir, regiao);
    }
}

//Buscar por intervalo de ID
void buscarIntervaloID(NO *raiz, int inicio, int fim){
    if(raiz == NULL)
        return;

    if(inicio < raiz->idEvento)
        buscarIntervaloID(raiz->esq, inicio, fim);

    if(raiz->idEvento >= inicio && raiz->idEvento <= fim)
        exibirEvento(raiz);

    if(fim > raiz->idEvento)
        buscarIntervaloID(raiz->dir, inicio, fim);
}

//Alterar status para resolvido
void alterarStatus(NO *raiz, int id){
    NO *evento = buscar(raiz, id);

    if(evento == NULL){
        printf("Evento nao encontrado.\n");
        return;
    }

    if(evento->status == RESOLVIDO){
        printf("Evento ja esta resolvido.\n");
        return;
    }

    evento->status = RESOLVIDO;
    printf("Evento resolvido.\n");
}

//Atualizar severidade
void atualizarSeveridade(NO *raiz, int id, int novaSeveridade){
    NO *evento = buscar(raiz, id);

    if(evento == NULL){
        printf("Evento nao encontrado.\n");
        return;
    }

    if(evento->status != ATIVO){
        printf("Somente eventos ativos podem ser alterados.\n");
        return;
    }

    if(novaSeveridade < 1 || novaSeveridade > 5){
        printf("Severidade invalida.\n");
        return;
    }

    evento->severidade = novaSeveridade;
    printf("Severidade atualizada.\n");
}

//Contar todos os nós
int contarNos(NO *raiz){
    if(raiz == NULL)
        return 0;

    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//Contar eventos ativos
int contarAtivos(NO *raiz){
    if(raiz == NULL)
        return 0;

    return (raiz->status == ATIVO) + contarAtivos(raiz->esq) + contarAtivos(raiz->dir);
}

//Somar fatores de balanceamento
int somaFatores(NO *raiz){
    int fb;

    if(raiz == NULL)
        return 0;

    fb = fatorBalanceamento(raiz);

    if(fb < 0)
        fb = fb * -1;

    return fb + somaFatores(raiz->esq) + somaFatores(raiz->dir);
}

//Mostrar metricas
void mostrarMetricas(NO *raiz){
    int totalNos = contarNos(raiz);
    float media = 0;

    if(totalNos > 0)
        media = (float)somaFatores(raiz) / totalNos;

    printf("\n--- Metricas da arvore ---\n");
    printf("Altura total: %d\n", altura_NO(raiz));
    printf("Total de nos: %d\n", totalNos);
    printf("Eventos ativos: %d\n", contarAtivos(raiz));
    printf("Fator medio de balanceamento: %.2f\n", media);
    printf("Total de rotacoes: %d\n", totalRotacoes);
}