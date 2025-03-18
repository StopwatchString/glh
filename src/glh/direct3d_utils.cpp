#include "glh/direct3d_utils.h"

#include "cpputils/SharedLibraryLoader.h"

#include "glh/openglapi.h"

#include <vector>

//---------------------------------------------------------
// createDirect3DContext()
//---------------------------------------------------------
Direct3DContext createDirect3DContext()
{
    Direct3DContext context;

    // Load D3D Library
    static cpputils::SharedLibraryLoader d3d11dll{"d3d11.dll"};
    if (!d3d11dll.valid()) {
        std::cerr << "ERROR initDirect3D() Unable to load d3d11.dll" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Get the function pointer for D3D11CreateDevice from the loaded D3D library
    PFN_D3D11_CREATE_DEVICE D3D11CreateDevicePtr
        = (PFN_D3D11_CREATE_DEVICE)d3d11dll.loadFunctionPointer("D3D11CreateDevice");
    if (D3D11CreateDevicePtr == NULL) {
        std::cerr << "ERROR initDirect3D() Could not GetProcAddress of D3D11CreateDevice" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Use D3D11CreateDevice() to make a D3DDevice and D3DDeviceContext
    Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dDeviceContext = nullptr;
    const bool directxDebugFlag = false;
    const UINT deviceFlags = D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
                             | (directxDebugFlag ? D3D11_CREATE_DEVICE_DEBUG : 0) | D3D11_CREATE_DEVICE_SINGLETHREADED;
    const std::vector<D3D_FEATURE_LEVEL> featureLevel = {D3D_FEATURE_LEVEL_11_1};
    HRESULT hr = D3D11CreateDevicePtr(
        NULL,                      // pAdapter
        D3D_DRIVER_TYPE_HARDWARE,  // DriverType
        NULL,                      // Software
        deviceFlags,               // Flags
        featureLevel.data(),       // pFeatureLevels
        (UINT)featureLevel.size(), // FeatureLevels
        D3D11_SDK_VERSION,         // SDK Version
        &d3dDevice,                // ppDevice
        NULL,                      // pFeatureLevel
        &d3dDeviceContext          // ppImmediateContext
    );
    if (hr != S_OK) {
        std::cerr << "ERROR initDirect3D() D3D11CreateDevicePtr failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Cast d3dDevice and d3dDeviceContext into their 11.1 variants
    if (!SUCCEEDED(d3dDevice.As(&context.d3dDevice1))) {
        std::cerr << "ERROR initDirect3D() Could not cast D3D11 device into its D3D11.1 counterpart!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!SUCCEEDED(d3dDeviceContext.As(&context.d3dDeviceContext1))) {
        std::cerr << "ERROR initDirect3D() Could not cast D3D11 device context into its D3D11.1 counterpart!"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    // Check that resource sharing is available
    D3D11_FEATURE_DATA_D3D11_OPTIONS opts;
    context.d3dDevice1->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &opts, sizeof(opts));
    if (opts.ExtendedResourceSharing != 1) {
        std::cout << "ERROR initDirect3D() DirectX Feature ExtendedResourceSharing is not supported." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create WGL interop device
    context.hWglD3DDevice = wglDXOpenDeviceNV(context.d3dDevice1.Get());
    if (context.hWglD3DDevice == NULL) {
        std::cerr << "ERROR initDirect3D() wglDXOpenDeviceNV failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    return context;
}

//---------------------------------------------------------
// destroyDirect3DContext()
//---------------------------------------------------------
void destroyDirect3DContext(Direct3DContext& context)
{
    if (context.hWglD3DDevice != NULL) {
        wglDXCloseDeviceNV(context.hWglD3DDevice);
        context.hWglD3DDevice = NULL;
    }

    if (context.d3dDeviceContext1 != nullptr) {
        context.d3dDeviceContext1->Release();
        context.d3dDeviceContext1 = nullptr;
    }

    if (context.d3dDevice1 != nullptr) {
        context.d3dDevice1->Release();
        context.d3dDevice1 = nullptr;
    }
}
