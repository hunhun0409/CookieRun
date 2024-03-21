#include "Framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	hFont = CreateFont(20, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"배달의민족 주아");

	store = new Store();
	store->size *= 0.5f;
	store->pos = { CENTER_X, 180 };
	store->SetFont(hFont, 20, MAGENTA);

	inventory = new Inventory();
	inventory->size *= 0.5f;
	inventory->pos = { CENTER_X, 530 };
	inventory->SetFont(hFont, 20, BLACK);

	DataManager::Get();
}

InventoryScene::~InventoryScene()
{
	delete store;
	delete inventory;
}

void InventoryScene::Update()
{
	store->Update();
	inventory->Update();
}

void InventoryScene::Render(HDC hdc)
{
	store->Render(hdc);
	inventory->Render(hdc);
}

void InventoryScene::Start()
{
}

void InventoryScene::End()
{
}
