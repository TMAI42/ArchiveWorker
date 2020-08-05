#pragma once

#include "Arhive/ArchiveSource/IArchive.h"
#include "FileInArchive.h"

#include <collection.h>
#include <algorithm>
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;


namespace ArchiveProjCX
{

	public enum class TypeOfArchive {
		Standart
	};

	public enum class TypeOfDiagram {
		ArchiveSizeDependency,
		MaxSizeDependency,
		TestGrid
	};

	public ref class ArchiveExternal sealed {
	public:

		
		ArchiveExternal(String^ path, TypeOfArchive type);
		IVector<FileInArchive^>^ ReadArchive();
		void WriteToArchive(IVector<String^>^ filenames, String^ name, String^ format, String^ extPath, int cLvl);
		void Extract(String^ extPath);
		void AddToArchive(IVector<String^>^ filenames);
		void ConvertTo(String^ extPath, String^ format);

		//void SetDrawingObject(IntPtr^ target, int width, int height, TypeOfDiagram Type);
		void UpdateDiagramData();
		void ResetDiagramType(TypeOfDiagram newType);
		void DisplayArchiv();
	private:
		 ~ArchiveExternal();
		IArchive* current;


		// TODO: Add your methods for this class here.
	};
}
