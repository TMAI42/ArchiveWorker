#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include "../DiagramTypes.h"

class IArchive {

public:

	virtual ~IArchive() = default;

	virtual std::vector<std::pair<std::wstring, int>> ReadArchive() = 0;
	virtual void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format, std::wstring extPath, int cLvl) = 0;
	virtual void Extract(std::wstring extPath) = 0;
	virtual void AddToArchive(std::vector<std::wstring> filenames) = 0;
	virtual void ConvertTo(std::wstring extPath, std::wstring newFormat) = 0;

	virtual void SetDrawingObject(HWND target, int width, int height, DiagramType newType) = 0;
	virtual void UpdateDiagramData() = 0;
	virtual void ResetDiagramType(DiagramType newType) = 0;
	virtual void DisplayArchiv() = 0;
};