#pragma once
#include "ArchiveFactory.h"

using namespace System;

namespace ArchiveProjectCLI {
	public ref class ArchiveExternal
	{
	public:

		ArchiveExternal(String^ path, ArchiveType type);

		std::vector<std::pair<std::wstring, int>> ReadArchive();
		void WriteToArchive(std::vector<std::wstring> filenames, std::wstring name, std::wstring format);
		void Extract();
		void AddToArchive(std::vector<std::wstring> filenames);

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


