#include "Libraries.h"
#include "Hephaestus.h"
#include "Logging.h"
#include "List.h"
using namespace std;

void List::Initilise(GLFWwindow* In_Window, Hephaestus In_Hephaestus){
	W_List = In_Window;
	H_List = In_Hephaestus;
}
void List::Load_List(string List_Name){
	bool Load = true;
	int Temp_Int = 0;
	string Temp_String = "";
	List_Item Temp_List_Item;
	ifstream In_List("Lists/" + List_Name + ".list");
	if (In_List.is_open()){
		In_List >> Number_Of_Items;
		In_List >> Total_Test_Takes;
		In_List >> Test_Data_Stored;
		for (int a = 0; a < Test_Data_Stored; a++){
			In_List >> Temp_Int;
			Past_Percent.push_back(Temp_Int);
		}
		for (int a = 0; a < Number_Of_Items; a++){
			In_List >> Temp_List_Item.Percent;
			getline(In_List, Temp_String);
			Temp_List_Item.Part_A = Temp_String;
			getline(In_List, Temp_String);
			Temp_List_Item.Part_B = Temp_String;
		}
	}
	else{
		Load = false;
	}
	if (Load == true){
		View_List();
	}
}
void List::Initilize_List(){

}

bool List::Close(){
	if (glfwWindowShouldClose(W_List)){
		return(true);
	}
	else{
		return(false);
	}
}

void List::View_List(){
	for (int a = 0; a < Number_Of_Items; a++){
		cout << List_Items[a].Part_A << "|" << List_Items[a].Part_B << endl;
	}
}