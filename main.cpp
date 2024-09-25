#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "hyperloglog.cpp"

int main() {

	unsigned int seed = rand();
	map<int, int> GenA = hyperloglog("GCF_000331305.1_ASM33130v1_genomic.fna", seed);
	map<int, int> GenB = hyperloglog("GCF_000959725.1_ASM95972v1_genomic.fna", seed);
	map<int, int> GenAoB;

	int cardA = 0;
	int cardB = 0;
	int cardAoB = 0;
	for(auto p: GenA)
		cardA += p.second;

	for(auto p: GenB)
		cardB += p.second;

	map<int, int>::iterator itA = GenA.begin();
	map<int, int>::iterator itB = GenB.begin();

	if(cardA<cardB){
		while(itA != GenA.end()){
			if(itA->first == itB->first){
				GenAoB.insert(pair<int, int>(itA->first, itA->second));
			}
			advance(itA, 1);
			advance(itB, 1);
		}
	}else{
		while(itB != GenB.end()){
			if(itA->first == itB->first){
				GenAoB.insert(pair<int, int>(itA->first, itA->second));
			}
			advance(itA, 1);
			advance(itB, 1);
		}
	}
	for(auto p: GenAoB)
		cardAoB += p.second;

	cout << "Cardinalidad A: " << cardA << endl;
	cout << "Cardinalidad B: " << cardB << endl;
	cout << "Cardinalidad AoB: " << cardAoB << endl;

	float Jaccard = (cardA + cardB - cardAoB) / cardAoB; 
	cout << "Jaccard: " << Jaccard << endl;
	return 0;
}
