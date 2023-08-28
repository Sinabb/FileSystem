#include <iostream>
#include <fstream>

bool LoadFile(const std::string& filename)
{
	// file stream
	std::ifstream ifs(filename);
	if (!ifs.good())
	{
		std::cerr << filename << "not found" << std::endl;
	}

	// file operation
	char ch;

	while (ifs.get(ch))
	{
		if (ifs.eof())
		{
			std::cerr << "end of file!!" << std::endl;
			break;
		}

		if (ifs.fail())
		{
			std::cerr << "logical error!" << std::endl;
		}
		if (ifs.bad())
		{
			std::cerr << "fatal error!" << std::endl;
		}

		std::cout << ch;
	}

	/*
	while (ifs>>ch)
	{
		std::cout << ch;
	}
	
	while (true)
	{
		ifs >> ch;
		if (ifs.eof())
		{
			break;
		}std::cout << ch;
	}

	char buffer[1024];
	while (ifs.getline(buffer, 1024))
	{
		std::cout << buffer << std::endl;
	}
	*/
	// close file
	ifs.close();
	return true;
}


int main()
{
	//path(directory of folder, file)
	LoadFile("C:/Users/askit/source/repos/FileSystem/Data/SimpleData.txt");
	LoadFile("./Data/SimpleData.txt");
	LoadFile("Data/SimpleData.txt");
}