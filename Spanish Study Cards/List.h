#include "Libraries.h"
using namespace std;
class List{
private:
	GLFWwindow* W_List;
	struct List_Item{
		int Percent;
		string Part_A, Part_B;
	};
	vector<List_Item> List_Items;
	vector<int> Past_Percent;
	int Number_Of_Items, Total_Test_Takes, Test_Data_Stored;
	void View_List();
	bool Close();
public:
	Hephaestus H_List;
	void Initilise(GLFWwindow* In_Window, Hephaestus In_Hephaestus);
	void Load_List(string List_Name);
	void Initilize_List();
};