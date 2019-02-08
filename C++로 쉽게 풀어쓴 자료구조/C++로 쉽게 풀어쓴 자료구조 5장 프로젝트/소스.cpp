#include <iostream>
#include <fstream>
#include <stack>

using std::cout;
using std::cin;
using std::endl;
using namespace std;
struct location2D
{
	int y, x;
	location2D(int _y = 0, int _x = 0) : y(_y), x(_x) {	}
};

class Maze
{
	int width;	// 미로의 너비
	int height;	// 미로의 높이
	int **map;	// 미로 맵
	location2D entryLoc, exitLoc;	//미로의 입구 및 출구
public:
	Maze()	{ init(0, 0);}
	~Maze() { reset(); }
	void init(int wid, int hei)
	{
		width = wid;
		height = hei;

		map = new int*[height];
		for (int i = 0; i < height; i++)
			map[i] = new int[width];
	}
	void reset()
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}
	void load(const char * fname)
	{
		int wid, hei;

		ifstream input(fname);
		
		input >> wid >> hei;
		init(wid, hei);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				input >> map[i][j];
				if (map[i][j] == 5)
					entryLoc = location2D(i, j);
				else if (map[i][j] == 9)
					exitLoc = location2D(i, j);
			}
		}
		input.close();
	}
	void print()
	{
		cout << width << " " << height << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == 0)
					cout << "■ ";
				else if (map[i][j] == 1)
					cout << "   ";
				else if (map[i][j] == -1)
					cout << "□ ";
				else if (map[i][j] == 5)
					cout << "○ ";
				else if (map[i][j] == 9)
					cout << "◎ ";
				else if (map[i][j] == -2)
					cout << "☆ ";
			}
			cout << endl;
		}
	}
	void searchExit()
	{
		stack<location2D> search;
		stack<location2D> rout;
		stack<location2D> rout2;
		search.push(entryLoc);
		location2D loc;
		int count ;
		while (!(search.top().y == exitLoc.y && search.top().x == exitLoc.x))
		{
			count = 0;
			loc = search.top();
			search.pop();
			map[loc.y][loc.x] = -1; // 지난 길이라고 체크

			// 벽이 아니고 지나온 길이 아니면 탐색하기
			if (loc.x > 0 && map[loc.y][loc.x - 1] != 0 && map[loc.y][loc.x - 1] != -1)
			{
				search.push(location2D(loc.y, loc.x - 1));
				count++;
			}
			if (loc.y > 0 && map[loc.y - 1][loc.x] != 0 && map[loc.y - 1][loc.x] != -1)
			{
				search.push(location2D(loc.y - 1, loc.x));
				count++;
			}
			if (loc.x < width - 1 && map[loc.y][loc.x + 1] != 0 && map[loc.y][loc.x + 1] != -1)
			{
				search.push(location2D(loc.y, loc.x + 1));
				count++;
			}
			if (loc.y < height - 1 && map[loc.y + 1][loc.x] != 0 && map[loc.y + 1][loc.x] != -1)
			{
				search.push(location2D(loc.y + 1, loc.x));
				count++;
			}

			if (count == 0)
			{
				while ( !(rout2.top().y == rout.top().y && rout2.top().x == rout.top().x))
					rout.pop();
				rout2.pop();
			}
			else if (count == 2)
			{
				rout.push(loc);
				rout2.push(loc);
			}
			else if (count == 1)
				rout.push(loc);
		}

		while(rout.empty() == false)
		{
			loc = rout.top();
			map[loc.y][loc.x] = -2;
			rout.pop();
		}
	}
};

int main(void)
{
	Maze maze;
	maze.load("map.txt");
	maze.print();
	maze.searchExit();
	cout << "--------------------------------" << endl;
	maze.print();

	return 0;
}