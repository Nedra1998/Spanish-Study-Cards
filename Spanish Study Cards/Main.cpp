#include "Libraries.h"
#include "Hephaestus.h"
#include "Logging.h"
#include "Menu.h"
#include "List.h"
using namespace std;
Hephaestus H;
Menu M;
List L;
GLFWwindow* Win;
void Key_Call(GLFWwindow* Win, int key, int scancode, int action, int mods){
	H.Key_Call_Back(Win, key, scancode, action, mods);
	M.H_Menu.Key_Call_Back(Win, key, scancode, action, mods);
	L.H_List.Key_Call_Back(Win, key, scancode, action, mods);
}
void Mouse_Call(GLFWwindow* Win, int button, int action, int mods){
	H.Mouse_Call_Back(Win, button, action, mods);
	M.H_Menu.Mouse_Call_Back(Win, button, action, mods);
	L.H_List.Mouse_Call_Back(Win, button, action, mods);
}
void Window_Call(GLFWwindow* Win, int width, int hight){
	glfwSetWindowSize(Win, width, hight);
}
int main(){
	GLFWwindow* Win;
	Win = H.Full_Setup();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetKeyCallback(Win, Key_Call);
	glfwSetMouseButtonCallback(Win, Mouse_Call);
	glfwSetWindowSizeCallback(Win, Window_Call);
	srand(time(NULL));
	/*>>>>>Place Before Start Code Here<<<<<*/
	int Menu = 0;
	M.Initilize_Menu(Win, H);
	L.Initilise(Win, H);
	while (!glfwWindowShouldClose(Win)){
		/*>>>>>Place While Running Code Here<<<<<*/
		if (Menu == -1){
			glfwSetWindowShouldClose(Win, 1);
		}
		if (Menu < 10){
			Menu = M.Run_Menu(Menu);
		}
		else{
			L.Load_List("Test");
		}
		H.Display_All_Layers();
		H.Frame();
	}
	H.Terminate_Log();
	return(0);
}