#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <iterator>
#include <algorithm>

using namespace std;


// Count leading zeroes
unsigned int clz(unsigned int num){
    return __builtin_clz(num);
}

// TO-DO: Horrible hash - replace later with smhasher
int hashString(string h){
    int hashValue = 0;
    for(int i = 0; i < h.size(); i++){
        hashValue += h[i];
    }
    return hashValue;
}

int main () {

    map<int, int> sketch;
    int hashValue;
    int sketchKey;
    int sketchValue;

    istream_iterator<char> eos; // end-of-stream 
    bool eosFlag = false;

    int p = 2; // length of sketchKey bits. 2 by default. Changes throughout the process. 

    int sizeOfStream = 0; // Changes throughout the process.
    bool firstIteration = true;

    string mer;
    int merSize = 3; // Edit for bigger or shorter mers to examine the stream. 3-mer by default
                     // If the stream's size isn't divisible by merSize, there will be
                     // segments which won't be read.

    // -------------------------------------------------------------------------------------- //

    istream_iterator<char> iit{cin};

    while(!eosFlag){

        if(firstIteration){
            firstIteration = false;
            p = max((int)ceil(log2(sizeOfStream)), 2);       
            for(int i = 0; i < merSize; i++){
                if(iit != eos){
                    mer.push_back(*iit);
                    advance(iit, 1);
                } else {
                    eosFlag = true;
                    cout << "eos reached." << '\n';
                    break;
                }
            }
        } else {
            p = max((int)ceil(log2(sizeOfStream)), p);
            mer.erase(mer.begin());
            if(iit != eos){
                mer.push_back(*iit);
                advance(iit, 1);
            } else {
                eosFlag = true;
                cout << "eos reached." << '\n';
                break;
            }
        }
        
        if(eosFlag){
            break;
        }

        sizeOfStream += merSize;
        cout << "The mer to hash is " << mer << '\n';

        if(firstIteration){
            p = max((int)ceil(log2(sizeOfStream)), 2);
            firstIteration = false;
        } else {
            p = ceil(log2(sizeOfStream));
        }
        

        hashValue = hashString(mer);
        cout << "The hash value is: " << hashValue << '\n';
        cout << "Therefore, the bits are: " << bitset<32>(hashValue).to_string() << '\n';

        // Our key will be the first p bits + 1
        sketchKey = (hashValue >> (32 - p)) + 1;
        cout << "sketchKey is " << sketchKey << '\n';

        // The remaining bits will be used to value the key
        sketchValue = clz(hashValue << p);
        cout << "sketchValue is " << sketchValue << '\n';

        // If the key doesn't exist, insert.
        /* If the key does exist, then insert only if 
        the value to insert is greater than the one saved */
        if(sketch.count(sketchKey) > 0){
            if(sketch[sketchKey] < sketchValue){
                sketch[sketchKey] = sketchValue;
            }
        } else {
            sketch[sketchKey] = sketchValue;
        }

        cout << '\n';

    }

    return 0;
}