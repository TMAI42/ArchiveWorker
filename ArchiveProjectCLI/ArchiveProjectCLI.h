#pragma once
#include "ArchiveFactory.h"



using namespace System;
using System::Collections::Generic::List;

namespace ArchiveProjectCLI {

	public enum class TypeOfArchive {
		Standart
	};

	public enum class TypeOfDiagram {
		ArchiveSizeDependency,
		MaxSizeDependency
	};


	public value class FileInArchive {
	public:
		FileInArchive(String^ name, int size);
		String^ name;
		int size;
	};


	public ref class ArchiveExternal
	{
	public:

		ArchiveExternal(String^ path, TypeOfArchive type);
		List<FileInArchive>^ ReadArchive();
		void WriteToArchive(List<String^>^ filenames, String^ name, String^ format);
		void Extract();
		void AddToArchive(List<String^>^ filenames);

		void SetDrawingObject(HWND target, int width, int height, TypeOfDiagram Type);
		void UpdateDiagramData();
		void ResetDiagramType(TypeOfDiagram newType);
		void DisplayArchiv();

	protected:
		!ArchiveExternal();

	private:
		IArchive* current;
	

		// TODO: Add your methods for this class here.
	};




}


