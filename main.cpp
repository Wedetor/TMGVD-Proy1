#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "hyperloglog.cpp"
#include "jaccard.cpp"
#include "realJaccard.cpp"

int main() {

	unsigned int seed = rand();

	string GenAName = "GCF_000331305.1_ASM33130v1_genomic.fna";
	string GenBName = "GCF_000959725.1_ASM95972v1_genomic.fna";
	string GenCName = "GCF_000373685.1_ASM37368v1_genomic.fna";
	string GenDName = "GCF_000583735.1_ASM58373v1_genomic.fna";
	string GenEName = "GCF_001189295.1_ASM118929v1_genomic.fna";

	map<unsigned int, unsigned int> GenA = hyperloglog(GenAName, seed);
	map<unsigned int, unsigned int> GenB = hyperloglog(GenBName, seed);
	map<unsigned int, unsigned int> GenC = hyperloglog(GenCName, seed);
	map<unsigned int, unsigned int> GenD = hyperloglog(GenDName, seed);
	map<unsigned int, unsigned int> GenE = hyperloglog(GenEName, seed);

	float jaccard = jaccard_function(GenA, GenB);
	float rejaccard = realJaccard(GenAName, GenBName);

	cout << "Jaccard of GenA & GenB: " << fixed << jaccard << endl;
	cout << "Real Jaccard: " << fixed << rejaccard << endl;

	return 0;
}
