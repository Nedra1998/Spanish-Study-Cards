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
			Menu_Number = Menu_One();
		}
		else if (Menu_Number == 2){
			Menu_Number = Menu_Two();
		}
		else{
			Logging::log_error("Invalid Menu: " + to_string(Menu_Number), "Run_Menu/Menu.cpp");
			return(0);
		}
		H_Menu.Clear_All_Layers();
	}
	return(Menu_Number);
}
 
bool Menu::Close(){
	if (glfwWindowShouldClose(W_Menu)){
		return(true);
	}
	else{
		return(false);
	}
}

void Menu::Reload_Menu(int Menu){
	Lists.clear();
	string Temp;
	ifstream Load_Lists;
	Number_Of_Lists = 0;
	if (Menu == 1){
		Load_Lists.open("Lists.list");
	}
	if (Menu == 2){
		Load_Lists.open("Tests.list");
	}
	if (Load_Lists.is_open()){
		while (getline(Load_Lists, Temp)){
			Lists.push_back(Temp);
			Number_Of_Lists++;
		}
		Load_Lists.close();
	}
	Number_Of_Pages = Number_Of_Lists / 10;
	if (remainder(Number_Of_Lists, 10) != 0){
		Number_Of_Pages++;
	}
}
char Menu::Key(int key){
	return(char(key));
}

