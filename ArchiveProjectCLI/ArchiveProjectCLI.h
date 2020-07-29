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

		property String^ Name {
			String^ get();
			void set(String^ value);
		}

		property int Size {
			int get();
			void set(int value);
		}

	private:
		String^ name;
		int size;
	};


	public ref class ArchiveExternal : IDisposable
	{
	public:

		~ArchiveExternal();
		ArchiveExternal(String^ path, TypeOfArchive type);
		List<FileInArchive>^ ReadArchive();
		void WriteToArchive(List<String^>^ filenames, String^ name, String^ format);
		void Extract(String^ extPath);
		void AddToArchive(List<String^>^ filenames);

		void SetDrawingObject(IntPtr^ target, int width, int height, TypeOfDiagram Type);
		void UpdateDiagramData();
		void ResetDiagramType(TypeOfDiagram newType);
		void DisplayArchiv();

	private:
		IArchive* current;
	

		// TODO: Add your methods for this class here.
	};




}


