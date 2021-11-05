#include "SearchFiles.hpp"

void FindFile(const std::wstring&);

/// <summary>
/// ����������� ������ SearchFile
/// </summary>
/// <param name="diskName">����������� ����� ��� ������ � ��� (��������, �)</param>
SearchFiles::SearchFiles(std::wstring diskname) {
	diskName = diskname;
	chooseSearchType();
}

/// <summary>
/// ���������� ������ SearchFile
/// </summary>
SearchFiles::~SearchFiles() {
	//delete this;
}


/// <summary>
/// ����� ��� ������ ���� ������
/// </summary>
void SearchFiles::chooseSearchType() {
	do {
		std::cout << "Choose search type:" << std::endl;
		std::cout << "[1] by template" << std::endl;
		std::cout << "[2] by create date" << std::endl;
		std::cout << "[3] by file size" << std::endl;
		std::cout << "Search type number: ";
		std::cin >> searchType;
		std::cout << "=====" << std::endl;
		std::cout << "Choosed " << searchType << " search type" << std::endl;
	} while (searchType < 1 || searchType > 3 || searchType == NULL);

	switch (searchType)
	{
	case 1: // ����� ������ ������ �� �������
		searchByTemplate();
		break;
	case 2: // ����� ������ ������ �� ���� ��������
		searchByCreating();
		break;
	case 3: // ����� ������ ������ �� ������� �����
		searchBySize();
		break;
	}
}

/// <summary>
/// ����� ��� ������ �� �������
/// </summary>
void SearchFiles::searchByTemplate() {
	std::wstring wregexpr;

	do {
		std::cout << "Enter regular expression for find file(s): ";
		std::wcin >> wregexpr;
	} while (wregexpr == L"");


	browseFiles(wregexpr, true);
}

/// <summary>
/// ����� ��� ������ �� ������� �������� �����
/// </summary>
void SearchFiles::searchByCreating() {
	std::wstring time;
	do {
		std::cout << "Enter time creating file: ";
		std::wcin >> time;
	} while (time == L"");

	browseFiles(time);
}

/// <summary>
/// ����� ��� ������ �� ������� �����
/// </summary>
void SearchFiles::searchBySize() {
	int size = 0;
	do {
		std::cout << "Enter file size: ";
		std::cin >> size;
	} while (size <= 0);

	browseFiles(size);
}

/// <summary>
/// ����� ����� �� �������
/// </summary>
/// <param name="re">���������� ���������</param>
/// <param name="isTrue">������� ��� ����������</param>
void SearchFiles::browseFiles(std::wstring re, bool isTrue) {
	std::wstring directory = diskName;
	std::wstring tmp = directory + L"\\" + regexp;

	WIN32_FIND_DATAW file;
	HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);

	if (search_handle != INVALID_HANDLE_VALUE)
	{
		std::vector<std::wstring> directories;
		do {
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
					continue;
			}

			tmp = directory + L"\\" + std::wstring(file.cFileName);
			std::wcout << tmp << std::endl;

			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				directories.push_back(tmp);
		} while (FindNextFileW(search_handle, &file));

		FindClose(search_handle);

		for (std::vector<std::wstring>::iterator iter = directories.begin(), end = directories.end(); iter != end; ++iter)
			FindFile(*iter);
	}
}


/// <summary>
/// ����� ������ �� �������
/// </summary>
/// <param name="filesize">������ �����</param>
void SearchFiles::browseFiles(int filesize) {

}

/// <summary>
/// ����� ������ �� ������� ��������
/// </summary>
/// <param name="timestamp">����� ��������</param>
void SearchFiles::browseFiles(std::wstring timestamp) {

}

void SearchFiles::setFileInfo(fileInfo& info, WIN32_FIND_DATAW file, SYSTEMTIME time) {
	std::ostringstream date;

	info.fileName = file.cFileName;
	info.filePath = diskName + L"\\" + std::wstring(file.cFileName);
	info.fileSize = file.nFileSizeLow;
	info.year = time.wYear;
	info.month = time.wMonth;
	info.day = time.wDay;
	date << time.wDay << '-' << time.wMonth << '-' << time.wYear;
	std::string str = date.str();
	info.createDate = str;
}