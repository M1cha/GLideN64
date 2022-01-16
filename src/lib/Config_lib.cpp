#include "GLideN64_lib.h"

#include "../Config.h"

Config config;

void Config_LoadConfig()
{
	config.resetToDefaults();
	config.frameBufferEmulation.enable = 0;
}
