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
	while (Menu_Number != -1 && Menu_Number < 10){
		if (Menu_Number == 0){
			Menu_Number = Menu_Zero();
			if (Menu_Number == 3){
				return(-1);
			}
		}
		else if (Menu_Number == 1){
			return(Menu_One());
		}
		else{
			Logging::log_error("Invalid Menu: " + to_string(Menu_Number), "Run_Menu/Menu.cpp");
			return(0);
		}
		H_Menu.Clear_All_Layers();
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
	H_Menu.Clear_All_Layers();
	int Layer = -1, Button = -1, Action = -1;
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
		if (Layer == 2 && Button != -1){
			return(Button + 1);
		}
		H_Menu.Display_All_Layers();
		H_Menu.Frame();
	}
	return(0);
}
int Menu::Menu_One(){
	H_Menu.Clear_All_Layers();
	vector<string> Lists;
	string Temp = "";
	int Number_Of_Lists = 0, Number_Of_Pages = 0, Start_List_on_Page = 0, Current_Page = 0, Current_List = 0;
	int Layer = -1, Button = -1, Action = -1, Load_Set = 10;
	bool Load = true;
	ifstream Load_Lists("Lists.list");
	if (Load_Lists.is_open()){
		while (getline(Load_Lists, Temp)){
			Lists.push_back(Temp);
			Number_Of_Lists++;
		}
	}
	Number_Of_Pages = Number_Of_Lists / 10;
	if (remainder(Number_Of_Lists, 10) != 0){
		Number_Of_Pages++;
	}
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(2);
	H_Menu.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button("Lists", "Textures/Transparent", "Basic/Black", 0.7, 0.15);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button(0.0, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages), "Textures/Transparent", "Basic/Black", 0.7, 0.05);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button(0.0, 0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button("Back", "Textures/Button", "Basic/Black", 0.3, 0.1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button(0.0, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button("Next", "Textures/Button", "Basic/Black", 0.3, 0.1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button(0.7, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button("Previous", "Textures/Button", "Basic/Black", 0.3, 0.1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button(-0.7, -0.7, 0.0);
	while (Close() == false){
		if (Load == true){
			int Index = 0;
			Load_Set = 10;
			Load = false;
			H_Menu.Layers[1]->Button_Objects[1]->Edit_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages));
			H_Menu.Layers[2]->Clear_All();
			for (Current_List = Current_Page * 10; Index < 10 && Current_List < Number_Of_Lists; Current_List++){
				H_Menu.Layers[2]->Initilize_Object(4);
				H_Menu.Layers[2]->Button_Objects[Index]->New_Button(Lists[Current_List], "Textures/Button", "Basic/Black", 0.4, 0.1);
				if (Index < 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(-0.5, 0.0, 0.0);
				}
				else if (Index >= 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.5, 0.0, 0.0);
				}
				if (Index == 0 || Index == 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.6, 0.0);
				}
				if (Index == 1 || Index == 6){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.35, 0.0);
				}
				if (Index == 2 || Index == 7){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.1, 0.0);
				}
				if (Index == 3 || Index == 8){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.15, 0.0);
				}
				if (Index == 4 || Index == 9){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.4, 0.0);
				}
				Index++;
			}
		}
		if (Load_Set > 0){
			H_Menu.Clear_Mouse();
			Load_Set--;
		}
		H_Menu.Check_All_Buttons(Layer, Button, Action);
		if (Layer == 1){
			if (Button == 2){
				return(0);
			}
			else if (Button == 3 && Current_Page < Number_Of_Pages - 1){
				Current_Page++;
				Load = true;
			}
			else if (Button == 4 && Current_Page > 0){
				Current_Page--;
				Load = true;
			}
		}
		H_Menu.Display_All_Layers();
		H_Menu.Frame();
	}
	return(1);
}