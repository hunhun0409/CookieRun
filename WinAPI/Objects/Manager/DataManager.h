#pragma once

struct ItemData {
	int key;
	string name;
	int price;
	wstring file;
};

class DataManager : public Singleton<DataManager>
{
private:
	friend class Singleton;
	DataManager();
	~DataManager();
	
public:
	map<int, ItemData> GetItemDatas() { return itemDatas; }

private:
	void LoadItemTable();
private:
	map<int, ItemData> itemDatas;
};
