#include "File.h"
#include <fstream>
#include <sstream>
#include <iostream>

File::File(std::string _path) :
	m_pFile(new std::fstream()),
	m_path(_path),
	m_cursor(0),
	m_isOpen(false)
{
	Open();
}

bool File::Open()
{
	if (m_path == "")
		return false;
	m_pFile->open(m_path, std::fstream::in);

	if (m_pFile->is_open() == false)
	{
		std::cout << "Failed to open following file : " << m_path << "\n";

		return false;
	}

	return true;
}

void File::Close()
{
	m_pFile->close();
}

std::string File::Read()
{
	std::string toReturn;

	(*m_pFile) >> toReturn;

	return toReturn;
}

int File::Size()
{
	if (!m_isOpen)
		return 0;

	m_pFile->seekg(std::ios::end);

	return (int)m_pFile->tellg();
}

bool File::IsOpen()
{
	return m_isOpen;
}
