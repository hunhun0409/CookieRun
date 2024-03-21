#include "Framework.h"
#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
	bg = new ImageRect(L"Textures/Cookierun/lobbyBG.bmp");
	bg->pos = bg->Half();

    hFont = CreateFont(40, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
        100, 0, 0, 0, L"배달의민족 주아");

    Texture* normal = Texture::Add(L"Textures/CookieRun/UI/PlayButton.bmp");

    startButton = new Button(normal);
    startButton->pos = { WIN_WIDTH - 200, WIN_HEIGHT - 100 };
    startButton->SetLeftEvent(bind(&LobbyScene::StartCookieRunScene, this));

    cookieThumbnail = new ImageRect(L"Textures/CookieRun/Cookies/HeroShop.bmp", 2, 1);
    cookieThumbnail->pos = { CENTER_X, CENTER_Y };
    cookie = new HeroCookie();
}

LobbyScene::~LobbyScene()
{
	delete bg;

    delete cookie;

}

void LobbyScene::Update()
{
    CookieAnimation();
    
    cookieThumbnail->Update();

    startButton->Update();
}

void LobbyScene::Render(HDC hdc)
{
	bg->Render(hdc);

    cookieThumbnail->Render(hdc, point);

    startButton->Render(hdc);
}

void LobbyScene::Start()
{
}

void LobbyScene::End()
{
}
void LobbyScene::CookieAnimation()
{
    blinkInterval -= DELTA;
    if (blinkInterval <= 0 && !isBlink)
    {
        point = { 1,0 };
        isBlink = true;
    }
    if (isBlink)
    {
        blinkDuration -= DELTA;
        if (blinkDuration <= 0)
        {
            point = { 0,0 };
            isBlink = false;
            blinkDuration = BLINK_DURATION;
            blinkInterval = BLINK_INTERVAL;
        }
    }
}
void LobbyScene::StartCookieRunScene()
{
    Observer::Get()->ExcuteParamEvents("SetCookie", cookie);
    SceneManager::Get()->ChangeScene("Loading");
}
