# Sistema de Eventos Críticos

Este projeto implementa um sistema em C para gerenciar eventos críticos de uma cidade inteligente, como acidentes, falhas em semáforos, interrupções de energia, alagamentos e incêndios.

A estrutura principal usada é uma Árvore AVL, onde cada evento é armazenado em um nó e organizado pelo ID do evento.

## Como Compilar e Rodar

1. Fazer download do projeto

2. Compilar no terminal:

   gcc main.c avl.c evento.c -o sistema.exe

3. Executar o programa:

   .\sistema.exe

## Funcionalidades

- Cadastrar eventos críticos
- Buscar evento por ID
- Listar eventos ativos por intervalo de severidade
- Gerar relatório de eventos ativos por região
- Buscar eventos por intervalo de ID
- Listar eventos ordenados por ID
- Atualizar severidade de evento ativo
- Alterar status de evento para resolvido
- Remover apenas eventos resolvidos
- Exibir métricas da Árvore AVL

## Estrutura da AVL

Cada nó da árvore armazena:

- ID do evento
- Tipo do evento
- Severidade
- Data e horário
- Região
- Status
- Altura do nó
- Ponteiro esquerdo
- Ponteiro direito

A árvore é ordenada pelo ID do evento, e após inserções ou remoções o sistema recalcula alturas, verifica o fator de balanceamento e aplica rotações quando necessário.

## Métricas

O sistema mostra:

- Altura total da árvore
- Número total de nós
- Número de eventos ativos
- Fator médio de balanceamento
- Total de rotações realizadas
