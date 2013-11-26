#include <iterator>
#include "file.h"
//input.txt
File::File()
:file_name("default.txt")
{}

File::File(const std::string & file_name)
:file_name(file_name)
{}

File::File(const std::string & file_name, const std::vector<std::string> & content)
:file_name(file_name), content(content)
{}

std::string File::get_file_name()
{
    return file_name;
}

std::vector<std::string> File::get_file_content()
{
    return content;
}
void File::set_file_name(const std::string & new_file_name)
{
    file_name = new_file_name;
    return;
}
void File::set_content(std::vector<std::string> new_content)
{
    content = new_content;
    return;
}

void File::read_file(const std::string & file_name)
{
    std::ifstream in;
    in.open(file_name.c_str());
    if(!in) {
        std::cout << "Could not open file for reading!" << std::endl;
        exit(1);
    }

    std::string first_line, sub_str, full_str = "";
    getline(in, first_line);
    content.push_back(first_line);
    
    while(!in.eof()) {
        getline(in, sub_str);
        if(sub_str.size() != 1) {

            full_str = full_str + sub_str;
        }
    }
    content.push_back(full_str);
    in.close();
}

void File::write_file(const std::string & file_name)
{
    std::ofstream out;
    out.open(file_name.c_str());
    if(!out) {
        std::cout << "Cannot open file for writing!" << std::endl;
        exit(1);
    }
    std::string str;
}
/*Print the file's name and contents*/
void File::print()
{
    std::cout << "File name: " << file_name << std::endl;
    
    for(int i = 1; i <= content.size(), ++i) {
        if(i % 2 == 1)
            std::cout << "Description: " << content[i - 1] << std::endl;
        else
            std::cout << "DNA sequence: " << std::endl << content[i - 1] << std::endl;
    }
}

std::ofstream& operator<<(std::ofstream& ofs, const File& myFile)
{}

std::fstream& operator>>(std::fstream& fs, const File& myFile)
{}
