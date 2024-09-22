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
#include "smhasher_copy/MurmurHash1.cpp"

using namespace std;

// Count leading zeroes
unsigned int clz(unsigned int num){
    return __builtin_clz(num);
}

int main () {
    int merSize = 3;  // Default k-mer size  
    int windowSize = 6; //Default window size

    //int kmers_in_window = windowSize - merSize + 1;
    istream_iterator<char> win_it{cin};
    istream_iterator<char> end_of_string;
    
    bool first_window_it = true;
    string window;

    while(true){
        if(first_window_it){
            first_window_it = false;
            window.push_back(*win_it);
            for(int i=0; i<windowSize;i++){
                advance(win_it, 1);
                if(win_it != end_of_string){
                    window.push_back(*win_it);
                }
            }
        }else{
            window.erase(window.begin());
            advance(win_it, 1);
            if(win_it != end_of_string){
                window.push_back(*win_it);
            }else{
                break;
            }
        }
        cout << "||=====================================================||" << endl << "Window to Kmer: " << window<< endl << endl;
        
        map<int, int> sketch;
        unsigned int hashValue;
        unsigned int sketchKey;
        unsigned int sketchValue;

        int p = 14; // length of sketchKey bits. 14 by project's error requirements. 
        int sizeOfStream = 0; // Changes throughout the process.
        bool first_mer_it = true;
        string mer;

        for(int i=0; i < windowSize - merSize + 1; i++){
            //cout<<"i: "<<i<<endl;
            int counter = 0;
            int next_pos;
            cout << "THIS MESSAGE SHOULD APPEAR ONCE PER [WINDOW]." <<endl;
            while(counter < windowSize-merSize){
                if(!first_mer_it){
                    mer.push_back(window[next_pos]);
                    mer.erase(mer.begin());
                    next_pos++;
                    counter++;
                    sizeOfStream++;
                }else{
                    first_mer_it = false;
                    for(int j = i; j < merSize; j++){
                        mer.push_back(window[j]);
                        counter++;
                        sizeOfStream += merSize;
                        next_pos = j+1;
                    }
                }
                if(mer.length() < 3){
                    cout << "APAGALO, OTTO!!!" << endl;
                    break;
                }
                cout << "The mer to hash is " << mer << '\n';
                // Hash the current mer
                hashValue = MurmurHash1Aligned(&mer, merSize, rand());
                cout << "The hash value is: " << hashValue << '\n';
                cout << "Therefore, the bits are: " << bitset<32>(hashValue).to_string() << '\n';

                // Our key will be the first p bits + 1
                sketchKey = (hashValue >> (31 - p)) + 1;
                cout << "sketchKey is " << sketchKey << '\n';

                // The remaining bits will be used to value the key
                sketchValue = clz(hashValue << p) + 1;
                cout << "sketchValue is " << sketchValue << '\n';

                // If the key doesn't exist, insert it.
                // If the key exists, insert only if the new value is greater than the stored value.
                if(sketch.count(sketchKey) > 0){
                    if(sketch[sketchKey] < sketchValue){
                        sketch[sketchKey] = sketchValue;
                    }
                } else {
                    sketch[sketchKey] = sketchValue;
                }
                cout <<"\n";
            }
        }
    }
    return 0;
}
