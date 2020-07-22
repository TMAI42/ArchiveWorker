#pragma once
#include "Arhive/ArchiveSource/IArchive.h"

#include "ArchiveTypes.h"
#include "Arhive/DiagramTypes.h"


class ArchiveFactory{

public:
	static std::unique_ptr<IArchive> CreateArchive(std::wstring path, ArchiveType archiveType, DiagramType diagramType);

};

