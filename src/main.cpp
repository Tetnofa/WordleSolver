#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<array<char,5>> word_array;
vector<string> all_words;

//function declarations
bool LoadInitialVector();
string getWord();
string getWordColours();
bool checkValidWord(string word);
//bool checkValidColours();

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!LoadInitialVector()){
        return 0;
    }
    
    getWord();
    //getWordColours();
    
    
    return 0;
}

bool LoadInitialVector(){
    ifstream allWords;
    array <char,5> eachWord;
    //change file path accordingly when running 
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
        word_array.push_back(eachWord);
        all_words.push_back(word);
        position = 0;
    }
    cout << all_words.size();
    return true;
}

string getWord(){
    string tried_word;
    
    while(1){
        cout << "Enter Word: ";
        cin >> tried_word;
    
        if (tried_word.size()==5){
            if (checkValidWord(tried_word)==true){return tried_word;}
            else {
                cout << "Error: Not a Word" << endl;
            }
        }
        else{
            cout << "Error: Incorrect Input" << endl;
        }
    }
    return tried_word;
}

string getWordColours(){
    string word_colours;
    
    while(1){
        cout << "Enter Word: ";
        cin >> word_colours;
    
        if (word_colours.size()==5){
            return word_colours;
        }
        else{
            cout << "Incorrect Input" << endl;
        }
    }
    return word_colours;
}

bool checkValidWord(string entered_word){
    for (int i = 0; i < all_words.size(); i++){
        if (entered_word==all_words[i]){
            return true;
        }
    }
    return false;
}
//test3
