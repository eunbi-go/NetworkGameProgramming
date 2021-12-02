#include "stdafx.h"
#include "MyEdit.h"
#include "KeyManager.h"
#include "BmpManager.h"
#include "TileManager.h"
#include "ObjManager.h"
#include "Basket.h"
#include "Leaf1.h"
#include "Leaf2.h"
#include "Flower.h"
#include "Grass.h"
#include "Rock1.h"
#include "Rock2.h"
#include "Rock3.h"
#include "SceneManager.h"

CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage.bmp", L"Stage");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile1.bmp", L"Tile1");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile2.bmp", L"Tile2");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile3.bmp", L"Tile3");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile4.bmp", L"Tile4");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile5.bmp", L"Tile5");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile6.bmp", L"Tile6");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile7.bmp", L"Tile7");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile8.bmp", L"Tile8");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile9.bmp", L"Tile9");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/tile/tile10.bmp", L"Tile10");

	//블록
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Basket.bmp", L"Basket");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Basket_pop.bmp", L"BasketPop");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Leaf1.bmp", L"Leaf1");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Leaf2.bmp", L"Leaf2");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Flower.bmp", L"Flower");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/block/Grass.bmp", L"Grass");

	//오브젝트 블록
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/object/Rock1.bmp", L"Rock1");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/object/Rock2.bmp", L"Rock2");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Map/forest/object/Rock3.bmp", L"Rock3");

	//CTileManager::Get_Instance()->Initialize();
}

void CMyEdit::Update()
{
	Key_Check();
	CTileManager::Get_Instance()->Update();
	CObjManager::Get_Instance()->Update();

	if (CKeyManager::Get_Instance()->Key_Down(VK_SPACE))
		CSceneManager::Get_Instance()->Scene_Change(CSceneManager::SCENE_MENU);
}

void CMyEdit::Late_update()
{
	CTileManager::Get_Instance()->Late_Update();
	CObjManager::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC _DC)
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Stage");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CTileManager::Get_Instance()->Render(_DC);
	CObjManager::Get_Instance()->Render(_DC);
}

void CMyEdit::Release()
{
}

void CMyEdit::Key_Check()
{
	CObj* pObj = nullptr;

	// 순서대로 1 2 3 4 5 6 7 8 9 10번타일임
	// Q W E R T Y U I O P
	if (CKeyManager::Get_Instance()->Key_Down('Q'))
		CTileManager::Get_Instance()->Picking_Tile(1);
	if (CKeyManager::Get_Instance()->Key_Down('W'))
		CTileManager::Get_Instance()->Picking_Tile(2);
	if (CKeyManager::Get_Instance()->Key_Down('E'))
		CTileManager::Get_Instance()->Picking_Tile(3);
	if (CKeyManager::Get_Instance()->Key_Down('R'))
		CTileManager::Get_Instance()->Picking_Tile(4);
	if (CKeyManager::Get_Instance()->Key_Down('T'))
		CTileManager::Get_Instance()->Picking_Tile(5);
	if (CKeyManager::Get_Instance()->Key_Down('Y'))
		CTileManager::Get_Instance()->Picking_Tile(6);
	if (CKeyManager::Get_Instance()->Key_Down('U'))
		CTileManager::Get_Instance()->Picking_Tile(7);
	if (CKeyManager::Get_Instance()->Key_Down('I'))
		CTileManager::Get_Instance()->Picking_Tile(8);
	if (CKeyManager::Get_Instance()->Key_Down('O'))
		CTileManager::Get_Instance()->Picking_Tile(9);
	if (CKeyManager::Get_Instance()->Key_Down('P'))
		CTileManager::Get_Instance()->Picking_Tile(10);

	if (CKeyManager::Get_Instance()->Key_Down('S'))
	{
		CTileManager::Get_Instance()->Save_Tile();
		CObjManager::Get_Instance()->Save_Object();
	}
	if (CKeyManager::Get_Instance()->Key_Down('L'))
	{
		CTileManager::Get_Instance()->Load_Tile();
		CObjManager::Get_Instance()->Load_Object();
	}
	if (CKeyManager::Get_Instance()->Key_Down('J'))
	{
		CTileManager::Get_Instance()->Save_Tile();
		CObjManager::Get_Instance()->Save_Object_Stage2();
	}
	if (CKeyManager::Get_Instance()->Key_Down('H'))
	{
		CTileManager::Get_Instance()->Load_Tile();
		CObjManager::Get_Instance()->Load_Object_Stage2();
	}
	if (CKeyManager::Get_Instance()->Key_Down('G'))
	{
		CTileManager::Get_Instance()->Save_Tile();
		CObjManager::Get_Instance()->Save_Object_Boss();
	}
	if (CKeyManager::Get_Instance()->Key_Down('F'))
	{
		CTileManager::Get_Instance()->Load_Tile();
		CObjManager::Get_Instance()->Load_Object_Boss();
	}

	if (CKeyManager::Get_Instance()->Key_Down('Z'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::BASKET);
	if (CKeyManager::Get_Instance()->Key_Down('X'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::LEAF1);
	if (CKeyManager::Get_Instance()->Key_Down('C'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::LEAF2);
	if (CKeyManager::Get_Instance()->Key_Down('V'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::FLOWER);
	if (CKeyManager::Get_Instance()->Key_Down('B'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::GRASS);

	if (CKeyManager::Get_Instance()->Key_Down('N'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::ROCK1);
	if (CKeyManager::Get_Instance()->Key_Down('M'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::ROCK2);
	if (CKeyManager::Get_Instance()->Key_Down('K'))
		CObjManager::Get_Instance()->Picking_Object(pObj, MAPBLOCK::ROCK3);


		
}
