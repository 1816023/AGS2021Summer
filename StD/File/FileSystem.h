#pragma once
#include <string>
#include <list>
#include <Windows.h>
#include "../StringUtil.h"
struct FileSystem
{
	using StrList = std::list<std::string>;
	// 指定フォルダー内にあるファイルをすべて取得する
	static bool serch(std::string folderPath, StrList& fileNameList)
	{
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;
		StrList fileNames;
		std::string searchPath = folderPath + "/*";
		hFind = FindFirstFile(_StW(searchPath).c_str(), &win32fd);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			// フォルダーパス参照時エラー
			return false;
		}
		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				/* ディレクトリの場合は何もしない */
				printf("directory\n");
			}
			else {
				/* ファイルが見つかったら配列に保存する */
				std::string name = _WtS(win32fd.cFileName);
				fileNameList.push_back(name);
			}
		} while (FindNextFile(hFind, &win32fd));

	}
};