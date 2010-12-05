	#include <cstdint>
	#include <iostream>
	#include <fstream>
	#include <unordered_map>
	#include <vector>
	#include <sstream>
	using namespace std;


	//////  DATA STRUCTURE

	size_t	const	static		max_link = 40;
	size_t	const	static		max_word = 1000000;
		

			typedef 		uint32_t	cnt_t;
			typedef 		uint32_t 	id_t;
			typedef 		uint32_t	inv_freq_t;
			typedef 		string	 	word_t;

		
		unordered_map<word_t, id_t> 	str2id;

		struct	  	link_freq_t	{
			id_t		id; 
			inv_freq_t	freq;
		};

	struct	  	rec_t  	{
		inv_freq_t	freq; 			// word freq
		link_freq_t	link[max_link];
	};

	cnt_t		seen_words	= 0;
	vector<rec_t>	TAB; 			// main table


int main(int argc, char** argv)  {


	/////  CHECK ARGS
	
	if (argc != 3)   {
		cerr << "Usage:  semgen  docs-file  dictionary-file\n";
		exit(1);
	}


	///// READ DICTIONARY

		ifstream 	dic  (argv[2]);		 if (!dic) { cerr << "error: can not open dictionary file\n";  exit(2); } 
		cnt_t 		cnt;
		word_t		word;
		//id_t		id;

	while (dic >> cnt >> word,   dic)  {
							// cout << "cnt: " << cnt << "            word: " << word << endl;
		size_t idx = str2id.size();
		str2id[word] = idx; 
		TAB.push_back(rec_t());
		TAB[idx].freq = cnt;
	}
	
	///// PROCESS DOCS /////////////////////////////////////////////////////////////////////////////

		ifstream 	docs  (argv[1]);	 if (!docs) { cerr << "error: can not open documents file\n";  exit(3); } 
		istringstream   line_stream;
		char		line[1000];
	
	while (docs.getline(line, 1000),   docs)  {
		line_stream.clear();
		line_stream.str(line);

		
		cerr << "\nDOC:\n";
		while (line_stream >> word,  line_stream)  {
			cerr << word << endl;
		}
	}
	


	

}





