#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

float realJaccard(string fileName1, string fileName2){
	ifstream firstGenomeFile(fileName1);
    if(!firstGenomeFile.is_open()){
        return 0;
    }

    ifstream secondGenomeFile(fileName2);
    if(!secondGenomeFile.is_open()){
        return 0;
    }

    map<char, int> firstCard;
    float firstCardValue = 0;
    map<char, int> secondCard;
    float secondCardValue = 0;
    map<char, int> unionCard;
    float unionValue;

    string firstLine;
    istream_iterator<char> iit1(firstGenomeFile);
    istream_iterator<char> iit2(secondGenomeFile);
    istream_iterator<char> eos; // end-of-stream 

    getline(firstGenomeFile, firstLine);
    advance(iit1, 1);

    getline(secondGenomeFile, firstLine);
    advance(iit2, 1);

    while(true){

    	if(iit1 != eos){
    		if(firstCard.count(*iit1) > 0){
	            firstCard[*iit1]++;
	        } else {
	            firstCard[*iit1] = 1;
	        }
	        advance(iit1, 1);
    	} else 
    		break;
  
    }

    while(true){
    	if(iit2 != eos){
    		if(secondCard.count(*iit2) > 0){
	            secondCard[*iit2]++;
	        } else {
	            secondCard[*iit2] = 1;
	        }
	        advance(iit2, 1);
    	} else 
    		break;
    }

    firstGenomeFile.close();
    secondGenomeFile.close();

    for(auto p: firstCard)
    	firstCardValue += p.second;

    for(auto p: secondCard)
    	secondCardValue += p.second;

    map<char, int>::iterator itA = firstCard.begin();
	map<char, int>::iterator itB = secondCard.begin();

    if(firstCardValue>secondCardValue){
		while(itA != firstCard.end()){
			map<char, int>::iterator itB = secondCard.begin();
			while(itB != secondCard.end()){
				if(itA->first == itB->first){
					if(itA->second > itB->second){
						unionCard.insert(pair<int, int>(itA->first, itA->second));
					} else {
						unionCard.insert(pair<int, int>(itA->first, itB->second));
					}
					break;
				}
				advance(itB, 1);
			}
			unionCard.insert(pair<int, int>(itA->first, itA->second));
			advance(itA, 1);	
		}
	}else{
		while(itB != secondCard.end()){
			map<char, int>::iterator itA = firstCard.begin();
			while(itA != firstCard.end()){
				if(itA->first == itB->first){
					if(itA->second > itB->second){
						unionCard.insert(pair<int, int>(itA->first, itA->second));
					} else {
						unionCard.insert(pair<int, int>(itA->first, itB->second));
					}
					break;
				}
				advance(itA, 1);
			}
			unionCard.insert(pair<int, int>(itA->first, itB->second));
			advance(itB, 1);	
		}
	}

	for(auto p: unionCard)
		unionValue += p.second;

	float reJaccard = (float)((firstCardValue + secondCardValue - unionValue) / unionValue); 


    return reJaccard;

}