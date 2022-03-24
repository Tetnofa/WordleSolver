#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

vector<array<char,5> > word_array;
vector<string> global_all_words;
vector<string> all_words;
vector<string> no_black_letters;
vector<char> blackLetters;
vector<string> noBlackLetters;
vector<pair<char, int> > greenLetters;
vector<string> accountedForGreen;
vector<pair<char, int> > yellowLetters;
vector<string> allPossibleWords;


//function declarations
bool LoadInitialVector();
string getWord();
string getWordColours();
bool checkValidWord(string word);
bool checkValidColours(string colours);
void removeBlackLetters(string word, string colours);
void GreenLetters(string word);
void YellowLetters(string word);
void reLoad();
void printAnswers();

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!LoadInitialVector()){
        return 0;
    }
    
    string word;
    string colours;
    
    for (int i = 0; i < 6; i++){
        word = getWord();
        colours = getWordColours();
        removeBlackLetters(word, colours);
        GreenLetters(word);
        YellowLetters(word);
        printAnswers();
        reLoad();
    }
    
    return 0;
}

bool LoadInitialVector(){
    ifstream allWords;
    array <char,5> eachWord;
    
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
        global_all_words.push_back(word);
        position = 0;
    }
    cout << all_words.size() << endl; ;
    return true;
}

string getWord(){
    string tried_word;
    
    while(1){
        cout << "Enter Word: ";
        cin >> tried_word;
    
        if (tried_word.size()==5){
            if (checkValidWord(tried_word)){return tried_word;}
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
        cout << "Enter Word Colours: ";
        cin >> word_colours;
    
        if (word_colours.size()==5){
            if (checkValidColours(word_colours)){return word_colours;}
        }
        else{
            cout << "Incorrect Input" << endl;
        }
    }
    return word_colours;
}

bool checkValidWord(string entered_word){
    for (int i = 0; i < global_all_words.size(); i++){
        if (entered_word==global_all_words[i]){
            return true;
        }
    }
    return false;
}

bool checkValidColours(string entered_colours){
    for (int i = 0; i<5; i++){
        if (entered_colours[i]=='B'||entered_colours[i]=='Y'||entered_colours[i]=='G'){
            goto nextLetter;
        }
        cout << "Error: Invalid Colours"<< endl; return false;
    nextLetter:;
    }
    return true;
}

void removeBlackLetters(string word, string colours){
    
    for (int pos = 0; pos<5; pos++){
        if (colours[pos] == 'B'){
            blackLetters.push_back(word[pos]);
        }
        else if (colours[pos]== 'G'){
            greenLetters.push_back(make_pair(word[pos], pos));
        }
        else if (colours[pos]== 'Y'){
            yellowLetters.push_back(make_pair(word[pos], pos));
        }
    }
    //removing overlaps
    for (int i = 0; i < blackLetters.size(); i++){
        for (int j = 0; j < yellowLetters.size(); j++){
            if (blackLetters[i] == yellowLetters[j].first){
                blackLetters.erase(blackLetters.begin()+i);
            }
        }
    }
    for (int i = 0; i < blackLetters.size(); i++){
        for (int j = 0; j < greenLetters.size(); j++){
            if (blackLetters[i] == greenLetters[j].first){
                blackLetters.erase(blackLetters.begin()+i);
            }
        }
    }
    
    for (int i = 0; i<all_words.size(); i++){//looping through al words
        for (int j = 0; j<5; j++){//looping through each letter of each word
            for (int k = 0; k< blackLetters.size(); k++){
                if (all_words[i][j] == blackLetters[k]){
                    goto nextWord;
                }
            }
        }
        noBlackLetters.push_back(all_words[i]);
        nextWord:;
    }
    
    cout << all_words.size()<< endl;
    cout << noBlackLetters.size() << endl;
    return;
}

void GreenLetters(string word){
    for (int i = 0; i<noBlackLetters.size(); i++){ //looping through al words
        int countOfGreen = 0;
        for (int j = 0; j<5; j++){ //looping through each letter of each word
            for (int k = 0; k< greenLetters.size(); k++){
                char letter = greenLetters[k].first;
                int position = greenLetters[k].second;
                
                if (noBlackLetters[i][j] == letter && j == position){
                    countOfGreen++;
                }
            }
        }
        if (countOfGreen==greenLetters.size()){
            //cout << noBlackLetters[i] << endl;
            accountedForGreen.push_back(noBlackLetters[i]);}
        nextWord:;
    }
    
    cout << accountedForGreen.size() << endl;
    return;
}

void YellowLetters(string word){
    for (int i = 0; i<accountedForGreen.size(); i++){ //looping through al words
        int countOfYellow = 0;
        int maxYellowColours = yellowLetters.size();
        for (int j = 0; j<5; j++){ //looping through each letter of each word
            for (int k = 0; k< yellowLetters.size(); k++){
                char letter = yellowLetters[k].first;
                int position = yellowLetters[k].second;
                
                if (accountedForGreen[i][j] == letter && j != position){
                    countOfYellow++;
                    yellowLetters.erase(yellowLetters.begin()+k);
                }
            }
        }
        if (countOfYellow==maxYellowColours){
            //cout << accountedForGreen[i] << endl;
            allPossibleWords.push_back(accountedForGreen[i]);}
        nextWord:;
    }
    
    cout << allPossibleWords.size() << endl;
    return;
}

void reLoad (){
    all_words.resize(allPossibleWords.size());
    for (int i = 0; i < allPossibleWords.size(); i++){
        all_words[i] = allPossibleWords[i];
    }
    no_black_letters.resize(0);
    blackLetters.resize(0);
    noBlackLetters.resize(0);
    greenLetters.resize(0);
    accountedForGreen.resize(0);
    yellowLetters.resize(0);
    allPossibleWords.resize(0);
}

void printAnswers(){
    cout << "There are " << allPossibleWords.size() << "Possible Solutions" << endl;
    for (int i = 0; i < allPossibleWords.size(); i++){
        cout << allPossibleWords[i]<< endl;
    }
}
