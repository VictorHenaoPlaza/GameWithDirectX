#include "Direct3D9.h"

LPDIRECT3D9 d3dInterface;
LPDIRECT3DDEVICE9 device;

void InitializeDirect3D9(HWND windowHandle)
{
    d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS presentParameters;
    ZeroMemory(&presentParameters, sizeof(D3DPRESENT_PARAMETERS));

    presentParameters.Windowed = TRUE;
    presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.hDeviceWindow = windowHandle;

    IDirect3D9_CreateDevice(
        d3dInterface,
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        windowHandle,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &presentParameters,
        &device
    );
}

void RenderDirect3D9()
{
    IDirect3DDevice9_Clear(device, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    IDirect3DDevice9_BeginScene(device);
    IDirect3DDevice9_EndScene(device);
    IDirect3DDevice9_Present(device, NULL, NULL, NULL, NULL);
}

void CleanDirect3D9()
{
    IDirect3D9_Release(d3dInterface);
    IDirect3DDevice9_Release(device);
}
