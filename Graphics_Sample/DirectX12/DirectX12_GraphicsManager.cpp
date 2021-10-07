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

            // �f�o�b�O�C���^�[�t�F�C�X���擾
            hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugController));
    
            if(FAILED(hr))
                return false;
            
            // �f�o�b�O���C���[��L����
            pDebugController->EnableDebugLayer();
        }
#endif // _DEBUG
    
        /*ComPtr<IDXGIFactory> pFactory;

        hr = CreateDXGIFactory(IID_PPV_ARGS(&pFactory));*/

        // �f�o�C�X�̍쐬
        hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));
    
        // �R�}���h�L���[�̏����ݒ�
        D3D12_COMMAND_QUEUE_DESC queueDesc;
        ZeroMemory(&queueDesc, sizeof(queueDesc));
    
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    
        // �R�}���h�L���[�̍쐬
        hr = m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue));
        
        if(FAILED(hr))
            return false;

        // �L���[�ƃA���P�[�^��Type�����킹��
        D3D12_COMMAND_LIST_TYPE type = queueDesc.Type;

        // �R�}���h�A���P�[�^�̍쐬
        hr = m_device->CreateCommandAllocator(type, IID_PPV_ARGS(&m_commandAllocaotr));

        if(FAILED(hr))
            return false;

        hr = m_device->CreateCommandList(0, type, m_commandAllocaotr.Get(), nullptr, IID_PPV_ARGS(&m_commandList));

        if (SUCCEEDED(hr)) 
        {
            // ���������ɂ͈�UClose����
            m_commandList->Close();
        }
        else if (FAILED(hr)) 
        {
            return false;
        }

        // �r���[�|�[�g���쐬
        m_viewPort.CreateViewPort(_size, Vector2(0,0));


        return false;
    }

    void DirectX12_GraphicsMng::ResetCommand()
    {
        // �R�}���h�A���P�[�^�����Z�b�g
        m_commandAllocaotr->Reset();

        // �R�}���h���X�g�����Z�b�g
        //m_commandList->Reset(m_commandAllocaotr.Get(), m_pipeLineState.Get());
        m_commandList->Reset(m_commandAllocaotr.Get(), nullptr);

        // �r���[�|�[�g���Z�b�g
        m_viewPort.SetViewPort(m_commandList.Get());
    }

    void BeforRender(float _clearColor[])
    {
        
    }

    void AfterEnder()
    {

    }
}