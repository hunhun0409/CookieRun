#include "Framework.h"

Ground::Ground(wstring file, UINT frameX, UINT frameY, COLORREF transColor)
	:ImageRect(file, frameX, frameY, transColor)
{
	tag = "Ground";
}

Ground::Ground(Texture* texture)
	:ImageRect(texture)
{
}
