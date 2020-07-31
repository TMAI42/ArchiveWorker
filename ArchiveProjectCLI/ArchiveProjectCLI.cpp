#include "pch.h"
#include <msclr\marshal_cppstd.h>

#include "ArchiveProjectCLI.h"


String^ WPtrToString(wchar_t const* pData, int length) {
	if (length == 0) {
		length = wcslen(pData);
		if (length == 0) {
			System::String^ ret = "";
			return ret;
		}
	}

	System::IntPtr bfr = System::IntPtr(const_cast<wchar_t*>(pData));
	System::String^ ret = System::Runtime::InteropServices::Marshal::PtrToStringUni(bfr, length);
	return ret;
}

ArchiveProjectCLI::ArchiveExternal::~ArchiveExternal() {
	delete current;
}

ArchiveProjectCLI::ArchiveExternal::ArchiveExternal(String^ path, TypeOfArchive type)
	:current(ArchiveFactory::CreateArchive(msclr::interop::marshal_as<std::wstring>(path),static_cast<ArchiveType>(type))){}


List<ArchiveProjectCLI::FileInArchive>^ ArchiveProjectCLI::ArchiveExternal::ReadArchive()
{
	List<FileInArchive>^ castedList = gcnew List<FileInArchive>();

	for (auto pairArchive: current->ReadArchive()){
		
		castedList->Add(FileInArchive( WPtrToString(pairArchive.first.c_str(), pairArchive.first.size()), pairArchive.second ));
	}

	return castedList;
}

void ArchiveProjectCLI::ArchiveExternal::WriteToArchive(List<String^>^ filenames, String^ name, String^ format, String^ extPath)
{
	std::vector<std::wstring> castedVector;

	for each (String^ fileName in filenames)
	{
		castedVector.push_back(msclr::interop::marshal_as<std::wstring>(fileName));
	}

	current->WriteToArchive(castedVector,
		msclr::interop::marshal_as<std::wstring>(name),
		msclr::interop::marshal_as<std::wstring>(format),
		msclr::interop::marshal_as<std::wstring>(extPath));

}

void ArchiveProjectCLI::ArchiveExternal::Extract(String^ extPath)
{
	current->Extract(msclr::interop::marshal_as<std::wstring>(extPath));
}

void ArchiveProjectCLI::ArchiveExternal::AddToArchive(List<String^>^ filenames)
{
	std::vector<std::wstring> castedVector;

	for each (String ^ fileName in filenames)
	{
		castedVector.push_back(msclr::interop::marshal_as<std::wstring>(fileName));
	}

	current->AddToArchive(castedVector);
}

void ArchiveProjectCLI::ArchiveExternal::ConvertTo(String^ extPath, String^ format)
{
	current->ConvertTo(msclr::interop::marshal_as<std::wstring>(extPath), msclr::interop::marshal_as<std::wstring>(format));
}

void ArchiveProjectCLI::ArchiveExternal::SetDrawingObject(IntPtr^ target, int width, int height, TypeOfDiagram newType)
{
	current->SetDrawingObject(reinterpret_cast<HWND>(target->ToPointer()), width, height, static_cast<DiagramType>(newType));
}

void ArchiveProjectCLI::ArchiveExternal::UpdateDiagramData()
{
	current->UpdateDiagramData();
}

void ArchiveProjectCLI::ArchiveExternal::ResetDiagramType(TypeOfDiagram newType)
{
	current->ResetDiagramType(static_cast<DiagramType>(newType));
}

void ArchiveProjectCLI::ArchiveExternal::DisplayArchiv()
{
	current->DisplayArchiv();
}


ArchiveProjectCLI::FileInArchive::FileInArchive(String^ mName, int mSize):name(mName), size(mSize){}

void ArchiveProjectCLI::FileInArchive::Name::set(String^ value) {
	name =value;
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
