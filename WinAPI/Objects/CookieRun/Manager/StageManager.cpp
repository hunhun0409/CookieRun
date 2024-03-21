#include "Framework.h"

StageManager::StageManager()
{
    Observer::Get()->AddEvent("DeactivateMagnet", bind(&StageManager::DeactivateMagnet, this));

    changeImage = new ImageRect(L"Textures/CookieRun/black.bmp");
    changeImage->pos = {CENTER_X, CENTER_Y};
}

void StageManager::Update()
{
    //typedef vector<vector<TileType>> MapData;
    //map<string, vector<MapData>> mapDatas;
    if (mapDatas.count(curKey) == 0) return;
    

    //오브젝트 업데이트
    for (pair<string, Objects> objects : totalObjects)
    {
        //현재 map objects들만 update
        string temp = objects.first;
        vector<string> datas = SplitString(temp, "_");
        if (datas[0] != curKey) continue;

        for (GameObject* object : objects.second)
        {
            object->Update();
            if (object->tag.find("Item") != -1)//아이템
            {
                Item* rect = (Item*)object;
                //카메라 오른쪽 밖에 있으면 isActive false
                if (rect->Left() > Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2)
                {
                    rect->isActive = false;
                }
                //카메라 화면 진입 직전에 isActive true
                if (rect->Left() <= Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2
                    && rect->Left() > Camera::Get()->Right())
                {
                    rect->isActive = true;
                }
                //카메라 화면 왼쪽 밖으로 나가면 오른쪽에 위치 계산해서 재배치
                if (rect->Right() <= Camera::Get()->Left())
                {
                    rect->pos.x = rect->changePos.x + mapSizeDatas[curKey].width * mapDatas[curKey].size() * mapTileSizeDatas[curKey].x;
                    rect->pos.y = rect->changePos.y;
                    rect->changePos = rect->pos;
                }
            }
            else if (object->tag.find("Obstacle") != -1)//장애물
            {
                Obstacle* rect = (Obstacle*)object;
                //최적화 부분
                if (object->tag.find("Trophy") != -1)
                {
                    Vector2 pos = object->pos;
                }
                if (rect->Left() > Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2)
                {
                    rect->isActive = false;
                }
                if (rect->Left() <= Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2
                    && rect->Left() > Camera::Get()->Right())
                {
                    rect->isActive = true;
                }

                if (rect->Right() <= Camera::Get()->Left())
                {
                    rect->pos.x = rect->changePos.x + mapSizeDatas[curKey].width * mapDatas[curKey].size() * mapTileSizeDatas[curKey].x;
                    rect->pos.y = rect->changePos.y;
                    rect->changePos = rect->pos;
                    rect->Init();
                }
            }
            else if (object->tag.find("Ground") != -1)//바닥
            {
                Ground* rect = (Ground*)object;
                //최적화 부분
                if (rect->Left() > Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2)
                {
                    rect->isActive = false;
                }
                if (rect->Right() <= Camera::Get()->Right() + mapTileSizeDatas[curKey].x * 2
                    && rect->Left() > Camera::Get()->Right())
                {
                    rect->isActive = true;
                }

                if (rect->Right() <= Camera::Get()->Left())
                {
                    rect->pos.x = rect->changePos.x + mapSizeDatas[curKey].width * mapDatas[curKey].size() * mapTileSizeDatas[curKey].x;
                    rect->pos.y = rect->changePos.y;
                    rect->changePos = rect->pos;
                }
            }
        }
    }

    //배경 업데이트
    for (pair<string, vector<ImageRect*>> backgrounds : backgroundDatas)
    {
        if (backgrounds.first == curKey)
        {
            for (ImageRect* background : backgrounds.second )
            {
                if (background->Right() <= Camera::Get()->Left())
                {
                    background->pos.x += background->size.x * backgrounds.second.size();
                }
            }
        }
    }

    SceneChange();

}

