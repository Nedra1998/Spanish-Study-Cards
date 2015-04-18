//#include "Hephaestus.h"
#include "Libraries.h"
using namespace std;
class Menu{
private:
	GLFWwindow* W_Menu;
	int Menu_Zero();
	int Menu_One();
	bool Close();
public:
	Hephaestus H_Menu;
	void Initilize_Menu(GLFWwindow* In_WIndow, Hephaestus In_Hephaestus);
	int Run_Menu(int Menu_Number);
};