#include "pch.h"
#include "FileInArchive.h"

//using namespace ArchiveProjCX::;

ArchiveProjCX::FileInArchive::FileInArchive(Platform::String^ mName, int mSize) :name(mName), size(mSize) {}

ArchiveProjCX::FileInArchive::FileInArchive(ArchiveProjCX::FileInArchive% old) : size(old.size), name(old.name) {}


void ArchiveProjCX::FileInArchive::Name::set(Platform::String^ value) {
	name = value;
}
Platform::String^ ArchiveProjCX::FileInArchive::Name::get() {
	return name;
}
int ArchiveProjCX::FileInArchive::Size::get() {
	return size;
}
void ArchiveProjCX::FileInArchive::Size::set(int value) {
	size = value;
}