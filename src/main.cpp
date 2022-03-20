#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<array<char,5>> all_words;

//function declarations
bool LoadInitialVector();

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!LoadInitialVector()){
        return 0;
    }
    //call other functions here 
    return 0;
}

bool LoadInitialVector(){
    ifstream allWords;
    array <char,5> eachWord;
    //Warning: Change file path when running 
    allWords.open("wordle_dict.txt");
    
    if (!allWords.is_open()){
        cout << "Error: Unable to open file \"wordle_dict.txt\""<< endl;
        return false;
    }
    
    string word;
    int position = 0;
    
    while(getline(allWords,word)){
        for (string::iterator it = word.begin(); it!=word.end(); it++, position++){
            eachWord[position] = *it;
        }
        all_words.push_back(eachWord);
        position = 0;
    }
    //cout << all_words.size();
    return true;
}
