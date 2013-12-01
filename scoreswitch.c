#include <iostream>

using namespace std;
float emptypenalty(bool consec)
{
	if(consec)
	{
		return -0.05;
	}
	consec = true;
	return -0.2;
}

float newscore(char a, char b, bool consec)
{
	switch(a)
	{
		/*
		if ( a == ' ')
		{
			return emptypenalty(consec);
		} 
		*/
		//consec = false;
		case 'A':
			switch(b)
			{
				case 'A': return 1;
				break;
				case 'C': return -0.1;
				break;
				case 'T': return -0.15;
				break;
				case 'G': return -0.1;
				break;
				default: break;
			}
		break;
		case 'C':
			switch(b)
			{
				case'A': return -0.1;
				break;
				case 'C': return 1;
				break;
				case 'T': return -0.1;
				break;
				case 'G': return -0.15;
				break;
				default: break;
			}
		break;
		case 'T':
			switch(b)
			{
				case'A': return -0.15;
				break;
				case 'C': return -0.1;
				break;
				case 'T': return 1;
				break;
				case 'G': return -0.1;
				break;
				default: break;
			}
		break;
		case 'G':
			switch(b)
			{
				case 'A': return -0.1;
				break;
				case 'C': return -0.15;
				break;
				case'T': return -0.1;
				break;
				case 'G': return 1;
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
	float** scoretable = new float*[Q.size()];
	for(int i = 0 ; i < Q.size(); i++)
	{
		scoretable[i] = new float[R.size()];
	}
	char a = 'A';
	char c = 'C';
	char t = 'T';
	char g = 'G';
	
	cout << a << ' ' << c << ' ' << newscore(a,c, consec) << endl;
	cout << c << ' ' << a << ' ' << newscore(c,a, consec) << endl;
	
	cout << a << ' ' << t << ' ' << newscore(a,t, consec) << endl;
	cout << t << ' ' << a << ' ' << newscore(t,a, consec) << endl;
	cout << a << ' ' << g << ' ' << newscore(a,g, consec) << endl;
	cout << g << ' ' << a << ' ' << newscore(g,a, consec) << endl;
	
	cout << a << ' ' << a << ' ' << newscore(a,a, consec) << endl;
	
	cout << endl;
	//
	
	cout << c << ' ' << t << ' ' << newscore(c,t, consec) << endl;
	cout << t << ' ' << c << ' ' << newscore(t,c, consec) << endl;
	cout << c << ' ' << g << ' ' << newscore(c,g, consec) << endl;
	cout << g << ' ' << c << ' ' << newscore(g,c, consec) << endl;
	
	cout << c << ' ' << c << ' ' << newscore(c,c, consec) << endl;
	
	cout << endl;
	//
	

	cout << t << ' ' << g << ' ' << newscore(t,g, consec) << endl;
	cout << g << ' ' << t << ' ' << newscore(g,t, consec) << endl;
	
	cout << t << ' ' << t << ' ' << newscore(t,t, consec) << endl;
	
	cout << endl;
	//
	
	cout << g << ' ' << g << ' ' << newscore(g,g, consec) << endl;
	
	
	return 0;
}
