#include <dxgi.h>

#include <DirectX12/DirectX12_GraphicsManager.h>

#pragma comment (lib,"d3d12.lib")
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"D3DCompiler.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dxguid.lib")

namespace DirectX12 {

    bool DirectX12_GraphicsMng::Init(HWND _hWnd, Vector2Int _size)
    {
        HRESULT hr = S_OK;
    
#ifdef _DEBUG
        {
            ComPtr<ID3D12Debug> pDebugController;

            // デバッグインターフェイスを取得
            hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController));
    
            if(FAILED(hr))
                return false;
            
            // デバッグレイヤーを有効化
            pDebugController->EnableDebugLayer();
        }
#endif // _DEBUG
    
        /*ComPtr<IDXGIFactory> pFactory;

        hr = CreateDXGIFactory(IID_PPV_ARGS(&pFactory));*/

        // デバイスの作成
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));
    
        // コマンドキューの初期設定
        D3D12_COMMAND_QUEUE_DESC queueDesc;
        ZeroMemory(&queueDesc, sizeof(queueDesc));
    
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    
        // コマンドキューの作成
        hr = m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue));
        
        if(FAILED(hr))
            return false;

        // キューとアロケータのTypeを合わせる
        D3D12_COMMAND_LIST_TYPE type = queueDesc.Type;

        // コマンドアロケータの作成
        hr = m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&m_commandAllocaotr));

        if(FAILED(hr))
            return false;

        hr = m_device->CreateCommandList(0, type, m_commandAllocaotr.Get(), nullptr, IID_PPV_ARGS(&m_commandList));

        if (SUCCEEDED(hr)) 
        {
            // 初期化時には一旦Closeする
            m_commandList->Close();
        }
        else if (FAILED(hr)) 
        {
            return false;
        }

        // ビューポートを作成
        m_viewPort.CreateViewPort(_size, Vector2(0,0));


        return false;
    }

    void DirectX12_GraphicsMng::ResetCommand()
    {
        // コマンドアロケータをリセット
        m_commandAllocaotr->Reset();

        // コマンドリストをリセット
        //m_commandList->Reset(m_commandAllocaotr.Get(), m_pipeLineState.Get());
        m_commandList->Reset(m_commandAllocaotr.Get(), nullptr);

        // ビューポートをセット
        m_viewPort.SetViewPort(m_commandList.Get());
    }

    void BeforRender(float _clearColor[])
    {
        
    }

    void AfterEnder()
    {

    }
}
