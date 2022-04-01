/**
 * @brief	Ficheiro com todas as fun��es relativas �s execu��es de opera��es
 * @file	executions.c
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


/**
* @brief	Criar nova execu��o
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @param	runtime			Unidades de tempo necess�rias para a execu��o da opera��o
* @return	Nova execu��o
*/
Execution* newExecution(int operationID, int machineID, int runtime)
{
	Execution* new = (Execution*)malloc(sizeof(Execution));
	if (new == NULL) // se n�o houver mem�ria para alocar
	{
		return NULL;
	}

	new->operationID = operationID;
	new->machineID = machineID;
	new->runtime = runtime;
	new->next = NULL;

	return new;
}


/**
* @brief	Inserir nova execu��o no in�cio da lista
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
Execution* insertExecutionAtStart(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
	{
		return NULL;
	}

	if (head == NULL) // se a lista estiver vazia
	{
		head = new;
	}
	else // se existir algum elemento na lista
	{
		new->next = head;
		head = new;
	}

	return head;
}


/**
* @brief	Inserir execu��o ordenada pelo ID da opera��o na lista
* @param	head	Lista de execu��es
* @param	new		Nova execu��o
* @return	Lista de execu��es atualizada
*/
Execution* insertExecutionByOperation(Execution* head, Execution* new)
{
	if (searchExecution(head, new->operationID, new->machineID)) // n�o permitir inserir uma nova com o mesmo ID de opera��o e ID de m�quina
	{
		return NULL;
	}

	if (head == NULL)
	{
		head = new; // inserir no in�cio se alista estiver vazia
	}
	else
	{
		Execution* aux = head;
		Execution* auxAnt = NULL;

		// enquanto que a atual tem o ID menor que a nova
		while (aux != NULL && aux->operationID < new->operationID)
		{
			auxAnt = aux;
			aux = aux->next;
		}

		if (auxAnt == NULL)
		{
			new->next = head;
			head = new; // inserir no meio
		}
		else
		{
			auxAnt->next = new;
			new->next = aux; // inserir no fim
		}
	}

	return head;
}


/**
* @brief	Atualizar as unidades de tempo necess�rias para a execu��o de uma opera��o
* @param	head			Apontador para a lista de execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @param	runtime			Unidades de tempo
* @return	Booleano para o resultado da fun��o
**/

bool updateRuntime(Execution** head, int operationID, int machineID, int runtime)
{
	if (*head == NULL) // se lista est� vazia
	{
		return false;
	}

	Execution* aux = *head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID && aux->machineID == machineID)
		{
			aux->runtime = runtime;
			return true;
		}
		aux = aux->next;
	}

	return false;
}


/**
* @brief	Remover execu��o pelo identificador da opera��o
* @param	head			Apontador para a lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o
*/
bool deleteExecutionByOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;
	Execution* auxAnt = NULL;

	if (aux != NULL && aux->operationID == operationID) { // se o elemento que ser� apagado � o primeiro da lista
		head = aux->next;
		free(aux);
		return true;
	}

	while (aux != NULL && aux->operationID != operationID) // procurar o elemento a ser apagado
	{
		auxAnt = aux;
		aux = aux->next;
	}

	if (aux == NULL) // se o elemento n�o foi encontrado
	{
		return false;
	}

	aux->next = aux->next; // desassociar o elemento da lista
	free(aux);

	return true;
}


/**
* @brief	Armazenar lista de execu��es em ficheiro bin�rio
* @param	fileName	Nome do ficheiro para armazenar a lista
* @param	head		Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool writeExecutions(char fileName[], Execution* head)
{
	if (head == NULL) // se lista est� vazia
	{
		return false;
	}

	FILE* file = NULL;

	if ((file = fopen(fileName, "wb")) == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return false;
	}

	Execution* current = head;
	FileExecution currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (current != NULL)
	{
		currentInFile.operationID = current->operationID;
		currentInFile.machineID = current->machineID;
		currentInFile.runtime = current->runtime;
		fwrite(&currentInFile, sizeof(FileExecution), 1, file); // guarda cada registo da lista no ficheiro

		current = current->next;
	}

	fclose(file);

	return true;
}


/**
* @brief	Ler lista de execu��es de ficheiro bin�rio
* @param	fileName	Nome do ficheiro para ler a lista
* @return	Lista de execu��ess
*/
Execution* readExecutions(char fileName[])
{
	FILE* file;

	if ((file = fopen(fileName, "rb")) == NULL) // se n�o foi poss�vel abrir o ficheiro
	{
		return NULL;
	}

	Execution* head = NULL;
	Execution* current = NULL;
	FileExecution currentInFile; // � a mesma estrutura mas sem o campo *next, uma vez que esse campo n�o � armazenado no ficheiro

	while (fread(&currentInFile, sizeof(FileExecution), 1, file)) // l� todos os registos do ficheiro e guarda na lista
	{
		current = newExecution(currentInFile.operationID, currentInFile.machineID, currentInFile.runtime);
		head = insertExecutionAtStart(head, current);
	}

	fclose(file);

	return head;
}



/**
* @brief	Mostrar a lista de execu��es na consola
* @param	head	Lista de execu��es
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool displayExecutions(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		printf("ID Opera��o: %d, ID M�quina: %d, Tempo de Execu��o: %d;\n", aux->operationID, aux->machineID, aux->runtime);
		aux = aux->next;
	}

	return true;
}


/**
* @brief	Procurar por uma execu��o na lista de execu��es
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @param	machineID		Identificador da m�quina
* @return	Booleano para o resultado da fun��o (se funcionou ou n�o)
*/
bool searchExecution(Execution* head, int operationID, int machineID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID && aux->machineID == machineID)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}


/**
* @brief	Procurar por uma execu��o atrav�s do identificador da opera��o, na lista de execu��es
* @param	head			Lista de execu��es
* @param	operationID		Identificador da opera��o
* @return	Booleano para o resultado da fun��o
*/
bool searchExecutionByOperation(Execution* head, int operationID)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return false;
	}

	Execution* aux = head;

	while (aux != NULL)
	{
		if (aux->operationID == operationID)
		{
			return true;
		}
		aux = aux->next;
	}

	return false;
}


/**
* @brief	Ordenar lista de execu��es por ordem crescente do identificador da opera��o
* @param	head			Lista de execu��es
* @return	Booleano para o resultado da fun��o
*/
Execution* SortExecutionsByOperation(Execution* head)
{
	if (head == NULL) // se a lista estiver vazia
	{
		return NULL;
	}

	Execution* current = head;
	Execution* sorted = NULL;
	Execution* new = NULL;

	while (current != NULL)
	{
		new = newExecution(current->operationID, current->machineID, current->runtime);
		sorted = insertExecutionByOperation(sorted, new);
		current = current->next;
	}

	return sorted;
}