#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <iterator>
#include <algorithm>
#include "smhasher_copy/sha1.cpp"

using namespace std;


// Count leading zeroes
unsigned int clz(unsigned int num){
    return __builtin_clz(num);
}

int main () {

    map<int, int> sketch;
    unsigned int hashValue;
    unsigned int sketchKey;
    unsigned int sketchValue;
    unsigned int randomSeed = rand();

    int p = 14; // length of sketchKey bits. 14 by project's error requirements.

    int sizeOfStream = 0; // Changes throughout the process.
    bool firstIteration = true;

    string mer;
    int merSize = 3; // Edit for bigger or shorter mers to examine the stream. 3-mer by default
                     // If the stream's size isn't divisible by merSize, there will be
                     // segments which won't be read.

    // -------------------------------------------------------------------------------------- //

    istream_iterator<char> iit{cin};
    istream_iterator<char> eos; // end-of-stream 
    

    while(true){

        if(firstIteration){
            firstIteration = false;

            mer.push_back(*iit);
            for(int i = 1; i < merSize; i++){
                advance(iit, 1);
                if(iit != eos){
                    mer.push_back(*iit);
                } else {
                    break;
                }
            }

        } else {
            mer.erase(mer.begin());

            advance(iit, 1);
            if(iit != eos){
                mer.push_back(*iit);            
            } else {
                break;
            }
        }
        
        cout << "The mer to hash is " << mer << '\n';
        
        sha1_32a (&mer, sizeof(mer), randomSeed, &hashValue);
        cout << "The hash value is: " << hashValue << '\n';
        cout << "Therefore, the bits are: " << bitset<32>(hashValue).to_string() << '\n';

        // Our key will be the first p bits + 1
        sketchKey = (hashValue >> (32 - p)) + 1;
        cout << "sketchKey is " << sketchKey << '\n';

        // The remaining bits will be used to value the key
        sketchValue = clz(hashValue << p) + 1;
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