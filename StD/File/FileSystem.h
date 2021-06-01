#pragma once
#include <string>
#include <list>
#include <Windows.h>
#include "../StringUtil.h"
struct FileSystem
{
	using StrList = std::list<std::string>;
	// �w��t�H���_�[���ɂ���t�@�C�������ׂĎ擾����
	static bool serch(std::string folderPath, StrList& fileNameList)
	{
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;
		StrList fileNames;
		std::string searchPath = folderPath + "/*";
		hFind = FindFirstFile(_StW(searchPath).c_str(), &win32fd);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			// �t�H���_�[�p�X�Q�Ǝ��G���[
			return false;
		}
		do {
			if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				/* �f�B���N�g���̏ꍇ�͉������Ȃ� */
				printf("directory\n");
			}
			else {
				/* �t�@�C��������������z��ɕۑ����� */
				std::string name = _WtS(win32fd.cFileName);
				fileNameList.push_back(name);
			}
		} while (FindNextFile(hFind, &win32fd));

	}
};