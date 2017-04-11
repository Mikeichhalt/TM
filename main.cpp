#include <iostream>

using namespace std;


class Cell {
public:
	Cell *befor;
	Cell *next;
	char value;
};

Cell *initCellList(char *config);
void printCellList(Cell *cell);

int main(int argc, char *argv[])
{
	printf("start\n");
	char config [100];
	scanf("%s", config);
	printf("start with config: %s\n", config);

	Cell* tmPointer = initCellList(config);
	printCellList(tmPointer);

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
