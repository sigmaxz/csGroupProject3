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
		std::string description;
        std::string content;
		std::string reference;
		std::string query;
/*
    May need for handling multiple descriptions of organisms for the
    output.
*/
// vector<string> descriptions
    public:
        File();
        File(const std::string & file_name);
        File(const std::string & file_name, const std::string & content);
 
        std::string get_file_name();
        std::string get_file_content();
		std::string get_query();
        void set_file_name(const std::string & new_file_name);
        void set_content(std::string new_content);
 
        void read_file(char *file_name);
		void read_query(const std::string & file_name);
        void write_file(const std::string & file_name);
 
        void print();

		std::string getReference()
		{
			return reference;
		}

		int getRefSize()
		{
			return reference.size();
		}

		int getContentSize()
		{
			return content.size();
		}

		int getQuerySize()
		{
			return query.size();
		}
 
};
#endif

//std::ostream& operator<<(std::ostream& ofs, const File& myFile);
//std::fstream& operator>>(std::fstream& fs, const File& myFile);
 

 
