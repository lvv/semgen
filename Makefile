CXXFLAGS = -Wall -std=c++0x 

run: semgen
	./semgen ukwac-uniqmultiwordterms.SAMPLE.txt ukwac-vocabulary.SAMPLE.txt 
