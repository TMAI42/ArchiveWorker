#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include "ArchiveProjectCLI.h"

ArchiveProjectCLI::ArchiveExternal::ArchiveExternal(String^ path, ArchiveType type)
	:current(ArchiveFactory::CreateArchive(msclr::interop::marshal_as<std::wstring>(path), type)){}

std::vector<std::pair<std::wstring, int>> ArchiveProjectCLI::ArchiveExternal::ReadArchive()
{
	return current->ReadArchive();
}

void ArchiveProjectCLI::ArchiveExternal::WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format)
{
	current->WriteToArchive(filenames, name, format);
}

void ArchiveProjectCLI::ArchiveExternal::Extract()
{
	current->Extract();
}

void ArchiveProjectCLI::ArchiveExternal::AddToArchive(std::vector<std::wstring> filenames)
{
	current->AddToArchive(filenames);
}

void ArchiveProjectCLI::ArchiveExternal::SetDrawingObject(HWND target, int width, int height, DiagramType newType)
{
	current->SetDrawingObject(target, width, height, newType);
}

void ArchiveProjectCLI::ArchiveExternal::UpdateDiagramData()
{
	current->UpdateDiagramData();
}

void ArchiveProjectCLI::ArchiveExternal::ResetDiagramType(DiagramType newType)
{
	current->ResetDiagramType(newType);
}

void ArchiveProjectCLI::ArchiveExternal::DisplayArchiv()
{
	current->DisplayArchiv();
}

ArchiveProjectCLI::ArchiveExternal::!ArchiveExternal()
{
	current->~IArchive();
}
