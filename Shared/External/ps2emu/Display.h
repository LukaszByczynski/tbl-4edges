
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
	#include "Win32Display.h"
#elif defined(_X11)
	#include "X11Display.h"
#else
	#error "Unsupported platform"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

