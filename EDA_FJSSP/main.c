/**
 * @brief	Ficheiro principal da aplicação, com menu e chamada de funções
 * @file	main.c
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
 *
 * -----------------
 *
 * Software desenvolvido para a proposta de escalonamento para a produção de um produto que envolve várias operações
 * e a utilização de várias máquinas, para minimizar o tempo necessário na sua produção.
 * @see
*/

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Função principal do programa
* @return	Resultado do programa na linha de comando
*/
int main()
{
	setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

	Job* jobs = NULL;
	Operation* operations = NULL;
	Machine* machines = NULL;
	Execution* executions = NULL;

#pragma region Ficheiros

	// carregar dados para as listas
	loadData(&jobs, &machines, &operations, &executions);
	printf("Dados carregados em memória com sucesso!\n");

	// guardar os dados em ficheiros
	SaveJob("jobs.txt", jobs);
	WriteMachine("machines.txt", machines);
	writeOperations("operations.txt", operations);
	writeExecutions("executions.txt", executions);
	printf("Dados exportados com sucesso!\n");

	// ler dados de ficheiros
	jobs = readJob("jobs.txt");
	machines = readMachine("machines.txt");
	operations = readOperations("operations.txt");
	executions = readExecutions("executions.txt");
	printf("Dados importados com sucesso!\n");
#pragma endregion


#pragma region Remover operação (3)

	// remover operação
	deleteOperation(&operations, 35);
	printf("Operação removida com sucesso!\n");


#pragma endregion

#pragma region Atualizar Operação (4)

	printf("\n\n-  4. Atualizar uma operação\n");
	// atualizar o tempo necessário para uma execução da operação
	updateRuntime(&executions, 2, 2, 10);
	printf("Tempo necessário para a execução da operação atualizada com sucesso!\n");
#pragma endregion

#pragma region Inserir Operação (5)

	printf("\n\n-  5. Inserir uma operação\n");

	// inserir nova operação
	Operation* operation = NULL;
	operation = newOperation(39, 2, 8);
	operations = insertOperationAtStart(operations, operation);

	// inserir nova execução de uma operação
	Execution* execution = NULL;
	execution = newExecution(39, 5, 17);
	executions = insertExecutionAtStart(executions, execution);

	// guardar as novas inserções em ficheiros
	writeOperations("operations.txt", operations);
	writeExecutions("executions.txt", executions);
	printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region  Tempo minimo para um Job

	printf("\n\n-  6. Determinar tempo mínimo para completar um trabalho e listagem das respetivas operações\n");

	// obter o tempo mínimo para completar um job e as respetivas operações
	Execution* minExecutions = NULL;
	int minTime = getMinTimeToCompleteJob(operations, executions, 1, &minExecutions);

	// mostrar resultados
	printf("Menor tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, minTime);
	printf("Operações com menor tempo:\n");
	minExecutions = SortExecutionsByOperation(minExecutions);
	displayExecutions(minExecutions);
#pragma endregion

#pragma region Tempo Maximo para um Job(7)
		printf("\n\n-  7. Determinar tempo máximo para completar um trabalho e listagem das respetivas operações\n");

	// obter o tempo máximo para completar um job
	Execution* maxExecutions = NULL;
	int maxTime = getMaxTimeToCompleteJob(operations, executions, 1, &maxExecutions);

	// mostrar resultados
	printf("Maior tempo necessário para completar o trabalho(ID: %d) é %d!\n", 1, maxTime);
	printf("Operações com maior tempo:\n");
	maxExecutions = SortExecutionsByOperation(maxExecutions);
	displayExecutions(maxExecutions);
#pragma endregion

#pragma region Tempo médio (8)
		printf("\n\n-  8. Determinar tempo médio para completar uma operação, considerando todas as alternativas possíveis\n");

	// obter o tempo médio para completar uma operação
	float average = getAverageTimeToCompleteOperation(executions, 1);

	// mostrar resultado
	printf("Média de tempo necessário para completar a operação(ID: %d) é %.2f!\n", 1, average);
#pragma endregion

#pragma region Mostrar os dados

	printf("\n\n-  Mostrar dados\n");

	// mostrar dados na consola
	printf("Trabalhos:\n");
	DisplayJob(jobs);
	printf("Máquinas:\n");
	displayMachine(machines);
	printf("Operações:\n");
	displayOperations(operations);
	printf("Execuções de Operações:\n");
	displayExecutions(executions);
	printf("Dados mostrados com sucesso!\n");


#pragma endregion
}