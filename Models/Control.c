#include <stdlib.h>

struct Control
{
    int N;		// Número de processos
	int T;		// Tamanho da fila de processos
	int Min;	// Tempo mínimo de execução dos processos
	int Max;	// Tempo máximo de execução dos processos;
	int Pi; 	// Prioridade mínima a ser gerada;
	int Pf;		// Prioridade máxima a ser gerada;
	int A; 		// Algoritmo de escalonamento, segundo Tabela 1;
	int Q; 		// Tamanho do Quantum. Obrigatório apenas quando A for RoundRobin.
};

struct Control getControl(char const *argv[])
{
    struct Control ctrl;
    
    ctrl.N = atoi(argv[1]);
	ctrl.T = atoi(argv[2]);
	ctrl.Min = atoi(argv[3]);
	ctrl.Max = atoi(argv[4]);
	ctrl.Pi = atoi(argv[5]);
	ctrl.Pf = atoi(argv[6]);
	ctrl.A = atoi(argv[7]);
	ctrl.Q = atoi(argv[8]);

    return ctrl;
}
