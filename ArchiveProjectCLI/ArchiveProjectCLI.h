#pragma once
#include "ArchiveFactory.h"
#include "FileInArchive.h"


using namespace System;
using System::Collections::Generic::List;

namespace ArchiveProjectCLI {

	public enum class TypeOfArchive {
		Standart
	};

	public enum class TypeOfDiagram {
		ArchiveSizeDependency,
		MaxSizeDependency, 
		TestGrid
	};


	public ref class ArchiveExternal : IDisposable
	{
	public:

		~ArchiveExternal();
		ArchiveExternal(String^ path, TypeOfArchive type);
		List<FileInArchive>^ ReadArchive();
		void WriteToArchive(List<String^>^ filenames, String^ name, String^ format, String^ extPath, int cLvl);
		void Extract(String^ extPath);
		void AddToArchive(List<String^>^ filenames);
		void ConvertTo(String^ extPath, String^ format);

		void SetDrawingObject(IntPtr^ target, int width, int height, TypeOfDiagram Type);
		void UpdateDiagramData();
		void ResetDiagramType(TypeOfDiagram newType);
		void DisplayArchiv();

	private:
		IArchive* current;
	

		// TODO: Add your methods for this class here.
	};




}


