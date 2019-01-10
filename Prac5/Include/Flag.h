#pragma once

//Scene Type
enum eSCENE_CREATE
{
	eSC_CURRENT,
	eSC_NEXT
};

//Object Type
enum eOBJ_CREATE
{
	eOBJ_PLAYER,
	eOBJ_DEFAULT,
	eOBJ_MONSTER
};


//Layer Type
enum eLAYER_CREATE
{
	eLAY_DEFAULT = 0,
	eLAY_UI = 1
};


//Monster, Player Direction
enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE = 0,
	MD_FRONT = 1
};
