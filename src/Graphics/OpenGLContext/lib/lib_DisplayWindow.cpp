#include <stdio.h>
#include <cstdlib>
#include <Graphics/Context.h>
#include <Graphics/OpenGLContext/GLFunctions.h>
#include <Graphics/OpenGLContext/opengl_Utils.h>
#include <Graphics/OpenGLContext/ThreadedOpenGl/opengl_Wrapper.h>
#include <lib/GLideN64_lib.h>
#include <GLideN64.h>
#include <Config.h>
#include <N64.h>
#include <gSP.h>
#include <Log.h>
#include <Revision.h>
#include <FrameBuffer.h>
#include <GLideNUI/GLideNUI.h>
#include <DisplayWindow.h>

using namespace opengl;

class DisplayWindowLib : public DisplayWindow
{
public:
	DisplayWindowLib() {}

private:
	bool _start() override;
	void _stop() override;
	void _restart() override;
	void _swapBuffers() override;
	void _saveScreenshot() override {};
	void _saveBufferContent(graphics::ObjectHandle _fbo, CachedTexture *_pTexture) override {};
	bool _resizeWindow() override;
	void _changeWindow() override;
	void _readScreen(void **_pDest, long *_pWidth, long *_pHeight) override {}
	void _readScreen2(void * _dest, int * _width, int * _height, int _front) override {};
	graphics::ObjectHandle _getDefaultFramebuffer() override;
};

DisplayWindow & DisplayWindow::get()
{
	static DisplayWindowLib video;
	return video;
}

bool DisplayWindowLib::_start()
{
	FunctionWrapper::setThreadedMode(config.video.threadedVideo);

	m_bFullscreen = config.video.fullscreen > 0;
	m_screenWidth = config.video.windowedWidth;
	m_screenHeight = config.video.windowedHeight;
	m_screenRefresh = config.video.fullscreenRefresh;

	_setBufferSize();

	LOG(LOG_VERBOSE, "Setting video mode %dx%d", m_screenWidth, m_screenHeight);
	auto returnValue = FunctionWrapper::LibCallback_SetVideoMode(m_screenWidth, m_screenHeight, m_bFullscreen);
	if (returnValue != 0) {
		LOG(LOG_ERROR, "Error setting videomode %dx%d @ %d. Error code: %d", m_screenWidth, m_screenHeight, m_screenRefresh, returnValue);
		return false;
	}

	return true;
}

void DisplayWindowLib::_stop()
{
}

void DisplayWindowLib::_restart()
{
}

void DisplayWindowLib::_swapBuffers()
{
	//Don't let the command queue grow too big buy waiting on no more swap buffers being queued
	FunctionWrapper::WaitForSwapBuffersQueued();

	FunctionWrapper::LibCallback_GL_SwapBuffers();
}

bool DisplayWindowLib::_resizeWindow()
{
	m_bFullscreen = false;
	m_width = m_screenWidth = m_resizeWidth;
	m_height = m_screenHeight = m_resizeHeight;

	FunctionWrapper::LibCallback_ResizeWindow(m_screenWidth, m_screenHeight);
	_setBufferSize();
	opengl::Utils::isGLError(); // reset GL error.
	return true;
}

void DisplayWindowLib::_changeWindow()
{
	pluginCallbacks.ToggleFullScreen(pluginContext);
}

graphics::ObjectHandle DisplayWindowLib::_getDefaultFramebuffer()
{
	return graphics::ObjectHandle::null;
}

