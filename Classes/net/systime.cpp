#include "systime.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#else
pthread_key_t g_systime_key;
pthread_once_t g_systime_key_once = PTHREAD_ONCE_INIT;
#endif
