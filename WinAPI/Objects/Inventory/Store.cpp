#include "Framework.h"

Store::Store()
	:Panel(L"Textures/UI/Panel.bmp")
{
	name = "Store";

	Observer::Get()->AddParamEvent("StoreItemSelect", bind(&Panel::SelectItem, this, placeholders::_1));
	Observer::Get()->AddParamEvent("StorePurchaseItem", bind(&Store::PurchaseItem, this, placeholders::_1));
	Observer::Get()->AddEvent("StoreClickPurchaseButton", bind(&Store::OnClickPurchaseButton, this));

	CreateButton();
	CreateItem();
}

Store::~Store()
{
	
}

void Store::Update()
{
	Panel::Update();

	purchaseButtonPos = { size.x / 3, -size.y / 3 };
	purchaseButton->pos = pos + purchaseButtonPos;
	purchaseButton->Update();

	sellButtonPos = { size.x / 3, -size.y/6 };
	sellButton->pos = pos + sellButtonPos;
	sellButton->Update();
}

void Store::Render(HDC hdc)
{
	Panel::Render(hdc);
	
	purchaseButton->Render(hdc);
	sellButton->Render(hdc);
}

void Store::CreateButton()
{
	HFONT hFont = CreateFont(18, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"배달의민족 주아");

	Texture* normal = Texture::Add(L"Textures/UI/BtnNormal.bmp");
	Texture* over = Texture::Add(L"Textures/UI/BtnOver.bmp");
	Texture* down = Texture::Add(L"Textures/UI/BtnDown.bmp");

	purchaseButton = new Button(normal);
	purchaseButton->size.x *= 0.5f;
	purchaseButton->size.y *= 0.75f;
	purchaseButton->SetOverTexture(over);
	purchaseButton->SetDownTexture(down);
	purchaseButton->SetLeftEvent(bind(&Store::OnClickPurchaseButton, this));
	purchaseButton->SetText("구매");
	purchaseButton->SetFont(hFont);
	purchaseButton->SetOffset({ 10, 15 });

	sellButton = new Button(normal);
	sellButton->size.x *= 0.5f;
	sellButton->size.y *= 0.75f;
	sellButton->SetOverTexture(over);
	sellButton->SetDownTexture(down);
	sellButton->SetLeftEvent(bind(&Store::OnClickSellButton, this));
	sellButton->SetText("판매");
	sellButton->SetFont(hFont);
	sellButton->SetOffset({ 10, 15 });
}

void Store::CreateItem()
{
	map<int, ItemData> itemDatas = DataManager::Get()->GetItemDatas();

	int colCount = 15;
	float interval = 6.0f;
	Vector2 startOffset(-274, 20);

	for (pair<int, ItemData> itemData : itemDatas)
	{
		for (int i = 0; i < 15; i++)
		{
			Item* item = new Item(itemData.second);
			item->size = { 33, 33 };

			Vector2 coord;
			coord.x = items.size() % colCount;
			coord.y = items.size() / colCount;

			Vector2 localPos;
			localPos.x = startOffset.x + item->size.x * coord.x + interval * coord.x;
			localPos.y = startOffset.y + item->size.y * coord.y + interval * coord.y;

			item->SetLocalPos(localPos);
			item->SetLeftEvent(bind(&Item::LeftClickStoreItem, item));
			item->SetRightEvent(bind(&Item::RightClickStoreItem, item));
			items.push_back(item);
		}
	}
}

void Store::OnClickPurchaseButton()
{
	Observer::Get()->ExcuteParamEvents("InventoryPurchaseItem", selectItem);
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
void Store::OnClickSellButton()
{
	Observer::Get()->ExcuteEvents("SellItem");
}

void Store::PurchaseItem(void* item)
{
	ItemData data = ((Item*)item)->GetData();

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
	newItem->SetLeftEvent(bind(&Item::LeftClickStoreItem, newItem));
	newItem->SetRightEvent(bind(&Item::RightClickStoreItem, newItem));

	items.push_back(newItem);

}