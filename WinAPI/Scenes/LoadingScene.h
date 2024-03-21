#pragma once

class LoadingScene : public Scene
{
private:
	const float LOAD_TIME = 2.0f;
public:
	LoadingScene();
	~LoadingScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;
private:
	ImageRect* bg;

	bool isLoad;
	float loadTime;

};
