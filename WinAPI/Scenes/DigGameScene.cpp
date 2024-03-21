#include "Framework.h"
#include "DigGameScene.h"

DigGameScene::DigGameScene()
{    
    backGround = new ImageRect(L"Textures/Pixel/Sky.bmp");        

    Texture* texture = Texture::Add(L"Textures/Effect/explosion.bmp", 4, 4);
    EffectManager::Get()->Add("Exp", 30, texture);   

    Audio::Get()->Add("Sing", "Sounds/singing.wav", true);
}

DigGameScene::~DigGameScene()
{
    delete backGround;    
}

void DigGameScene::Update()
{
    megaman->Update();
    siva->Update();

    BombManager::Get()->Update();

    if (KEY_DOWN('1'))
        SceneManager::Get()->ChangeScene("Battle");
}

void DigGameScene::Render(HDC hdc)
{
    backGround->CamRender(hdc, { 0, 0 }, false);
    land->CamRender(hdc);

    megaman->Render(hdc);
    siva->Render(hdc);

    BombManager::Get()->Render(hdc);
}

void DigGameScene::Start()
{
    land = new ImageRect(L"Textures/Pixel/Ground.bmp");
    land->pos = land->Half();
    backGround->size = land->size;
    backGround->pos = land->Half();

    megaman = new Megaman();
    megaman->pos = { CENTER_X, 0 };
    megaman->SetLand(land->GetTexture());

    BombManager::Get()->SetLand(land->GetTexture());

    siva = new Siva();
    siva->pos = { CENTER_X + 100, 0 };
    siva->SetLand(land->GetTexture());
           
    Camera::Get()->SetTarget(megaman);
    //Camera::Get()->SetOffset(-300, 200);
    Camera::Get()->SetMapRect(land);
    Camera::Get()->SetPos(megaman->pos);

    Audio::Get()->Play("Sing", 0.1f);
}

void DigGameScene::End()
{
    Camera::Get()->SetTarget(nullptr);
    Camera::Get()->SetMapRect(nullptr);

    delete land;
    delete megaman;
    delete siva;

    BombManager::Get()->Clear();

    Audio::Get()->Stop("Sing");

    Texture::Remove(L"Textures/Pixel/Ground.bmp");
}
