
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
	SearchFiles(std::wstring); // Конструктор
	~SearchFiles();    // Деструктор
private:
	int searchType;   // Тип поиска

	void chooseSearchType(); // Метод для выбора типа поиска
	void searchByTemplate(); // Метод для поиска по шаблону
	void searchByCreating(); // Метод для поиска по времени создания файла
	void searchBySize();     // Метод для поиска по размеру файла

	void browseFiles(int);               // Поиск файлов по размеру
	void browseFiles(std::wstring, bool); // Поиск файлов по регулярному выражению (шаблону)
	void browseFiles(std::wstring);       // Поиск файлов по времени создания (UTC+3)
	void FindFile(std::wstring);         // Рекурсивный поиск файлов

	void setFileInfo(fileInfo&, WIN32_FIND_DATAW, SYSTEMTIME); // 
};

#endif
