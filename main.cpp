#include <iostream>

using namespace std;


class Cell {
public:
	Cell *befor;
	Cell *next;
	char value;
};

Cell *initCellList(char *config);

int main(int argc, char *argv[])
{
	cout << "Hello World!" << endl;

	printf("start\n");
	char config [100];
	scanf("%s", config);
	printf("start with config:%s\n", config);

	Cell* currentCell = initCellList(config);



	return 0;
}

Cell *initCellList(char *config){
	int index = 0;
	Cell *first = new Cell();
	Cell *currentCell = first;

	while(config[index] != '\0'){
		currentCell->value = config[index];
		currentCell->befor = nullptr;
		currentCell->next = new Cell();
		currentCell->next->befor = currentCell;
		currentCell->next->next = nullptr;
		currentCell = currentCell->next;
		index++;
	}
	return nullptr;
}
