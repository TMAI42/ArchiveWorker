#include "pch.h"
#include "FileInArchive.h"

ArchiveProjectCLI::FileInArchive::FileInArchive(String^ mName, int mSize) :name(mName), size(mSize) {}

void ArchiveProjectCLI::FileInArchive::Name::set(String^ value) {
	name = value;
}
String^ ArchiveProjectCLI::FileInArchive::Name::get() {
	return name;
}
int ArchiveProjectCLI::FileInArchive::Size::get() {
	return size;
}
void ArchiveProjectCLI::FileInArchive::Size::set(int value) {
	size = value;
}