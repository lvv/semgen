CXXFLAGS = -O3 -O3 -march=native  -fwhole-program --combine -Wall -std=gnu++0x  -lm

run: semgen
	./semgen ukwac-uniqmultiwordterms.SAMPLE.txt ukwac-vocabulary.SAMPLE.txt  |gzip > result.gz
