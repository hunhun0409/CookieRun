#pragma once

class CookieCharacter;
class Pet;

class StageManager : 
    public PoolingManager, 
    public Singleton<StageManager>
{
private:
    const float CHANGE_TIME = 1.0f;
    const float BLACK_TIME = 0.2f;
private:
    enum TileType
    {
        NONE, GROUND, ITEM, OBSTACLE
    };

    struct Point {
        UINT width = 0;
        UINT height = 0;

        Point() = default;
        Point(int x, int y) : width(x), height(y) {};
    };

    friend class Singleton;

	StageManager();
	~StageManager() = default;

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void Init();

    float GetGroundHeight(Vector2 pos);
    void CollisionItem(GameObject* object, string tag);
    bool CollisionObstacle(GameObject* object);

    void AddMapData(string key, string file);

    void LoadTileData(string key);
    void InitMap(string key);

    void AddBackground(string key, int alpha, ImageRect* bg);


    void SetKey(string key);

    string& OldKey() { return oldKey; }

    void DeactivateMagnet();

    void SetCookie(CookieCharacter* cookie) { this->cookie = cookie; }
    void SetPet(Pet* pet) { this->pet = pet; }

    const string Key() const { return curKey; }

public:
    void ChangeScene(string key);
private:
    void SceneChange();

private:
    void CreateTile(string key);
private:
    
    map<string, Point> mapSizeDatas;
    map<string, Vector2> mapTileSizeDatas;

    typedef vector<vector<TileType>> MapData;
    map<string, vector<MapData>> mapDatas;

    map<string, vector<ImageRect*>> backgroundDatas;

    string curKey = "";

    string oldKey = "";
    string newKey = "";
    Vector2 returnPos = {};


    CookieCharacter* cookie = nullptr;
    Pet* pet = nullptr;

    int alphaValue = 0;
    bool isIncreaseAlpha = true;

    float changeTime;
    ImageRect* changeImage;
    bool isChangeScene = false;

    bool isBlack = false;
    float blackTime = 0;
};
