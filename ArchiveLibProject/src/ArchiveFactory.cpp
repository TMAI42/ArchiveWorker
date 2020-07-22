#include "ArchiveFactory.h"

#include "Arhive/ArchiveSource/Archive.h"

IArchive* ArchiveFactory::CreateArchive(std::wstring path, ArchiveType archiveType, DiagramType diagramType) {

	switch (archiveType) {

	case ArchiveType::Standart:

		return new Archive(path, diagramType);

	default:

		return nullptr;

	}
}
