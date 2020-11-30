#pragma once

#include <d3d9.h>

/// <summary>
/// Intializes the Direct3D 9 interface from a window handle.
/// </summary>
/// <param name="windowHandle">The window handle.</param>
void InitializeDirect3D9(HWND windowHandle);

/// <summary>
/// Clears the current window.
/// </summary>
void RenderDirect3D9();

/// <summary>
/// Closes Direct3D 9 and releases memory.
/// </summary>
void CleanDirect3D9();
