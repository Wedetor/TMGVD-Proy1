#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "hyperloglog.cpp"
#include "jaccard.cpp"

int main() {

	unsigned int seed = rand();
	map<int, int> GenA = hyperloglog("GCF_000331305.1_ASM33130v1_genomic.fna", seed);
	map<int, int> GenB = hyperloglog("GCF_000959725.1_ASM95972v1_genomic.fna", seed);

	float jaccard = jaccard_function(GenA, GenB);

	cout << "Jaccard: " << jaccard << endl;
	return 0;
}
