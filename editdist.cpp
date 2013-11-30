#include "file.h"
#include <string>
#include <iostream>

using namespace std;

//void findLongestString(int r_end, int q_end);

//string r = "AAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGTAAACCCGGGT";
//string q =        "GGTAAACCCGGGTAAACCCTGGTAAACCCTGGTAAACCCTGGTAAACCCTGGTAAACCCTGGTAAACCCTGGTAAACCCTGGTAAACCCT";
//const int size_r = 100;
//const int size_q = 90; 

//string r = "AACCTGACATCTT";
//string q = "CCAGCGTCAACTT";
//const int size_r = 13;
//const int size_q = 13;

//string r = "AACCTGAC";
//string q = "CCAGCGTC";

//string r = "AGCT"; //reference sequence    AGC
//string q = "ACGT"; //query sequence        A-C
//const int size_r = 4;
//const int size_q = 4;


//string r = "AGCT"; //reference sequence
//string q = "AGC"; //query sequence
//const int size_r = 4;
//const int size_q = 3;

//string r = "AACCTT";
//string q = "AT";
//const int size_r = 6;
//const int size_q = 2;

class EditDist
{
	string r;
	string q;
	int size_r;
	int size_q;
	double **M;
	double **M_down;
	double **M_right;
	double v[5][5]; //Matrix/2D array of similarity score
	//double M[(size_r+1)][(size_q+1)]; //Matrix/2D array of edit-distance scores
	//double M_down[size_r+1][size_q+1];
	//double M_right[size_r+1][size_q+1];
public:
	EditDist(string r, string q)
		: r(r), q(q), size_r(r.size()), size_q(q.size()) 
	{
		M = new double*[size_r+1];
		M_down = new double*[size_r+1];
		M_right = new double*[size_r+1];

		for(int i = 0; i < size_r+1; ++i)
		{	
			M[i] = new double [size_q+1];
			M_down[i] = new double [size_q+1];
			M_right[i] = new double [size_q+1];
		}
	}

	void init()
	{ 
			v[0][0] = -0.2;    v[0][1] = -0.2;  v[0][2] = -0.2;  v[0][3] = -0.2;  v[0][4] = -0.2;
			v[1][0] = -0.2;    v[1][1] =  1;    v[1][2] = -0.1;  v[1][3] = -0.1;  v[1][4] = -0.15;
			v[2][0] = -0.2;    v[2][1] = -0.1;  v[2][2] = 1;     v[2][3] = -0.15; v[2][4] = -0.1;
			v[3][0] = -0.2;    v[3][1] = -0.1;  v[3][2] = -0.15; v[3][3] = 1;     v[3][4] = -0.1;        
			v[4][0] = -0.2;    v[4][1] = -0.15; v[4][2] = -0.1;  v[4][3] = -0.1;  v[4][4] = 1;                
	}

	void printSimScore()
	{
		for(int x = 0; x < 5 ; ++x)
		{
			for(int y = 0; y < 5; ++y)
			{
					cout << v[x][y] << '\t';
			}
			cout << endl;
		}
	}

	void printEditDistMatrix()
	{
		for(int i = 0; i < (size_r+1); ++i){
			for(int j = 0; j < (size_q+1); ++j){
					cout << M[i][j] << '\t';}
			cout << endl << endl;}
	}

	void printDownMatrix()
	{
		for(int i = 0; i < (size_r+1); ++i){
			for(int j = 0; j < (size_q+1); ++j){
					cout << M_down[i][j] << '\t';}
			cout << endl << endl;}
	}

	void printRightMatrix()
	{
		for(int i = 0; i < (size_r+1); ++i){
			for(int j = 0; j < (size_q+1); ++j){
					cout << M_right[i][j] << '\t'; }
			cout << endl << endl;}
	}

