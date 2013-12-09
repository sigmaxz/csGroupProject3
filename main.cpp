#include <cmath>
#include "editdist.h"

int main(int argc, char *argv[])
{
	vector<Alignment> alignments;
	SortAlignments pq; //instanstiate the priority queue for sorting alignment scores.
	////code to use command line parameters
	string file1,file2,file3;
    int k_organisms, flag;        
    command_line(argc, argv, file1, file2,file3, k_organisms, flag);
	//TODO: give correct parameters to File class

	File dna(file1); //Instanciate File Input class
    dna.read_file(file1.c_str()); //Parse reference file
    dna.read_query(file2); //Parse query file

	double score[18];
	ifstream fin;
	fin.open(file3);
	initS(score, fin);

    //test sequences give by TA on Ileran. best alignment score is 7.35
    //File dna("chromosomes.txt"); //Instanciate File Input class
    //dna.read_file("chromosomes.txt"); //Parse reference file
    //dna.read_query("input.txt"); //Parse query file

    ////uses chromosomes-small.txt as reference and input.txt as query
    //File dna("chromosomes-small.txt"); //Instanciate File Input class
    //dna.read_file("chromosomes-small.txt"); //Parse reference file
    //dna.read_query("input.txt"); //Parse query file
	//dna.read_query("querytest.txt"); //Parse query fil

	//File dna("chromosomes-small-ta.txt"); //Instanciate File Input class
	//dna.read_file("chromosomes-small-ta.txt"); //Parse reference file
	//dna.read_query("tatestquery.txt"); //Parse query file


	int num_ref = dna.getRefSize();      //the number of DNA seqences
    int query_size = dna.getQuerySize(); //the length of the DNA query sequence

	const int SPLITLENGTH = 400000;   
	const int OVERLAP = 1000;

	//for(int i = 0; i < num_ref; ++i) 
	for(int i= 2; i < 3; ++i)	     //TODO: use other for loop
    {
		int string_size = dna.getLengthOfRefString(i);
		if(string_size > SPLITLENGTH)                                     
		{
			cout << "size of ref : " << i << "  " << string_size << endl;
			int num_splits = ceil((double)string_size / (double)SPLITLENGTH);
			vector<Alignment> tmpalign;
			SortAlignments tmppq; 
			string ref_string = dna.getReference(i);
			int j = 0;
			while(j < num_splits)
			{
				string ref_sub;
				if(j == 0)
				{
					 ref_sub = ref_string.substr(0, SPLITLENGTH-1);
				}
				else if(j > 0 && j < num_splits -1)
				{
					ref_sub = ref_string.substr(  (j)*SPLITLENGTH - OVERLAP - 1 , SPLITLENGTH + 1000);
				}
				else if(j == num_splits-1)
				{
					ref_sub = ref_string.substr( j*SPLITLENGTH -1 , (string_size - 1) - (j*SPLITLENGTH -1) );
				}

				EditDist fd(ref_sub, dna.get_query(), dna.getDescription(i), alignments, score);
				//fd.init();
       			fd.bestSequence();

				Alignment score1 = fd.findHightestScore();
				tmpalign.push_back(score1);
       			cout << i << "-" << j  << endl;
				
				++j;
			}
			tmppq.pqsort(tmpalign, tmpalign.size());
			alignments.push_back(tmppq.pq.top());
		}
		else
		{
			EditDist fd(dna.getReference(i), dna.get_query(),dna.getDescription(i), alignments, score);
			//fd.init();
       		fd.bestSequence();
			Alignment score = fd.findHightestScore();
			alignments.push_back(score);
       		cout << i << endl;
			//fd.printEditDistMatrix();
			//fd.printDownMatrix();
			//fd.printRightMatrix();
		}
	} 
	pq.pqsort(alignments, k_organisms);
	pq.display(flag);
return 0;
}
