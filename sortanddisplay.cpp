#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>

const int SETP = 2;
const int SETW = 2;
const int INDENT = 4;
const int BUF_SIZE = 3;
const int DASHES = 80;

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
void sort(const std::vector<Alignment> & vec, int n, mypq_type & pq);
void display(const mypq_type & pq, const int & flag);


int main ()
{
    std::vector<Alignment> v;
    double scores[] = { 345.14, 308.05, 124.76 };
    std::string ref[] = { "ATGCAGTCGAGCTABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBATGCAGTCGAGCTABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", "AGCTCCAGCAT", "ACGCGAGSTCA" };
    std::string query[] = { "ATGCTAGCATCGATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCATGCTAGCATCGATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", "AGCTCGATCGA", "AGCGCAGTGAA" };
    std::string desc[] = { ">gi|89036899|ref|NT_113923.1| Homo sapiens unplaced genomic contig, GRCh37.p13 Primary Assembly", "Kiwi", "Strawberry" };
    for(int i = 0; i < BUF_SIZE; ++i)
    {
        v.push_back(Alignment(scores[i], ref[i], query[i], desc[i]));
    }
    mypq_type mypq;
    sort(v, BUF_SIZE, mypq);

    mypq_type mypq_temp = mypq;
    display(mypq_temp, 1);
  return 0;
}

void sort(const std::vector<Alignment>&vec, int n, mypq_type &pq)
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

void display(const mypq_type & pq, const int & flag)
{
        mypq_type temp_pq = pq;
        /*Transfer contents of pq into stack*/
        std::stack<Alignment> top_list;
        std::stack<Alignment> temp_s;
        while(!temp_pq.empty())
        {       temp_s.push(temp_pq.top());
                top_list.push(temp_pq.top());
                temp_pq.pop();
        }
        std::cout << std::endl;
        
        if(flag == 0)
        {
            int size = top_list.size();
            std::stringstream ss;
            ss << size;
            std::string str_size;
            ss >> str_size;
            int setw1 = str_size.length();
            
            std::stringstream ss1;
            double max = top_list.top().score;
            ss1 << max;
            ss1 >> str_size;
            int setw2 = str_size.length() + 3;
            std::cout << str_size << "\n";
            
            // printing out #,score, and description
            for(int i = 0; i < size; ++i)
            {
                Alignment temp = top_list.top();
                std::cout << std::setw(setw1) << i + 1 << ". ";
                std::cout << std::left;
                std::cout << std::setw(setw2);
                std::cout << std::setprecision(2) << std::fixed;
                std::cout << temp.score <<  " * " << temp.description << "\n";
                top_list.pop();
            }

        }
        else if(flag == 1)
        {
            int size = top_list.size();
            std::stringstream ss;
            ss << size;
            std::string str_size;
            ss >> str_size;
            int setw1 = str_size.length();
            
            std::stringstream ss1;
            double max = top_list.top().score;
            ss1 << max;
            ss1 >> str_size;
            int setw2 = str_size.length();
            std::cout << str_size << "\n";
            // printing out #,score, and description
            for(int i = 0; i < size; ++i) {
                Alignment temp = top_list.top();
                std::cout << std::setw(setw1) << i + 1 << " * ";
                std::cout << std::left;
                std::cout << std::setw(setw2);
                std::cout << std::setprecision(2) << std::fixed;
                std::cout << temp.score <<  " * " << temp.description << "\n";
                int i = 0;
                int j = 0;
                // printing out the ref and query
                for (; i < temp.ref_alignment.size(); i++) {
                    if (i > 0 && i % 80 == 0) {
                        std::cout << "\n";
                        for(; j < i; j++) {
                            std::cout << temp.query_alignment.substr(j,1);
                        }
                        std::cout << "\n" << "\n";
                    }
                    std::cout << temp.ref_alignment.substr(i,1);
                }
                if ( i != j) {
                    std::cout << "\n";
                    for(;j<i ;j++) {
                        std::cout << temp.query_alignment.substr(j,1);
                    }
                }
                std::cout << "\n";
                top_list.pop();
                for(int j = 0; j < DASHES; ++j)
                    std::cout << "-";
                std::cout << "\n";
            }
        }
}


