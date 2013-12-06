
 
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
        std::string file_name;                    //name of file
        std::vector<std::string> descriptions;    //vector of c++ strings of descriptions for each gene
        std::vector<std::string> reference;       //vector of c++ string holding the DNA sequence for each gene
        std::string query;                        //the DNA sequence for the query
/*
May need for handling multiple descriptions of organisms for the
output.
*/
// 
    public:
        File();
        File(const std::string & file_name);
 
        std::string get_file_name();
        std::string get_query();
        void set_file_name(const std::string & new_file_name);
        void set_content(std::string new_content);
 
        void read_file(char *file_name);
        void read_query(const std::string & file_name);
        void write_file(const std::string & file_name);
        
        std::string getReference(int index);
        std::string getDescription(int index);
        int getRefSize();
        int getQuerySize();
 
        void print();

                
 
};
#endif

//std::ostream& operator<<(std::ostream& ofs, const File& myFile);
//std::fstream& operator>>(std::fstream& fs, const File& myFile);

 