void StageManager::Render(HDC hdc)
{
    if (mapDatas.count(curKey) == 0) return;



    vector<ImageRect*> backgrounds = backgroundDatas[curKey];

    for (ImageRect* background : backgrounds)
    {
        background->CamRender(hdc);
    }

    //changeImage->Render(hdc);


    vector<GameObject*> grounds = totalObjects[curKey + "_Ground"];

    for (GameObject* ground : grounds)
    {
        if (!ground->isActive) continue;
        ImageRect* rect = (ImageRect*)ground;
        rect->CamRender(hdc);
    }

    vector<GameObject*> items = totalObjects[curKey + "_Item"];

    for (GameObject* item : items)
    {
        if (!item->isActive) continue;
        Item* coin = (Item*)item;
        coin->CamRender(hdc);
    }

    vector<GameObject*> objects = totalObjects[curKey + "_Obstacle"];

    for (GameObject* object : objects)
    {
        if (!object->isActive) continue;
        Obstacle* obstacle = (Obstacle*)object;
        obstacle->CamRender(hdc);
    }
    

    if (isChangeScene)
    {
        changeImage->Render(hdc, alphaValue);
    }
}

void StageManager::Init()
{
    
}

float StageManager::GetGroundHeight(Vector2 pos)
{
    vector<GameObject*> grounds = totalObjects[curKey +"_Ground"];

    float minHeight = WIN_HEIGHT + 500;

    for (GameObject* ground : grounds)
    {
        ImageRect* rect = (ImageRect*)ground;

        if (pos.x < rect->Left() || pos.x > rect->Right())
            continue;

        if (pos.y >= rect->Top())
            continue;

        if (rect->Top() < minHeight)
            minHeight = rect->Top();
    }

    return minHeight;
}

void StageManager::CollisionItem(GameObject* object, string tag)
{
    vector<GameObject*> items = totalObjects[curKey + "_Item"];

    for (GameObject* obj : items)
    {
        if (obj->isActive == false) continue;

        if (obj->IsCollision(object))
        {
            if (tag == "magnetRect") // 자석 범위에 들어갔고
            {
                if (obj->tag.find("Jelly") != -1) // 점수 젤리면 빨려가고
                {
                    Item* item = (Item*)obj;
                    item->SetTarget(pet);
                }
            }
            else
            {
                Item* item = (Item*)obj;
                item->ActivateEffect(object);
                return;
            }
        }
    }
}


bool StageManager::CollisionObstacle(GameObject* object)
{
    vector<GameObject*> obstacles = totalObjects[curKey + "_Obstacle"];

    for (GameObject* obj : obstacles)
    {
        if (obj->isActive == false) continue;
        if (obj->IsCollision(object))
        {
            if (object->tag == "Cookie")
            {
                if (((CookieCharacter*)object)->IsInvincible())
                {
                    ((Obstacle*)obj)->Destroy(object);
                }
                else
                {
                    Observer::Get()->ExcuteEvents("CookieCrash");
                }
            }
        }

        Fist* fist = (Fist*)obj;
        Vector2 v = Vector2(fist->pos.x - object->pos.x, 0);
        if (v.Length() < 400)
        {
            fist->Spawn();
        }
        
    }

    return false;
}

void StageManager::AddMapData(string key, string file)
{
    ifstream loadFile(file);

    string temp;
    MapData temp_map;

    UINT width;
    UINT height = 0;

    while (true)
    {
        loadFile >> temp;

        vector<string> datas = SplitString(temp, ",");

        width = datas.size();

        vector<TileType> rowDatas;
        rowDatas.reserve(width);

        for (string data : datas)
        {
            rowDatas.push_back((TileType)stoi(data));
        }

        temp_map.push_back(rowDatas);
        height++;

        if (loadFile.eof())
            break;
    }

    if(mapSizeDatas.count(key) == 0)
        mapSizeDatas[key] = Point(width, height);
    if (mapTileSizeDatas.count(key) == 0)
    {
        Vector2 tileSize = { WIN_WIDTH / (float)width, WIN_HEIGHT / (float)height };
        mapTileSizeDatas[key] = tileSize;
    }
    mapDatas[key].push_back(temp_map);
}



void StageManager::LoadTileData(string key)
{
    if (mapDatas.count(key) > 0)
    {
        curKey = key;
        CreateTile(key);
    }
        
}

