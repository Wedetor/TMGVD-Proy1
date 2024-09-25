#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

float jaccard_function(map<int, int> GenA, map<int, int> GenB){
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

    return Jaccard;
}