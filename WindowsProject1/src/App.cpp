#include "App.h"



CApp::CApp() {

	try {

		this->init_native_window_obj();
		this->create_native_controle();

		this->diagram.reset(new DiagramArcSIzeDep(this->m_hDrawArea, 300, 400));

	}
	catch (const std::exception& e) {
		std::string expr_data = e.what();

		MessageBox(nullptr, std::wstring(begin(expr_data), end(expr_data)).c_str(), L"ERROR", MB_ICONERROR | MB_OK);
		ExitProcess(EXIT_FAILURE);
	}
}


int CApp::run() {

	MSG _msg{};

	ShowWindow(this->m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hWnd);

	while (GetMessage(&_msg, nullptr, 0, 0)) {
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return static_cast<int>(_msg.wParam);
}


std::wstring CApp::Browse() {

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);

	std::wstring temp;

	if (SUCCEEDED(hr)){

		CComPtr<IFileOpenDialog> pFileOpen;

		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));


		if (SUCCEEDED(hr)){

			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr)){

				CComPtr<IShellItem> pItem;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr)){
					
					wchar_t* tempPszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &tempPszFilePath);
					std::unique_ptr<wchar_t, std::function<void(void*)>> pszFilePath{ tempPszFilePath, &CoTaskMemFree };
					
					if (SUCCEEDED(hr)){

						temp = std::wstring(pszFilePath.get());
						
					}
				}
			}
		}
		CoUninitialize();
	}
	return temp;
}


void CApp::DisplayDataFormArchive()
{

	SendMessage(this->m_hListDisk, LB_RESETCONTENT, 0, 0);
	SendMessage(this->m_hListArchive, LB_RESETCONTENT, 0, 0);


	auto readData = this->currentArchive->ReadArchive();
	for (const auto& o : readData) {
		SendMessage(this->m_hListArchive,
			LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(o.first.c_str()));
	}

	diagram->SetData(std::move(readData));
	diagram->Draw();

	UpdateWindow(this->m_hWnd);
}


void CApp::init_native_window_obj() {

	using std::_Xruntime_error;
	//using namespace std::string_literals;

	WNDCLASSEX wcex{ sizeof(WNDCLASSEX) };

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.lpfnWndProc = CApp::application_proc;
	wcex.hInstance = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = this->m_szClassName.c_str();
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex)) {
		//throw _Xruntime_error("ERROR, can't register main window class!"s);
	}

	RECT _windoRC{ 0, 0, this->m_nAppWidth, this->m_nAppHeight };
	AdjustWindowRect(&_windoRC, WS_DLGFRAME|WS_SYSMENU| WS_MINIMIZEBOX | WS_MAXIMIZE, false);

	if (this->m_hWnd = CreateWindowEx(
		0,
		this->m_szClassName.c_str(),
		this->m_szAppName.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
		(GetSystemMetrics(SM_CXSCREEN) - _windoRC.right) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _windoRC.bottom) / 2,
		_windoRC.right, _windoRC.bottom, nullptr, nullptr, nullptr, this
	); !this->m_hWnd);
		//throw _Xruntime_error();


}

