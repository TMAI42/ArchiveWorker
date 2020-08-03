#include "pch.h"
#include <msclr\marshal_cppstd.h>

#include "ArchiveProjectCLI.h"

using System::Text::Encoding;

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

String^ NaiveToStringClr(std::string native) {
	//array<Byte>^ encodedBytes = Encoding::UTF8->GetBytes(native);

	// prevent GC moving the bytes around while this variable is on the stack
	//pin_ptr<Byte> pinnedBytes = &encodedBytes[0];

	// Call the function, typecast from byte* -> char* is required
	//MyTest(reinterpret_cast<char*>(pinnedBytes), encodedBytes->Length);

	return gcnew String(native.c_str(),0,native.length(), System::Text::Encoding::UTF8);
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
		
		castedList->Add(FileInArchive(NaiveToStringClr(pairArchive.first), pairArchive.second ));
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