	//converts DNA letter in string to appropriate int value;
	//isreference_file is true if the string is part of the reference file
			//and false if it is the query file
	int L(bool isreference_file, int index)
	{        
			if(isreference_file)
			{
					switch(r[index])
					{
					case 'A':
							return 1;
							break;
					case 'G':
							return 2;
							break;
					case 'C':
							return 3;
							break;
					case 'T':
							return 4;
							break;
					default:
							string tmp = isreference_file ? "true" : "false";
							cerr << "Invalid string " << tmp << " " << index<< endl;
							cerr << r[index] << endl;
							exit(0);
					}
			}
			else
			{
					switch(q[index])
					{
					case 'A':
							return 1;
							break;
					case 'G':
							return 2;
							break;
					case 'C':
							return 3;
							break;
					case 'T':
							return 4;
							break;
					default:
							string tmp = isreference_file ? "true" : "false";
							cerr << "Invalid string " << tmp << " " << index<< endl;
							exit(0);
					}
			}        
	}

	double max(double x, double y, double z)
	{
			double m = x;
			if(y > m)
					m = y;
			if(z > m)
					m = z;
			return m;
	}


	void bestSequence()
	{
		//int size_q = q.size();
		//int size_r = r.size();

		double current_total = 0;

		double gi = 0.2; //Penalty for introducing a gap
		double gc = 0.05; //Penalty for each additional gap added.

		double down1 = 0;
		double down2 = 0;
		double right1 = 0;
		double right2 = 0;
		double nogap1 = 0;
		double nogap2 = 0;
		double nogap3 = 0;
		double down = 0;
		double right = 0;
		double max_nogap = 0;

		for(int i = 0; i < size_r+1; ++i)
		{
			M[i][0] = 0;
			M_down[i][0] = 0;
			M_right[i][0] = 0;
		}
		for(int j = 0; j < size_q+1; ++j)
		{
			M[0][j] = 0;
			M_down[0][j] = 0;
			M_right[0][j] = 0;
		}
	
		for(int i = 1; i < size_r+1; ++i)
		{
			for(int j = 1; j < size_q+1; ++j)
			{
				down1 = M_down[i-1][j] - gc;
				down2 = M[i-1][j] - gi;
				down = down1 > down2 ? down1 : down2;
				M_down[i][j] = down;

				right1 = M_right[i-1][j] -gc;
				right2 = M[i-1][j] -gi;
				right = right1 > right2 ? right2 : right2;
				M_right[i][j] = right;

				nogap1 = M[i-1][j-1] + v[ L(true, i-1)][L(false, j-1)];
				nogap2 = M_down[i][j];
				nogap3 = M_right[i][j];
				max_nogap = max(nogap1, nogap2, nogap3);
				M[i][j] = max_nogap;
			}
		}
	}

	double findHightestScore()
	{
			int tsize_r = r.size();
			int tsize_q = q.size();
			double highestscore = -9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.0;
			int r_end = -1;
			int q_end = -1;
			for(int i = 1; i < tsize_r+1; ++i)
			{
					for(int j = 1; j < tsize_q+1; ++j)
					{
							if(M[i][j] > highestscore)
							{
									highestscore = M[i][j];
									r_end = i;
									q_end = j;
							}
					}
			}

			//findLongestString(r_end,q_end);
			return highestscore;
	}

	void findLongestString(int r_end, int q_end)
	{
			//find the strings of longest sequence
			string A = "";
			string B = "";
			int i = r_end;
			int j = q_end;

			while(i > 0 || j > 0)
			{
					if(i > 0 && j > 0 )//&& M[i-1][j-1] + v[ L(1,i) ][ L(0,j) ] == M[i][j] )
					{
							A+=q[i];
							B+=r[j];
							--i;
							--j;
					}
					else if(i > 0 )//&& M[i][j] == M[i-1][j] + v[i][0])
					{
							A+= r[i];
							B+= '_';
							--i;
					}
					else //if(j > 0 && M[i][j] == M[i][j-1] + v[0][j])
					{
							A+='_';
							B+=r[j];
							--j;
					}                
			}
			cout << "ref :   ";
			for(string::reverse_iterator it = A.rbegin(); it != A.rend(); ++it)
				cout << *it;
			cout << endl;

			cout << "query : ";
			for(string::reverse_iterator it = B.rbegin(); it != B.rend(); ++it)
				cout << *it;
			cout << endl;
	}
};

