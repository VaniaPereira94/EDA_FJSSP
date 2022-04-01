/**
 * @brief	Ficheiro principal da aplica��o, com menu e chamada de fun��es
 * @file	main.c
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
 *
 * -----------------
 *
 * Software desenvolvido para a proposta de escalonamento para a produ��o de um produto que envolve v�rias opera��es
 * e a utiliza��o de v�rias m�quinas, para minimizar o tempo necess�rio na sua produ��o.
 * @see
*/

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Fun��o principal do programa
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
	printf("Dados carregados em mem�ria com sucesso!\n");

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


#pragma region Remover opera��o (3)

	// remover opera��o
	deleteOperation(&operations, 35);
	printf("Opera��o removida com sucesso!\n");


#pragma endregion

#pragma region Atualizar Opera��o (4)

	printf("\n\n-  4. Atualizar uma opera��o\n");
	// atualizar o tempo necess�rio para uma execu��o da opera��o
	updateRuntime(&executions, 2, 2, 10);
	printf("Tempo necess�rio para a execu��o da opera��o atualizada com sucesso!\n");
#pragma endregion

#pragma region Inserir Opera��o (5)

	printf("\n\n-  5. Inserir uma opera��o\n");

	// inserir nova opera��o
	Operation* operation = NULL;
	operation = newOperation(39, 2, 8);
	operations = insertOperationAtStart(operations, operation);

	// inserir nova execu��o de uma opera��o
	Execution* execution = NULL;
	execution = newExecution(39, 5, 17);
	executions = insertExecutionAtStart(executions, execution);

	// guardar as novas inser��es em ficheiros
	writeOperations("operations.txt", operations);
	writeExecutions("executions.txt", executions);
	printf("Novos dados exportados com sucesso!\n");
#pragma endregion

#pragma region  Tempo minimo para um Job

	printf("\n\n-  6. Determinar tempo m�nimo para completar um trabalho e listagem das respetivas opera��es\n");

	// obter o tempo m�nimo para completar um job e as respetivas opera��es
	Execution* minExecutions = NULL;
	int minTime = getMinTimeToCompleteJob(operations, executions, 1, &minExecutions);

	// mostrar resultados
	printf("Menor tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, minTime);
	printf("Opera��es com menor tempo:\n");
	minExecutions = SortExecutionsByOperation(minExecutions);
	displayExecutions(minExecutions);
#pragma endregion

#pragma region Tempo Maximo para um Job(7)
		printf("\n\n-  7. Determinar tempo m�ximo para completar um trabalho e listagem das respetivas opera��es\n");

	// obter o tempo m�ximo para completar um job
	Execution* maxExecutions = NULL;
	int maxTime = getMaxTimeToCompleteJob(operations, executions, 1, &maxExecutions);

	// mostrar resultados
	printf("Maior tempo necess�rio para completar o trabalho(ID: %d) � %d!\n", 1, maxTime);
	printf("Opera��es com maior tempo:\n");
	maxExecutions = SortExecutionsByOperation(maxExecutions);
	displayExecutions(maxExecutions);
#pragma endregion

#pragma region Tempo m�dio (8)
		printf("\n\n-  8. Determinar tempo m�dio para completar uma opera��o, considerando todas as alternativas poss�veis\n");

	// obter o tempo m�dio para completar uma opera��o
	float average = getAverageTimeToCompleteOperation(executions, 1);

	// mostrar resultado
	printf("M�dia de tempo necess�rio para completar a opera��o(ID: %d) � %.2f!\n", 1, average);
#pragma endregion

#pragma region Mostrar os dados

	printf("\n\n-  Mostrar dados\n");

	// mostrar dados na consola
	printf("Trabalhos:\n");
	DisplayJob(jobs);
	printf("M�quinas:\n");
	displayMachine(machines);
	printf("Opera��es:\n");
	displayOperations(operations);
	printf("Execu��es de Opera��es:\n");
	displayExecutions(executions);
	printf("Dados mostrados com sucesso!\n");


#pragma endregion
}