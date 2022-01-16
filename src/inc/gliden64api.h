#ifndef GLIDEN64_API_H
#define GLIDEN64_API_H

typedef struct {
    unsigned char * HEADER;  /* This is the rom header (first 40h bytes of the rom) */
    unsigned char * RDRAM;
    unsigned char * DMEM;
    unsigned char * IMEM;

    unsigned int * MI_INTR_REG;

    unsigned int * DPC_START_REG;
    unsigned int * DPC_END_REG;
    unsigned int * DPC_CURRENT_REG;
    unsigned int * DPC_STATUS_REG;
    unsigned int * DPC_CLOCK_REG;
    unsigned int * DPC_BUFBUSY_REG;
    unsigned int * DPC_PIPEBUSY_REG;
    unsigned int * DPC_TMEM_REG;

    unsigned int * VI_STATUS_REG;
    unsigned int * VI_ORIGIN_REG;
    unsigned int * VI_WIDTH_REG;
    unsigned int * VI_INTR_REG;
    unsigned int * VI_V_CURRENT_LINE_REG;
    unsigned int * VI_TIMING_REG;
    unsigned int * VI_V_SYNC_REG;
    unsigned int * VI_H_SYNC_REG;
    unsigned int * VI_LEAP_REG;
    unsigned int * VI_H_START_REG;
    unsigned int * VI_V_START_REG;
    unsigned int * VI_V_BURST_REG;
    unsigned int * VI_X_SCALE_REG;
    unsigned int * VI_Y_SCALE_REG;

    void (*CheckInterrupts)(void);
} GFX_INFO;

typedef struct {
    void (*SwapBuffers)(void* userdata);
    void (*ToggleFullScreen)(void* userdata);
    void (*ResizeWindow)(void* userdata, int screenWidth, int screenHeight);
    int (*SetVideoMode)(void* userdata, int screenWidth, int screenHeight, BOOL fullscreen);
} PluginCallbacks;

int PluginStartup(void *Context, PluginCallbacks Callbacks);
BOOL InitiateGFX (GFX_INFO Gfx_Info);
int RomOpen(void);
void ProcessDList(void);
void UpdateScreen(void);
void ResizeVideoOutput(int width, int height);

#endif /* GLIDEN64_API_H */
