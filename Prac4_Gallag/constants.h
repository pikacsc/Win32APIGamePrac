#pragma once
namespace constants
{
	extern const long ClientRECT_LEFT(0);
	extern const long ClientRECT_TOP(0);
	extern const long ClientRECT_RIGHT(600);
	extern const long ClientRECT_BOTTOM(800);

	extern const float ClientPosX_CENTER((ClientRECT_LEFT + ClientRECT_RIGHT) / 2.f);


	extern const long PlayerStartPoint_LEFT(260);
	extern const long PlayerStartPoint_TOP(600);
	extern const long PlayerStartPoint_RIGHT(310);
	extern const long PlayerStartPoint_BOTTOM(650);

	extern const int iPlayerDefaultSpeed(500);

	extern const float fPlayerBulletDefaultSpeed(500.f);


	extern const float SphereEnemySize_SMALL(20.f);
	extern const float SphereEnemySize_Middle(40.f);
	extern const size_t SphereEnemyRespawnPos_minX(static_cast<size_t>(ClientRECT_LEFT)+20);
	extern const size_t SphereEnemyRespawnPos_maxX(static_cast<size_t>(ClientRECT_RIGHT)-20);
	extern const float SphereEnemyRespawnPos_Y(-50.f);
	extern const float SphereEnemyRespawnMinTime(0.f);
	extern const float SphereEnemyRespawnMaxTime(2.f);

	extern const size_t MAX_ENEMY_COUNT(5);
}

enum MOVE_DIRECTION
{

};