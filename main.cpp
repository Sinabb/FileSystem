#include <iostream>
#include <fstream>
#include <vector>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:
	Monster(std::string name, int level, int hp,int mp): mName{name},mLevel{level},mHP{hp},mMP{mp}
	{
	}
	friend std::ostream& operator <<(std::ostream& os, Monster m)
	{
		os << m.mName << ":" << m.mLevel << "," << m.mHP << "," << m.mMP;
		return os;
	}
};


bool LoadFile(const std::string& filename,std::vector<Monster>)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename);
		char ch;
		while (ifs.get(ch))
		{
			std::cout << ch;
		}
		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << std::endl << e.code() << "," << e.what() << std::endl;
		ifs.close();
		return false;
	}

	return true;
}


int main()
{
	//path(directory of folder, file)
	/*LoadFile("C:/Users/askit/source/repos/FileSystem/Data/SimpleData.txt");
	LoadFile("./Data/SimpleData.txt");*/
	std::vector<Monster> monsters;
	//LoadFile("Data/SimpleData.txt", monsters);

	for (const auto& e:monsters)
	{
		std::cout << e << std::endl;
	}
}

/*
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
	
	// close file
ifs.close();
return true;
}
*/