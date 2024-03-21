#include "Framework.h"
#include "CookieRunScene.h"

CookieRunScene::CookieRunScene()
{
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_0.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_1.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_2.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_8.csv");

    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_3.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_4.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_5.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_6.csv");
    StageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_7.csv");
    //CookieRunStageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_1.csv");
    //CookieRunStageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_2.csv");
    //CookieRunStageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_1.csv");
    //CookieRunStageManager::Get()->AddMapData("Stage1", "TextData/CookieRun/cookieStage1_2.csv");

    Texture* bg1 = Texture::Add(L"Textures/CookieRun/CookieBG.bmp");

    ImageRect* background1 = new ImageRect(bg1);
    StageManager::Get()->AddBackground("Stage1", 0, background1);
    Audio::Get()->Add("HeroBGM", "Sounds/CookieRUn/HeroBGM.wav", true);


    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_0.csv");
    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_1.csv");
    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_1.csv");
    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_1.csv");
    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_1.csv");
    StageManager::Get()->AddMapData("BonusTime", "TextData/CookieRun/bonusTime1_1.csv");

    Texture* bg2 = Texture::Add(L"Textures/CookieRun/BonusTimeBG.bmp");

    ImageRect* background2 = new ImageRect(bg2);
    StageManager::Get()->AddBackground("BonusTime", 0, background2);

    //Observer::Get()->AddParamEvent("SivaDamage", bind(&Siva::Damage, this, placeholders::_1));
    
    Observer::Get()->AddParamEvent("SetCookie", bind(&CookieRunScene::SetCookie, this, placeholders::_1));
}

CookieRunScene::~CookieRunScene()
{
    delete backGround;

    StageManager::Delete();

}

void CookieRunScene::Update()
{
    cookie->Update();
    pet->Update();

    StageManager::Get()->Update();
       
    StageManager::Get()->CollisionItem(cookie, cookie->tag);

    if (!pet->isFollow)
    {
        StageManager::Get()->CollisionItem(pet, pet->tag);
        StageManager::Get()->CollisionItem(pet->GetMagnetRect(), pet->GetMagnetRect()->tag);
    }

    StageManager::Get()->CollisionObstacle(cookie);

    ScoreManager::Get()->Update();
    BonusTimeManager::Get()->Update();
}

void CookieRunScene::Render(HDC hdc)
{
    StageManager::Get()->Render(hdc);
    cookie->Render(hdc);
    pet->CamRender(hdc);

    ScoreManager::Get()->Render(hdc);
    BonusTimeManager::Get()->Render(hdc);
}

void CookieRunScene::Start()
{
    //hero = new HeroCookie();
    cookie->pos = { CENTER_X, CENTER_Y + 100 };


    pet = new Pet(L"Textures/CookieRun/Pets/Jellyco.bmp", 4, 1, MAGENTA,
        L"Textures/CookieRun/Pets/JellycoSkill.bmp", 19, 1, MAGENTA);
    pet->SetOwner(cookie);

    Camera::Get()->SetTarget(cookie);
    Camera::Get()->SetOffset(-350, 0);
    Camera::Get()->SetPos(CENTER_X, CENTER_Y);

    StageManager::Get()->LoadTileData("BonusTime");

    StageManager::Get()->LoadTileData("Stage1");
    StageManager::Get()->SetCookie(cookie);
    StageManager::Get()->SetPet(pet);

    ScoreManager::Get();
    BonusTimeManager::Get();
    //Camera::Get()->SetPos(kumiho->pos);

    Audio::Get()->Play("HeroBGM");

}

void CookieRunScene::End()
{
    StageManager::Get()->SetKey("");
    StageManager::Get()->SetCookie(nullptr);
    StageManager::Get()->SetPet(nullptr);

    ScoreManager::Delete();
    BonusTimeManager::Delete();

    Camera::Get()->SetTarget(nullptr);
    Camera::Get()->SetPos({});
    delete cookie;
    delete pet;

    
}

void CookieRunScene::SetCookie(void* cookie)
{
    CookieCharacter* cookieCharacter = (CookieCharacter*)cookie;

    if(cookieCharacter)
        this->cookie = cookieCharacter;
}
