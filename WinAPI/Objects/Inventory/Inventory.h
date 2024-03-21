#pragma once

class Inventory : public Panel
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render(HDC hdc);

	void PurchaseItem(void* item);
	void SellItem();

private:
	int gold = 1000;
};