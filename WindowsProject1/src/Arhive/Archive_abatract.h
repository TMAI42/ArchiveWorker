#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <fcntl.h>
#include <utility>
#include <iostream>
#include <io.h>


#include "Helpers.h"
#include "includes/zlib.h"
#include "include/archive.h"
#include "include/archive_entry.h"


class Archive_abstract {
	
public:

	virtual ~Archive_abstract() = default;

	virtual std::vector<std::pair<std::wstring, int>> ReadArchive() = 0;
	virtual void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name) = 0;
	virtual void Extract() = 0;
	virtual void AddToArchive(std::vector<std::wstring> filenames) = 0;
};