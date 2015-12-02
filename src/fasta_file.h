// read FASTA file format

#include <fstream>
#include <map>

class FastaFile
{

private:
	std::vector<std::pair<std::string, std::string> > sequences;

private:

	bool readFasta(std::string file_path)
	{
		std::ifstream input(file_path.c_str());

		if(!input.good())
		{
			std::cerr << "Error opening FASTA file.\n";
			return false;
		}

		bool flag_insert = false;
		std::string line, name, content;

		while(std::getline(input, line))
		{
			if(!line.empty())
			{
				if(line[0] == '>')
				{
					if(flag_insert)
					{
						sequences.push_back(std::make_pair(name, content));
						content.clear();
						flag_insert = false;
					}
					name = line.substr(1);
				}
				else
				{
					content += line;
					flag_insert = true;
				}
			}
		}

		if(!content.empty())
			sequences.push_back(std::make_pair(name, content));

		return true;
	}

public:

	FastaFile(std::string file_path)
	{
		readFasta(file_path);
	}

	void showSequences()
	{
		std::cout << "\nShowing sequences of the FASTA file:\n\n";

		std::vector<std::pair<std::string, std::string> >::iterator it;

		for(it = sequences.begin(); it != sequences.end(); it++)
			std::cout << (*it).first << "\n" << (*it).second << "\n\n";
	}

	// return the sequences
	const std::vector<std::pair<std::string, std::string> > & getSequences()
	{
		return sequences;
	}
};