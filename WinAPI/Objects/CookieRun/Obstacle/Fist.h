#pragma once

class Fist : public Obstacle
{
private:
	enum State 
	{
		NOTICE, UPING, UPEND
	};
public:
	Fist();
	~Fist();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void CamRender(HDC hdc) override;


	void Spawn();

	void Uping();
	void UpEnd();

	virtual void Destroy(void* obj) override;
	
	virtual void Init() override;
	


	virtual void CreateAnimation() override;


private:
	bool isSpawn = false;

};

