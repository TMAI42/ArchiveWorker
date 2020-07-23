#pragma once
#include "Arhive/ArchiveSource/IArchive.h"

#include "ArchiveTypes.h"
#include "Arhive/DiagramTypes.h"
#include<memory>


class ArchiveFactory{

public:
	static IArchive* CreateArchive(std::wstring path, ArchiveType archiveType);

};

