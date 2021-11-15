#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__

namespace OBJID
{
	enum ID { PLAYER, BOMB, BOSSBOMB, BOMBWAVE, TILE, BLOCK, MONSTER, BOSS, END };
}

namespace OBJDIR
{
	enum DIR { IDLE, TOP, BOTTOM, LEFT, RIGHT, TOPEND, BOTTOMEND, LEFTEND, RIGHTEND, END };
}

namespace CHARNAME
{
	enum NAME { BAZZI, DAO, DIGENIE, UNI, END };
}

namespace MONSTERNAME
{
	enum NAME { MESSI, MBAPE, HMSON };
}

namespace GAMEITEM
{
	enum ITEM { BALLON, POTION, MAXPOTION, SKATE, END };
}

#endif // !__ENUM_H__
