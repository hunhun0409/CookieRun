#pragma once

class Store : public Panel
{
public:
	Store();
	~Store();

	void Update();
	void Render(HDC hdc);

	void PurchaseItem(void* item);
private:
	void CreateButton();
	void CreateItem();

	void OnClickPurchaseButton();
	void OnClickSellButton();



private:
	Button* purchaseButton;
	Vector2 purchaseButtonPos;

	Button* sellButton;
	Vector2 sellButtonPos;
};