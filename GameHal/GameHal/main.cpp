#include"map.h"
#include<ctime>

int main()
{
	srand(time(NULL));
	Map m;
	m.generateRandomMap("Read_Edit_map.txt", 7, 7);
	system("pause");
	return 0;
}