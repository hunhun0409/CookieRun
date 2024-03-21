#include "Framework.h"

Inventory::Inventory()
	:Panel(L"Textures/UI/Panel.bmp")
{
	name = "Inventory";

	Observer::Get()->AddParamEvent("InventoryItemSelect", bind(&Panel::SelectItem, this, placeholders::_1));
	Observer::Get()->AddParamEvent("InventoryPurchaseItem", bind(&Inventory::PurchaseItem, this, placeholders::_1));
	Observer::Get()->AddEvent("SellItem", bind(&Inventory::SellItem, this));
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	Panel::Update();
}

void Inventory::Render(HDC hdc)
{
	Panel::Render(hdc);

	string goldStr = "소지금 : " + to_string(gold);
	TextOutA(hdc, pos.x - size.x * 0.4, pos.y - size.y * 0.05, goldStr.c_str(), goldStr.size());
}

void Inventory::PurchaseItem(void* item)
{
	if (item == nullptr)
	{
		MessageBox(hWnd, L"선택된 아이템이 없습니다", L"Error", MB_OK);
		return;
	}

	ItemData data = ((Item*)item)->GetData();

	if (gold < data.price)
	{
		MessageBox(hWnd, L"돈이 부족합니다", L"Not Enough Money", MB_OK);
		return;
	}
	gold -= data.price;

	Item* newItem = new Item(data);
	newItem->size = ((Item*)item)->size;

	int colCount = 15;
	float interval = 6.0f;
	Vector2 startOffset(-274, 20);

	Vector2 coord;
	coord.x = items.size() % colCount;
	coord.y = items.size() / colCount;

	Vector2 localPos;
	localPos.x = startOffset.x + newItem->size.x * coord.x + interval * coord.x;
	localPos.y = startOffset.y + newItem->size.y * coord.y + interval * coord.y;

	newItem->SetLocalPos(localPos);
	newItem->SetLeftEvent(bind(&Item::LeftClickInventoryItem, newItem));
	newItem->SetRightEvent(bind(&Item::RightClickInventoryItem, newItem));

	items.push_back(newItem);
	
}

void Inventory::SellItem()
{
	if (selectItem == nullptr)
	{
		MessageBox(hWnd, L"선택된 아이템이 없습니다", L"Error", MB_OK);
		return;
	}

	gold += selectItem->GetData().price * 0.5f;

	Observer::Get()->ExcuteParamEvents("StorePurchaseItem", selectItem);

	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == selectItem)
		{
			delete items[i];
			items.erase(items.begin() + i);
			selectItem = nullptr;
			thumbnailImage->SetTexture(nullptr);
			descStr = "";
			return;
		}
	}
}
