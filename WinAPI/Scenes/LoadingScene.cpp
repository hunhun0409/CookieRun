#include "Framework.h"
#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
	bg = new ImageRect(L"Textures/CookieRun/LoadingBG.bmp");
	bg->pos = bg->Half();
}

LoadingScene::~LoadingScene()
{
	delete bg;
}

void LoadingScene::Update()
{
	if(isLoad)
		loadTime -= DELTA;
	if (loadTime <= 0)
		SceneManager::Get()->ChangeScene("CookieRun");
}

void LoadingScene::Render(HDC hdc)
{
	bg->Render(hdc);
}

void LoadingScene::Start()
{	
	isLoad = true;
	loadTime = LOAD_TIME;
}

void LoadingScene::End()
{
	isLoad = false;
}
