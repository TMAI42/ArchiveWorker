#include "ArchiveFactory.h"

#include "Arhive/ArchiveSource/ArchiveClass.h"

std::unique_ptr<IArchive> ArchiveFactory::CreateArchive(std::wstring path, ArchiveType archiveType) {

	switch (archiveType) {

	case ArchiveType::Standart:

		return std::unique_ptr<IArchive> {new Archive(path)};

	default:

		return nullptr;

	}
}
