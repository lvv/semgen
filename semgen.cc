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
		cnt_t  dic_word_cnt = 0; 

	while (dic >> cnt >> word,   dic)  {
							// cout << "cnt: " << cnt << "            word: " << word << endl;
		size_t idx = str2id.size();
		str2id[word] = idx; 
		TAB.push_back(rec_t());
		TAB[idx].freq = cnt;
		dic_word_cnt++;
	}
	cerr << "*** dictionary words:  " << dic_word_cnt << endl;
	

	///// PROCESS DOCS /////////////////////////////////////////////////////////////////////////////

		ifstream 	docs  (argv[1]);	 if (!docs) { cerr << "error: can not open documents file\n";  exit(3); } 
		istringstream   line_stream;
		char		line_buf[100000];
		vector<id_t>	line_words;
		cnt_t 		docs_word_cnt = 0; 
		cnt_t 		doc_cnt = 0; 
	
	while (docs.getline(line_buf, 100000),   docs)  {
		line_stream.clear();
		line_stream.str(line_buf);
		line_words.clear();

		
		//cerr << "\nDOC:\n";
		while (line_stream >> word,  line_stream)  {
			if  ( str2id.find(word) == str2id.end() )  { cerr << "word \"" << word << "\" is not in dictinary\n"; }
			//id_t  id = str2id[word];
			//cerr << word << "   (" << id << ")   " << endl;
			docs_word_cnt++;
		}
		doc_cnt++;
	}

	cerr << "*** document  words:  " << docs_word_cnt << endl;
	cerr << "*** documents      :  " << doc_cnt << endl;
	


	

}





