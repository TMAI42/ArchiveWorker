#pragma once
#include <string>

namespace Helpers {

    //TODO: exeptions
    std::string GetNameFromPath(std::string mString);

    std::wstring GetNameFromPath(std::wstring mString);

    std::string GetPathFromAbsPath(std::string absPath);

    std::wstring GetPathFromAbsPath(std::wstring absPath);

    std::string ArchNameToFolder(std::string absPath);

    std::wstring ArchNameToFolder(std::wstring absPath);

    std::wstring GetFormatFromPath(std::wstring);

    std::string GetFormatFromPath(std::string);

    std::wstring GetRawName(std::wstring);

    std::string GetRawName(std::string);

    namespace Converters {

        std::wstring StringToWStr(std::string str);

        std::string WStringToStr(std::wstring str);

    }
}
