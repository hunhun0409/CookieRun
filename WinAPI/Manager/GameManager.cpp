#include "Framework.h"

//#include "Scenes/TutorialScene.h"
//#include "Scenes/SpawnScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/BattleScene.h"
#include "Scenes/PixelCollisionScene.h"
#include "Scenes/DigGameScene.h"
#include "Scenes/ButtonScene.h"
//#include "Scenes/InventoryScene.h"

#include "Scenes/CookieRunScene.h"
#include "Scenes/LobbyScene.h"
#include "Scenes/LoadingScene.h"



GameManager* GameManager::instance = nullptr;

GameManager::GameManager()    
{    
    Init();

    //Timer::Get()->SetLockFPS(1000);
    // 
    //SceneManager::Get()->Add("Battle", new BattleScene());
    //SceneManager::Get()->Add("Dig", new DigGameScene());
    //SceneManager::Get()->Add("Start", new ButtonScene());
    //SceneManager::Get()->Add("Start", new CollisionScene());
    //SceneManager::Get()->Add("Start", new ButtonScene());
    //SceneManager::Get()->Add("Start", new InventoryScene());
    
    SceneManager::Get()->Add("Lobby", new LobbyScene());
    SceneManager::Get()->Add("Loading", new LoadingScene());
    SceneManager::Get()->Add("CookieRun", new CookieRunScene());

    SceneManager::Get()->ChangeScene("Lobby");
}

GameManager::~GameManager()
{
    Timer::Delete();
    Keyboard::Delete();
    Texture::Delete();
    Audio::Delete();
    EffectManager::Delete();
    Camera::Delete();
    Observer::Delete();
    SceneManager::Delete();
}

void GameManager::Init()
{
    hdc = GetDC(hWnd);

    hBackDC = CreateCompatibleDC(hdc);
    hBackBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    SelectObject(hBackDC, hBackBitmap);    

    Timer::Get();
    Keyboard::Get();
    Audio::Get();
    EffectManager::Get();
    Camera::Get();
    Observer::Get();    

    SetBkMode(hBackDC, TRANSPARENT);
}

void GameManager::Update()
{
    if (KEY_DOWN(VK_TAB))
        Texture::SetDebug();

    Timer::Get()->Update();
    Keyboard::Get()->Update();
    Audio::Get()->Update();
    EffectManager::Get()->Update();

    SceneManager::Get()->Update();

    Camera::Get()->Update();
}

void GameManager::Render()
{
    PatBlt(hBackDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

    //InvalidateRect(hWnd, nullptr, false);
    SceneManager::Get()->Render(hBackDC);
    EffectManager::Get()->Render(hBackDC);

    Timer::Get()->Render(hBackDC);

    BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
        hBackDC, 0, 0, SRCCOPY);
}
