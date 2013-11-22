#include <iostream>
#include <vector>
#include "file.h"

using namespace std;

void command_line(int argc, char ** argv, string & file1, string & file2, int & k_organisms, int & flag);

int main(int argc, char** argv)
{
    
    string file1, file2;
    int k_organisms, alignment_flag;
    command_line(argc, argv, file1, file2, k_organisms, alignment_flag);
    //cout << file1 << " " << file2 << " " << k_organisms << " " << alignment_flag << endl;

    File dna_sequence(file1);
    File query(file2);
    dna_sequence.read_file(file1);
    query.read_file(file2);

    vector<string> content;

    return 0;
}

void command_line(int argc, char ** argv, string & file1 , string & file2, int & k_organisms, int & flag )
{
//change default text to input.txt when finished testing
	file1 = "short_v.txt";
	file2 = "query.txt";
	k_organisms = 100;
	flag = 1;

	for(int i = 1; i < argc; i++)
	{
			if(*(argv[i]) == 'd')
			{
				file1 = argv[i+2];
			}
			else if(*(argv[i]) == 'q')
			{
				file2 = argv[i+2];
			}
			else if(*(argv[i]) == 'n')
			{
				string ks = (argv[i+2]);
				k_organisms = atoi(ks.c_str());
			}
			else if(*(argv[i]) == 'a')
			{
				string fs = (argv[i+2]);
				flag = atoi(fs.c_str());
			}
			else
				cout << "error" << endl;
	
			i = i+2;
	}

}


