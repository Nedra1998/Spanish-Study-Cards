#include "Libraries.h"
using namespace std;
class Menu{
private:
	GLFWwindow* W_Menu;
	void Reload_Menu(int Menu);
	char Key(int key);
	int Menu_Zero();
	int Menu_One();
	int Menu_Two();

	int Create_Test(string Name);
	bool Close();
	vector<string> Lists;
	int Number_Of_Lists = 0, Number_Of_Pages = 0, Start_List_on_Page = 0, Current_Page = 0, Current_List = 0;
public:
	Hephaestus H_Menu;
	void Initilize_Menu(GLFWwindow* In_WIndow, Hephaestus In_Hephaestus);
	int Run_Menu(int Menu_Number);
};