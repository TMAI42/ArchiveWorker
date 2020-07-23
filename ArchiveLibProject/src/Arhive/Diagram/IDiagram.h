#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <d2d1.h>
#include <atlcomcli.h>
#include <time.h>



class IDiagram {


public:

	IDiagram(HWND hwnd, int width, int height);
	virtual ~IDiagram() = default;

	virtual void SetData(std::vector<std::pair<std::wstring, int>> data);

	virtual void Draw() = 0;

	std::tuple<HWND, int, int> ReleseTarget();

protected:
	int targetWidth, targetHeight;

	HWND target;

	CComPtr<ID2D1HwndRenderTarget> pRT;
	CComPtr<ID2D1Factory> pD2DFactory;
	std::vector<CComPtr<ID2D1SolidColorBrush>> brushes;

	std::vector<std::pair<std::wstring, int>> pairsNameSize;


};