void StageManager::InitMap(string key)
{
    vector<MapData> temp = mapDatas[key];
    int mapNum = temp.size();

    UINT width = mapSizeDatas[key].width;
    UINT height = mapSizeDatas[key].height;

    Vector2 tileSize = mapTileSizeDatas[key];
    Vector2 startOffset = tileSize * 0.5f;

    for (pair<string, Objects> objects : totalObjects)
    {
        //현재 map objects들만 update
        string temp = objects.first;
        vector<string> datas = SplitString(temp, "_");
        if (datas[0] != key) continue;

        for (GameObject* object : objects.second)
        {
            if (object->tag.find("Item") != -1)
            {
                Item* item = (Item*)object;
                item->pos = item->initPos;
                item->changePos = item->initPos;
                item->isMove = false;
                item->isActive = true;
            }
            else if (object->tag.find("Obstacle") != -1)
            {
                Obstacle* obstacle = (Obstacle*)object;
                obstacle->pos = obstacle->initPos;
                obstacle->changePos = obstacle->initPos;
                obstacle->isActive = true;
            }
            else if (object->tag.find("Ground") != -1)
            {
                Ground* ground = (Ground*)object;
                ground->pos = ground->initPos;
                ground->changePos = ground->initPos;
                ground->isActive = true;
            }
        }
    }
    for (pair<string, vector<ImageRect*>> backgrounds : backgroundDatas)
    {
        if (backgrounds.first == key)
        {
            for (int i = 0; i < backgrounds.second.size(); i++)
            {
                backgrounds.second[i]->pos = backgrounds.second[i]->size * 0.5f;
                backgrounds.second[i]->pos.x += backgrounds.second[i]->size.x * i;
            }
        }
    }
}

void StageManager::AddBackground(string key, int alpha, ImageRect* bg)
{
    ImageRect* temp1 = new ImageRect(bg->GetTexture());
    temp1->size = temp1->GetTexture()->GetSize();
    temp1->pos = temp1->size * 0.5f;
    temp1->isActive = true;
    ImageRect* temp2 = new ImageRect(bg->GetTexture());
    temp2->size = temp1->size;
    temp2->pos = temp1->pos + Vector2(temp2->size.x, 0);
    temp2->isActive = true;
    ImageRect* temp3 = new ImageRect(bg->GetTexture());
    temp3->size = temp1->size;
    temp3->pos = temp1->pos + Vector2(2*temp3->size.x, 0);
    temp3->isActive = true;
    backgroundDatas[key].push_back(temp1);
    backgroundDatas[key].push_back(temp2);
    backgroundDatas[key].push_back(temp3);
    
}

void StageManager::SetKey(string key)
{
    oldKey = curKey;
    curKey = key;
}

void StageManager::DeactivateMagnet()
{
    vector<GameObject*> items = totalObjects[curKey + "_Item"];

    for (GameObject* obj : items)
    {
        Item* item =  (Item*)obj;
        if (item->isMove)
        {
            item->DeactivateMoveTo();
        }
    }
}

void StageManager::ChangeScene(string key)
{
    if(key == "BonusTime")
        returnPos = cookie->pos;

    newKey = key;
    isChangeScene = true;
}

