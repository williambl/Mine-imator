#include "filefunc.h"

wstring fileGetName(wstring filename) {
	int pos = filename.find_last_of(SLASH);

	if (pos == string::npos)
		return filename;

	return filename.substr(pos + 1, filename.size() - pos - 1);
}

wstring fileGetPath(wstring filename) {
	int pos = filename.find_last_of(SLASH);

	if (pos == string::npos)
		return filename;

	return filename.substr(0, pos + 1);
}

wstring fileGetDirectory(wstring filename) {
	int pos = filename.find_last_of(SLASH);

	if (pos == string::npos)
		return filename;

	return filename.substr(0, pos);
}