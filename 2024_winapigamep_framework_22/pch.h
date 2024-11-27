#pragma once

// ���� include
#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<ctime>
#include<format>
#define _USE_MATH_DEFINES
#include<math.h>

// My Header
#include "Define.h"
#include "Enums.h"
#include "Vector2.h"

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")

// ���� using
using std::vector;
using std::map;
using std::wstring;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
#include "Utils.h"

// ���� define
#define PI 3.14159265f
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

#define DELTATIME GET_SINGLETON(TimeManager)->getDeltaTime()

#define SAFE_DELETE(ptr)        \
    if (ptr)                    \
    {                            \
        delete ptr;                \
        ptr = nullptr;            \
    }

// ������ �ܼ�â
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>
using std::cout;
using std::endl;