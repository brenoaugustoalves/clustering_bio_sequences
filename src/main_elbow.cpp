/*
	This file uses the header "elbow.h" that uses
	the koolplot library for to plot the graph 
	generated by Elbow method.

	Installation of the koolplot library:
		http://koolplot.codecutter.org/

	Libs for the compilation process using the koolplot library:
		lkoolplot, lbgi, lgdi32, lcomdlg32, luuid, loleaut32, lole32

	Elbow method is a heuristic to discover the number of clusters.
	This may or may not work well in particular because is a heuristic!

	Example of the use of the koolplot:

		const char * header = "Elbow Method";
		char winTitle[120];

		vector<double> v_x, v_y;

		v_x.push_back(2);
		v_x.push_back(3);
		v_x.push_back(4);
		v_x.push_back(5);
		v_x.push_back(6);

		v_y.push_back(0.4);
		v_y.push_back(0.6);
		v_y.push_back(0.8);
		v_y.push_back(0.82);
		v_y.push_back(0.83);

		Plotdata x(v_x), y(v_y);

		sprintf(winTitle, "%s", header);
		plot(x, y, winTitle);
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "elbow.h"
#include "fasta_file.h"

int main()
{
	clock_t begin = clock();

	srand(time(NULL));

	std::string dataset_name("splice.data.600.sequences.fasta");
	FastaFile ff(dataset_name);
	std::vector<std::pair<std::string, std::string> > dataset;

	dataset = ff.getSequences();

	std::vector<std::pair<std::string, std::string> >::iterator it;
	std::vector<std::string> sequences;

	for(it = dataset.begin(); it != dataset.end(); it++)
		sequences.push_back((*it).second);
	
	/*
	KMeans kmeans(3, sequences.size(), sequences.size(),
				  100, sequences, "HAMMING", true, false, false);
	kmeans.run();
	*/

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "\nTime: " << elapsed_secs << " seconds.\n";

	return 0;
}