#pragma once

class Panel : public Button
{
public:
	Panel(wstring file);
	~Panel();

	void Update();
	void Render(HDC hdc);

	void SelectItem(void* item);

	void PurchaseItem(void* item);

private:
	void Drag();

	void SetItemPos();

private:
	Rect* dragRect = nullptr;
	bool isDrag = false;

protected:
	string name;

	Vector2 offset = {};
	vector<Item*> items;

	ImageRect* thumbnailImage;
	Vector2 thumbnailOffset = {};

	Item* selectItem;

	string descStr;

	
};