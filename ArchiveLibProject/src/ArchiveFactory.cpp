#include "ArchiveFactory.h"

#include "Arhive/ArchiveSource/ArchiveClass.h"

IArchive* ArchiveFactory::CreateArchive(std::wstring path, ArchiveType archiveType) {

	switch (archiveType) {

	case ArchiveType::Standart:

		return new Archive(path);

	default:

		return nullptr;

	}
}
