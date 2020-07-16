
#include "Helpers.h"

//TODO: exeptions
std::string Helpers::GetNameFromPath(std::string mString) {

    auto a = mString.rfind('\\');
    if (a < 0) {
        return mString;
    }
    return mString.substr(a + 1, mString.size() - a - 1);
}


std::wstring Helpers::GetNameFromPath(std::wstring mString) {

    auto a = mString.rfind('\\');
    if (a < 0) {
        return mString;
    }
    return mString.substr(a + 1, mString.size() - a - 1);
}


std::string Helpers::GetPathFromAbsPath(std::string absPath) {
    auto a = absPath.rfind('\\');
    if (a < 0) 
        return NULL;
    return absPath.substr(0, a+1);
}


std::wstring Helpers::GetPathFromAbsPath(std::wstring absPath) {
    auto a = absPath.rfind('\\');
    if (a < 0)
        return NULL;
    return absPath.substr(0, a + 1);
}


std::wstring Helpers::ArchNameToFolder(std::wstring absPath) {
    auto a = absPath.rfind('.');
    if (a < 0)
        return NULL;
    return absPath.substr(0, a + 1) + L'\\';
}

std::string Helpers::GetFormatFromPath(std::string mString)
{
    auto a = mString.rfind('.');
    if (a < 0) {
        return mString;
    }
    return mString.substr(a + 1, mString.size() - a - 1);
}

std::wstring Helpers::GetFormatFromPath(std::wstring mString)
{
    auto a = mString.rfind('.');
    if (a < 0) {
        return mString;
    }
    return mString.substr(a + 1, mString.size() - a - 1);
}


std::string Helpers::ArchNameToFolder(std::string absPath) {
    auto a = absPath.rfind('.');
    if (a < 0)
        return NULL;
    return absPath.substr(0, a + 1) + '\\';
}


std::wstring Helpers::Converters::StringToWStr(std::string str) {
    return std::wstring(str.begin(), str.end());
}


std::string Helpers::Converters::WStringToStr(std::wstring str) {
    return std::string(str.begin(), str.end());
}
