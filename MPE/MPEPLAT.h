#ifdef MPE_PLATFORM_WINDOWS
#    include <Windows.h>
#endif

#ifdef MPE_PLATFORM_LINUX
#    include <unistd.h>
#endif

#ifdef MPE_PLATFORM_OSX
#    include <Cocoa/Cocoa.h>
#    include <unistd.h>
#endif