#include <iostream>
#include <string>

using namespace std;
void command_line(int argc, char ** argv, string & file1 , string & file2, int & k_organisms, int & flag )
{

	file1 = "short_v.txt";
	file2 = "query.txt";
	file3 = "score.txt";
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
			else if(*(argv[i]) == 's')
			{
				file3 = argv[i+2];
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
			else if(argc == 5 || argc == 6) 
			{
				file1 = argv[1];
				file2 = argv[2];
				k_organisms = atoi(argv[3]);
				flag = atoi(argv[4]);
				if(argc == 6)
				{
					file3 = argv[5];
				}
			}


			else
				cout << "error" << endl;
	
			i = i+2;
	}

}
int main( int argc, char** argv)
{
	string file1,file2,file3;
	int k_organisms, flag;	
	command_line(argc, argv, file1, file2,file3, k_organisms, flag);
	cout << file1 << " " << file2 << " " << k_organisms << " " << flag;

	return 0;
}
