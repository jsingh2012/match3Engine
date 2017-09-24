#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctime>
#include <cstdlib>


class Grid
{
	int grid[100][100];
	static Grid *instance;
	int rowCount;
	int colCount;
	
	public:
	Grid(const int _rowCount ,const int _colCount )
	{
		// dynamically allocate memory of size M*N
		memset(grid, 0, sizeof(grid[0][0]) * _rowCount * _colCount);
		this->rowCount = _rowCount;
		this->colCount = _colCount;
	}

	void printGrid()
	{
		for(int i = 0 ; i < rowCount; i++)
		{
			for(int j = 0; j < colCount; j++)
			{
				printf("%2d ", grid[i][j]);
			}
			printf("\n");
		}
	}


	void fillTheGrid(int maxDiffTileType)
	{
		std::srand(std::time(0));
		for(int i = 0 ; i < rowCount; i++)
		{
			for(int j = 0; j < colCount; j++)
			{
				grid[i][j] = std::rand() % maxDiffTileType;
			}
		}
	}
};



int main(){
	Grid myGrid(10, 10);
	//myGrid.printGrid();
	myGrid.fillTheGrid(10);
	myGrid.printGrid();
}


