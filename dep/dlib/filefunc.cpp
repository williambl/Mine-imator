#include "filefunc.h"

bool fileExists(string filename) {
	wifstream file(filename.c_str());
    return (bool)file;
}

int fileGetSize(string filename) {
	wifstream file(filename.c_str(), ios::binary | ios::ate);
	return file.tellg();
}

wstring fileGetName(wstring filename) {
	size_t pos = filename.find_last_of(SLASH);
	if (pos == string::npos)
		return filename;

	return filename.substr(pos + 1, filename.size() - pos - 1);
}

wstring fileGetPath(wstring filename) {
	size_t pos = filename.find_last_of(SLASH);

	if (pos == string::npos)
		return filename;

	return filename.substr(0, pos + 1);
}

wstring fileGetDirectory(wstring filename) {
	size_t pos = filename.find_last_of(SLASH);

	if (pos == string::npos)
		return filename;

	return filename.substr(0, pos);
}

wstring fileGetExtension(wstring filename) {
	wstring fn = fileGetName(filename);
	size_t pos = fn.find_last_of(DOT);

	if (pos == string::npos)
		return L"";

	return fn.substr(pos, fn.size() - pos);
}

wstring fileSetExtension(wstring filename, wstring ext) {
	wstring fn = fileGetName(filename);
	wstring fp = fileGetPath(filename);
	size_t pos = fn.find_last_of(DOT);

	if (pos != string::npos)
		fn = fn.substr(0, pos);

	return fp + fn + ext;
}

bool directoryExists(wstring directory) {

#ifdef _WIN32
	struct _stat info;
	if (_wstat(&directory[0], &info) != 0)
		return false;
#else
	struct stat info;
	if (stat(&wstringToString(directory)[0], &info) != 0)
		return false;
#endif

	return (info.st_mode & S_IFDIR);
}