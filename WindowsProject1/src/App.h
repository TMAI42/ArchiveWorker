#pragma once

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <shobjidl.h> 
#include <string>
#include <algorithm>
#include <exception>
#include <bitset>
#include <vector>
#include <memory>
#include "../../Helpers/src/Helpers.h"
#include "../../ArchiveLibProject/src/ArchiveFactory.h"

class CApp {
	enum class CTRL_ID{
		ADD_TO_LIST,
		OPEN_ARCHIVE,
		TO_ARCHIVE,
		TO_EXTRACT, 
		ADD_TO_ARCHIVE
	};

public:
	explicit CApp();
	~CApp() = default;

	int run();

private:
	void init_native_window_obj();

	static LRESULT CALLBACK application_proc(HWND hWnd, UINT nMng, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK window_proc(HWND hWnd, UINT nMng, WPARAM wParam, LPARAM lParam);

	void create_native_controle();

	std::wstring Browse();
	void DisplayDataFormArchive();

private:

	std::vector<std::wstring> suportedFormats = {
		L"zip",
		L"tar",
		L"pax",
		L"7zip"
	};

	const std::wstring m_szAppName{ L"App Name" };
	const std::wstring m_szClassName{ L"App Name" };

	HWND m_hWnd;
	HWND m_hWndEdit;
	//Listboxes
	HWND m_hListArchive;
	HWND m_hListDisk;
	//textbox for pathes
	HWND m_hPathBoxArchive;
	HWND m_hPathBoxFiles;
	HWND m_hArchiveNamebox;
	//buttons
	HWND m_hArchiveButton;
	HWND m_hOpenArchiveButton;
	HWND m_hAddToListButton;
	HWND m_hExtractButton;
	HWND m_hWriteNewArchiveButton;
	//draw area
	HWND m_hDrawArea;
	//combobox
	HWND m_hFormatBox;

	const int m_nAppWidth = 1000;
	const int m_nAppHeight = 500;

	//Archive stuff
	std::unique_ptr<IArchive> currentArchive;
	std::vector<std::wstring> addList;

	//Diagram stuff

};
