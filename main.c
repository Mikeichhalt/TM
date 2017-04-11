#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Cell Cell;
struct Cell {
	Cell *befor;
	Cell *next;
	char value;
};

typedef struct Function Function;
struct Function {
	Function *befor;
	Function *next;

	//if:
	char stateCondition;
	char input;

	//then:
	char stateNew;
	char output;
	char move;
};

Cell *initCellList(char *config);
void printCellList(Cell *cell, bool showCurrent);
Function *createFunctionList(int argc, char *argv[]);
void printFunctionList(Function *f);

/**
 * start state: 0
 * end state: $
 *
 * function: S X : S' Y d
 * example:  0 1 : 0 1 >
 *
 * input, output, state: char
 * d:
 *   right: >
 *   left: <
 *   stay: _
 */
int main(int argc, char *argv[])
{
	char config [100];
	scanf("%s", config);

	Cell* tmPointer = initCellList(config);
	//printCellList(tmPointer, true);//DEBUG

	Function *f = createFunctionList(argc, argv);
	//printFunctionList(f);//DEBUG

	char state = '0';

	while(state != '$'){
		Function *currentF = f;
		while(currentF->stateCondition != state || currentF->input != tmPointer->value){
			if(currentF->next == NULL){
				printf("error: no function found state: %c; input:%c\n", state, tmPointer->value);
				exit(1);
			}
			currentF = currentF->next;
		}

		//use currentF
		state = currentF->stateNew;
		tmPointer->value = currentF->output;
		if(currentF->move == '<'){
			if(tmPointer->befor == NULL){
				tmPointer->befor = (struct Cell*) malloc(sizeof(struct Cell));
				tmPointer->befor->befor = NULL;
				tmPointer->befor->next = tmPointer;
				tmPointer->befor->value = '#';
			}
			tmPointer = tmPointer->befor;
		}
		if(currentF->move == '>'){
			if(tmPointer->next == NULL){
				tmPointer->next = (struct Cell*) malloc(sizeof(struct Cell));
				tmPointer->next->befor = tmPointer;
				tmPointer->next->next = NULL;
				tmPointer->next->value = '#';
			}
			tmPointer = tmPointer->next;
		}
	}

	printCellList(tmPointer, false);

	return 0;
}

Cell *initCellList(char *config){
	Cell *firstCell = (struct Cell*) malloc(sizeof(struct Cell));
	Cell *currentCell = firstCell;
	currentCell->value = config[0];
	currentCell->befor = NULL;

	int index = 0;
	while(config[index+1] != '\0'){
		index++;
		currentCell->next = (struct Cell*) malloc(sizeof(struct Cell));
		currentCell->next->befor = currentCell;
		currentCell->next->next = NULL;
		currentCell->next->value = config[index];
		currentCell = currentCell->next;
	}
	return firstCell;
}

void printCellList(Cell *cell, bool showCurrent){
	Cell *c = cell;

	//go to start:
	while(c->befor != NULL)
		c = c->befor;

	//print
	while(c != NULL){
		if(showCurrent && c == cell)
			printf("[");
		printf("%c", c->value);
		if(showCurrent && c == cell)
			printf("]");

		c = c->next;
	}
}

Function *createFunctionList(int argc, char *argv[]){
	Function *firstFunction = (struct Function*) malloc(sizeof(struct Function));
	Function *currentFunction = firstFunction;

	char *fStr = argv[1];//0 1 : 0 1 >
	currentFunction->stateCondition = fStr[0];
	currentFunction->input = fStr[2];
	currentFunction->stateNew = fStr[6];
	currentFunction->output = fStr[8];
	currentFunction->move = fStr[10];

	currentFunction->befor = NULL;

	int index = 1;
	while(index < argc-1){
		index++;
		currentFunction->next = (struct Function*) malloc(sizeof(struct Function));
		currentFunction->next->befor = currentFunction;
		currentFunction->next->next = NULL;

		char *fStr = argv[index];//0 1 : 0 1 >
		currentFunction->next->stateCondition = fStr[0];
		currentFunction->next->input = fStr[2];
		currentFunction->next->stateNew = fStr[6];
		currentFunction->next->output = fStr[8];
		currentFunction->next->move = fStr[10];

		currentFunction = currentFunction->next;
	}

	return firstFunction;
}

void printFunctionList(Function *f){
	//go to start:
	while(f->befor != NULL)
		f = f->befor;

	//print
	while(f != NULL){
		printf("%c %c : %c %c %c\n", f->stateCondition, f->input, f->stateNew, f->output, f->move);
		f = f->next;
	}
}
