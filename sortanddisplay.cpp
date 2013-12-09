#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>

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
void sort(const std::vector<Alignment> & vec, int k_organisms, mypq_type & pq);
void display(const mypq_type & pq, const int & flag);

int flag = 1;
int main ()
{
    std::vector<Alignment> v;
    double scores[] = { 345.14, 308.05, 124.76 };
    std::string ref[] = { "ATGCAGTCGAGCTABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBATGCAGTCGAGCTABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", "AGCTCCAGCAT", "ACGCGAGSTCA" };
    std::string query[] ={"ATGCTAGCATCGATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCATGCTAGCATCGATCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", "AGCTCGATCGA", "AGCGCAGTGAA" };
    std::string desc[] = { ">gi|89036899|ref|NT_113923.1| Homo sapiens unplaced genomic contig, GRCh37.p13 Primary Assembly", "Kiwi", "Strawberry" };
    for(int i = 0; i < BUF_SIZE; ++i)
    {
        v.push_back(Alignment(scores[i], ref[i], query[i], desc[i]));
    }
    mypq_type mypq;
    sort(v, BUF_SIZE, mypq);
    mypq_type mypq_temp = mypq;
    display(mypq_temp, flag);
  return 0;
}

void sort(const std::vector<Alignment>&vec, int k_organisms, mypq_type &pq)
{
    int i = 0;
    // fills the priority queue to the input size of k_organisms
    while(pq.size() < k_organisms)
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
                for(int a = 0; a < DASHES; ++a)
                    std::cout << "-";
                std::cout << "\n";
            }
            else
                top_list.pop();

        }
}



