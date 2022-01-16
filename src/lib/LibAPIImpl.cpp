#include "GLideN64_lib.h"
#include "../PluginAPI.h"
#include <DisplayWindow.h>

void *pluginContext;
PluginCallbacks pluginCallbacks;

int PluginAPI::PluginStartup(void *Context, PluginCallbacks Callbacks)
{
	pluginContext = Context;
	pluginCallbacks = Callbacks;

	return 0;
}

void PluginAPI::ResizeVideoOutput(int _Width, int _Height)
{
	dwnd().setWindowSize(_Width, _Height);
}
