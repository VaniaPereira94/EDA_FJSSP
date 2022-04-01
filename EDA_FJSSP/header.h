/**
 * @brief	Ficheiro com todas as assinaturas globais necessários para a aplicação
 * @file	header.h
 * @author	Vânia Pereira
 * @email	a19264@alunos.ipca.pt
 * @date	2022
 * @Disciplina Estruturas de Dados Avançadas
*/


#ifndef HEADER_H

#pragma region constantes

#define HEADER_H

#pragma endregion


#pragma endregion

#pragma region estruturas de dados em memória

/**
 * @brief	Estrutura de dados para a lista (em memória) de trabalhos
 */
typedef struct Job
{
	int id;
	struct Job* next;
} Job;
extern Job* jobs; // Dá a informação que a variável está definida algures no código

/**
 * @brief	Estrutura de dados para a lista (em memória) das máquinas
 */
typedef struct Machine
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
	struct Machine* next;
} Machine;
extern Machine* machines;

/**
 * @brief	Estrutura de dados para a lista (em memória) das execuções das operações em máquinas
 */
typedef struct Execution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
	struct Execution* next;
} Execution;
extern Execution* executions;

/**
 * @brief	Estrutura de dados para a lista (em memória) de operações
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
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de máquinas
 */
typedef struct MachineFile
{
	int id;
	bool isBusy; // se a máquina está ou não em utilização
}MachineFile;


/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de execuções das operações em máquinas
 */
typedef struct FileExecution
{
	int operationID;
	int machineID;
	int runtime; // unidades de tempo necessárias para a execução da operação
} FileExecution;

/**
 * @brief	Estrutura de dados para armazenar em ficheiro a lista de operações
 */
typedef struct FileOperation
{
	int id;
	int jobID;
} FileOperation;

#pragma endregion

#pragma region funções

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
 * @brief	Sobre máquinas
 */
Machine* newMachine(int id, bool isBusy);
Machine* insertMachineAtStart(Machine* head, Machine* new);
bool WriteMachine(char* fileName, Machine* head);
Machine* readMachine(char* fileName);
void displayMachine(Machine* head);
bool searchMachine(Machine* head, int id);


/**
 * @brief	Sobre operações
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
 * @brief	Sobre execuções
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