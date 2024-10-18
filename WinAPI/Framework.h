#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 100
#define WIN_START_Y 100

#define WIN_WIDTH 1360
#define WIN_HEIGHT 640

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define PI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;

//FMOD Library
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/fmod_vc.lib")

//Framework Header
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Audio.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Animation.h"
#include "Framework/Render/Camera.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"
#include "Objects/Basic/Effect.h"

#include "Objects/UI/ProgressBar.h"
#include "Objects/UI/Button.h"

#include "Objects/Manager/PoolingManager.h"
#include "Objects/Manager/EffectManager.h"
#include "Objects/Manager/Observer.h"
#include "Objects/Manager/DataManager.h"

//#include "Objects/Inventory/Item.h"
//#include "Objects/Inventory/Panel.h"
//#include "Objects/Inventory/Inventory.h"
//#include "Objects/Inventory/Store.h"


#include "Objects/CookieRun/Ground.h"

#include "Objects/CookieRun/Item/Item.h"
#include "Objects/CookieRun/Item/JellyBean.h"
#include "Objects/CookieRun/Item/Coin.h"
#include "Objects/CookieRun/Item/Energy.h"
#include "Objects/CookieRun/Item/Magnet.h"
#include "Objects/CookieRun/Item/Giant.h"
#include "Objects/CookieRun/Item/Invincible.h"

#include "Objects/CookieRun/Item/BonusJelly.h"


#include "Objects/CookieRun/Obstacle/Obstacle.h"
#include "Objects/CookieRun/Obstacle/Fist.h"

#include "Objects/CookieRun/Character/CookieCharacter.h"
#include "Objects/CookieRun/Character/KumihoCookie.h"
#include "Objects/CookieRun/Character/HeroCookie.h"

#include "Objects/CookieRun/Pet/Pet.h"
#include "Objects/CookieRun/Pet/Missile.h"

#include "Objects/CookieRun/HUD/Digit.h"

#include "Objects/CookieRun/Manager/MissileManager.h"
#include "Objects/CookieRun/Manager/StageManager.h"
#include "Objects/CookieRun/Manager/ScoreManager.h"
#include "Objects/CookieRun/Manager/BonusTimeManager.h"

//Scene Header
#include "Scenes/Scene.h"

//Manager Header
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;