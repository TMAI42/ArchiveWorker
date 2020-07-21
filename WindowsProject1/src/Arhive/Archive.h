#pragma once

#include "Archive_abatract.h"

class Archive : public Archive_abstract {
public:

	Archive(std::wstring mPath);
	~Archive() = default;

	std::vector<std::pair<std::wstring, int>> ReadArchive() final;
	void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format) final;
	void Extract() final;
	void AddToArchive(std::vector<std::wstring> filenames) final;

private:

	int CopyData(archive* ar, archive* aw);

private:
	
	std::wstring currentPath;
	std::vector<std::wstring> resentExtractedFiles;
};