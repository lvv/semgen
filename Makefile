CXXFLAGS +=  -std=gnu++0x -O3 -march=native  -fwhole-program --combine -Wall -lm -openmp

run: semgen
	/usr/bin/time ./semgen ukwac-uniqmultiwordterms.SAMPLE.txt ukwac-vocabulary.SAMPLE.txt  |gzip > result.gz
