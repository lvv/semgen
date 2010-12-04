#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

	typedef 		uint32_t	cnt_t;
	typedef 		uint32_t 	id_t;
	typedef 		uint32_t	inv_freq_t;
	typedef 		string	 	word_t;

	size_t	const	static		max_link = 40;
	size_t	const	static		max_word = 1000000;
	
	
	unordered_map<word_t, id_t> 	str2id;

	struct	  	link_freq_t	{
		id_t		id; 
		inv_freq_t	freq;
	};

	struct	  	rec_t  	{
		inv_freq_t	freq; 			// word freq
		link_freq_t	link[max_link];
	};

cnt_t					seen_words	= 0;

vector<rec_t>	TAB; 

int main(int argc, char** argv)  {
	if (argc != 3)   {
		cerr << "Usage:  semgen  docs-file  dictionary-file\n";
		exit(1);
	}

	cout << argv[1] << endl;
	cout << argv[2] << endl;

}





