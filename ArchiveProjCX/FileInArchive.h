#pragma once
using Platform::String;

namespace ArchiveProjCX {

	public ref class FileInArchive sealed {
	public:
		FileInArchive(String^ name, int size);
	internal:
		FileInArchive(FileInArchive%);

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
