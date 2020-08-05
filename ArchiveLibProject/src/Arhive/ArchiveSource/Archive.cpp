#include "ArchiveClass.h"
#include "../DiagramFactory.h"

#include "archive.h"
#include "archive_entry.h"


Archive::Archive(std::wstring mPath) : currentPath(mPath) {}


namespace Deleter {

	void ReadDeleter(archive* a) {
		auto status = archive_read_close(a);
		status = archive_read_free(a);
	}

	void WriteDeliter(archive* a) {
		auto status = archive_write_close(a);
		status = archive_write_free(a);
	}

}


int Archive::CopyData(archive* ar, archive* aw)
{
	int r;
	const void* buff;
	size_t size;
	int64_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r != ARCHIVE_OK) {
			;
			return (r);
		}
		r = archive_write_data_block(aw, buff, size, offset);
		if (r != ARCHIVE_OK) {

			return (r);
		}
	}
}


std::vector<std::pair<std::wstring, int>> Archive::ReadArchive() {

	std::unique_ptr<archive, std::function<void(archive*)>> archivePtr(nullptr, Deleter::ReadDeleter);
	archive_entry* entry;

	std::vector<std::pair<std::wstring, int>> temp;

	archivePtr.reset(archive_read_new());
	auto r = archive_read_support_filter_all(archivePtr.get());
	r = archive_read_support_format_all(archivePtr.get());
	r = archive_read_open_filename_w(archivePtr.get(),
		currentPath.c_str(),
		10240);

	if (r != ARCHIVE_OK)
		return temp;

	while (archive_read_next_header(archivePtr.get(), &entry) == ARCHIVE_OK) {
		auto str = std::wstring(archive_entry_pathname_w(entry));
		temp.push_back({str, archive_entry_size(entry) / 8192 });
		archive_read_data_skip(archivePtr.get());
	}

	lastReadFiles = temp;

	if (currntDiagram)
		UpdateDiagramData();

	return temp;
}

//TODO: error handler
void Archive::WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format, std::wstring extPath, int cLvl) {

	std::unique_ptr<archive, std::function<void(archive*)>> archivePtr(nullptr, Deleter::WriteDeliter);
	archive_entry* entry;
	struct stat st;
	char buff[8192];
	int len;

	this->currentPath = extPath + name;
	auto fd = CreateFileW(currentPath.c_str(),
		GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(fd);

	archivePtr.reset(archive_write_new());
	//archive_write_set_format_zip(archivePtr.get());
	//archive_write_zip_set_compression_deflate(archivePtr.get());

	std::string compressionLvl;

	if (cLvl < 10 || cLvl > 0) 
		compressionLvl = cLvl;
	 else
		compressionLvl = "9";

	archive_write_set_format_option(archivePtr.get(),
		Helpers::Converters::WStringToStr(format).c_str(), "compression-level", compressionLvl.c_str());
	auto r = archive_write_open_filename_w(archivePtr.get(),
		this->currentPath.c_str());

	for (auto filename : filenames) {

		stat(std::string(filename.begin(), filename.end()).c_str(), &st);
		entry = archive_entry_new();
		archive_entry_copy_pathname_w(entry, Helpers::GetNameFromPath(
			filename).c_str());
		archive_entry_set_size(entry, st.st_size);
		archive_entry_set_filetype(entry, AE_IFREG);
		archive_entry_set_perm(entry, 0644);
		archive_write_header(archivePtr.get(), entry);

		auto file = CreateFileW(filename.c_str(),
			GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		auto t = ReadFile(file, buff, sizeof(buff), reinterpret_cast<DWORD*> (&len), NULL);

		while (len > 0) {
			archive_write_data(archivePtr.get(), buff, len);
			t = ReadFile(file, buff, sizeof(buff), reinterpret_cast<DWORD*>(&len), NULL);
		}
		archive_entry_free(entry);
		CloseHandle(file);
	}
}


void Archive::Extract(std::wstring extPath) {

	const int BUFFER_SIZE = 8192;
	const int SIZE_OF_READING_DATA = 102400;

	std::unique_ptr<archive, std::function<void(archive*)>> archivePtr(nullptr, Deleter::ReadDeleter);
	std::unique_ptr<archive, std::function<void(archive*)>> diskPtr(nullptr, Deleter::WriteDeliter);
	archive_entry* entry;
	int flags;
	int r;
	wchar_t buff[BUFFER_SIZE];
	int len;

	resentExtractedFiles.clear();

	flags = ARCHIVE_EXTRACT_TIME;
	flags |= ARCHIVE_EXTRACT_PERM;
	flags |= ARCHIVE_EXTRACT_ACL;
	flags |= ARCHIVE_EXTRACT_FFLAGS;

	archivePtr.reset(archive_read_new());
	archive_read_support_format_all(archivePtr.get());
	diskPtr.reset(archive_write_disk_new());
	archive_write_disk_set_options(diskPtr.get(), flags);
	archive_write_disk_set_standard_lookup(diskPtr.get());
	if ((r = archive_read_open_filename_w(archivePtr.get(),
		currentPath.c_str(),
		SIZE_OF_READING_DATA)))
		return;

	for (;;) {
		r = archive_read_next_header(archivePtr.get(), &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r < ARCHIVE_WARN)
			return;

		auto newPath = extPath + std::wstring(archive_entry_pathname_w(entry));

		resentExtractedFiles.push_back(newPath);

		archive_entry_copy_pathname_w(entry,
			newPath.c_str());

		r = archive_write_header(diskPtr.get(), entry);

		if (archive_entry_size(entry) > 0) {
			r = CopyData(archivePtr.get(), diskPtr.get());
			if (r < ARCHIVE_WARN)
				return;
		}
		r = archive_write_finish_entry(diskPtr.get());
		if (r < ARCHIVE_WARN)
			return;
	}
}


void Archive::AddToArchive(std::vector<std::wstring> filenames) {

	Extract(Helpers::GetPathFromAbsPath(currentPath));

	for (auto& file : resentExtractedFiles)
		filenames.push_back(file);

	WriteToArchive(filenames,
		Helpers::GetNameFromPath(currentPath),
		Helpers::GetFormatFromPath(currentPath),
		Helpers::GetPathFromAbsPath(currentPath), 9);

	for (auto& file : resentExtractedFiles)
		DeleteFile(file.c_str());
}

void Archive::ConvertTo(std::wstring extPath, std::wstring newFormat) {
	Extract(Helpers::GetPathFromAbsPath(currentPath));

	WriteToArchive(resentExtractedFiles,
		Helpers::GetRawName(currentPath) + L"." + newFormat, newFormat, extPath, 9);

	for (auto& file : resentExtractedFiles)
		DeleteFile(file.c_str());
}

void Archive::SetDrawingObject(HWND target, int width, int height, DiagramType type) {

	auto tempDiagram = std::move(DiagramFactory::CreateDiagram(target, width, height, type));
	currntDiagram.swap(tempDiagram);

	UpdateDiagramData();
}

void Archive::UpdateDiagramData() {
	if (lastReadFiles.size() != 0)
		currntDiagram->SetData(lastReadFiles);
}

void Archive::ResetDiagramType(DiagramType newType) {
	auto [target, width, height] = currntDiagram->ReleseTarget();

	auto tempDiagram = std::move(DiagramFactory::CreateDiagram(target, width, height, newType));
	currntDiagram.swap(tempDiagram);

	UpdateDiagramData();
}

void Archive::DisplayArchiv() {
	if (currntDiagram)
		if (lastReadFiles.size() != 0)
			currntDiagram->Draw();
}


