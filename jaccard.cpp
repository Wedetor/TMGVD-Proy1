#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

float jaccard_function(map<unsigned int, unsigned int> GenA, map<unsigned int, unsigned int> GenB){
    map<unsigned int, unsigned int> GenAoB;
	bool breakLoopFlag;

	float cardA = 0;
	float cardB = 0;
	float cardAoB = 0;
	for(auto p: GenA)
		cardA += p.second;

	for(auto p: GenB)
		cardB += p.second;

	map<unsigned int, unsigned int>::iterator itA = GenA.begin();
	map<unsigned int, unsigned int>::iterator itB = GenB.begin();

	if(cardA>cardB){
		while(itA != GenA.end()){
			breakLoopFlag = false;
			map<unsigned int, unsigned int>::iterator itB = GenB.begin();
			while(itB != GenB.end()){
				if(itA->first == itB->first){
					if(itA->second > itB->second){
						GenAoB.insert(pair<unsigned int, unsigned int>(itA->first, itA->second));
					} else {
						GenAoB.insert(pair<unsigned int, unsigned int>(itA->first, itB->second));
					}
					breakLoopFlag = true;
					break;
				}
				advance(itB, 1);
			}
			if(!breakLoopFlag)
				GenAoB.insert(pair<unsigned int, unsigned int>(itA->first, itA->second));
			advance(itA, 1);	
		}
	}else{
		while(itB != GenB.end()){
			breakLoopFlag = false;
			map<unsigned int, unsigned int>::iterator itA = GenA.begin();
			while(itA != GenA.end()){
				if(itA->first == itB->first){
					if(itA->second > itB->second){
						GenAoB.insert(pair<unsigned int, unsigned int>(itA->first, itA->second));
					} else {
						GenAoB.insert(pair<unsigned int, unsigned int>(itA->first, itB->second));
					}
					breakLoopFlag = true;
					break;
				}
				advance(itA, 1);
			}
			if(!breakLoopFlag)
				GenAoB.insert(pair<unsigned int, unsigned int>(itB->first, itB->second));
			advance(itB, 1);	
		}
	}
	for(auto p: GenAoB)
		cardAoB += p.second;

    cout << "Cardinalidad A: " << cardA << endl;
	cout << "Cardinalidad B: " << cardB << endl;
    cout << "Cardinalidad AoB: " << cardAoB << endl;

    float Jaccard = (float)((cardA + cardB - cardAoB) / cardAoB); 

    return Jaccard;
}