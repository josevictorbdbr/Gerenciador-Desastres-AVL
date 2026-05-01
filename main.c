#include <stdio.h>
#include "avl.h"
#include "evento.h"

//Cadastro de evento
NO *cadastrarEvento(NO *raiz){
    int id, severidade;
    char evento[50], dataHora[30], regiao[50];

    printf("\n--- Cadastro de Evento ---\n");

    printf("ID do evento: ");
    scanf("%d", &id);

    if(buscar(raiz, id) != NULL){
        printf("ID ja cadastrado.\n");
        return raiz;
    }

    printf("Tipo do evento: ");
    scanf(" %[^\n]", evento);

    printf("Severidade de 1 a 5: ");
    scanf("%d", &severidade);

    if(severidade < 1 || severidade > 5){
        printf("Severidade invalida.\n");
        return raiz;
    }

    printf("Data e Horario: ");
    scanf(" %[^\n]", dataHora);

    printf("Regiao: ");
    scanf(" %[^\n]", regiao);

    raiz = inserir(raiz, id, evento, severidade, dataHora, regiao);

    printf("Evento cadastrado.\n");

    return raiz;
}

//Menu consultas
void menuConsultas(NO *raiz){
    int op, id, min, max;
    char regiao[50];
    NO *evento;

    do{
        printf("\n--- Consultas ---\n");
        printf("1. Buscar evento por ID\n");
        printf("2. Listar ativos por severidade\n");
        printf("3. Relatorio por regiao\n");
        printf("4. Buscar por intervalo de ID\n");
        printf("5. Listar eventos por ID\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("ID do evento: ");
                scanf("%d", &id);

                evento = buscar(raiz, id);

                if(evento == NULL)
                    printf("Evento nao encontrado.\n");
                else
                    exibirEvento(evento);
                break;

            case 2:
                printf("Severidade minima: ");
                scanf("%d", &min);

                printf("Severidade maxima: ");
                scanf("%d", &max);

                if(min < 1 || max > 5 || min > max)
                    printf("Intervalo invalido.\n");
                else
                    listarAtivosPorSeveridade(raiz, min, max);
                break;

            case 3:
                printf("Regiao: ");
                scanf(" %[^\n]", regiao);

                relatorioPorRegiao(raiz, regiao);
                break;

            case 4:
                printf("ID inicial: ");
                scanf("%d", &min);

                printf("ID final: ");
                scanf("%d", &max);

                if(min > max)
                    printf("Intervalo invalido.\n");
                else
                    buscarIntervaloID(raiz, min, max);
                break;

            case 5:
                if(raiz == NULL)
                    printf("Nenhum evento cadastrado.\n");
                else
                    listarEmOrdem(raiz);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida, tente novamente\n");
                break;
        }

    }while(op != 0);
}

//Menu atualizaçoes
NO *menuAtualizacoes(NO *raiz){
    int op, id, severidade;

    do{
        printf("\n--- Atualizar Eventos ---\n");
        printf("1. Resolver evento\n");
        printf("2. Atualizar severidade\n");
        printf("3. Remover evento resolvido\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("ID do evento: ");
                scanf("%d", &id);

                alterarStatus(raiz, id);
                break;

            case 2:
                printf("ID do evento: ");
                scanf("%d", &id);

                printf("Nova severidade: ");
                scanf("%d", &severidade);

                atualizarSeveridade(raiz, id, severidade);
                break;

            case 3:
                printf("ID do evento: ");
                scanf("%d", &id);

                raiz = remover(raiz, id);
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida, tente novamente\n");
                break;
        }

    }while(op != 0);

    return raiz;
}

int main(){
    NO *raiz = NULL;
    int op;

    do{
        printf("\n===== Sistema de Eventos Criticos =====\n");
        printf("1. Cadastrar evento\n");
        printf("2. Consultas\n");
        printf("3. Atualizar evento\n");
        printf("4. Metricas da arvore\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                raiz = cadastrarEvento(raiz);
                break;

            case 2:
                menuConsultas(raiz);
                break;

            case 3:
                raiz = menuAtualizacoes(raiz);
                break;

            case 4:
                mostrarMetricas(raiz);
                break;

            case 0:
                printf("Desligando...\n");
                break;

            default:
                printf("Opcao invalida, tente novamente\n");
                break;
        }

    }while(op != 0);

    liberarArvore(raiz);
    return 0;
}