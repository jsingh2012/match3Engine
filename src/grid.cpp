#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class node
{
	static int id;
	public:
	int posX;
	int posY;
	int type;
	node(){
		id++;
		type = 0;
	}
	node(int x,int y, int _type)
	{
		id++;
		posX = x;
		posY = y;
		type = _type;
	}

	bool operator==(node& rhs)const
	{
		if (this->type ==rhs.type)
			return true;
		return false;
	}
};

int node::id = 0;

class Grid
{
	node grid[100][100];
	static Grid *instance;
	int rowCount;
	int colCount;
	
	public:
	Grid(const int _rowCount ,const int _colCount )
	{
		// dynamically allocate memory of size M*N
		this->rowCount = _rowCount;
		this->colCount = _colCount;
	}

	void printGrid()
	{
		for(int i = 0 ; i < rowCount; i++)
		{
			for(int j = 0; j < colCount; j++)
			{
				printf("(%2d,%2d)%2d ",i,j, grid[i][j].type);
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
				grid[i][j].type = std::rand() % maxDiffTileType;
				grid[i][j].posX = i;
				grid[i][j].posY = j;
			}
		}
	}

	void checkAllMatches()
	{
		for(int i = 0 ; i < rowCount; i++)
		{
			for(int j = 0; j < colCount; j++)
			{
				bool matched = false;
				vector <node*> matchesNodes;
				printf("START getMatchAtPos at := %2d %2d := \n", i, j);
				matchesNodes = getMatchAtPos(i, j);
				for (auto&& node : matchesNodes)
				{
					printf("%d ", node->type);
					matched = true;
				}
				printf("\n");
				if(matched)
					printGrid();
				matched = false;	
			printf("END\n");
			}
		}
		
	}	

	vector <node*> getMatchAtPos(int posX, int posY)
	{
		int maxLeft = 0;
		int maxRight = 0;
		int maxUp = 0;
		int maxDown = 0;
		int matchingTiles = 0;
		vector <node*> matchedNode;
		for(int i = posX - 1; i >= 0; i--)	
		{
			if(grid[posX][posY] == grid[i][posY])
				maxUp++;
			else
				break;
		}
		
		for(int i = posX + 1; i < colCount; i++)	
		{
			if(grid[posX][posY] == grid[i][posY])
				maxDown++;
			else
				break;
		}
		
		for(int j = posY - 1; j >= 0; j--)	
		{
			if(grid[posX][posY] == grid[posX][j])
				maxLeft++;
			else
				break;
		}
		
		for(int j = posY + 1; j < rowCount; j++)	
		{
			if(grid[posX][posY] == grid[posX][j])
				maxRight++;
			else
				break;
		}
		
		if((maxLeft + maxRight + 1) >= 3){
			printf("Match in horizontal Direction at %2d %2d := %d\n", posX, posY, (maxLeft + maxRight + 1));
			matchingTiles = maxLeft + maxRight + 1;
			for(int i = posY - maxLeft; i <= posY + maxRight; i++)
			{
				matchedNode.push_back(&grid[posX][i]);	
			}
		}
		if((maxUp + maxDown + 1) >= 3) {
			printf("Match in Vertical Direction at %2d %2d := %d\n", posX, posY, (maxUp + maxDown + 1));
			matchingTiles += maxUp + maxDown + 1;
			
			for(int i = posX - maxUp; i <= posX + maxDown; i++)
			{
				matchedNode.push_back(&grid[i][posY]);	
			}
		}
		return matchedNode;
	}
};



int main(){
	Grid myGrid(10, 10);
	//myGrid.printGrid();
	myGrid.fillTheGrid(5);
	myGrid.printGrid();
	myGrid.checkAllMatches();
}


