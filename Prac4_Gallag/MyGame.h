#pragma once
#include <Windows.h>
#include <list>
#include <array>
#include <random>
#include "constants.h"
#include "enemy.h"
namespace Game
{
	using namespace constants;
	using namespace std;

	//Bullets
	typedef struct _tagBullet1
	{
		fSPHERE		tSphere;
		float		fRange;
		float		fLimitRange;
	} SPHEREBULLET, *PSPHEREBULLET;

	typedef struct _tagBullet2
	{
		fRECTANGLE	rc;
		float		fRange;
		float		fLimitRange;
	} RECTBULLET, *PRECTBULLET;

	typedef struct _tagEnemy1
	{
		fSPHERE tSphere;
		float fTime = 0.f;
		float fLimitTime = 1.2f;
	} SPENEMY, *PSPENEMY;


	//window api variables
	HWND			g_hWnd;
	HDC				g_hDC;
	bool			g_bLoop = true;

	//game variables
	RECT				g_ClientRECT; //client Rectangle
	fRECTANGLE			g_tPlayerSquare = {};
	float				g_fPlayerSpeed;
	float				g_fEnemySpeed;
	list<RECTBULLET>	g_PlayerRectBulletList;
	list<SPHEREBULLET>  g_PlayerSphereBulletList;
	list<RECTBULLET>	g_EnemyRectBulletList;
	list<SPHEREBULLET>  g_EnemySphereBulletList;

	SPENEMY				g_spEnemy = {};

	array<SphereEnemy,MAX_ENEMY_COUNT> g_EnemyArray;

	//Delta time
	LARGE_INTEGER	g_tSecond;
	LARGE_INTEGER	g_tTime;
	float			g_fDeltaTime;
	float			g_fTimeScale = 1.f;
	float			g_fEnemyRespawnTime = 0.f;


	inline void DrawingSPHERE(const float& _x, const float& _y, const float& _r) {
		Ellipse(g_hDC,static_cast<int>(_x - _r),static_cast<int>(_y - _r),static_cast<int>(_x + _r),static_cast<int>(_y + _r));
	}
	inline void DrawingSPHERE(fSPHERE _SPHERE){
		Ellipse(g_hDC,
			static_cast<int>(_SPHERE.x - _SPHERE.r),
			static_cast<int>(_SPHERE.y - _SPHERE.r),
			static_cast<int>(_SPHERE.x + _SPHERE.r),
			static_cast<int>(_SPHERE.y + _SPHERE.r));
	}
	inline void DrawingRECT(fRECTANGLE _fRECT) {
		Rectangle(g_hDC,static_cast<int>(_fRECT.left),static_cast<int>(_fRECT.top),static_cast<int>(_fRECT.right),static_cast<int>(_fRECT.bottom));
	}
	inline void DrawingRECT(RECT _RECT) { Rectangle(g_hDC, _RECT.left,_RECT.top,_RECT.right,_RECT.bottom);}
	inline bool LeftInput() {
		GetClientRect(g_hWnd, &g_ClientRECT); //GetClientRect(hWnd, &clientRECT) - current time window left, top, right, bottom
		return (GetAsyncKeyState(VK_LEFT) & 0x8000) && (g_tPlayerSquare.left > g_ClientRECT.left);
	}
	inline bool RightInput() {
		GetClientRect(g_hWnd, &g_ClientRECT);
		return (GetAsyncKeyState(VK_RIGHT) & 0x8000) && (g_tPlayerSquare.right < g_ClientRECT.right);
	}
	inline bool UpInput() {
		GetClientRect(g_hWnd, &g_ClientRECT);
		return (GetAsyncKeyState(VK_UP) & 0x8000) && (g_tPlayerSquare.top > g_ClientRECT.top);
	}
	inline bool DownInput() {
		GetClientRect(g_hWnd, &g_ClientRECT);
		return (GetAsyncKeyState(VK_DOWN) & 0x8000) && (g_tPlayerSquare.bottom < g_ClientRECT.bottom);
	}
	inline void UpdatePlayerSpeed() { g_fPlayerSpeed = (iPlayerDefaultSpeed * g_fDeltaTime) * g_fTimeScale;}
	inline bool IsBulletOutOfRange(const RECTBULLET& rBullet) { return (rBullet.fRange >= rBullet.fLimitRange); }
	inline bool IsBulletOutOfRange(const SPHEREBULLET& sBullet) { return (sBullet.fRange >= sBullet.fLimitRange); }
	inline bool IsBulletOutOfClient(const RECTBULLET& rBullet) { return (rBullet.rc.top <= g_ClientRECT.top); }
	//inline bool IsBulletOutOfClient(const SPHEREBULLET& sBullet) { return (sBullet.r <= g_ClientRECT.top); }

