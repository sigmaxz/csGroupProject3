#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


/* This class will read a file and store the contents of that file
   in a string.
 */
class File
{
    private:
        std::string file_name;
        std::vector<std::string> content;
/*
    May need for handling multiple descriptions of organisms for the
    output.
 */
// vector<string> descriptions
    public:
        File();
        File(const std::string & file_name);
        File(const std::string & file_name, const std::vector<std::string> & content);

        std::string get_file_name();
        std::vector<std::string> get_file_content();
        void set_file_name(const std::string & new_file_name);
        void set_content(std::vector<std::string> new_content);

        void read_file(const std::string & file_name);
        void write_file(const std::string & file_name);

        void print();

};
#endif

std::ostream& operator<<(std::ostream& ofs, const File& myFile);
std::fstream& operator>>(std::fstream& fs, const File& myFile);