int main()
{        
		//File dna("input.txt");
		//dna.read_file("input.txt");

		File dna("test.txt");
		dna.read_file("test.txt");
		dna.read_query("querytest.txt");

		////test sequences give by TA on Ileran.   best alignment score is 7.35
		//File dna("tatestref.txt");             //Instanciate File Input class
		//dna.read_file("tatestref.txt");        //Parse reference file
		//dna.read_query("tatestquery.txt");     //Parse query file
		
		int ref_size = dna.getRefSize();       //the length of the DNA reference sequence (white space have been removed) 
		int query_size = dna.getQuerySize();   //the length of the DNA query sequence
	
		int num_divs = 4;           //currently hard coded value for the number strings/sequences the reference sequence gets split into
		double sub_string_size_d = ref_size/num_divs;   //length of each partial ref sequence gets split into (as a double)
		int sub_string_size = ceil(sub_string_size_d);  //length of each partial ref sequence gets split into (as a int)

		vector <int> ref_sub_string_start;              //vector storing the starting indices for each partial ref sequence
		vector <int> ref_sub_string_end;                //vector storing the ending indices for each partial ref sequence
		vector <string> ref_sub_strings;                


		//sequences are small enough that they don't need to be split up
		if(ref_size < 1000000 || query_size >= ref_size / 2) 
		{
			ref_sub_string_start.push_back(0);
			ref_sub_string_end.push_back(ref_size-1);

			num_divs = 1;
			ref_sub_strings.push_back( dna.getReference());
		}
		//sequences are large enough that they need to be split up
		else
		{
			//non looping way to find the starting and ending indices for the split ref sequences 
			ref_sub_string_start.push_back(0);
			ref_sub_string_end.push_back(sub_string_size-1 + query_size);

			ref_sub_string_start.push_back(sub_string_size-1);
			ref_sub_string_end.push_back(2*sub_string_size-1 + query_size);

			ref_sub_string_start.push_back(2* sub_string_size-1);
			ref_sub_string_end.push_back(3 * sub_string_size-1 + query_size);

			ref_sub_string_start.push_back(3 * sub_string_size-1);
			ref_sub_string_end.push_back(4 *sub_string_size -1);
		
			////lopping way to find the starting and ending indices for the split ref sequences 
			//for(int i = 0; i < num_divs; ++i)
			//{
			//	ref_sub_string_start.push_back(i * sub_string_size);
			//	ref_sub_string_end.push_back(i * sub_string_size + sub_string_size + query_size);
			//}
		
			
			for(int i = 0; i < num_divs; ++i)
			{
				string ref_tmp = dna.getReference();
				string tmp;
				for( int j = ref_sub_string_start[i]; j < ref_sub_string_end[i]; ++j)
				{
					tmp += ref_tmp[j];
				}
				ref_sub_strings.push_back(tmp);
			}
		}
		cout << "starting const()" << endl;
		EditDist fd(ref_sub_strings[0], dna.get_query());
		cout << "ending const()" << endl;

		cout << "starting init()" << endl;
        fd.init();
		cout << "ending init()" << endl;
        //cout << endl;
        //cout << "similiarty score matrix" << endl;
        //fd.printSimScore();
        //cout << endl;
		//cout << dna.getContentSize() << endl;

		cout << "starting bestSequence()" << endl;
        fd.bestSequence();
		cout << "finshish bestSequence()" << endl;

		//cout << endl;
		//cout << "edit dist matrix" << endl;
		//printEditDistMatrix();

		//cout << endl;
		//cout << "down matrix" << endl;
		//printDownMatrix();

		//cout << endl;
		//cout << "right matrix" << endl;
		//printRightMatrix();

        cout << endl << "Highest score " << fd.findHightestScore() << endl;
        // findLongestString();   //currently called in findHighestScore();
        
return 0;
}


