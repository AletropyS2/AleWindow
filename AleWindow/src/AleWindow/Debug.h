#pragma once
#include <iostream>

#ifdef ALE_DEBUG

#define ALE_LOG(x) std::cout << "[AleWindow | LOG] " << x << std::endl
#define ALE_WARN(x) std::cout << "[AleWindow | WARN] " x << std::endl
#define ALE_ERROR(x) std::cout << "[AleWindow | ERROR] " x << std::endl

#else

#define ALE_LOG(x) 
#define ALE_WARN(x) 
#define ALE_ERROR(x)

#endif