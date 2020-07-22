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
#include "archive.h"
#include "archive_entry.h"
#include "../DiagramTypes.h"


class Archive : public IArchive {
public:

	Archive(std::wstring mPath, DiagramType mDiagramType);
	~Archive() = default;

	std::vector<std::pair<std::wstring, int>> ReadArchive() final;
	void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format) final;
	void Extract() final;
	void AddToArchive(std::vector<std::wstring> filenames) final;

	void ResetDiagramType() final;
	void DisplayArchiv() final;

private:

	int CopyData(archive* ar, archive* aw);

private:
	
	std::wstring currentPath;
	std::vector<std::wstring> resentExtractedFiles;
};