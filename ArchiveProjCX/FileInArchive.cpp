#include"FileInArchive.h"
#include "pch.h"

using namespace ArchiveProjCX;

FileInArchive::FileInArchive(String^ mName, int mSize) :name(mName), size(mSize) {}

FileInArchive::FileInArchive(FileInArchive% old) : size(old.size), name(old.name) {}


void FileInArchive::Name::set(String^ value) {
	name = value;
}
String^ FileInArchive::Name::get() {
	return name;
}
int FileInArchive::Size::get() {
	return size;
}
void FileInArchive::Size::set(int value) {
	size = value;
}