#include "Shader.h"
#include "DirectX11Graphics.h"

bool Shader::Init()
{
    ID3D11Device* device = DirectX11::GraphicsMng::GetInstance()->GetDevice();

    D3D11_INPUT_ELEMENT_DESC layout[] = 
    {
        {"POSITION",    0,  DXGI_FORMAT_R32G32B32_FLOAT,    0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA,    0   },
        {"TEXCOORD",    0,  DXGI_FORMAT_R32G32_FLOAT,       0,  D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA,    0   },
    };

    uint32_t numElements = ARRAYSIZE(layout);

    // 頂点シェーダーを作成
    bool sts = CreateVertexShader(
        device,
        "Shader/VertexShader.hlsl",
        "main",
        "vs_5_0",
        layout,
        numElements,
        nullptr,
        &m_vertexShader,
        &m_inputLayout);

    if (!sts) 
        return false;

    // ピクセルシェーダーを作成
    sts = CreatePixelShader(
        device,
        "Shader/PixelShader.hlsl",
        "main",
        "ps_5_0",
        nullptr,
        &m_pixelShader);

    if (!sts)
        return false;

    return true;
}

bool Shader::CreateVertexShader(ID3D11Device* device, 
                                const char* fileName, 
                                LPCSTR entryPoint,
                                LPCSTR shaderModel, 
                                D3D11_INPUT_ELEMENT_DESC* layout,
                                uint32_t numElements, 
                                ID3D11ClassLinkage* pClassLinkage, 
                                ID3D11VertexShader** ppVertexShader, 
                                ID3D11InputLayout** ppInputLayout)
{
    HRESULT hr;

    ID3DBlob* pBlob = nullptr;

    void* ShaderObject;
    size_t	ShaderObjectSize;

    // ファイルの拡張子に合わせてコンパイル
    hr = CompileShader(fileName, entryPoint, shaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
    if (FAILED(hr))
    {
        if (pBlob)pBlob->Release();
        return false;
    }

    // 頂点シェーダーを生成
    hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, pClassLinkage, ppVertexShader);
    if (FAILED(hr))
    {
        if (pBlob)pBlob->Release();
        return false;
    }

    // 頂点データ定義生成
    hr = device->CreateInputLayout(
        layout,
        numElements,
        ShaderObject,
        ShaderObjectSize,
        ppInputLayout);
    if (FAILED(hr)) {
        MessageBox(nullptr, L"CreateInputLayout error", L"error", MB_OK);
        pBlob->Release();
        return false;
    }

    return true;
}

bool Shader::CreatePixelShader(ID3D11Device* device, 
                               const char* fileName, 
                               LPCSTR entryPoint, 
                               LPCSTR shaderModel, 
                               ID3D11ClassLinkage* pClassLinkage, 
                               ID3D11PixelShader** ppPixelShader)
{
    HRESULT hr;

    ID3DBlob* pBlob = nullptr;

    void* ShaderObject;
    size_t	ShaderObjectSize;

    // ファイルの拡張子に合わせてコンパイル
    hr = CompileShader(fileName, entryPoint, shaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
    if (FAILED(hr))
    {
        return false;
    }

    // ピクセルシェーダーを生成
    hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, pClassLinkage, ppPixelShader);
    if (FAILED(hr))
    {
        if (pBlob)pBlob->Release();
        return false;
    }

    return true;
}

HRESULT Shader::CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut)
{
    HRESULT hr;
    static std::vector<unsigned char> byteArray;
    *ppBlobOut = nullptr;

    std::string extname = GetFileExt(szFileName);
    if (extname == "cso") {
        bool sts = readShader(szFileName, byteArray);
        if (!sts) {
            //FILE* fp;
            //fopen_s(&fp, "debug.txt", "a");
            //fprintf(fp, "file open error \n");
            //fclose(fp);
            return E_FAIL;
        }
        *ShaderObject = byteArray.data();
        ShaderObjectSize = byteArray.size();
    }
    else {
        hr = CompileShaderFromFile(szFileName, szEntryPoint, szShaderModel, ppBlobOut);
        if (FAILED(hr)) {
            if (*ppBlobOut)(*ppBlobOut)->Release();
            return E_FAIL;
        }
        *ShaderObject = (*ppBlobOut)->GetBufferPointer();
        ShaderObjectSize = (*ppBlobOut)->GetBufferSize();
    }

    return S_OK;
}


std::string Shader::ExtractFileName(std::string fullpath, char split)
{
    unsigned int path_i = static_cast<unsigned int>(fullpath.find_last_of(split) + 1);	//7
    unsigned int ext_i = static_cast<unsigned int>(fullpath.find_last_of("."));			//10
    std::string pathname = fullpath.substr(0, path_i + 1);								//0文字目から７文字切り出す "C:\\aaa\\"
    std::string extname = fullpath.substr(ext_i, fullpath.size() - ext_i);				// 10文字目から４文字切り出す ".txt"
    std::string filename = fullpath.substr(path_i, ext_i - path_i);//

    return filename + extname;
}

std::string Shader::GetFileExt(const char* filename) 
{
    std::string extname;

    std::string fullpathstr(filename);
    size_t ext_i = fullpathstr.find_last_of(".");
    extname = fullpathstr.substr(ext_i + 1, fullpathstr.size() - ext_i);
    return extname;
}

bool Shader::readShader(const char* csoName, std::vector<unsigned char>& byteArray)
{
    FILE* fp;
    int ret = fopen_s(&fp, csoName, "rb");
    if (ret != 0) {
        return false;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    byteArray.resize(size);
    fseek(fp, 0, SEEK_SET);

    fread(byteArray.data(), byteArray.size(), 1, fp);
    fclose(fp);

    return true;
}

HRESULT Shader::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob * *ppBlobOut)
{
    HRESULT hr = S_OK;

    WCHAR	filename[512];
    size_t 	wLen = 0;
    int err = 0;

    // char -> wcharに変換
    setlocale(LC_ALL, "japanese");
    err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(
        filename,							// filename LPCWST pFileName
        nullptr,							// D3D_SHADER_MACRO *pDefines
        D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ID3DInclude *pInclude
        szEntryPoint,						// LPCSTR pEntrypoint
        szShaderModel,						// LPCSTR pTarget
        dwShaderFlags,						// UINT Flags1
        0,									// UINT Flags2
        ppBlobOut,							// ID3DBlob** ppCode
        &pErrorBlob);						// ID3DBlob** ppErrorMsg 
    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr) {
            MessageBox(NULL,
                (wchar_t*)pErrorBlob->GetBufferPointer(), L"Error", MB_OK);
        }
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}
