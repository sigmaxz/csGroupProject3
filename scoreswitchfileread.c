#include <iostream>
#include <fstream>

using namespace std;
double emptypenalty(bool consec) // can be ignored depends on how nick wants penalties
{
        if(consec)
        {
                return -0.05;
        }
        consec = true;
        return -0.2;
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

double newscore(char a, char b, bool consec,double (&sarr)[18])
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



int main()
{
        string R = "AACCTGACATCTT";
        string Q = "CCAGCGTCAACTT";
        bool consec = false;
        ifstream in_score;
        in_score.open("scorefile2.txt"); // default scores in this text file changed to the file variable
        double scores[18] = {0};
        initS(scores, in_score);
        double** scoretable = new double*[Q.size()];
        for(int i = 0 ; i < Q.size(); i++)
        {
                scoretable[i] = new double[R.size()];
        }
        char a = 'A';
        char c = 'C';
        char t = 'T';
        char g = 'G';
        
        //all case test except penalties 
        cout << a << ' ' << c << ' ' << newscore(a,c, consec, scores) << endl;
        cout << c << ' ' << a << ' ' << newscore(c,a, consec, scores) << endl;
        
        cout << a << ' ' << t << ' ' << newscore(a,t, consec, scores) << endl;
        cout << t << ' ' << a << ' ' << newscore(t,a, consec, scores) << endl;
        cout << a << ' ' << g << ' ' << newscore(a,g, consec, scores) << endl;
        cout << g << ' ' << a << ' ' << newscore(g,a, consec, scores) << endl;
        
        cout << a << ' ' << a << ' ' << newscore(a,a, consec, scores) << endl;
        
        cout << endl;
        //
        
        cout << c << ' ' << t << ' ' << newscore(c,t, consec, scores) << endl;
        cout << t << ' ' << c << ' ' << newscore(t,c, consec, scores) << endl;
        cout << c << ' ' << g << ' ' << newscore(c,g, consec, scores) << endl;
        cout << g << ' ' << c << ' ' << newscore(g,c, consec, scores) << endl;
        
        cout << c << ' ' << c << ' ' << newscore(c,c, consec, scores) << endl;
        
        cout << endl;
        //
        

        cout << t << ' ' << g << ' ' << newscore(t,g, consec, scores) << endl;
        cout << g << ' ' << t << ' ' << newscore(g,t, consec, scores) << endl;
        
        cout << t << ' ' << t << ' ' << newscore(t,t, consec, scores) << endl;
        
        cout << endl;
        //
        
        cout << g << ' ' << g << ' ' << newscore(g,g, consec, scores) << endl;
        //penalties 
        cout << scores[16] << " " << scores[17] ;
        
        return 0;
}