		void			KeyBoardInteract();
		void			InitDeltaTime();
		SPHEREBULLET	InstanciateSphereBullet();
		RECTBULLET		InstanciateRectBullet(const unsigned short& _sLimitDist);
		void			DrawingPlayerRectBullet();
		void			DrawingEnemyRectBullet();
		void			DrawingPlayerSphereBullet();
		void			DrawingEnemySphereBullet();
		void			InstanciateEnemy();
		void			DrawingEnemy();
		size_t			GetRandomNumber(const size_t& a, const size_t& b);

		// Initialize Game variables, Game Objects
		void Init()
		{
			QueryPerformanceFrequency(&g_tSecond);
			QueryPerformanceCounter(&g_tTime);
			// client area --
			g_ClientRECT = { ClientRECT_LEFT, ClientRECT_TOP, ClientRECT_RIGHT, ClientRECT_BOTTOM };
			AdjustWindowRect(&g_ClientRECT, WS_OVERLAPPEDWINDOW, FALSE);
			SetWindowPos(g_hWnd, HWND_TOPMOST, 100, 100,
				g_ClientRECT.right - g_ClientRECT.left,
				g_ClientRECT.bottom - g_ClientRECT.top,
				SWP_NOMOVE | SWP_NOZORDER);
			//-- client area


			//Player start point
			g_tPlayerSquare = { PlayerStartPoint_LEFT, PlayerStartPoint_TOP ,PlayerStartPoint_RIGHT, PlayerStartPoint_BOTTOM };
			/*
			g_spEnemy.tSphere.r = SphereEnemySize_Middle;
			g_spEnemy.tSphere.x = ClientPosX_CENTER;
			g_spEnemy.tSphere.y = -50.f;
			*/	

		}

		void Update()
		{
			InitDeltaTime();
			UpdatePlayerSpeed();

			//Enemy Respawn by 2seconds
			g_fEnemyRespawnTime += g_fDeltaTime * g_fTimeScale;
			if (g_fEnemyRespawnTime >= SphereEnemyRespawnMaxTime)
			{
				InstanciateEnemy();
				g_fEnemyRespawnTime -= SphereEnemyRespawnMaxTime;
			}

			KeyBoardInteract();
		}
	
		void Render()
		{
			//DrawingRECT(g_ClientRECT);
			DrawingRECT(g_tPlayerSquare);
			DrawingPlayerRectBullet();
			DrawingEnemy();
			//DrawingSPHERE(g_spEnemy.tSphere);
		}

		void Release()
		{
			ReleaseDC(g_hWnd, g_hDC);
		}