int Menu::Menu_Zero(){
	H_Menu.Clear_All_Layers();
	int Layer = -1, Button = -1, Action = -1;
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(2);
	H_Menu.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button("Spanish Study Program", "Textures/Transparent", "Basic/White", 0.7, 0.3);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button(0.0, 0.7, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[0]->New_Button("List", "Textures/Button", "Basic/White", 0.5, 0.1);
	H_Menu.Layers[2]->Button_Objects[0]->Translate_Button(0.0, 0.4, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[1]->New_Button("Test", "Textures/Button", "Basic/White", 0.5, 0.1);
	H_Menu.Layers[2]->Button_Objects[1]->Translate_Button(0.0, 0.0, 0.0);
	H_Menu.Layers[2]->Initilize_Object(4);
	H_Menu.Layers[2]->Button_Objects[2]->New_Button("Quit", "Textures/Button", "Basic/White", 0.5, 0.1);
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
	Number_Of_Lists = 0;
	Number_Of_Pages = 0;
	Start_List_on_Page = 0;
	Current_Page = 0;
	Current_List = 0;
	Lists.clear();
	H_Menu.Clear_All_Layers();
	string Temp = "";
	int Layer = -1, Button = -1, Action = -1, Load_Set = 10;
	bool Load = true, Delete = false;
	ifstream Load_Lists("Lists.list");
	if (Load_Lists.is_open()){
		while (getline(Load_Lists, Temp)){
			Lists.push_back(Temp);
			Number_Of_Lists++;
		}
		Load_Lists.close();
	}
	Number_Of_Pages = Number_Of_Lists / 10;
	if (remainder(Number_Of_Lists, 10) != 0){
		Number_Of_Pages++;
	}
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(2);
	H_Menu.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button("Lists", "Textures/Transparent", "Basic/White", 0.7, 0.15);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button(0.0, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages), "Textures/Transparent", "Basic/White", 0.7, 0.05);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button(0.0, 0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button("Back", "Textures/Button", "Basic/White", 0.3, 0.1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button(0.0, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button("Next", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button(0.7, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button("Previous", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button(-0.7, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[5]->New_Button("Delete", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[5]->Translate_Button(-0.7, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[6]->New_Button("New", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[6]->Translate_Button(0.7, -0.7, 0.0);
	while (Close() == false){
		if (Load == true){
			int Index = 0;
			Load_Set = 10;
			Load = false;
			H_Menu.Layers[1]->Button_Objects[1]->Edit_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages));
			H_Menu.Layers[2]->Clear_All();
			for (Current_List = Current_Page * 10; Index < 10 && Current_List < Number_Of_Lists; Current_List++){
				H_Menu.Layers[2]->Initilize_Object(4);
				if (Delete == false){
					H_Menu.Layers[2]->Button_Objects[Index]->New_Button(Lists[Current_List], "Textures/Button", "Basic/White", 0.4, 0.1);
				}
				else if (Delete == true){
					H_Menu.Layers[2]->Button_Objects[Index]->New_Button(Lists[Current_List], "Textures/Button Red", "Basic/White", 0.4, 0.1);
				}
				if (Index < 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(-0.5, 0.0, 0.0);
				}
				else if (Index >= 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.5, 0.0, 0.0);
				}
				if (Index == 0 || Index == 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.55, 0.0);
				}
				if (Index == 1 || Index == 6){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.3, 0.0);
				}
				if (Index == 2 || Index == 7){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.05, 0.0);
				}
				if (Index == 3 || Index == 8){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.2, 0.0);
				}
				if (Index == 4 || Index == 9){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.45, 0.0);
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
				cout << "A";
				Current_Page++;
				Load = true;
			}
			else if (Button == 4 && Current_Page > 0){
				Current_Page--;
				Load = true;
			}
			else if (Button == 5){
				if (Delete == false){
					Delete = true;
				}
				else if (Delete == true){
					Delete = false;
				}
				Load = true;
			}
			else if (Button == 6){
				int Quit = 0;
				string Name = "", New = "", Total = "", Temp = "";
				H_Menu.Layers[3]->Initilize_Object(4);
				H_Menu.Layers[3]->Button_Objects[0]->New_Button("", "Textures/Button", "Basic/White", 0.7, 0.2);
				H_Menu.Layers[3]->Button_Objects[0]->Translate_Button(0.0, 0.0, 0.0);
				while (Quit == 0){
					int Layer, Button, Action;
					if (Load_Set > 0){
						Load_Set--;
						H_Menu.Clear_Key();
					}
					if (H_Menu.Check_Key() < 97 && H_Menu.Check_Key() > 31 && Load_Set == 0){
						Name = Name + Key(H_Menu.Check_Key());
						Load_Set = 10;
					}
					if (glfwGetKey(W_Menu, GLFW_KEY_BACKSPACE) && Load_Set == 0){
						string New = "";
						for (int i = 0; i < Name.size() - 1 && Name.size() > 0; i++){
							New = New + Name[i];
						}
						Name = New;
						Load_Set = 10;
					}
					if (glfwGetKey(W_Menu, GLFW_KEY_ENTER)){
						if (Name == "" || Name == " "){
							Name = "NEW LIST";
						}
						Quit = 2;
					}
					else if (glfwGetKey(W_Menu, GLFW_KEY_ESCAPE)){
						Quit = 1;
					}
					H_Menu.Layers[3]->Button_Objects[0]->Edit_Button(Name);
					H_Menu.Display_All_Layers();
					H_Menu.Frame();
					Close();
				}
				if (Quit == 2){
					ifstream In_List("Lists.list");
					if (In_List.is_open()){
						while (getline(In_List, Temp)){
							Total = Total + Temp + "\n";
						}
						In_List.close();
					}
					Total = Total + Name + "\n";
					ofstream Out_List("Lists.list");
					if (Out_List.is_open()){
						Out_List << Total;
						Out_List.close();
					}
					Name = "Lists/" + Name + ".list";
					ofstream Initilize_List(Name.c_str());
					Reload_Menu(1);
					Load = true;
				}
				H_Menu.Layers[3]->Clear_All();

			}
			H_Menu.Clear_Mouse();
		}
		if (Layer == 2 && Delete == false){
			return((Button + (Current_Page * 10)) * 10);
		}
		else if (Layer == 2 && Delete == true){
			int To_Remove = (Button + (Current_Page * 10));
			int Max = Lists.size();
			string Remove = "Lists/" + Lists[To_Remove] + ".list";
			remove(Remove.c_str());
			ofstream Removal("Lists.list");
			if (Removal.is_open()){
				for (int i = 0; i < Max; i++){
					if (i != To_Remove){
						Removal << Lists[i] << "\n";
					}
				}
				Removal.close();
			}
			Reload_Menu(1);
			Load = true;
		}
		H_Menu.Display_All_Layers();
		H_Menu.Frame();
	}
	return(1);
}
int Menu::Menu_Two(){
	Number_Of_Lists = 0;
	Number_Of_Pages = 0;
	Start_List_on_Page = 0;
	Current_Page = 0;
	Current_List = 0;
	Lists.clear();
	H_Menu.Clear_All_Layers();
	string Temp = "";
	int Layer = -1, Button = -1, Action = -1, Load_Set = 10;
	bool Load = true, Delete = false;
	ifstream Load_Lists("Tests.list");
	if (Load_Lists.is_open()){
		while (getline(Load_Lists, Temp)){
			Lists.push_back(Temp);
			Number_Of_Lists++;
		}
		Load_Lists.close();
	}
	Number_Of_Pages = Number_Of_Lists / 10;
	if (remainder(Number_Of_Lists, 10) != 0){
		Number_Of_Pages++;
	}
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(2);
	H_Menu.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button("Tests", "Textures/Transparent", "Basic/White", 0.7, 0.15);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button(0.0, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages), "Textures/Transparent", "Basic/White", 0.7, 0.05);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button(0.0, 0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button("Back", "Textures/Button", "Basic/White", 0.3, 0.1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button(0.0, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button("Next", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button(0.7, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button("Previous", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button(-0.7, 0.8, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[5]->New_Button("Delete", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[5]->Translate_Button(-0.7, -0.7, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[6]->New_Button("New", "Textures/Button", "Basic/White", 0.25, 0.1);
	H_Menu.Layers[1]->Button_Objects[6]->Translate_Button(0.7, -0.7, 0.0);
	while (Close() == false){
		if (Load == true){
			int Index = 0;
			Load_Set = 10;
			Load = false;
			H_Menu.Layers[1]->Button_Objects[1]->Edit_Button(to_string(Current_Page + 1) + "/" + to_string(Number_Of_Pages));
			H_Menu.Layers[2]->Clear_All();
			for (Current_List = Current_Page * 10; Index < 10 && Current_List < Number_Of_Lists; Current_List++){
				H_Menu.Layers[2]->Initilize_Object(4);
				if (Delete == false){
					H_Menu.Layers[2]->Button_Objects[Index]->New_Button(Lists[Current_List], "Textures/Button", "Basic/White", 0.4, 0.1);
				}
				else if (Delete == true){
					H_Menu.Layers[2]->Button_Objects[Index]->New_Button(Lists[Current_List], "Textures/Button Red", "Basic/White", 0.4, 0.1);
				}
				if (Index < 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(-0.5, 0.0, 0.0);
				}
				else if (Index >= 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.5, 0.0, 0.0);
				}
				if (Index == 0 || Index == 5){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.55, 0.0);
				}
				if (Index == 1 || Index == 6){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.3, 0.0);
				}
				if (Index == 2 || Index == 7){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, 0.05, 0.0);
				}
				if (Index == 3 || Index == 8){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.2, 0.0);
				}
				if (Index == 4 || Index == 9){
					H_Menu.Layers[2]->Button_Objects[Index]->Translate_Button(0.0, -0.45, 0.0);
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
				cout << "A";
				Current_Page++;
				Load = true;
			}
			else if (Button == 4 && Current_Page > 0){
				Current_Page--;
				Load = true;
			}
			else if (Button == 5){
				if (Delete == false){
					Delete = true;
				}
				else if (Delete == true){
					Delete = false;
				}
				Load = true;
			}
			else if (Button == 6){
				int Quit = 0;
				string Name = "", New = "", Total = "", Temp = "";
				H_Menu.Layers[3]->Initilize_Object(4);
				H_Menu.Layers[3]->Button_Objects[0]->New_Button("", "Textures/Button", "Basic/White", 0.7, 0.2);
				H_Menu.Layers[3]->Button_Objects[0]->Translate_Button(0.0, 0.0, 0.0);
				while (Quit == 0){
					int Layer, Button, Action;
					if (Load_Set > 0){
						Load_Set--;
						H_Menu.Clear_Key();
					}
					if (H_Menu.Check_Key() < 97 && H_Menu.Check_Key() > 31 && Load_Set == 0){
						Name = Name + Key(H_Menu.Check_Key());
						Load_Set = 10;
					}
					if (glfwGetKey(W_Menu, GLFW_KEY_BACKSPACE) && Load_Set == 0){
						string New = "";
						for (int i = 0; i < Name.size() - 1 && Name.size() > 0; i++){
							New = New + Name[i];
						}
						Name = New;
						Load_Set = 10;
					}
					if (glfwGetKey(W_Menu, GLFW_KEY_ENTER)){
						if (Name == "" || Name == " "){
							Name = "NEW LIST";
						}
						Quit = 2;
					}
					else if (glfwGetKey(W_Menu, GLFW_KEY_ESCAPE)){
						Quit = 1;
					}
					H_Menu.Layers[3]->Button_Objects[0]->Edit_Button(Name);
					H_Menu.Display_All_Layers();
					H_Menu.Frame();
					Close();
				}
				if (Quit == 2){
					if (Create_Test(Name) == 1){
						Reload_Menu(2);
						Load = true;
					}
				}
				H_Menu.Layers[3]->Clear_All();
			}
			H_Menu.Clear_Mouse();
		}
		if (Layer == 2 && Delete == false){
			return((Button + (Current_Page * 10)) * 10);
		}
		else if (Layer == 2 && Delete == true){
			int To_Remove = (Button + (Current_Page * 10));
			int Max = Lists.size();
			string Remove = "Tests/" + Lists[To_Remove] + ".list";
			if (remove(Remove.c_str()) != 0){
				cout << "Error Deleating: " << Remove << endl;
			}
			ofstream Removal("Tests.list");
			if (Removal.is_open()){
				for (int i = 0; i < Max; i++){
					if (i != To_Remove){
						Removal << Lists[i] << "\n";
					}
				}
				Removal.close();
			}
			Reload_Menu(2);
			Load = true;
		}
		H_Menu.Display_All_Layers();
		H_Menu.Frame();
	}
	return(1);
}

int Menu::Create_Test(string Name){
	vector<string> Files;
	int Quit = 0, Load_Set = 10, Index = 0;
	string New_List = "", Old_List = "";
	bool Open = false;
	H_Menu.Layers[4]->Initilize_Object(2);
	H_Menu.Layers[4]->Textured_Objects[0]->New_Textured_Object("Textures/Background", 4, 1, 1, 0, 0);
	H_Menu.Layers[6]->Initilize_Object(4);
	H_Menu.Layers[6]->Button_Objects[0]->New_Button("New Test", "Textures/Button 1", "Basic/White", 0.7, 0.15);
	H_Menu.Layers[6]->Button_Objects[0]->Translate_Button(0.0, 0.8, 0.0);
	H_Menu.Layers[6]->Initilize_Object(4);
	H_Menu.Layers[6]->Button_Objects[1]->New_Button("Cancel", "Textures/Button", "Basic/White", 0.4, 0.1);
	H_Menu.Layers[6]->Button_Objects[1]->Translate_Button(-0.5, -0.8, 0.0);
	H_Menu.Layers[6]->Initilize_Object(4);
	H_Menu.Layers[6]->Button_Objects[2]->New_Button("Create", "Textures/Button", "Basic/White", 0.4, 0.1);
	H_Menu.Layers[6]->Button_Objects[2]->Translate_Button(0.5, -0.8, 0.0);
	H_Menu.Layers[6]->Initilize_Object(4);
	H_Menu.Layers[6]->Button_Objects[3]->New_Button("", "Textures/Button 1", "Basic/White", 0.7, 0.15);
	H_Menu.Layers[6]->Button_Objects[3]->Translate_Button(0.0, -0.5, 0.0);
	while (Quit == 0){
		int Layer, Button, Action;
		if (Load_Set > 0){
			Load_Set--;
			H_Menu.Clear_Key();
		}
		if (H_Menu.Check_Key() < 97 && H_Menu.Check_Key() > 31 && Load_Set == 0){
			New_List = New_List + Key(H_Menu.Check_Key());
			Load_Set = 10;
		}
		if (glfwGetKey(W_Menu, GLFW_KEY_BACKSPACE) && Load_Set == 0){
			string New = "";
			for (int i = 0; i < New_List.size() - 1 && New_List.size() > 0; i++){
				New = New + New_List[i];
			}
			New_List = New;
			Load_Set = 10;
		}
		if (glfwGetKey(W_Menu, GLFW_KEY_ENTER) && Open == true){
			for (int i = 0; i < Index; i++){
				H_Menu.Layers[5]->Button_Objects[i]->Translate_Button(0.0, 0.21, 0.0);
			}
			H_Menu.Layers[5]->Initilize_Object(4);
			H_Menu.Layers[5]->Button_Objects[Index]->New_Button(New_List, "Textures/Button 1", "Basic/White", 0.5, 0.1);
			H_Menu.Layers[5]->Button_Objects[Index]->Translate_Button(0.0, -0.2, 0.0);
			Files.push_back(New_List);
			Index++;
			New_List = "";
			Open = false;
		}
		else if (glfwGetKey(W_Menu, GLFW_KEY_ESCAPE)){
			Quit = 1;
		}
		if (New_List != Old_List){
			Open = false;
			string Test_File = "Lists/" + New_List + ".list";
			ifstream Test(Test_File.c_str());
			if (Test.is_open()){
				H_Menu.Layers[6]->Button_Objects[3]->New_Button("", "Textures/Button 2", "Basic/White", 0.7, 0.15);
				Open = true;
				Test.close();
			}
			else{
				H_Menu.Layers[6]->Button_Objects[3]->New_Button("", "Textures/Button Red 2", "Basic/White", 0.7, 0.15);
			}
			H_Menu.Layers[6]->Button_Objects[3]->Translate_Button(0.0, -0.5, 0.0);
			H_Menu.Layers[6]->Button_Objects[3]->Edit_Button(New_List);
			Old_List = New_List;
		}
		H_Menu.Check_All_Buttons(Layer, Button, Action);
		if (Layer == 6){
			if (Button == 1){
				Quit = 2;
			}
			if (Button == 2 && Index > 0){
				Quit = 1;
			}
		}

		H_Menu.Display_All_Layers();
		H_Menu.Frame();
		Close();

	}
	if (Quit == 1){
		string Total = "", Temp = "";
		ifstream In_Test("Tests.list");
		if (In_Test.is_open()){
			while (getline(In_Test, Temp)){
				Total = Total + Temp + "\n";
			}
			In_Test.close();
		}
		Total = Total + Name + "\n";
		ofstream Out_Test("Tests.list");
		if (Out_Test.is_open()){
			Out_Test << Total;
			Out_Test.close();
		}
		Name = "Tests/" + Name + ".list";
		ofstream Initilize_Test(Name.c_str());
		if (Initilize_Test.is_open()){
			for (int i = 0; i < Index; i++){
				Initilize_Test << Files[i] << ".list\n";
			}
			Initilize_Test.close();
		}
	}
	H_Menu.Layers[4]->Clear_All();
	H_Menu.Layers[5]->Clear_All();
	H_Menu.Layers[6]->Clear_All();
	return(Quit);
}