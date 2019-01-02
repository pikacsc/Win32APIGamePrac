#pragma once
#include <list>
namespace Game 
{
	using namespace std;
	class SphereEnemy
	{

	public:
		SphereEnemy()
			: x(0), y(0), r(0), fTime(0), fLimitTime(0)
		{}

		SphereEnemy(const float& _x, const float& _y, const float& _r, const float& _fTime, const float& _fLimitTime)
			: x(_x), y(_y), r(_r), fTime(_fTime), fLimitTime(_fLimitTime)
		{}


		float GetX() {
			return x;
		}

		float GetY() {
			return y;
		}

		float GetR() {
			return r;
		}

		void SetX(const float& _x) {
			x = _x;
		}

		void SetY(const float& _y) {
			y = _y;
		}

		void SetR(const float& _r) {
			r = _r;
		}



		float GetFTime() {
			return fTime;
		}

		void SetFTime(const float& _fTime) {
			fTime = _fTime;
		}

		float GetFLimitTime() {
			return fLimitTime;
		}

		void SetFLimitTime(const float& _fLimitTime) {
			fLimitTime = _fLimitTime;
		}


		void MoveX(const float& _fDirection, const float& _fSpeed) {
			while (x != _fDirection)
			{
				if (x > _fDirection || x == _fDirection)
				{
					x = _fDirection;
					break;
				}
				x += _fSpeed;
			}
		}

		void MoveY(const float& _fDirection, const float& _fSpeed) {
			while (y != _fDirection)
			{
				//Issue : Enemy can't moving smoothly
				/*if (y > _fDirection || x == _fDirection)
				{
					y = _fDirection;
					break;
				}*/
				y += _fSpeed;
			}
		}

	private:
		float x, y;
		float r;
		float fTime = 0.f;
		float fLimitTime = 1.2f;
	};
}
