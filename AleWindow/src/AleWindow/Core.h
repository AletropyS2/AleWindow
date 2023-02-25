#pragma once

#if ALE_BUILD_DLL
#define ALE_API __declspec(dllexport)
#else
#define ALE_API
#endif