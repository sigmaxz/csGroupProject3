#include <iterator>
#include <cstdlib>
#include "file.h"

File::File()
:file_name("default.txt")
{}

File::File(const std::string & file_name)
:file_name(file_name)
{}

std::string File::get_file_name()
{
    return file_name;
}

std::string File::get_query()
{
    return query;
}

void File::set_file_name(const std::string & new_file_name)
{
    file_name = new_file_name;
}

void File::read_file(const char *file_name)
{
        std::ifstream file(file_name, std::ios::in);
        if(file)
        {
        		//read in the entire contents of the reference file into one string
                std::string file_content;
                file.seekg(0, std::ios::end);
                file_content.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                file.read(&file_content[0], file_content.size());
                file.close();
              
              	//std::cout << "file_content size " << file_content.size() << std::endl;
                unsigned int i = 0;      //current location/index of file_content
             	unsigned int file_size = file_content.size();
             	
             	//make sure the index is at the start of the first description
             	while( file_content[i] != '>')
             		++i;
             	
             	//parse the string holding the entire file content
             	while( i < file_size)
             	{
             		unsigned int d_start = i; //starting index of description
             		std::string tmp_d;     //tmp string holding the current description being parsed
                	
                	//parse current description and insert it into the vector
                	while(file_content[i] != 13 && file_content[i] != 10 )
                	{
                        tmp_d += file_content[i];
                        ++i;
                    }
					descriptions.push_back(tmp_d);
					
					++i; //skip past end line char

					//parse current DNA sequence and insert it into the vector
					std::string tmp_reference;     //tmp string holding the current DNA sequence being parsed
                	while(file_content[i] != 13 && file_content[i] != 10)
                	{
                        if(file_content[i] != ' ' && file_content[i] != 10 && file_content[i] != 13 && file_content[i] != 0)
                        {
                        	tmp_reference += file_content[i];
                        }
                        ++i;
                	}	
                	reference.push_back(tmp_reference);
                	++i;
               	}
        }
        else
        {
        	std::cerr << "error reading file" << std::endl;
        	exit(0);
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

//returns the string of a DNA sequence 
std::string File::getReference(int index)
{
	return reference[index];
}

//returns the string of a description
std::string File::getDescription(int index)
{
	return descriptions[index];
}

int File::getRefSize()
{
	return reference.size();
}

int File::getQuerySize()
{
	return query.size();
}

int File::getLengthOfRefString(int index)
{
	return reference[index].size();
}


//std::ofstream& operator<<(std::ofstream& ofs, const File& myFile)
//{}
//
//std::fstream& operator>>(std::fstream& fs, const File& myFile)
//{}

