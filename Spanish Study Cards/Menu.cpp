#include "Libraries.h"
#include "Hephaestus.h"
#include "Logging.h"
#include "Menu.h"
using namespace std;

void Menu::Initilize_Menu(GLFWwindow* In_Window, Hephaestus In_Hephaestus){
	H_Menu = In_Hephaestus;
	W_Menu = In_Window;
}
int Menu::Run_Menu(int Menu_Number){
	if (Menu_Number == 0){
		return(Menu_Zero());
	}
	else if (Menu_Number == 1){
		return(Menu_One());
	}
	else{
		Logging::log_error("Invalid Menu: " + to_string(Menu_Number), "Run_Menu/Menu.cpp");
		return(0);
	}
}
 
bool Menu::Close(){
	if (glfwWindowShouldClose(W_Menu)){
		return(true);
	}
	else{
		return(false);
	}
}

int Menu::Menu_Zero(){
	int Layer = -1, Button = -1, Action = -1;
	H_Menu.Clear_All_Layers();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(2);
	H_Menu.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button("Spanish Study Program", "Textures/Transparent", "Basic/Black", 0.7, 0.3);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button(0.0, 0.7, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[0]->New_Button("List", "Textures/Button", "Basic/Black", 0.5, 0.1);
	H_Menu.Layers[2]->Button_Objects[0]->Translate_Button(0.0, 0.4, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[1]->New_Button("Test", "Textures/Button", "Basic/Black", 0.5, 0.1);
	H_Menu.Layers[2]->Button_Objects[1]->Translate_Button(0.0, 0.0, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[2]->New_Button("Quit", "Textures/Button", "Basic/Black", 0.5, 0.1);
	H_Menu.Layers[2]->Button_Objects[2]->Translate_Button(0.0, -0.4, 0.0);
	while (Close() == false){
		H_Menu.Check_All_Buttons(Layer, Button, Action);
		H_Menu.Display_All_Layers();
		H_Menu.Frame();
	}
	return(0);
}
int Menu::Menu_One(){
	return(1);
}