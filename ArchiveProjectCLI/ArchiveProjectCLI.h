#pragma once
#include "ArchiveFactory.h"



using namespace System;
using System::Collections::Generic::List;

namespace ArchiveProjectCLI {


	public value class FileInArchive {
	public:
		FileInArchive(String^ name, int size);
		String^ name;
		int size;
	};


	public ref class ArchiveExternal
	{
	public:

		ArchiveExternal(String^ path, ArchiveType type);
		List<FileInArchive>^ ReadArchive();
		void WriteToArchive(List<String^>^ filenames, String^ name, String^ format);
		void Extract();
		void AddToArchive(List<String^>^ filenames);

		void SetDrawingObject(HWND target, int width, int height, DiagramType newType);
		void UpdateDiagramData();
		void ResetDiagramType(DiagramType newType);
		void DisplayArchiv();

	protected:
		!ArchiveExternal();

	private:
		IArchive* current;
	

		// TODO: Add your methods for this class here.
	};



}