void StageManager::CreateTile(string key)
{
    //typedef vector<vector<TileType>> MapData;
    //map<string, vector<MapData*>> mapDatas;

    vector<MapData> temp = mapDatas[key];
    int mapNum = temp.size();

    UINT width = mapSizeDatas[key].width;
    UINT height = mapSizeDatas[key].height;

    Vector2 tileSize = mapTileSizeDatas[key];
    Vector2 startOffset = tileSize * 0.5f;

    vector<GameObject*> grounds;
    vector<GameObject*> items;
    vector<GameObject*> obstacles;



    //grounds.reserve(width * mapNum);
    //items.reserve(width * mapNum);
    //obstacles.reserve(width * mapNum);


    for (UINT i = 0; i < mapNum; i++)
    {
        for (UINT y = 0; y < height; y++)
        {
            for (UINT x = 0; x < width; x++)
            {
                //TileType type = temp[i][y][x];
                int data = temp[i][y][x];
                TileType type = (TileType)(data / 100);
                int key = data % 100;


                switch (type)
                {
                case StageManager::GROUND:
                {
                    switch (key)
                    {
                    case 0:
                    {
                        Ground* ground = new Ground(L"Textures/CookieRun/Tiles/CookieGround.bmp");
                        ground->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        ground->initPos = ground->pos;
                        ground->changePos = ground->pos;
                        ground->isActive = true;
                        grounds.push_back(ground);
                        
                    }
                    break;
                    case 1:
                        Ground * ground = new Ground(L"Textures/CookieRun/Tiles/FloatingGround.bmp");
                        ground->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        ground->initPos = ground->pos;
                        ground->changePos = ground->pos;
                        ground->isActive = true;
                        grounds.push_back(ground);
                        
                    }
                    break;
                }
                break;
                    
                case StageManager::ITEM:
                {
                    /*Coin* coin = new Coin();
                    coin->pos = startOffset + tileSize * Vector2(x + width * i, y);
                    coin->isActive = true;
                    items.push_back(coin);
                    break;*/
                    switch (key)
                    {
                    case 0:
                    {
                        JellyBean* jelly = new JellyBean(L"Textures/CookieRun/Items/jellybean.bmp");
                        jelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        jelly->initPos = jelly->pos;
                        jelly->changePos = jelly->pos;
                        jelly->SetValue(50);
                        jelly->isActive = true;
                        items.push_back(jelly);
                        break;
                    }
                    case 1:
                    {
                        JellyBean* jelly = new JellyBean(L"Textures/CookieRun/Items/jelly_bearyellow.bmp");
                        jelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        jelly->initPos = jelly->pos;
                        jelly->changePos = jelly->pos;
                        jelly->SetValue(200);
                        jelly->isActive = true;
                        items.push_back(jelly);
                        break;
                    }
                    case 2:
                    {
                        JellyBean* jelly = new JellyBean(L"Textures/CookieRun/Items/jelly_bearpink.bmp");
                        jelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        jelly->initPos = jelly->pos;
                        jelly->changePos = jelly->pos;
                        jelly->SetValue(250);
                        jelly->isActive = true;
                        items.push_back(jelly);
                        break;
                    }
                    case 3:
                    {
                        JellyBean* jelly = new JellyBean(L"Textures/CookieRun/Items/jelly_bearbig.bmp", 2, 1);
                        jelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        jelly->initPos = jelly->pos;
                        jelly->changePos = jelly->pos;
                        jelly->SetValue(500);
                        jelly->isActive = true;
                        items.push_back(jelly);
                        break;
                    }
                    case 4:
                    {
                        Coin* coin = new Coin(L"Textures/CookieRun/Items/small_coin1.bmp", 4, 1);
                        coin->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        coin->initPos = coin->pos;
                        coin->changePos = coin->pos;
                        coin->SetValue(10);
                        coin->isActive = true;
                        items.push_back(coin);
                        break;
                    }
                    case 5:
                    {
                        Coin* coin = new Coin(L"Textures/CookieRun/Items/coin1.bmp", 6, 1);
                        coin->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        coin->initPos = coin->pos;
                        coin->changePos = coin->pos;
                        coin->SetValue(20);
                        coin->isActive = true;
                        items.push_back(coin);
                        break;
                    }
                    case 6:
                    {
                        Coin* coin = new Coin(L"Textures/CookieRun/Items/big_coin1.bmp", 4, 1);
                        coin->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        coin->initPos = coin->pos;
                        coin->changePos = coin->pos;
                        coin->SetValue(200);
                        coin->isActive = true;
                        items.push_back(coin);
                        break;
                    }
                    case 7:
                    {
                        Energy* energy = new Energy();
                        energy->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        energy->initPos = energy->pos;
                        energy->changePos = energy->pos;
                        energy->isActive = true;
                        items.push_back(energy);
                        break;

                    }
                    case 8:
                    {
                        Magnet* magnet = new Magnet();
                        magnet->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        magnet->initPos = magnet->pos;
                        magnet->changePos = magnet->pos;
                        magnet->isActive = true;
                        items.push_back(magnet);
                        break;

                    }
                    case 9:
                    {
                        Giant* giant = new Giant();
                        giant->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        giant->initPos = giant->pos;
                        giant->changePos = giant->pos;
                        giant->isActive = true;
                        items.push_back(giant);
                        break;
                    }
                        
                    case 10:
                    {
                        Invincible* invincible = new Invincible();
                        invincible->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        invincible->initPos = invincible->pos;
                        invincible->changePos = invincible->pos;
                        invincible->isActive = true;
                        items.push_back(invincible);
                        break;
                    }
                    case 11:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(0);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 12:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(1);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 13:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(2);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 14:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(3);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 15:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(4);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 16:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(5);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 17:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(6);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 18:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(7);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    case 19:
                    {
                        BonusJelly* bonusJelly = new BonusJelly(8);
                        bonusJelly->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        bonusJelly->initPos = bonusJelly->pos;
                        bonusJelly->changePos = bonusJelly->pos;
                        bonusJelly->isActive = true;
                        items.push_back(bonusJelly);
                        break;
                    }
                    }
                }
                break;
                case StageManager::OBSTACLE:
                {
                    switch (key)
                    {
                    case 0:
                    {
                        Fist* fist = new Fist();
                        fist->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        fist->initPos = fist->pos;
                        fist->changePos = fist->pos;
                        obstacles.push_back(fist);
                        break;
                    }
                    case 1:
                    {
                        Obstacle* book = new Obstacle(L"Textures/Cookierun/Obstacles/book1.bmp",1, 1);
                        book->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        book->pos.y += book->Half().y * 0.85f;
                        book->initPos = book->pos;
                        book->changePos = book->pos;
                        book->tag += "Book";
                        obstacles.push_back(book);
                        break;
                    }
                    case 2:
                    {
                        Obstacle* book = new Obstacle(L"Textures/Cookierun/Obstacles/book2.bmp", 1, 1);
                        book->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        book->pos.y += book->Half().y * 0.65f;
                        book->initPos = book->pos;
                        book->changePos = book->pos;
                        book->tag += "Book";
                        obstacles.push_back(book);
                        break;
                    }
                    case 3:
                    {
                        Obstacle* trophy = new Obstacle(L"Textures/Cookierun/Obstacles/trophyA.bmp", 1, 1,true);
                        trophy->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        trophy->initPos = trophy->pos;
                        trophy->changePos = trophy->pos;
                        trophy->tag += "_Trophy";
                        obstacles.push_back(trophy);
                        break;
                    }
                    case 4:
                    {
                        Obstacle* trophy = new Obstacle(L"Textures/Cookierun/Obstacles/trophyB.bmp", 1, 1,true);
                        trophy->pos = startOffset + tileSize * Vector2(x + width * i, y);
                        trophy->initPos = trophy->pos;
                        trophy->changePos = trophy->pos;
                        trophy->tag += "_Trophy";
                        obstacles.push_back(trophy);
                        break;
                    }
                    }
                    break;
                }
                break;
                }
            }
        }
    }

    totalObjects[key + "_Ground"] = grounds;
    totalObjects[key + "_Item"] = items;
    totalObjects[key + "_Obstacle"] = obstacles;
}

