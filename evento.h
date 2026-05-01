#ifndef EVENTO_H
#define EVENTO_H

#include "avl.h"

//Mostrar texto do status
char *statusTexto(StatusEvento status);

//Exibir um evento
void exibirEvento(NO *no);

//Listar eventos em ordem
void listarEmOrdem(NO *raiz);

//Listar ativos por severidade
void listarAtivosPorSeveridade(NO *raiz, int min, int max);

//Gerar relatorio por região
void relatorioPorRegiao(NO *raiz, char regiao[]);

//Buscar por intervalo de ID
void buscarIntervaloID(NO *raiz, int inicio, int fim);

//Alterar status para resolvido
void alterarStatus(NO *raiz, int id);

//Atualizar severidade
void atualizarSeveridade(NO *raiz, int id, int novaSeveridade);

//Contar todos os nós
int contarNos(NO *raiz);

//Contar eventos ativos
int contarAtivos(NO *raiz);

//Somar fatores de balanceamento
int somaFatores(NO *raiz);

//Mostrar metricas
void mostrarMetricas(NO *raiz);

#endif