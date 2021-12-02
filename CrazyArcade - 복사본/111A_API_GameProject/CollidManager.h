#pragma once

#ifndef __COLLIDMANAGER_H__
#define __COLLIDMANAGER_H__


class CCollidManager
{
public:
	CCollidManager();
	~CCollidManager();

public:
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToBallon(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToSkate(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToPotion(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToMaxPotion(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_BombWaveToBlock(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_BombWaveToMonster(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToBoss(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_PlayerToMonster(list<CObj*>& _Dst, list<CObj*>& _Src);
	static bool isCollision_Rect_BombWaveToBlock(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_BombToBombWave(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_NoPush(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_NoPushBombToPlayer(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Rect_NoPush(list<CObj*>& _Dst, list<CStageMap*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
	static bool Check_Rect(CObj* _Dst, CStageMap* _Src, float* _x, float* _y);
	static bool Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y);
	
	static bool isCollid(list<CObj*>& _Dst, list<CObj*>& _Src);





};


#endif // !__COLLIDMANAGER_H__