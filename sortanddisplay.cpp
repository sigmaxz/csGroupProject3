#ifndef SORTANDDISPLAY
#define SORTANDDISPLAY

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int UNDERSCORES = 80;

struct Alignment
{
    double score;
    std::string ref_alignment;
    std::string query_alignment;
    std::string description;
    
    Alignment(const double & score, const std::string & ref, const std::string & que, 
                const std::string & des)
    :score(score), ref_alignment(ref), query_alignment(que), description(des)
    {}
};




bool operator<(const Alignment& lhs, const Alignment& rhs)
{
    return lhs.score < rhs.score;
}
bool operator>(const Alignment& lhs, const Alignment& rhs)
{
    return lhs.score > rhs.score;
}
typedef std::priority_queue<Alignment,std::vector<Alignment>,std::greater<Alignment> > mypq_type;
void pqsort(const std::vector<Alignment> & vec, int n, mypq_type & pq);
void display(const mypq_type & pq, const int & flag);

class SortAlignments
{
public:
	mypq_type pq;

	void pqsort(std::vector<Alignment> vec, int n)
	{
		int i = 0;
		// fills the priority queue to the input size n
		while(pq.size() < n) 
		{
			pq.push(vec[i]);
			i++;
		}
		// goes through the rest of the vector and if it belongs in priority queue, then insert
		for(; i < vec.size(); i++)
		{
			if(vec[i].score > pq.top().score)
			{ 
				pq.pop();
				pq.push(vec[i]);
			}
		}
	}

	void display(const int & flag)
	{
        mypq_type temp_pq = pq;
        /*Transfer contents of pq into stack*/
        std::stack<Alignment> top_list;
        while(!temp_pq.empty())
        { 
             top_list.push(temp_pq.top());
             temp_pq.pop();
        }
        int size = top_list.size();         //size of the stack for top k_organisms.
        std::string str_size;               //string type of the size.
        int setw1 = 0;
        int setw2 = 0;
        std::stringstream ss;               /*Convert int size to string type*/ 
        ss << size;                         
        ss >> str_size;                     
        setw1 = str_size.length();  
        ss.str(std::string());    

        double top_num = top_list.top().score;
        std::ostringstream oss;
        oss << top_num;
        str_size = oss.str();
        setw2 = str_size.length();

        for(int i = 0; i < size; ++i)
        {
            Alignment temp = top_list.top();
			std::cout << std::left;
            std::cout << std::setw(setw1) << i + 1 << " * ";
            std::cout << std::left;
            std::cout << std::setw(setw2);
            std::cout << std::setprecision(2) << std::fixed;
            std::cout << temp.score << " * " << temp.description << "\n";
            if(flag == 1)
            {
                int k = 0;
                int j = 0;
                for(; j < temp.ref_alignment.size(); ++j) {
                    if(j > 0 && j % 80 == 0) {
                        std::cout << "\n";
                        for(; k < j; k++) {
                            std::cout << temp.query_alignment.substr(k, 1);
                        }
                        std::cout << std::endl << std::endl;
                    }
                    std::cout << temp.ref_alignment.substr(j, 1);
                }
                if(j != k)
                {   
                    std::cout << "\n";
                    for(; k < j; ++k)
                    {
                        std::cout << temp.query_alignment.substr(k, 1);
                    }
                }
                std::cout << "\n";
                top_list.pop();
                for(int a = 0; a < UNDERSCORES; ++a)
                    std::cout << "_";
                std::cout << std::endl;
            }
            else
                top_list.pop();
			std::cout << std::endl;
        }
	}
};

void command_line(int argc, char ** argv, string & file1 , string & file2, string & file3, int & k_organisms, int & flag )
{

    file1 = "short_v.txt";
    file2 = "query.txt";
    file3 = "scorefile.txt";
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

void initS( double (& sarr)[18] ,ifstream &in)
{
    double temp;
    for(size_t i = 0; i < 18; i++)
    {
        if(!in.good())
        {
            std:cout<< "error score grab\n";
        }
        else
        {
            in >> temp;
            sarr[i] = temp;
        }
    }
}

float newscore(char a, char b ,float (&sarr)[18])
{
    switch(a)
    {
        case 'A':
            switch(b)
            {
                    case 'A': return sarr[0];
                    break;
                    case 'C': return sarr[1];
                    break;
                    case 'T': return sarr[2];
                    break;
                    case 'G': return sarr[3];
                    break;
                    default: break;
            }
        break;
        case 'C':
                switch(b)
                {
                        case'A': return sarr[4];
                        break;
                        case 'C': return sarr[5];
                        break;
                        case 'T': return sarr[6];
                        break;
                        case 'G': return sarr[7];
                        break;
                        default: break;
                }
        break;
        case 'T':
                switch(b)
                {
                        case'A': return sarr[8];
                        break;
                        case 'C': return sarr[9];
                        break;
                        case 'T': return sarr[10];
                        break;
                        case 'G': return sarr[11];
                        break;
                        default: break;
                }
        break;
        case 'G':
                switch(b)
                {
                        case 'A': return sarr[12];
                        break;
                        case 'C': return sarr[13];
                        break;
                        case'T': return sarr[14];
                        break;
                        case 'G': return sarr[15];
                        break;
                        default: break;
                }
        break;
        default: break;
    }
}
#endif
