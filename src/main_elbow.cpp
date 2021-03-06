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
*/

#include <iostream>
#include <time.h>
#include "elbow.h"
#include "fasta_file.h"
#include "common.h"

void run_algorithm(int clusters, std::string & fasta_file, int max_iter = 100,
				   const std::string & method = "LCS", bool kmeansplusplus = true,
				   bool hybrid = false);

int main(int argc, char *argv[])
{
	srand(time(NULL));


	std::string instructions;

	// checks the number of arguments
	if(argc > 1)
	{
		std::string number_clusters(argv[1]);

		if(number_clusters == "help")
		{
			instructions = "\nTwo parameters are required: number of clusters and fasta file.\
								\n\nCommand example 1:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file>\
								\n\n\tmy_executable 3 my_file.fasta\
								\n\nOptional parameters:\
								\n\n\t[max_iterations] -> maximum of iterations, default is 100.\
								\n\n\t[comparison_method] -> method to compare strings, default is LCS.\
								\n\n\t\tMethods available:\
								\n\n\t\tED -> edit distance (levenshtein distance)\
								\n\n\t\tNW -> Needleman-Wunsch (optimal global alignment)\
								\n\n\t\tSW -> Smith-Waterman (optimal local alignment)\
								\n\n\t\tWS -> White-Similarity or Dice's Coefficient (similarity ranking)\
								\n\n\t\tLCS -> Longest Common Subsequence\
								\n\n\t\tHAMMING -> Hamming distance (only for strings of equal length)\
								\n\nCommand example 2:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method]\
								\n\n\tmy_executable 3 my_file.fasta 50 NW\
								\n\nObservation: KMeans++ is used for default.\
								\n\nYou do not want to use the KMeans++? Try this for example:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus]\
								\n\n\tmy_executable 3 my_file_fasta 50 NW 0\
								\n\n\tmy_executable 3 my_file_fasta 50 NW 1\
								\n\nThe number 0 indicates that you not will use KMeans++.\
								\nThe number 1 indicates that KMeans++ will be used.\
								\n\nYou want to use the hybrid clustering? Try this:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus] [uses_hybrid]\
							   	\n\n\tmy_executable 3 my_file.fasta 50 NW 0 1\
							   	\n\n\tExplanation:\
								\n\t\t3 -> number of clusters\
								\n\t\t50 -> maximum iterations\
								\n\t\t0 -> Dont uses KMeans++\
								\n\t\t1 -> Uses the hybrid clustering\n\
							   ";

			std::cout << instructions;
		}
		else
		{
			if(contains_number(number_clusters) == true)
			{
				int n_clusters = atoi(number_clusters.c_str());

				if(argc > 2)
				{
					std::string fasta_file(argv[2]);

					if(argc > 3)
					{
						std::string max_iterarions(argv[3]);

						if(contains_number(max_iterarions) == true)
						{
							int max_iter = atoi(max_iterarions.c_str());

							if(argc > 4)
							{
								std::string method(argv[4]);

								if(method != "NW" && method != "WS" &&
										method != "LCS" && method != "HAMMING" &&
										method != "ED" && method != "SW")
									std::cout << "\nError: method not found.\n";
								else
								{
									if(argc > 5)
									{
										std::string kmeansplusplus(argv[5]);
										bool flag_kmeansplusplus = true;

										if(kmeansplusplus == "0")
											flag_kmeansplusplus = false;

										if(argc > 6)
										{
											std::string hybrid(argv[6]);
											bool flag_hybrid = true;

											if(hybrid == "0")
												flag_hybrid = false;

											run_algorithm(n_clusters, fasta_file, max_iter,
														  method, flag_kmeansplusplus, flag_hybrid);
										}
										else
											run_algorithm(n_clusters, fasta_file,
														  max_iter, method, flag_kmeansplusplus);
									}
									else
										run_algorithm(n_clusters, fasta_file, max_iter, method);
								}
							}
							else
								run_algorithm(n_clusters, fasta_file, max_iter);
						}
						else
							std::cout << "\nError: max iterations is a positive integer.\n";
					}
					else
						run_algorithm(n_clusters, fasta_file);
				}
				else
					std::cout << "\nError: fasta file not found.\n";

			}
			else
				std::cout << "\nError: number of clusters is a positive integer.\n";
		}
	}
	else
	{
		instructions = "\nInsufficient arguments. Dont panic...\
		\n\nExample of a basic command: \
											\n\n\texecutable_name <number_of_clusters> <fasta_file>\
											\n\n\tmy_executable 3 my_file.fasta\
											\n\nWant more options ? Execute the command : executable_name help\n";

		std::cout << instructions;
	}

	return 0;
}

void run_algorithm(int clusters, std::string & fasta_file, int max_iter,
				   const std::string & method, bool kmeansplusplus, bool hybrid)
{
	std::string dataset_name(fasta_file);
	FastaFile ff(dataset_name);
	std::vector<std::pair<std::string, std::string> > dataset;

	dataset = ff.getSequences();

	std::vector<std::pair<std::string, std::string> >::iterator it;
	std::vector<std::string> sequences, headers;

	for(it = dataset.begin(); it != dataset.end(); it++)
	{
		headers.push_back((*it).first);
		sequences.push_back((*it).second);
	}

	Elbow elbow(clusters, sequences, headers, max_iter,
				method, kmeansplusplus, hybrid);

	elbow.run();
}