		void KeyBoardInteract()
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				g_bLoop = false;
			}
			if (LeftInput()) {
				g_tPlayerSquare.left -= g_fPlayerSpeed;
				g_tPlayerSquare.right -= g_fPlayerSpeed;
			}
			if (RightInput()) {
				g_tPlayerSquare.left += g_fPlayerSpeed;
				g_tPlayerSquare.right += g_fPlayerSpeed;
			}
			if (UpInput()) {
				g_tPlayerSquare.top -= g_fPlayerSpeed;
				g_tPlayerSquare.bottom -= g_fPlayerSpeed;
			}
			if (DownInput()) {
				g_tPlayerSquare.top += g_fPlayerSpeed;
				g_tPlayerSquare.bottom += g_fPlayerSpeed;
			}
			if (GetAsyncKeyState(VK_F3) & 0x8000) {
				g_fTimeScale -= g_fDeltaTime;
				if (g_fTimeScale < 0.f)
					g_fTimeScale = 0.f;
			}
			if (GetAsyncKeyState(VK_F4) & 0x8000) {
				g_fTimeScale += g_fDeltaTime;
				if (g_fTimeScale > 1.f)
					g_fTimeScale = 1.f;
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				RECTBULLET rBullet = InstanciateRectBullet(7);
				g_PlayerRectBulletList.push_back(rBullet);
			}

		}

		//Initialize Delta time
		void InitDeltaTime()
		{
			LARGE_INTEGER tTime;
			QueryPerformanceCounter(&tTime);
			g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / static_cast<float>(g_tSecond.QuadPart);
			g_tTime = tTime;
		}

		/*SPHEREBULLET InstanciateSphereBullet()
		{

		}
		*/
		RECTBULLET InstanciateRectBullet(const unsigned short& _sLimitDist)
		{
			RECTBULLET tBullet;
			tBullet.rc.left = (g_tPlayerSquare.left + g_tPlayerSquare.right)/ 2.f - 5.f;
			tBullet.rc.right = g_tPlayerSquare.left + 30.f;
			tBullet.rc.top = g_tPlayerSquare.top + 25.f;
			tBullet.rc.bottom = tBullet.rc.top - 50.f;
			tBullet.fRange = 0.f;
			tBullet.fLimitRange = 100.f * static_cast<float>(_sLimitDist); //fire range
			return tBullet;
		}

		void DrawingPlayerRectBullet()
		{
			list<RECTBULLET>::iterator iter;
			list<RECTBULLET>::iterator iterEnd = g_PlayerRectBulletList.end();
			float fSpeed = fPlayerBulletDefaultSpeed * g_fDeltaTime * g_fTimeScale;

			for (iter = g_PlayerRectBulletList.begin(); iter != iterEnd; ++iter)
			{
				(*iter).rc.top -= fSpeed;
				(*iter).rc.bottom -= fSpeed;
				(*iter).fRange += fSpeed;
				if (IsBulletOutOfRange(*iter))
				{
					iter = g_PlayerRectBulletList.erase(iter);
					iterEnd = g_PlayerRectBulletList.end();
					break;
				}
				else if (IsBulletOutOfClient(*iter))
				{
					iter = g_PlayerRectBulletList.erase(iter);
					iterEnd = g_PlayerRectBulletList.end();
					break;
				}
			}
			for (iter = g_PlayerRectBulletList.begin(); iter != iterEnd; ++iter)
				DrawingRECT((*iter).rc);
		}

		void DrawingPlayerSphereBullet()
		{

		}

		void DrawingEnemyRectBullet()
		{


		}
		void DrawingEnemySphereBullet()
		{
			
		}


		void InstanciateEnemy()
		{
			SphereEnemy sphereEnemy;
			sphereEnemy.SetX(static_cast<float>(GetRandomNumber(SphereEnemyRespawnPos_minX, SphereEnemyRespawnPos_maxX)));
			sphereEnemy.SetY(SphereEnemyRespawnPos_Y);
			sphereEnemy.SetR(SphereEnemySize_Middle);
			sphereEnemy.SetFLimitTime(2.f);
			g_EnemyArray.fill(sphereEnemy);
		}


		void DrawingEnemy()
		{
			array<SphereEnemy, MAX_ENEMY_COUNT>::iterator iter;
			array<SphereEnemy, MAX_ENEMY_COUNT>::iterator iterEnd = g_EnemyArray.end();

			float fSpeed = fPlayerBulletDefaultSpeed * g_fDeltaTime * g_fTimeScale;

			for (iter = g_EnemyArray.begin(); iter != iterEnd; ++iter)
			{
				(*iter).MoveY(50.f, 5.f);
			}
			for (iter = g_EnemyArray.begin(); iter != iterEnd; ++iter)
				DrawingSPHERE((*iter).GetX(), (*iter).GetY(), (*iter).GetR());
		}

		size_t GetRandomNumber(const size_t& a, const size_t& b)
		{
			//<random>, recommended way
			random_device rd;
			mt19937 mersenne(rd()); //mt19937 : 32bit random nubmer
			uniform_int_distribution<> dice(a, b); //equal chance value, random number between 1 and 6 
			return dice(mersenne);
		}

}
