#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// Count leading zeroes
unsigned int clz(unsigned int num){
    return __builtin_clz(num);
}

// Horrible hash - replace later with smhasher
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
    int hashValue;
    int sketchKey;
    int sketchValue;


    cin >> stream;

    p = ceil(log2(stream.size()));

    for(int i = 0; i < stream.size()-2; i++){
        if(i+3 > stream.size()){
            break;
        }
        window = stream[i] + stream[i+1] + stream[i+2];
        hashValue = hashString(window);
        sketchKey = (hashValue + 1) >> (32 - p);
        sketchValue = (hashValue << p) >> p;
        if(sketch.count(sketchKey) > 0){
            if(sketch[sketchKey] < sketchValue){
                sketch[sketchKey] = sketchValue;
            }
        } else {
            sketch[sketchKey] = sketchValue;
        }
    }




    return 0;
}