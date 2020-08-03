#pragma once

using System::String;

namespace ArchiveProjectCLI {

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
}

