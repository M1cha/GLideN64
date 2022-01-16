#include "PluginAPI.h"
#include "Types.h"
#include "lib/GLideN64_lib.h"
#include "N64.h"

extern "C" {

EXPORT int CALL RomOpen(void)
{
	RDRAMSize = 0;
	return api().RomOpen();
}

EXPORT int CALL PluginStartup(void *Context, PluginCallbacks Callbacks)
{
	return api().PluginStartup(Context, Callbacks);
}

EXPORT void CALL ResizeVideoOutput(int width, int height)
{
	api().ResizeVideoOutput(width, height);
}

} // extern "C"

