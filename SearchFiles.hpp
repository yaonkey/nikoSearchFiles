
#ifndef OLEG_MIREA_SEARCHFILES_HPP
#define OLEG_MIREA_SEARCHFILES_HPP

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <vector>    
#include <filesystem>

class SearchFiles {
	struct fileInfo {
		std::wstring filePath;
		std::wstring fileName;
		WORD year;
		WORD month;
		WORD day;
		std::string createDate;
		int fileSize;
	};

	std::vector<fileInfo>filesInfo;
	std::wstring diskName;
public:
	SearchFiles(std::wstring); // �����������
	~SearchFiles();    // ����������
private:
	int searchType;   // ��� ������

	void chooseSearchType(); // ����� ��� ������ ���� ������
	void searchByTemplate(); // ����� ��� ������ �� �������
	void searchByCreating(); // ����� ��� ������ �� ������� �������� �����
	void searchBySize();     // ����� ��� ������ �� ������� �����

	void browseFiles(int);               // ����� ������ �� �������
	void browseFiles(std::wstring, bool); // ����� ������ �� ����������� ��������� (�������)
	void browseFiles(std::wstring);       // ����� ������ �� ������� �������� (UTC+3)
	void FindFile(std::wstring);         // ����������� ����� ������

	void setFileInfo(fileInfo&, WIN32_FIND_DATAW, SYSTEMTIME); // 
};

#endif
