PROJETO DE ESTRTURA DE DADOS (APLICAÇÃO DE CONTEÚDOS DA FACULDADE)
** Tauan Neres**

Descrição do Projeto

Este projeto consiste em uma implementação simplificada do clássico jogo de tabuleiro War, desenvolvida inteiramente em linguagem C. O objetivo principal foi aplicar e consolidar conceitos fundamentais da programação estruturada e do gerenciamento de estruturas de dados dinâmicas em um projeto prático e funcional.

A analogia escolhida foi a de um campo de batalha virtual, em que dois jogadores, Azul e Verde, competem pelo domínio do mapa. A vitória é determinada por um sistema de missões estratégicas, sorteadas aleatoriamente no início de cada partida.

Funcionalidades Implementadas

Mapa Dinâmico:
Criado em tempo de execução, representado por territórios com atributos de nome, cor do jogador dominante e quantidade de tropas.

Sistema de Turnos:
Execução alternada entre Jogador 1 (Azul) e Jogador 2 (Verde).

Mecânica de Ataque:
Jogadores podem atacar territórios inimigos a partir de territórios dominados. O resultado é definido por uma rolagem de dados simulada.

Conquista de Territórios:
Em caso de vitória, o território passa a ser controlado pelo jogador atacante.

Missões Estratégicas:
Cada jogador recebe uma missão secreta no início (ex.: “Conquistar o Continente Norte” ou “Eliminar todas as tropas Verdes”). A primeira missão concluída define o vencedor.

Verificação de Vitória:
Ao final de cada turno, o sistema verifica se algum jogador atingiu as condições de vitória.

Conceitos de Estrutura de Dados Aplicados

Structs:
Modelagem de territórios, armazenando múltiplas informações em um único tipo de dado estruturado.

Modularização:
O código foi dividido em funções específicas (inicializarMapa, atacar, verificarMissao, etc.), facilitando clareza, manutenção e reutilização.

Ponteiros:

Manipulação direta de memória.

Passagem de parâmetros por referência, permitindo que as funções alterem o estado global do jogo.

Alocação Dinâmica de Memória:

Uso de malloc() para criar estruturas em tempo de execução.

Liberação com free() para evitar memory leaks.

Manipulação de Strings:

Funções da <string.h> como strcpy e strcmp foram utilizadas para gerenciar nomes de territórios, cores e descrições de missões.

Geração de Números Aleatórios:

Implementação com srand() e rand() para:

Sorteio das missões.

Simulação da rolagem de dados nos combates.

Conclusão

O desenvolvimento deste projeto permitiu unir teoria e prática em um sistema lúdico, mas com fundamentos sólidos de Estruturas de Dados em C. A implementação trouxe experiência real no uso de structs, ponteiros, memória dinâmica, modularização, strings e geração de aleatoriedade, além de estimular a organização lógica e estratégica do código.

Assim, o jogo War em C não foi apenas um exercício criativo, mas também um meio eficiente para compreender e consolidar conceitos essenciais da disciplina.# Aplica-o-de-Estrutura-De-Dados
Fazendo um Jogo WAR para trazer analogia dos conceitos que utilizamos de Estrutura De Dados
