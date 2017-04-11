#include <iostream>

class Cell {
public:
	Cell *befor;
	Cell *next;
	char value;
};

class Function {
public:
	Function *befor;
	Function *next;

	//wenn:
	char stateCondition;
	char input;

	//dann:
	char stateNew;
	char output;
	char move;
};

Cell *initCellList(char *config);
void printCellList(Cell *cell);
Function *createFunctionList(int argc, char *argv[]);
void printFunctionList(Function *f);

int main(int argc, char *argv[])
{
	char config [100];
	scanf("%s", config);

	Cell* tmPointer = initCellList(config);
	//printCellList(tmPointer);//DEBUG

	Function *f = createFunctionList(argc, argv);
	//printFunctionList(f);//DEBUG



	return 0;
}

Cell *initCellList(char *config){
	Cell *firstCell = new Cell();
	Cell *currentCell = firstCell;
	currentCell->value = config[0];
	currentCell->befor = nullptr;

	int index = 0;
	while(config[index+1] != '\0'){
		index++;
		currentCell->next = new Cell();
		currentCell->next->befor = currentCell;
		currentCell->next->next = nullptr;
		currentCell->next->value = config[index];
		currentCell = currentCell->next;
	}
	return firstCell;
}

void printCellList(Cell *cell){
	Cell *c = cell;

	//go to start:
	while(c->befor != nullptr)
		c = c->befor;

	//print
	while(c != nullptr){
		if(c == cell)
			printf("[");
		printf("%c", c->value);
		if(c == cell)
			printf("]");

		c = c->next;
	}

	printf("\n\n");
}

Function *createFunctionList(int argc, char *argv[]){
	Function *firstFunction = new Function();
	Function *currentFunction = firstFunction;

	char *fStr = argv[1];//0 1 : 0 1 >
	currentFunction->stateCondition = fStr[0];
	currentFunction->input = fStr[2];
	currentFunction->stateNew = fStr[6];
	currentFunction->output = fStr[8];
	currentFunction->move = fStr[10];

	currentFunction->befor = nullptr;

	int index = 1;
	while(index < argc-1){
		index++;
		currentFunction->next = new Function();
		currentFunction->next->befor = currentFunction;
		currentFunction->next->next = nullptr;

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
	while(f->befor != nullptr)
		f = f->befor;

	//print
	while(f != nullptr){
		printf("%c %c : %c %c %c\n", f->stateCondition, f->input, f->stateNew, f->output, f->move);
		f = f->next;
	}

	printf("\n\n");
}
