#include "Framework.h"
#include "PixelCollisionScene.h"

PixelCollisionScene::PixelCollisionScene()
{
    land = new ImageRect(L"Textures/Pixel/land.bmp", 1, 1, RGB(0, 178, 255));
    land->pos = land->Half();
    backGround = new ImageRect(L"Textures/Pixel/background.bmp");
    backGround->size = land->size;
    backGround->pos = land->Half();

    megaman = new Megaman();
    megaman->pos = { CENTER_X, 0 };
    megaman->SetLand(land->GetTexture());

    Camera::Get()->SetTarget(megaman);
    //Camera::Get()->SetOffset(-300, 200);
    Camera::Get()->SetMapRect(land);

    Texture* texture = Texture::Add(L"Textures/Effect/explosion.bmp", 4, 4);
    EffectManager::Get()->Add("Exp", 30, texture);
}

PixelCollisionScene::~PixelCollisionScene()
{
    delete land;
    delete backGround;
    delete megaman;
}

void PixelCollisionScene::Update()
{   
    megaman->Update();
}

void PixelCollisionScene::Render(HDC hdc)
{
    backGround->CamRender(hdc, {0, 0}, false);
    land->CamRender(hdc);
    megaman->Render(hdc);
}
