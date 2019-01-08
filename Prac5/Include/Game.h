#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Flag.h"
#include "Types.h"


template <typename T>
void Safe_Delete_VecList(T& p)
{
	T::template iterator iter;
	T::template iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}
	p.clear();
}

template <typename T>
void Safe_Release_VecList(T& p)
{
	T::template iterator iter;
	T::template iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}
	p.clear();
}