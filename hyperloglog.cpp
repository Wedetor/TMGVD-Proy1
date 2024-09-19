#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

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
    string stream; // Stream won't be saved; this is just for testing purposes.
    int p; // length of sketchKey bits. 
    string window;
    int windowSize;
    int hashValue;
    int sketchKey;
    int sketchValue;

    // TO-DO: Replace cin >> stream with a while loop that reads the stream without saving it
    cin >> stream;

    p = ceil(log2(stream.size()));
    windowSize = 3; // Edit for bigger or shorter windows to examine the stream

    
    for(int i = 0; i < stream.size()-2; i++){
        window.clear();

        // If the stream is too short for our window to analyze, break;
        if(i + windowSize > stream.size()){
            break;
        }

        // Move our window through the stream, saving the char values
        for(int j = i; j < windowSize + i; j++){
            window.push_back(stream[j]);
        }
        cout << "The window to hash is " << window << '\n';

        // Hash the portion of stream saved
        hashValue = hashString(window);
        cout << "The hash value is: " << hashValue << '\n';
        cout << "Therefore, the bits are: " << bitset<32>(hashValue).to_string() << '\n';

        // Our key will be the first p bits + 1
        sketchKey = (hashValue >> (32 - p)) + 1;
        cout << "sketchKey is " << sketchKey << '\n';

        // The remaining bits will be used to value the key
        sketchValue = (hashValue << p) >> p;
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