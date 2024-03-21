#include "Framework.h"

DataManager::DataManager()
{
	LoadItemTable();
}

DataManager::~DataManager()
{
}

void DataManager::LoadItemTable()
{
	ifstream loadFile("TextData/Inventory/ItemTable.csv");
	string temp;

	bool isFirstLine = true;
	
	while (true)
	{
		loadFile >> temp;

		if (isFirstLine) {
			isFirstLine = false;
			continue;
		}

		vector<string> datas = SplitString(temp, ",");
		ItemData data;
		data.key = stoi(datas[0]);
		data.name = datas[1];
		data.price = stoi(datas[2]);
		data.file = To_WString("Textures/UI/Item/" + datas[3]);

		itemDatas[data.key] = data;

		if (loadFile.eof())
			break;
	}

}
