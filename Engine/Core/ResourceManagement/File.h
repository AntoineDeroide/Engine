#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>


class File
{
	std::string m_path;

	std::fstream* m_pFile;
	unsigned int m_cursor;
	bool m_isOpen;

	bool Open();
	void Close();

public:

	File(std::string path);

	std::string Read();

	int Size();
	bool IsOpen();
};

#endif // FILE_H