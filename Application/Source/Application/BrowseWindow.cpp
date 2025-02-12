#include "BrowseWindow.hpp"
#include <shobjidl.h>

std::filesystem::path BrowseWindow::selectFolder()
{
    std::filesystem::path folderPath;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (!SUCCEEDED(hr))
    {
        return folderPath;
    }
    IFileDialog* pFileDialog = nullptr;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileDialog, reinterpret_cast<void**>(&pFileDialog));
    if (!SUCCEEDED(hr))
    {
        return folderPath;
    }
    DWORD options;
    pFileDialog->GetOptions(&options);
    pFileDialog->SetOptions(options | FOS_PICKFOLDERS);

    hr = pFileDialog->Show(NULL);
    if (!SUCCEEDED(hr))
    {
        return folderPath;
    }
    IShellItem* pItem;
    hr = pFileDialog->GetResult(&pItem);
    if (!SUCCEEDED(hr))
    {
        return folderPath;
    }
    PWSTR pszFolderPath;
    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);
    if (!SUCCEEDED(hr))
    {
        return folderPath;
    }
    folderPath = std::filesystem::path(pszFolderPath);
    CoTaskMemFree(pszFolderPath);
    pItem->Release();
    pFileDialog->Release();
    CoUninitialize();
    return folderPath;
}
