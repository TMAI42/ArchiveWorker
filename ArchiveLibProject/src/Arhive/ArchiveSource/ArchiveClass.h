#pragma once

#include "IArchive.h"

#include <Windows.h>
#include <functional>
#include <memory>
#include <fcntl.h>
#include <utility>
#include <iostream>
#include <io.h>

 
#include "Helpers.h"
#include "ArchiveClass.h"
#include "archive_entry.h"
#include "../DiagramTypes.h"
#include "../Diagram/IDiagram.h"


class Archive : public IArchive {
public:

	Archive(std::wstring mPath);
	~Archive() = default;

	std::vector<std::pair<std::wstring, int>> ReadArchive() final;
	void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format, std::wstring extPath, int cLvl) final;
	void Extract(std::wstring extPath) final;
	void AddToArchive(std::vector<std::wstring> filenames) final;
	void ConvertTo(std::wstring extPath, std::wstring newFormat) final;

	void SetDrawingObject(HWND target, int width, int height, DiagramType newType) final;
	void UpdateDiagramData() final;
	void ResetDiagramType(DiagramType newType) final;
	void DisplayArchiv() final;

private:

	int CopyData(archive* ar, archive* aw);

private:
	std::unique_ptr<IDiagram> currntDiagram;

	std::vector<std::pair<std::wstring, int>> lastReadFiles;
	std::wstring currentPath;
	std::vector<std::wstring> resentExtractedFiles;
};