//TODO: exeptions
void CApp::create_native_controle(){

	if (this->m_hArchiveButton = CreateWindowEx(
		0,
		L"button",
		L"--->>",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		275, 430, 150, 30, 
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::ADD_TO_ARCHIVE),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hListDisk = CreateWindowEx(
		0,
		L"listbox",
		L"ListDisk",
		WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
		40, 40, 300, 400,
		this->m_hWnd, reinterpret_cast<HMENU>(10), 
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hListArchive = CreateWindowEx(
		0,
		L"listbox",
		L"ListArchive",
		WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_WANTKEYBOARDINPUT,
		360, 40, 300, 400,
		this->m_hWnd, reinterpret_cast<HMENU>(10), 
		nullptr, nullptr); !this->m_hWndEdit);

	if(this->m_hPathBoxArchive = CreateWindowEx(
		0,
		L"Edit",
		L"test",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
		360, 20, 250, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(10), 
		nullptr, nullptr); !this->m_hWndEdit);
	
	if(this->m_hOpenArchiveButton = CreateWindowEx(
		0,
		L"button",
		L"Open",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		610, 20, 50, 20, 
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::OPEN_ARCHIVE),
		nullptr, nullptr); !this->m_hWndEdit);
	
	if(this->m_hPathBoxFiles = CreateWindowEx(
		0,
		L"Edit",
		L"test",
		WS_CHILD | WS_VISIBLE |ES_AUTOHSCROLL | WS_BORDER,
		40, 20, 250, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(10), nullptr, nullptr); !this->m_hWndEdit);
	
	if (this->m_hAddToListButton = CreateWindowEx(
		0,
		L"button",
		L"Add",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		290, 20, 50, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::ADD_TO_LIST),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hArchiveNamebox = CreateWindowEx(
		0,
		L"Edit",
		L"test",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER,
		360, 0, 250, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(10),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hExtractButton = CreateWindowEx(
		0,
		L"button",
		L"Extract",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		610, 430, 70, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::TO_EXTRACT),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hWriteNewArchiveButton = CreateWindowEx(
		0,
		L"button",
		L"NEW>>",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		450, 430, 150, 30,
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::TO_ARCHIVE),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hDrawArea = CreateWindowEx(
		0,
		L"edit",
		L"",
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_DISABLED,
		680, 30, 300, 400,
		this->m_hWnd, reinterpret_cast<HMENU>(CTRL_ID::TO_ARCHIVE),
		nullptr, nullptr); !this->m_hWndEdit);

	if (this->m_hFormatBox = CreateWindowEx(
		0,
		L"Combobox",
		L"",
		WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST | WS_VISIBLE,
		610, 0, 50, 20,
		this->m_hWnd, reinterpret_cast<HMENU>(365),
		nullptr, nullptr); !this->m_hWndEdit);

	for(const auto& format:suportedFormats)
		SendMessage(this->m_hFormatBox, CB_ADDSTRING, 1, reinterpret_cast<LPARAM>(format.c_str()));
}


LRESULT CApp::application_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	CApp* pApp;
	if(uMsg==WM_NCCREATE){
		
		pApp = static_cast<CApp*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp))) {
			if (GetLastError() != 0)
				return false;
		}
	}
	else{
		pApp = reinterpret_cast<CApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if(pApp){
		pApp->m_hWnd = hwnd;
		return pApp->window_proc(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd,uMsg,wParam, lParam);
}


LRESULT CApp::window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{

	case WM_PAINT: {
		
		if (currentArchive != nullptr)
			diagram->Draw();
		UpdateWindow(this->m_hWnd);
		break;

	}
				 
	case WM_COMMAND: {

		switch (static_cast<CTRL_ID>(wParam))
		{

		case CTRL_ID::OPEN_ARCHIVE:{

			SendMessage(this->m_hListArchive, LB_RESETCONTENT, 0, 0);
			
			std::wstring text = Browse();
			if (text.empty())
				break;
			std::wstring format = Helpers::GetFormatFromPath(text);

			if (format == L"zip" ||
				format == L"tar" ||
				format == L"rar" ||
				format == L"pax" ||
				format == L"gz"  ||
				format == L"lz"  ||
				format == L"7z") {

				SetWindowText(this->m_hPathBoxArchive, text.c_str());
				currentArchive.reset(new Archive(text));
				
				DisplayDataFormArchive();

			}
			else {
				MessageBox(this->m_hWnd, L"This Format is not supported!", L"Info", MB_ICONINFORMATION | MB_OK);
			}
			break;
		}
		
		case CTRL_ID::ADD_TO_LIST: {

			std::wstring text= Browse();

			if (text.empty())
				break;

			addList.push_back(text);

			SetWindowText(this->m_hPathBoxFiles, L"");

			SendMessage(this->m_hListDisk, 
				LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(Helpers::GetNameFromPath(text).c_str()));

			break;
		}

		case CTRL_ID::TO_ARCHIVE: {
			try {
				std::wstring text{};
				text.resize(260);
				GetWindowText(this->m_hArchiveNamebox, &text[0], 260);
				text.erase(remove(text.begin(), text.end(), 0), text.end());

				if ((addList.size() == 0))
					break;

				if (currentArchive == nullptr) {

					WCHAR pathToExe[500];
					DWORD size = GetModuleFileNameW(NULL, pathToExe, 500);

					currentArchive.reset(new Archive(std::wstring(pathToExe)));
				}

				auto formatNum = SendMessage(this->m_hFormatBox, CB_GETCURSEL, 0, 0L);

				if (formatNum < 0) {
					//MessageBox(this->m_hWnd, L"Choose format!", L"Info", MB_ICONINFORMATION | MB_OK);
					break;
				}

				text += L"." + suportedFormats[formatNum];
				currentArchive->WriteToArchive(addList, text, suportedFormats[formatNum]);

				addList.clear();

				DisplayDataFormArchive();
			}
			catch (...) { }
			break;

		}

		case CTRL_ID::TO_EXTRACT: {

			currentArchive->Extract();
			break;
		}

		case CTRL_ID::ADD_TO_ARCHIVE: {

			std::wstring text{};
			text.resize(260);
			GetWindowText(this->m_hArchiveNamebox, &text[0], 260);

			if ((addList.size() == 0)|| !currentArchive)
				break;

			currentArchive->AddToArchive(addList);
			addList.clear();

			DisplayDataFormArchive();
			break;
		}

		default:
			break;
		}

	}
	return 0;
	case WM_DESTROY: {
		PostQuitMessage(EXIT_SUCCESS);
	}
	return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}



