#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include <algorithm>

#include "ArchiveProjectCLI.h"

using namespace System::Runtime::InteropServices;


//void StringToStlWString(System::String const^ s, std::wstring& os)
//{
//	String^ string = const_cast<String^>(s);
//	const wchar_t* chars = reinterpret_cast<const wchar_t*>((Marshal::StringToHGlobalUni(string)).ToPointer());
//	os = chars;
//	Marshal::FreeHGlobal(IntPtr((void*)chars));
//
//}


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

ArchiveProjectCLI::ArchiveExternal::ArchiveExternal(String^ path, ArchiveType type)
	:current(ArchiveFactory::CreateArchive(msclr::interop::marshal_as<std::wstring>(path), type)){}


List<ArchiveProjectCLI::FileInArchive>^ ArchiveProjectCLI::ArchiveExternal::ReadArchive()
{
	List<FileInArchive>^ castedList = gcnew List<FileInArchive>();

	for (auto pairArchive: current->ReadArchive()){
		
		castedList->Add(FileInArchive( WPtrToString(pairArchive.first.c_str(), pairArchive.first.size()), pairArchive.second ));
	}

	return castedList;
}

void ArchiveProjectCLI::ArchiveExternal::WriteToArchive(List<String^>^ filenames, String^ name, String^ format)
{
	std::vector<std::wstring> castedVector;

	for each (String^ fileName in filenames)
	{
		castedVector.push_back(msclr::interop::marshal_as<std::wstring>(fileName));
	}

	current->WriteToArchive(castedVector,
		msclr::interop::marshal_as<std::wstring>(name),
		msclr::interop::marshal_as<std::wstring>(format));

}

void ArchiveProjectCLI::ArchiveExternal::Extract()
{
	current->Extract();
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

ArchiveProjectCLI::FileInArchive::FileInArchive(String^ mName, int mSize):name(mName), size(mSize){}
