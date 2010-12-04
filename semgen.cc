

	typedef 	cnt_t					uint32_t;
	typedef 	id_t					size_t;
	typedef 	inv_freq_t				uint32_t;
	typedef 	word_t					string;

	size_t	const	static		max_link = 40;
	size_t	const	static		max_word = 1000000;
	
	
	unordered_map<word_t, id_t> 	str2id;

	struct	  	link_freq_t	{
		id_t		id; 
		inv_freq_t	freq;
	};

	struct	  	rec_t  	{
		freq_t		freq; 			// word freq
		link_freq_t	link[max_link];
	};

cnt_t					seen_words	= 0;

vector<rec_t>	TAB; 

int main(char** argv, int argc)  {
	if (argc != 2)   {
		cerr << "Usage:  semgen  docs-file  dictionary-file\n";
		exit(1);
	}

}





