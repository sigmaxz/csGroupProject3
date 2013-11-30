#include <iterator>
#include <cstdlib>
#include "file.h"

File::File()
:file_name("default.txt")
{}

File::File(const std::string & file_name)
:file_name(file_name)
{}

File::File(const std::string & file_name, const std::string & content)
:file_name(file_name), content(content)
{}

std::string File::get_file_name()
{
    return file_name;
}

std::string File::get_file_content()
{
    return content;
}

std::string File::get_query()
{
	return query;
}
void File::set_file_name(const std::string & new_file_name)
{
    file_name = new_file_name;
    return;
}
void File::set_content(std::string new_content)
{
	
    content = new_content;
    return;
}

void File::read_file(char *file_name)
{
	std::ifstream file(file_name, std::ios::in);
	if(file)
	{
		std::string file_content;
		file.seekg(0, std::ios::end);
		file_content.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&file_content[0], file_content.size());
		file.close();
		content = file_content;
		std::cout << content.size() << std::endl;

		int i = 0; 
		while(file_content[i] != 13 && file_content[i] != 10)
			++i;

		description = content.substr(0, i);

	
		for(; i < file_content.size(); ++i)
		{
			if(file_content[i] != ' ' && file_content[i] != 10 && file_content[i] != 13 && file_content[i] != 0)
				reference += file_content[i];
		}

	}
}



void File::read_query(const std::string & file_name)
{
	std::ifstream in;
	in.open(file_name.c_str());
    if(!in)
    {
        std::cout << "Could not open file for reading!" << std::endl;
        exit(1);
    }
	std::string line;
	while(!in.eof())
	{
		getline(in, line);
		if(line.size() > 1)
		{
			query += line;
		}
	}

}

void File::write_file(const std::string & file_name)
{
    std::ofstream out;
    out.open(file_name.c_str());
    if(!out)
    {
        std::cout << "Cannot open file for writing!" << std::endl;
        exit(1);
    }
    std::string str;
}

//std::ofstream& operator<<(std::ofstream& ofs, const File& myFile)
//{}
//
//std::fstream& operator>>(std::fstream& fs, const File& myFile)
//{}
