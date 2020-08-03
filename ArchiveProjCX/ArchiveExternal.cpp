#include "pch.h"
#include "ArchiveExternal.h"
#include "ArchiveFactory.h"
#include <algorithm>

using namespace ArchiveProjCX;
using namespace Platform;


ArchiveExternal::~ArchiveExternal() {
	delete current;
}

ArchiveExternal::ArchiveExternal(String^ path, TypeOfArchive type)
	:current(ArchiveFactory::CreateArchive(std::wstring(path->Data()), static_cast<ArchiveType>(type))) {}


IVector<FileInArchive^>^ ArchiveExternal::ReadArchive()
{

	std::vector<FileInArchive^> castedList;

	for (auto pairArchive : current->ReadArchive()) {

		castedList.push_back(ref new FileInArchive{ ref new String(pairArchive.first.c_str()), pairArchive.second });
	}

	return ref new Vector<FileInArchive^>(std::move(castedList));
}

void ArchiveExternal::WriteToArchive(IVector<String^>^ filenames, String^ name, String^ format, String^ extPath)
{
	std::vector<std::wstring> castedVector;

	for each (String ^ fileName in filenames)
	{
		castedVector.push_back(std::wstring(fileName->Data()));
	}

	current->WriteToArchive(castedVector,
		std::wstring(name->Data()),
		std::wstring(format->Data()),
		std::wstring(extPath->Data()));

}

void ArchiveExternal::Extract(String^ extPath)
{
	current->Extract(std::wstring(extPath->Data()));
}

void ArchiveExternal::AddToArchive(IVector<String^>^ filenames)
{
	std::vector<std::wstring> castedVector;

	for each (String ^ fileName in filenames)
	{
		castedVector.push_back(std::wstring(fileName->Data()));
	}

	current->AddToArchive(castedVector);
}

void ArchiveExternal::ConvertTo(String^ extPath, String^ format)
{
	current->ConvertTo(std::wstring(extPath->Data()), std::wstring(format->Data()));
}

//void ArchiveExternal::SetDrawingObject(IntPtr^ target, int width, int height, TypeOfDiagram newType)
//{
//	current->SetDrawingObject(reinterpret_cast<HWND>(target->ToPointer()), width, height, static_cast<DiagramType>(newType));
//}

void ArchiveExternal::UpdateDiagramData()
{
	current->UpdateDiagramData();
}

void ArchiveExternal::ResetDiagramType(TypeOfDiagram newType)
{
	current->ResetDiagramType(static_cast<DiagramType>(newType));
}

void ArchiveExternal::DisplayArchiv()
{
	current->DisplayArchiv();
}

