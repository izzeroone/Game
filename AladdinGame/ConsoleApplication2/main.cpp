#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include "../pugixml/src/pugixml.hpp"
using namespace std;
using namespace pugi;

#define MAP_HEIGHT 689;
#define OFFSETX 0;
#define OFFSETY 47;

void loadSpriteInfo(const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	ofstream myfile("result.txt");
	int left, top, width, height;
	if (file)
	{
		while (!feof(file))
		{

			char name[100];
			fscanf(file, "%s %d %d %d %d", &name, &left, &top, &width, &height);
			myfile << name << "\t" << left << "\t" << top << "\t" << left + width << "\t" << top + height << "\t0\t0" <<endl;
		}
	}
	myfile.close();
	fclose(file);
}

void fixXML(const string path)
{
	pugi::xml_document readDoc;
	pugi::xml_document writeDoc;

	// Mở file và đọc
	xml_parse_result result = readDoc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return;
	}

	int i = 0;

	// Lấy id từ file xml. so sánh với eID, tuỳ theo eID nào mà gọi đến đúng hàm load cho riêng object đó.
	for (auto item : readDoc.children())
	{
		i++;
		string s = std::to_string(i);
		int id = item.attribute("id").as_int();
		int x = item.attribute("x").as_int();
		int y = item.attribute("y").as_int();
		int width = item.attribute("width").as_int();
		int height = item.attribute("height").as_int();

		xml_node node = writeDoc.append_child("Item");
		node.append_attribute("Id") = 28;
		node.append_attribute("Name") = ("wall_" + std::to_string(i)).c_str();
		node.append_attribute("X") = x + OFFSETX;
		node.append_attribute("Y") = 689 - y + OFFSETY;
		node.append_attribute("Width") = width;
		node.append_attribute("Height") = height;

		xml_node elem = node.append_child("Elem");
		elem.append_attribute("Key") = "physicBodyDirection";
		elem.append_attribute("Value") = 15;

		//xml_node elem1 = node.append_child("Elem");
		//elem1.append_attribute("Key") = "type";
		//elem1.append_attribute("Value") = 4;
		
	}

	bool saveSucceeded = writeDoc.save_file("result.xml", PUGIXML_TEXT("  "));
}

void fixXMLwithRange(const string path)
{
	pugi::xml_document readDoc;
	pugi::xml_document writeDoc;
	vector<xml_node> nodeList;

	// Mở file và đọc
	xml_parse_result result = readDoc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return;
	}

	int i = 0;

	// Lấy id từ file xml. so sánh với eID, tuỳ theo eID nào mà gọi đến đúng hàm load cho riêng object đó.

	for (auto item : readDoc.child("object").children())
	{
		i++;
		string s = std::to_string(i);
		int id = item.attribute("id").as_int();
		int x = item.attribute("x").as_int();
		int y = item.attribute("y").as_int();
		int width = item.attribute("width").as_int();
		int height = item.attribute("height").as_int();

		xml_node node = writeDoc.append_child("Item");
		node.append_attribute("Id") = 8;
		node.append_attribute("Name") = ("nahbi_" + std::to_string(i)).c_str();
		node.append_attribute("X") = x + OFFSETX;
		node.append_attribute("Y") = 689 - y + OFFSETY;
		node.append_attribute("Width") = width;
		node.append_attribute("Height") = height;

	}

	auto rNode = writeDoc.child("Item");
	for (auto item : readDoc.child("objectarea").children())
	{
		int x = item.attribute("x").as_int();
		int y = item.attribute("y").as_int();
		int width = item.attribute("width").as_int();
		int height = item.attribute("height").as_int();

		xml_node node = rNode.append_child("Bound");
		node.append_attribute("Left") = x + OFFSETX;
		node.append_attribute("Bottom") = 689 - y + OFFSETY;
		node.append_attribute("Right") = x + width + OFFSETX;
		node.append_attribute("Top") = 689 - y + height + OFFSETY;
		rNode = rNode.next_sibling();
	}


	bool saveSucceeded = writeDoc.save_file("result.xml", PUGIXML_TEXT("  "));
}

void generaladder(int sx, int sy, int ex, int ey, int numberofstep)
{
	pugi::xml_document writeDoc;

	float width = 1.0f * (ex - sx) / numberofstep;
	float height = 1.0f * (ey - sy) / numberofstep;
	for (int i = 0; i <= numberofstep; i++)
	{
		int x = sx + width * i;
		int y = sy + height * i;

		xml_node node = writeDoc.append_child("Item");
		node.append_attribute("Id") = 1;
		node.append_attribute("Name") = ("ladder_" + std::to_string(i)).c_str();
		node.append_attribute("X") = x;
		node.append_attribute("Y") = y;
		node.append_attribute("Width") = (int)width;
		node.append_attribute("Height") = (int)height;
	}

	bool saveSucceeded = writeDoc.save_file("result.xml", PUGIXML_TEXT("  "));
}
int main()
{
	cout << "Fuck you !";
	loadSpriteInfo("text.txt");
	//fixXML("save.xml");
	//generaladder(1107, 64, 1387, 126, 30);
}