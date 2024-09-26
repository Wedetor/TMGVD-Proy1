#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "hyperloglog.cpp"
#include "jaccard.cpp"
#include "realJaccard.cpp"

int main() {

	unsigned int seed = rand();

	vector<map<unsigned int, unsigned int>> genSketches;
	vector<string> genNames;

	string GenAName = "GCF_000331305.1_ASM33130v1_genomic.fna";
	string GenBName = "GCF_000959725.1_ASM95972v1_genomic.fna";
	string GenCName = "GCF_000373685.1_ASM37368v1_genomic.fna";
	string GenDName = "GCF_000583735.1_ASM58373v1_genomic.fna";
	string GenEName = "GCF_001189295.1_ASM118929v1_genomic.fna";
	genNames.push_back(GenAName);
	genNames.push_back(GenBName);
	genNames.push_back(GenCName);
	genNames.push_back(GenDName);
	genNames.push_back(GenEName);

	map<unsigned int, unsigned int> GenA = hyperloglog(GenAName, seed);
	map<unsigned int, unsigned int> GenB = hyperloglog(GenBName, seed);
	map<unsigned int, unsigned int> GenC = hyperloglog(GenCName, seed);
	map<unsigned int, unsigned int> GenD = hyperloglog(GenDName, seed);
	map<unsigned int, unsigned int> GenE = hyperloglog(GenEName, seed);
	genSketches.push_back(GenA);
	genSketches.push_back(GenB);
	genSketches.push_back(GenC);
	genSketches.push_back(GenD);
	genSketches.push_back(GenE);

	vector<float> jaccardVector;
	vector<float> rejaccardVector;
	float jaccard;
	float rejaccard;

	for(int i = 0; i < genNames.size(); i++){
		for(int j = i+1; j < genNames.size(); j++){
			cout << "Gen 1: " << genNames[i] << endl;
			cout << "Gen 2: " << genNames[j] << endl;
			
			jaccard = jaccard_function(genSketches[i], genSketches[j]);
			rejaccard = realJaccard(genNames[i], genNames[j]);

			jaccardVector.push_back(jaccard);
			rejaccardVector.push_back(rejaccard);
			
			cout << "Jaccard of GenA & GenB: " << fixed << jaccard << endl;
			cout << "Real Jaccard: " << fixed << rejaccard << endl;
			cout << '\n';
		}
	}

	float errorRelativoMedio = 0;
	float errorAbsolutoMedio = 0;

	for(int i = 0; i < jaccardVector.size(); i++){
		errorRelativoMedio = errorRelativoMedio + ((abs(jaccardVector[i] - rejaccardVector[i]))/rejaccardVector[i]);
	}
	errorRelativoMedio = errorRelativoMedio/jaccardVector.size();

	cout << "Error Relativo Medio: " << errorRelativoMedio << endl;

	for(int i = 0; i < jaccardVector.size(); i++){
		errorAbsolutoMedio = errorAbsolutoMedio + (abs(jaccardVector[i] - rejaccardVector[i]));
	}
	errorAbsolutoMedio = errorAbsolutoMedio/jaccardVector.size();
	
	cout << "Error Absoluto Medio: " << errorAbsolutoMedio << endl;

	return 0;
}
