#include "SearchFiles.hpp"

void FindFile(const std::wstring&);

/// <summary>
/// Конструктор класса SearchFile
/// </summary>
/// <param name="diskName">Обозначение диска для работы с ним (например, С)</param>
SearchFiles::SearchFiles(std::wstring diskname) {
	diskName = diskname;
	chooseSearchType();
}

/// <summary>
/// Диструктор класса SearchFile
/// </summary>
SearchFiles::~SearchFiles() {
	//delete this;
}


/// <summary>
/// Метод для выбора типа поиска
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
	case 1: // Вызов метода поиска по шаблону
		searchByTemplate();
		break;
	case 2: // Вызов метода поиска по дате создания
		searchByCreating();
		break;
	case 3: // Вызов метода поиска по размеру файла
		searchBySize();
		break;
	}
}

/// <summary>
/// Метод для поиска по шаблону
/// </summary>
void SearchFiles::searchByTemplate() {
	std::wstring wregexpr;

	do {
		std::cout << "Enter regular expression for find file(s): ";
		std::wcin >> wregexpr;
	} while (wregexpr == L"");


	//browseFiles(wregexpr, true);
	FindFile(wregexpr);
}

/// <summary>
/// Метод для поиска по времени создания файла
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
/// Метод для поиска по размеру файла
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
/// Поиск файла по шаблону
/// </summary>
/// <param name="re">Регулярное выражение</param>
/// <param name="isTrue">Костыль для перегрузки</param>
void SearchFiles::browseFiles(std::wstring re, bool isTrue) {
	std::wstring tmp = diskName + L"\\" + re;
	std::wcout << "Search: " << tmp << std::endl;

	WIN32_FIND_DATAW file;	
	HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);
	SYSTEMTIME time;

	if (search_handle != INVALID_HANDLE_VALUE) {
		do
		{
			if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::wcout << file.dwFileAttributes << std::endl;
				if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
					continue;
			}
			tmp = diskName + L"\\" + std::wstring(file.cFileName);
			std::wcout << tmp << std::endl;
			FileTimeToSystemTime(&file.ftCreationTime, &time);
			SearchFiles::fileInfo info;
			setFileInfo(info, file, time);
			filesInfo.push_back(info);
		} while (FindNextFileW(search_handle, &file));
	}
	else {
		std::cout << "FAILED!" << std::endl;
		FindFile(re);
	}
}


/// <summary>
/// Поиск файлов по размеру
/// </summary>
/// <param name="filesize">Размер файла</param>
void SearchFiles::browseFiles(int filesize) {

}

/// <summary>
/// Поиск файлов по времени создания
/// </summary>
/// <param name="timestamp">Время создания</param>
void SearchFiles::browseFiles(std::wstring timestamp) {

}

/// <summary>
/// Поиск файла по шаблону
/// </summary>
/// <param name="regexp">Регулярное выражение (шаблон)</param>
void SearchFiles::FindFile(std::wstring regexp)
{
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