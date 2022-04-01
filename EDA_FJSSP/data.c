/**
 * @brief	Ficheiro com função para carregar dados em listas
 * @file	data.c
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
*/

#include <stdio.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Carregar dados para as listas
* @param	jobs		Apontador para a lista de jobs
* @param	machines	Apontador para a lista de máquinas
* @param	operations	Apontador para a lista de operações
* @param	executions	Apontador para a lista de execuções de operações
*/
void loadData(Job** jobs, Machine** machines, Operation** operations, Execution** executions)
{
	Job* job = NULL;
	Machine* machine = NULL;
	Operation* operation = NULL;
	Execution* execution = NULL;

	// jobs
	job = newJob(1);
	*jobs = insertJobAtStart(*jobs, job);

	// machines
	machine = newMachine(1, false);
	*machines = insertMachineAtStart(*machines, machine);

	// operations - job 1
	operation = newOperation(1, 1);
	*operations = insertOperationAtStart(*operations, operation);
	operation = newOperation(2, 1);
	*operations = insertOperationAtStart(*operations, operation);
	operation = newOperation(3, 1);
	*operations = insertOperationAtStart(*operations, operation);
	operation = newOperation(4, 1);
	*operations = insertOperationAtStart(*operations, operation);

	// execution - job 1
	execution = newExecution(1, 1, 4);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(1, 3, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(2, 2, 4);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(2, 4, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(3, 3, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(3, 5, 6);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(4, 4, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(4, 5, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(4, 6, 4);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(4, 7, 5);
	*executions = insertExecutionAtStart(*executions, execution);
	execution = newExecution(4, 8, 9);
	*executions = insertExecutionAtStart(*executions, execution);

}