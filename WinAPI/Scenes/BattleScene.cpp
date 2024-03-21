#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
    Audio::Get()->Add("BG", "Sounds/drumloop.wav", true);
    Audio::Get()->Add("Hit", "Sounds/Hit.wav");    

    Texture* texture = Texture::Add(L"Textures/Effect/explosion.bmp", 4, 4);
    EffectManager::Get()->Add("Exp", 30, texture);
    texture = Texture::Add(L"Textures/Effect/explosion2.bmp", 8, 1);
    EffectManager::Get()->Add("Exp2", 30, texture);
}

BattleScene::~BattleScene()
{
    
}

void BattleScene::Update()
{
    if (fighter->GetAttackCollider()->IsRectCollision(monster))
    {
        monster->Damage();
    }

    fighter->Update();
    monster->Update();

    if (KEY_DOWN('1'))
        SceneManager::Get()->ChangeScene("Dig");
}

void BattleScene::Render(HDC hdc)
{
    fighter->Render(hdc);
    monster->Render(hdc);
}

void BattleScene::Start()
{
    fighter = new Fighter();
    fighter->pos = { CENTER_X - 100, CENTER_Y };

    monster = new Monster();
    monster->SetTarget(fighter);

    Audio::Get()->Play("BG", 0.2f);
}

void BattleScene::End()
{
    delete fighter;
    delete monster;

    Audio::Get()->Stop("BG");
}
