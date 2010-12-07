
	#include <cmath>
	#include <cstdint>
	#include <iostream>
	#include <fstream>
	#include <unordered_map>
	#include <deque>
	#include <sstream>
	#include <algorithm>
	using namespace std;


	//////  DATA STRUCTURES

	size_t	const	static		max_link = 130;
		
			typedef 		uint32_t	cnt_t;
			typedef 		uint32_t 	id_t;
			typedef 		string	 	word_t;
		
		unordered_map<word_t, id_t> 	str2id;

		struct	  	link_t	{
				link_t ():   id(0),  cnt(0), dist(1) {};
			id_t	id; 
			cnt_t	cnt;
			float	dist;				// distance factor sum
		};

	struct	  	rec_t  	{
			rec_t ():   tcnt(0), link_size(0) {};
		cnt_t	tcnt;					// this word total count
		size_t	link_size;				// total links
		link_t	link[max_link];				// word tracked pairs
		word_t	word;
	};

	deque <rec_t>	TAB; 			// main table

float   distance_factor(int pos1, int pos2 ) { return  1.f / (sqrt(std::abs(int(pos1)-pos2))); }
float   relevancy(link_t *L) { return  (0.5f*L->cnt*L->cnt + 0.5f*L->cnt) / TAB[L->id].tcnt * L->dist; }


void 	update_link_list (id_t m, id_t s) {

	///// update cnt if in list

	auto it          =   TAB[m].link;
	auto link_begin  =   TAB[m].link;
	auto link_end    = & TAB[m].link[TAB[m].link_size];

	for (;  it != link_end  &&  it->id != s;   it++) 	// find link to update
		;

	if (  it !=  link_end )  {				// if found,  update
		it->cnt ++;
		it->dist += distance_factor(m,s);
	}
	
	///// else add to link list if not full 

	else if (TAB[m].link_size < max_link)  {
		it = link_end;
		it->id	  = s;
		it->cnt   = 1;
		it->dist  = distance_factor(m,s);
		TAB[m] .link_size ++;
	}
	
	/////  else replace tail (least relevant) with more  relavant

	else {
		it  = link_end - 1;		// last link
		if  (relevancy(it) < 1.f/TAB[s].tcnt * distance_factor(m,s))  {
			it->id   = s;
			it->cnt  = 1;
			it->dist = distance_factor(m,s);
		}
	}

	// re-sort  (IT holds updated link, buble it up)

	while (it != link_begin   &&  relevancy(it) > relevancy(it-1)) {	// re-sort
		swap(*it, *(it-1));
	}
 }


int main(int argc, char** argv)  {

	TAB .push_back(rec_t()); 		// 1st row no used;

	/////  CHECK ARGS
	
	if (argc != 3)   {
		cerr << "Usage:  semgen  docs-file  dictionary-file\n";
		exit(1);
	}


	/////  READ DICTIONARY  /////////////////////////////////////////////////////////////////////////////////////

		cnt_t 		cnt;
		word_t		word;
		//id_t		id;
		cnt_t 		dic_word_cnt = 0; 
		ifstream 	dic  (argv[2]);		 if (!dic) { cerr << "error: can not open dictionary file\n";  exit(2); } 
		size_t		total_docs_words = 0;

	while (dic >> cnt >> word,   dic)  {
							// cout << "cnt: " << cnt << "            word: " << word << endl;
		id_t id = str2id.size();		
		str2id[word] = id; 			// we assume words in dic are unique
		TAB .push_back (rec_t());
		TAB[id].tcnt = cnt;
		TAB[id].word = word;
		total_docs_words += cnt;
		dic_word_cnt++;
	}

	cerr << "*** dictionary words:  " << dic_word_cnt << endl;
	cerr << "*** total dictionary words count:  " << total_docs_words << endl;
	

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

		while (line_stream >> word,  line_stream)  {
			if  ( str2id.find(word) == str2id.end() )  { cerr << "word \"" << word << "\" is not in dictinary\n"; }
			id_t  id = str2id[word];
			line_words .push_back (id);
			docs_word_cnt++;

			// all word pairs
			for (size_t m=0;   m < line_words.size();   m++)   {	// main/sub word cycles
			for (size_t s=0;   s < line_words.size();   s++)   {
				if (m==s) continue;
				update_link_list( line_words[m], line_words[s] );
			}
			}
		}
		doc_cnt++;
	}

	cerr << "*** document  words:  " << docs_word_cnt << endl;
	cerr << "*** documents      :  " << doc_cnt << endl;
	

	/////  PRINT RESULT  /////////////////////////////////////////////////////////////////////////////

	for (id_t id=0;   id < TAB.size();   id++)  {
		cout << TAB[id].word;
		for (size_t l = 0;   l < std::min((size_t)10, TAB[id].link_size);   l++)
			cout << " " << TAB [TAB[id] .link[l] .id] .word;
		cout << endl;
	}
					{
					string word("group");
					id_t id = str2id[word];
					cerr << word << "/" << id << " tcnt=" << TAB[id].tcnt << endl;
					for (size_t i=0; i<60; i++) 
						cerr << "\t(" << i << ") " << TAB[TAB[id].link[i].id].word <<
							"\t/"		<<  TAB[id].link[i].id <<
							"\t[cnt:"	<<  TAB[id].link[i].cnt << 
							"\t tcnt:"	<<  TAB[TAB[id].link[i].id].tcnt <<
							"\t dist:"	<<  TAB[id].link[i].dist <<
							"]\n";
					}
}
