#include "Framework.h"
#include "ButtonScene.h"

ButtonScene::ButtonScene()
{
    hFont = CreateFont(40, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
        100, 0, 0, 0, L"배달의민족 주아");

    Texture* normal = Texture::Add(L"Textures/UI/BtnNormal.bmp");
    Texture* over = Texture::Add(L"Textures/UI/BtnOver.bmp");
    Texture* down = Texture::Add(L"Textures/UI/BtnDown.bmp");

    battleButton = new Button(normal);
    battleButton->SetOverTexture(over);
    battleButton->SetDownTexture(down);
    battleButton->pos = { CENTER_X, CENTER_Y - 100 };
    battleButton->SetLeftEvent(bind(&ButtonScene::StartBattleScene, this));
    battleButton->SetText("배틀씬");
    battleButton->SetFont(hFont, 40, RED);

    digButton = new Button(normal);
    digButton->SetOverTexture(over);
    digButton->SetDownTexture(down);
    digButton->pos = { CENTER_X, CENTER_Y + 100 };
    digButton->SetLeftEvent(bind(&ButtonScene::StartDigScene, this));
    digButton->SetText("땅파기 게임");
    digButton->SetFont(hFont, 40, BLUE);

    pet = new Pet(L"Texuters/CookieRun/Pets/Jellyco.bmp", 4, 1, MAGENTA, L"Texuters/CookieRun/Items/Coin.bmp", 6, 1, MAGENTA);
    pet->pos = { CENTER_X, CENTER_Y };
    pet->size = { 100, 100 };


    LoadFile();
    LoadFolder();
}

ButtonScene::~ButtonScene()
{
    DeleteObject(hFont);

    delete battleButton;
    delete digButton;

    delete pet;
}

void ButtonScene::Update()
{
    battleButton->Update();
    digButton->Update();

    pet->Update();
}

void ButtonScene::Render(HDC hdc)
{
    HFONT defalutFont = (HFONT)SelectObject(hdc, hFont);

    wstring str = L"StartScene";
    TextOut(hdc, CENTER_X, 0, str.c_str(), str.length());

    SelectObject(hdc, defalutFont);

    battleButton->Render(hdc);
    digButton->Render(hdc);

    pet->Render(hdc);
}

void ButtonScene::StartBattleScene()
{
    SceneManager::Get()->ChangeScene("Battle");
}

void ButtonScene::StartDigScene()
{
    SceneManager::Get()->ChangeScene("Dig");
}

void ButtonScene::LoadFile()
{
    HANDLE handle;

    WIN32_FIND_DATA findData;
    handle = FindFirstFile(L"Textures/UI/Item/*.bmp", &findData);

    bool result = true;
    

    vector<wstring> fileList;

    while (result)
    {
        fileList.push_back(findData.cFileName);

        result = FindNextFile(handle, &findData);
    }
    FindClose(handle);
}

void ButtonScene::LoadFolder()
{
    
    WIN32_FIND_DATA findFileData;
    HANDLE handle = FindFirstFile(L"Textures/\\*", &findFileData);

    bool result = true;

    vector<wstring> folderList;

    while (result)
    {
        //파일 형식이 폴더인지 확인
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            wstring folderName = findFileData.cFileName;
            if (folderName != L"." && folderName != L"..") {
                folderList.push_back(folderName);
            }
        }
        result = FindNextFile(handle, &findFileData);

    }

    FindClose(handle);
}
