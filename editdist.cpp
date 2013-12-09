#ifndef EDITDIST
#define EDITDIST
#include "file.h"
#include "sortanddisplay.h"
#include <cmath>

class EditDist
{
		vector<Alignment> alignments;
        string r;
        string q;
		string description;
        int size_r;
        int size_q;
        float **M;
        float **M_down;
        float **M_right;
        double v[5][5]; //Matrix/2D array of similarity score
		float gi;
		float gc;

		string A;
		string B;
		vector <string> R; //TODO: check if used
		vector <string> Q;

public:
        EditDist(string r, string q, string d, vector<Alignment> &alignments, double score[18])
                : r(r), q(q), size_r(r.size()), size_q(q.size()), description(d), alignments(alignments)
        {
                M = new float*[size_r+1];
                M_down = new float*[size_r+1];
                M_right = new float*[size_r+1];

                for(int i = 0; i < size_r+1; ++i)
                {        
                        M[i] = new float [size_q+1];
                        M_down[i] = new float [size_q+1];
                        M_right[i] = new float [size_q+1];
                }
				
				v[0][0] = -0.2f; v[0][1] = -0.2f; v[0][2] = -0.2f; v[0][3] = -0.2f; v[0][4] = -0.2f;
				v[1][0] = -0.2f; v[1][1] = score[0]; 	v[1][2] = score[1]; v[1][3] = score[2]; v[1][4] = score[3];
				v[2][0] = -0.2f; v[2][1] = score[4]; 	v[2][2] = score[5]; v[2][3] = score[6]; v[2][4] = score[7];
				v[3][0] = -0.2f; v[3][1] = score[8]; 	v[3][2] = score[9]; v[3][3] = score[10]; v[3][4] = score[11];
				v[4][0] = -0.2f; v[4][1] = score[12]; 	v[4][2] = score[13]; v[4][3] = score[14]; v[4][4] = score[15];

				gi = (float)score[16];
				gc = (float)score[17];

        }

		~EditDist()
		{
			for(int i = 0; i < size_r; ++i)
			{
				delete [] this->M[i];
				delete [] this->M_down[i];
				delete [] this->M_right[i];
			}
			delete [] M;
			delete [] M_down;
			delete [] M_right;
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
					cerr << "Invalid string " << tmp << " " << r[index-5] << r[index-4] <<  
					r[index-3] << r[index-2] << r[index-1] << r[index] << r[index+1] << r[index+2] << r[index+3] << r[index+4] << r[index+5]<<endl;
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
                    cerr << "Invalid string " << tmp << " " << q[index-5] << q[index-4] <<  
                    q[index-3] << q[index-2] << q[index-1] << q[index] << q[index+1] << q[index+2] << q[index+3] << q[index+4] << q[index+5]<<endl;
                    exit(0);
                }
            }
        }

        float max(float x, float y, float z)
        {
                float m = x;
                if(y > m)
                    m = y;
                if(z > m)
                    m = z;
                return m;
        }


        void bestSequence()
        {
            float current_total = 0;
            float down1 = 0;
            float down2 = 0;
            float right1 = 0;
            float right2 = 0;
            float nogap1 = 0;
            float nogap2 = 0;
            float nogap3 = 0;
            float down = 0;
            float right = 0;
            float max_nogap = 0;

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

        Alignment findHightestScore()
        {
        	int tsize_r = r.size();
			int tsize_q = q.size();
            float highestscore = -99999999999999999999.0f;
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
			
			findLongestString(r_end,q_end);
			Alignment currentMatch((double)highestscore, A, B, description);

				
            return currentMatch;
		}

        void findLongestString(int r_end, int q_end)
        {
            int i = r_end;
            int j = q_end;
					
			A += r[i-1];
			B += q[j-1];
			--i;
			--j;
			//int id = 0;
			while(i >= 0 && j >= 0 && M[i][j] > 0)
			{
				//no gap
				//float a = max(M[i-1][j-1] + v[ L(true, i-1)][L(false, j-1)],
				//	M_down[i][j],
				//	M_right[i][j]);

				////gap in query
				//float b = max(M_right[i][j-1] - gc,
				//					M[i][j-1] - gi,
				//				    -99999.0f);
				////gap in ref
				//float c = max(M_down[i-1][j] - gc, 
				//				    M[i-1][j] - gi, 
				//				    -99999.0f);
				float a = M[i-1][j-1];
				float b = M_right[i][j];
				float c = M_down[i][j];
				//
				float _max = max(a, b, c);
				if(_max == a)
				{
					A += r[i-1];
					B += q[j-1];
					--i;
					--j;
				}
				else if (_max == b)
				{
								
					B += '-';
					A += q[j-1];
					if(i > 0)
						--i;
				}
				else //max == c
				{
								
					B += r[i-1];
					A += '-';
					if(j > 0)
						--j;
				}
			} 
					
			////TODO: remove cout statements
   //         cout << "ref :   " << endl;
			////cout << A << endl;
			//			
			//string tmpA;
			//string tmpB;
			//int k = 0;
   //         for(string::reverse_iterator it = A.rbegin(); it != A.rend(); ++it)
			//{
			//	tmpA[k] = *it;
			//}
			//A = tmpA;
   ////                 cout << *it;
   ////         cout << endl;

   ////         cout << "query : " << endl;
			//////cout << B << endl;
			//k = 0;
   //         for(string::reverse_iterator it = B.rbegin(); it != B.rend(); ++it)
			//{   tmpB[k] = *it; }
			//B = tmpB;
   //         cout << endl;
        }
};

#endif
