#include<bits/stdc++.h>
using namespace std;

// TRIES-I
struct Node{
    Node* arr[26];
    bool flag = false;

    bool contain(char c){
        return (arr[c-'a'] != NULL);
    }
    void put(char c, Node* newNode){
        arr[c-'a'] = newNode;
    }
    Node* goNext(char c){
        return arr[c-'a'];
    }
    void setFlag(){
        flag = true;
    }
};

Node* root = new Node();

void insert(string word){
    Node* temp = root;
    for(int i = 0; i < word.size(); i++){
        if(!temp->contain(word[i])){
            Node* newNode = new Node();
            temp->put(word[i], newNode);
        }
        temp = temp->goNext(word[i]);
    }
    temp->setFlag();
}

bool search(string word){
    Node* temp = root;
    for(int i = 0; i < word.size(); i++){
        if(temp->contain(word[i]))  temp->goNext(word[i]);
        else    return false;
    }
    if(temp->flag == true)  return true;
    return false;
}

bool startsWith(string word){
    Node* temp = root;
    for(int i = 0; i < word.size(); i++){
        if(temp->contain(word[i]))  temp->goNext(word[i]);
        else    return false;
    }
    return true;
}

// TRIES-II
struct Node{
    Node* arr[26];
    int ends = 0;
    int prefixes = 0;

    bool contain(char c){
        return (arr[c-'a'] != NULL);
    }
    void put(char c, Node* newNode){
        arr[c-'a'] = newNode;
    }
    Node* goNext(char c){
        return arr[c-'a'];
    }
    void increaseEnds(){
        ends++;
    }
    void increasePrefixes(){
        prefixes++;
    }
    void decreaseEnds(){
        ends--;
    }
    void decreasePrefixes(){
        prefixes--;
    }
    int getEndCount(){
        return ends;
    }
    int getPrefixesCount(){
        return prefixes;
    }
};

Node* root1 = new Node();

void insert(string word){
    Node* temp = root1;
    for(int i = 0; i < word.size(); i++){
        if(!temp->contain(word[i])){
            Node* newNode = new Node();
            temp->put(word[i], newNode);
        }
        temp->increasePrefixes();
        temp = temp->goNext(word[i]);
    }
    temp->increaseEnds();
}

int countsWordsEqualTo(string word){
    Node* temp = root1;
    for(int i = 0; i < word.size(); i++){
        if(temp->contain(word[i]))  temp->goNext(word[i]);
        else    return 0;
    }
    return temp->getEndCount();
}

int countWordsEndsWith(string word){
    Node* temp = root1;
    for(int i = 0; i < word.size(); i++){
        if(temp->contain(word[i]))  temp->goNext(word[i]);
        else    return 0;
    }
    return temp->getPrefixesCount();
}

void erase(string word){
    Node* temp = root1;
    if(!countsWordsEqualTo(word))   return;
    for(int i = 0; i < word.size(); i++){
        temp->decreasePrefixes();
        temp = temp->goNext(word[i]);
    }
    temp->decreaseEnds();
}