void StageManager::SceneChange()
{
    if (isChangeScene)
    {
        changeTime += DELTA;

        //자연스러운 씬 전환을 위해 
        //화면을 점점 어둡게 해준다
        if (isIncreaseAlpha)
        {
            if (isBlack)
            {
                blackTime += DELTA;
            }
            else
            {
                alphaValue += (2 * 255 / CHANGE_TIME) * DELTA;
            }

            if (blackTime > BLACK_TIME)
            {
                isBlack = false;
                blackTime = 0;
                isIncreaseAlpha = false;
            }
            if (alphaValue > 255.0f)
            {
                isBlack = true;
                alphaValue = 255.0f;
                oldKey = curKey;
                curKey = newKey;
                newKey = "";
                
                if (curKey == "BonusTime")
                {
                    cookie->pos.x = CENTER_X-100;
                    Camera::Get()->SetPos(CENTER_X, CENTER_Y);
                }
                if (curKey == "Stage1")
                {
                    cookie->pos = returnPos;
                    cookie->pos.y = -cookie->Half().y;
                    Camera::Get()->SetPos(cookie->pos.x, CENTER_Y);
                    InitMap("BonusTime");

                }
                //cookie->pos = { CENTER_X, CENTER_Y };
                //cookie->isFly = true;
                //Camera::Get()->SetPos(CENTER_X, CENTER_Y);
            }
        }

        //화면이 완전히 어두워지면 Stage를 
        //전환하고 점점 밝아지게 해준다.
        else
        {
            alphaValue -= (2 * 255 / CHANGE_TIME ) * DELTA;
            if (alphaValue < 0.0f)
            {
                isIncreaseAlpha = true;

                isChangeScene = false;
                changeTime = 0.0f;
                alphaValue = 0.0f;
            }
        }
    }
}
