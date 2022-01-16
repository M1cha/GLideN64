#include "../PluginAPI.h"
#include "../Types.h"

int PluginAPI::InitiateGFX(const GFX_INFO & _gfxInfo)
{
	_initiateGFX(_gfxInfo);
	return TRUE;
}

void PluginAPI::GetUserDataPath(wchar_t * _strPath)
{
	_strPath[0] = 0;
}

void PluginAPI::GetUserCachePath(wchar_t * _strPath)
{
	_strPath[0] = 0;
}

void PluginAPI::FindPluginPath(wchar_t * _strPath)
{
	if (_strPath == nullptr)
		return;

	_strPath[0] = 0;
}
