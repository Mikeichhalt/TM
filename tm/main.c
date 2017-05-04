#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TM_BLANK '#'
#define TM_STOPSTATE '$'
#define TM_STARTSTATE '0'

#define TRIM_OUTPUT
//#define TM_DEBUG

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
int printCellList(Cell *cell);
Function *createFunctionList(int argc, char *argv[]);
void printFunction(Function *f);
void printFunctionList(Function *f);
void trimCellList(Cell **c);
char *inputString(FILE* fp, size_t startSize);

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
	char *config = inputString(stdin, 10);
	Cell* tmPointer = initCellList(config);
	free(config);

	Function *f = createFunctionList(argc, argv);

	char state = TM_STARTSTATE;

	while(state != TM_STOPSTATE){
		Function *currentF = f;
		while(currentF->stateCondition != state || currentF->input != tmPointer->value){
			if(currentF->next == NULL){
				fprintf(stderr, "no function found; state: %c; input:%c\n", state, tmPointer->value);
				exit(1);
			}
			currentF = currentF->next;
		}

#ifdef TM_DEBUG
		int currentPosition = printCellList(tmPointer);
		printf("\t  \"");
		printFunction(currentF);
		printf("\"\n");

		//print current pointer
		for(int i = 0; i < currentPosition; i++)
			printf(" ");
		printf("^\n");
#endif

		//use currentF
		state = currentF->stateNew;
		tmPointer->value = currentF->output;
		if(currentF->move == '<'){
			if(tmPointer->befor == NULL){
				tmPointer->befor = (struct Cell*) malloc(sizeof(struct Cell));
				tmPointer->befor->befor = NULL;
				tmPointer->befor->next = tmPointer;
				tmPointer->befor->value = TM_BLANK;
			}
			tmPointer = tmPointer->befor;
		}
		if(currentF->move == '>'){
			if(tmPointer->next == NULL){
				tmPointer->next = (struct Cell*) malloc(sizeof(struct Cell));
				tmPointer->next->befor = tmPointer;
				tmPointer->next->next = NULL;
				tmPointer->next->value = TM_BLANK;
			}
			tmPointer = tmPointer->next;
		}
	}

#ifdef TM_DEBUG
	int currentPosition = printCellList(tmPointer);
	printf("\n");

	//print current pointer
	for(int i = 0; i < currentPosition; i++)
		printf(" ");
	printf("^\n");
#else
# ifdef TRIM_OUTPUT
	trimCellList(&tmPointer);
# endif
	printCellList(tmPointer);
	printf("\n");
#endif

	return 0;
}

Cell *initCellList(char *config){
	Cell *firstCell = (struct Cell*) malloc(sizeof(struct Cell));
	firstCell->befor = NULL;
	if(config[0] == '\0'){
		firstCell->value = '#';
		return firstCell;
	}
	firstCell->value = config[0];

	Cell *currentCell = firstCell;

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

int printCellList(Cell *cell){
	Cell *c = cell;

	//go to start:
	while(c->befor != NULL)
		c = c->befor;

	//print
	int currentCounter = 0;
	bool currentFound = false;
	while(c != NULL){
		if(!currentFound && c != cell){
			currentCounter++;
		}else
			currentFound = true;

		printf("%c", c->value);
		c = c->next;
	}

	return currentCounter;
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

void printFunction(Function *f){
	printf("%c %c : %c %c %c", f->stateCondition, f->input, f->stateNew, f->output, f->move);
}

void printFunctionList(Function *f){
	//go to start:
	while(f->befor != NULL)
		f = f->befor;

	//print
	while(f != NULL){
		printFunction(f);
		f = f->next;
	}
}

void trimCellList(Cell **c){
	Cell *cell = *c;

	//go to start:
	while(cell->befor != NULL)
		cell = cell->befor;

	//remove blanks at start
	while(cell->value == TM_BLANK){
		if(cell->next == NULL){// list is just one blank
			*c = cell;
			return;
		}

		Cell *remCell = cell;
		cell = cell->next;
		free(remCell);
		cell->befor = NULL;
	}

	//go to end:
	while(cell->next != NULL)
		cell = cell->next;

	//remove blanks at end
	while(cell->value == TM_BLANK){
		Cell *remCell = cell;
		cell = cell->befor;
		free(remCell);
		cell->next = NULL;
	}

	//go to start:
	while(cell->befor != NULL)
		cell = cell->befor;

	*c = cell;
}

char *inputString(FILE* fp, size_t startSize){
	int ch;
	size_t len = 0;

	char *str = realloc(NULL, sizeof(char) * startSize);
	if(!str)
		return str;

	while(EOF != (ch = fgetc(fp)) && ch != '\n'){
		str[len++] = ch;
		if(len == startSize){
			str = realloc(str, sizeof(char) * (startSize += 16));
			if(!str)
				return str;
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char) * len);
}
