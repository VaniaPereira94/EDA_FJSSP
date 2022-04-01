/**
 * @brief	Ficheiro com todas as assinaturas globais necess�rios para a aplica��o
 * @file	header.h
 * @author	V�nia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avan�adas
*/


#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

#pragma endregion


#pragma endregion

#pragma region estruturas de dados em mem�ria

/**
 * @brief	Estrutura de dados para a lista (em mem�ria) de trabalhos
 */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;
extern Job* jobs; // D� a informa��o que a vari�vel est� definida algures no c�digo

/**
 * @brief	Estrutura de dados para a lista (em mem�ria) das m�quinas
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
	struct Machine* next;
} Machine;
extern Machine* machines;

/**
 * @brief	Estrutura de dados para a lista (em mem�ria) das execu��es das opera��es em m�quinas
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
	struct Execution* next;
} Execution;
extern Execution* executions;

/**
 * @brief	Estrutura de dados para a lista (em mem�ria) de opera��es
 */
typedef struct Operation
{
	int id;
	int jobID;
	struct Operation* next;
} Operation;
extern Operation* operations;

#pragma endregion

#pragma region Estruturas Ficheiros

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de trabalhos
 */
typedef struct JobFile
{
	int id;
} JobFile;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de m�quinas
 */
typedef struct MachineFile
{
	int id;
	bool isBusy; // se a m�quina est� ou n�o em utiliza��o
}MachineFile;


/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execu��es das opera��es em m�quinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necess�rias para a execu��o da opera��o
} FileExecution;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de opera��es
 */
typedef struct FileOperation
{
	int id;
	int jobID;
} FileOperation;

#pragma endregion

#pragma region fun��es

/**
 * @brief	Sobre trabalhos
 */
Job* newJob(int id);
Job* insertJobAtStart(Job* head, Job* new);
bool SaveJob(char* fileName, Job* h);
Job* readJob(char* fileName);
void DisplayJob(Job* head);
bool searchJob(Job* head, int id);


/**
 * @brief	Sobre m�quinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool WriteMachine(char* fileName, Machine* head);
Machine* readMachine(char* fileName);
void displayMachine(Machine* head);
bool searchMachine(Machine* head, int id);


/**
 * @brief	Sobre opera��es
 */
Operation* newOperation(int id, int jobID);
Operation* insertOperationAtStart(Operation* head, Operation* new);
bool deleteOperation(Operation** head, int id);
Operation* readOperations(char fileName[]);
bool writeOperations(char fileName[], Operation* head);
bool displayOperations(Operation* head);
bool searchOperation(Operation* head, int id);
int getMinTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** minExecutions);
int getMaxTimeToCompleteJob(Operation* operations, Execution* executions, int jobID, Execution** maxExecutions);
float getAverageTimeToCompleteOperation(Execution* head, int operationID);


/**
 * @brief	Sobre execu��es
 */
Execution* newExecution(int operationID, int machineID, int runtime);
Execution* insertExecutionAtStart(Execution* head, Execution* new);
Execution* insertExecutionByOperation(Execution* head, Execution* new);
bool updateRuntime(Execution** head, int operationID, int machineID, int runtime);
bool deleteExecutionByOperation(Execution* head, int operationID);
bool writeExecutions(char fileName[], Execution* head);
Execution* readExecutions(char fileName[]);
bool displayExecutions(Execution* head);
bool searchExecution(Execution* head, int operationID, int machineID);
bool searchExecutionByOperation(Execution* head, int operationID);
Execution* SortExecutionsByOperation(Execution* head);

/**
 * @brief	Carregar dados para listas
 */
void loadData(Job** jobs, Machine** machines, Operation** operations, Execution** executions);

#pragma endregion

#endif