//-------------------------------------------------------------------------------------------------
// Copyright (c) 2025 Mason Speck
// Licensed under the MIT License.
//
// Project: GLH
// Author: Mason Speck https://github.com/StopwatchString
// File: direct3d_utils.h
// Description:
//    Collection of utility functions related to working with DirectX statically. Located in
//    GLH for the purpose of creating interoperability tools between OpenGL and DirectX.
//-------------------------------------------------------------------------------------------------

#ifndef GLH_D3D_INTEROP_UTILS_H
#define GLH_D3D_INTEROP_UTILS_H

#include <D3D11_1.h>
#include <wrl/client.h> // for Microsoft::WRL::ComPtr template

struct Direct3DContext
{
    Microsoft::WRL::ComPtr<ID3D11Device1> d3dDevice1{nullptr};
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3dDeviceContext1{nullptr};
    HANDLE hWglD3DDevice{nullptr};

    bool valid() const { return d3dDevice1 != NULL && d3dDeviceContext1 != NULL && hWglD3DDevice != NULL; }
};

Direct3DContext createDirect3DContext();
void destroyDirect3DContext(Direct3DContext& context);

#endif