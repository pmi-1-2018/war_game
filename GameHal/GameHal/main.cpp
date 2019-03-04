#include"map.h"
#include<ctime>
#include<fstream>

int main()
{
	srand(time(NULL));
	Map m;
	ofstream delCont;
	m.generateRandomMap("Read_Edit_Map.txt", 5, 5);
	while (true)
	{
		int action;
		cout << "what do u want to do?(press 1 to save your changes made to map, press 2 to generate new random map, 3 to exit) " << endl;
		cin >> action;
		switch (action)
		{
		case 1:
			m.readMapFromFile("Read_Edit_Map.txt");
			cout << "changes saved" << endl;
			break;
		case 2:
			cout << "enter size" << endl;
			int height, length;
			cin >> height >> length;
			delCont.open("Read_Edit_Map.txt", ofstream::out | ofstream::trunc);
			delCont.close();
			m.generateRandomMap("Read_Edit_Map.txt", height, length);
			cout << "new map was generated" << endl;
			break;
		default:
			break;
		}
		if (action == 3)
		{
			break;
		}
	}
	system("pause");
	return 0;
}