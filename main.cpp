#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Node{
    char c;
    Node* prev;
    Node* next;
    Node* above;
    Node* below;
    Node(){
        prev = next = above = below = NULL;
    }
    Node(char ch){
        c = ch;
        prev = next = above = below = NULL;
    }
    ~Node(){
        delete prev;
        delete next;
        delete above;
        delete below;
    }
};
struct Notepad{
    Node* head;
    Node* current;
    Node* cursor;
    vector<string> dictionary;
    Notepad(){
        head = current = cursor = NULL;
    }
    ~Notepad(){
        delete head;
        delete current;
        delete cursor;
        dictionary.clear();
    }
    void in(char ch){
        if(head == NULL){
            Node* temp = new Node(ch);
            cursor = new Node('|');
            head = temp;
            current = head;
            head -> next = cursor;
            cursor -> prev = temp;
        }else{
            Node* n = new Node(ch);
            if(cursor->prev == NULL && cursor->next == NULL){
                if(cursor->above == NULL){
                    n->next = cursor;
                    cursor->prev = n;
                    head = current = n;
                    return;
                }
                cursor->above->below = n;
                cursor->prev = n;
                n->next = cursor;
                n->above = current;
                current = n;
                n->below = cursor->below;
            }else if(cursor->prev && cursor->next){
                n->next = cursor;
                n->prev = cursor->prev;
                cursor->prev->next = n;
                cursor->prev = n;
            }else if(cursor->prev && cursor->next == NULL){
                cursor->prev->next = n;
                n -> prev = cursor->prev;
                cursor->prev = n;
                n ->next = cursor;
            }else if(cursor->prev == NULL && cursor->next){
                if(cursor->above == NULL){
                    head = n;
                }else{
                    cursor->above->below = n;
                    current = n;
                    n->above = cursor->above;
                }
                n->next = cursor;
                cursor->prev = n;
            }
            if(ch == '\n'){
                current->below = cursor;
                cursor->above = current;
                n->next = NULL;
                cursor->prev = NULL;
            }
        }
    }
    void connect(){
        if(head!=NULL){
            Node* line1 = head;
            Node* line2 = head->below;
            Node* c1 = NULL;
            Node* c2 = NULL;
            if(current != head){
                while(line1&&line2){
                    c1 = line1;
                    c2 = line2;
                    while(c1&&c2){
                        c1->below = c2;
                        c2->above = c1;
                        c1 = c1->next;
                        c2 = c2->next;
                    }
                    line1 = line1->below;
                    line2 = line2->below;
                }
            }
        }
    }
    void cursor_up(){
        if(head != NULL){
            if(cursor->above != NULL && cursor->prev && cursor->next){
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
                cursor->prev = cursor->above->prev;
                cursor->next = cursor->above;
                cursor->next->prev = cursor;
                cursor->prev->next = cursor;
                cursor->above = NULL;
                cursor->below = NULL;
            }
        }
    }
    void cursor_down(){
        if(head != NULL){
            if(cursor->below != NULL && cursor->prev && cursor->next){
                cursor->next->prev = cursor->prev;
                cursor->prev->next = cursor->next;
                cursor->prev = cursor->below->prev;
                cursor->next = cursor->below;
                cursor->next->prev = cursor;
                cursor->prev->next = cursor;
                cursor->above = NULL;
                cursor->below = NULL;
            }
        }
    }
    void cursor_left(){
        if(head != NULL){
            if(cursor->prev != NULL){
                if(cursor->prev && cursor->next == NULL){
                    cursor->next = cursor->prev;
                    cursor->prev = cursor->next->prev;
                    cursor->next->prev->next = cursor;
                    cursor->next->prev = cursor;
                    cursor->next->next = NULL;
                }else if(cursor->prev->prev == NULL){
                    Node* temp = cursor->prev;
                    if(head == current){
                        head = current = cursor;
                    }else{
                        current = cursor;
                        cursor->above = temp->above->below;
                        temp->above->below = cursor;
                    }
                    temp->next = cursor->next;
                    temp->prev = cursor;
                    cursor->next->prev = temp;
                    cursor->next = temp;
                    cursor->prev = NULL;
                }else{
                    Node* temp = cursor->next;
                    cursor->next = cursor->prev;
                    cursor->prev = cursor->next->prev;
                    cursor->next->prev->next = cursor;
                    cursor->next->prev = cursor;
                    cursor->next->next = temp;
                }
            }
        }
    }
    void cursor_right(){
        if(head != NULL){
            if(cursor->next != NULL){
                if(cursor->next->next == NULL){
                    Node* temp = cursor->next;
                    temp->prev = cursor->prev;
                    temp->next = cursor;
                    cursor->prev->next = temp;
                    cursor->prev = temp;
                    cursor->next = NULL;
                }else if(cursor->next && cursor->prev){
                    Node* temp = cursor->next;
                    temp->prev = cursor->prev;
                    cursor->prev->next = temp;
                    cursor->next = temp->next;
                    temp->next->prev = cursor;
                    temp->next = cursor;
                    cursor->prev = temp;
                }else{
                    Node* temp = cursor->next;
                    if(head == current){
                        head = current = temp;
                    }else{
                        current = temp;
                        temp->above = cursor->above->below;
                        cursor->above->below = temp;
                    }
                    cursor->next = temp->next;
                    temp->next->prev = cursor;
                    temp->next = cursor;
                    cursor->prev = temp;
                    temp->prev = NULL;
                }
            }
        }
    }
    void del(){
        if(head != NULL){
            if(cursor->prev != NULL){
                if(current->next == cursor && cursor->next == NULL){
                    if(head != current){
                        current->above->below = cursor;
                        current = cursor;
                        cursor->prev = NULL;
                    }else{
                        head = current = cursor;
                        cursor->prev = NULL;
                    }
                }else{
                    cursor->prev = cursor->prev->prev;
                    cursor->prev->next = cursor;
                }
            }
        }
    }
    void display(){
        Node* i = head;
        Node* j = head;
        while(i){
            while(j){
                cout<<j->c;
                j = j -> next;
            }
            i = i->below;
            j = i;
        }
    }
    string getWordUnderCursor() {
        string word = "";
        Node* temp = cursor;
        if (temp && temp->c == '|') {
            temp = temp->prev;
        }
        while (temp && (temp->c!=' ')) {
            word = temp->c + word;
            temp = temp->prev;
        }
        return word;
    }
    void spellCheck(){
        if(head!=NULL){
            string word = getWordUnderCursor();
            cout<<" _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl<<endl<<"|\tSpell Checker"<<endl;
            cout <<"|"<<endl<<"| Checking: "<<word<<" => ";
            if(word != ""){
                if(find(dictionary.begin(), dictionary.end(), word) != dictionary.end()){
                cout<<"Correct"<<endl<<"|"<<endl;
                }else{
                    vector<string> suggestions;
                    // Substitution
                    for(int i=0; i<word.length(); i++){
                        for(char c='a'; c<='z'; c++){
                            string modifiedWord = word;
                            modifiedWord[i] = c;
                            if(find(dictionary.begin(), dictionary.end(), modifiedWord) != dictionary.end()){
                                suggestions.push_back(modifiedWord);
                            }
                        }
                    }
                    // Omission
                    for(int i=0; i<word.length(); i++){
                        string modifiedWord = word;
                        modifiedWord.erase(i, 1);
                        if(find(dictionary.begin(), dictionary.end(), modifiedWord) != dictionary.end()){
                            suggestions.push_back(modifiedWord);
                        }
                    }
                    // Insertion
                    for(int i=0; i<=word.length(); i++){
                        for (char c='a'; c<='z'; c++){
                            string modifiedWord = word;
                            modifiedWord.insert(i, 1, c);
                            if(find(dictionary.begin(), dictionary.end(), modifiedWord) != dictionary.end()){
                                suggestions.push_back(modifiedWord);
                            }
                        }
                    }
                    // Reversal
                    for(int i=0; i<word.length()-1; i++){
                        string modifiedWord = word;
                        swap(modifiedWord[i], modifiedWord[i + 1]);
                        if(find(dictionary.begin(), dictionary.end(), modifiedWord) != dictionary.end()){
                            suggestions.push_back(modifiedWord);
                        }
                    }
                    if(suggestions.empty()) {
                        cout<< "You are a hopeless speller!" <<endl<<"|"<<endl;
                    }else{
                        cout << "Suggestions: ";
                        for (const string& suggestion : suggestions) {
                            cout<<suggestion<<", ";
                        }
                        cout<<endl<<"|"<<endl;
                    }
                }
            }else{
                cout<<endl<<"|"<<endl;
            }
        } 
    }
    void loadDictionary(const string& dict){
        ifstream file(dict);
        string word;
        while(file>>word){
            dictionary.push_back(word);
        }
        file.close();
    }
    void saveToFile(const string& filename){
        ofstream file(filename);
        Node* i = head;
        Node* j = head;
        while(i){
            while(j){
                if (j->c == '\n') {
                    file << endl;
                } else {
                    if(j->c != '|')
                        file << j->c;
                }
                j = j -> next;
            }
            i = i->below;
            j = i;
        }
        file.close();
        system("cls");
        cout<<endl<<"File has been saved"<<endl;
        system("pause");
    }
    void loadFromFile(const string& filename, Notepad& N){
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open the file for loading." << endl;
            return;
        }
        char ch;
        while(file.get(ch)){
            N.in(ch);
        }
        system("cls");
        cout<<endl<<"File loaded"<<endl;
        system("pause");
        file.close();
    }
};
void handleInput(Notepad& N) {
    int ch = getch();
    if (ch==0 || ch==224){
        ch = getch(); // Geting the actual key code
        switch (ch) {
            case 72: // Up arrow
                N.cursor_up();
                break;
            case 80: // Down arrow
                N.cursor_down();
                break;
            case 75: // Left arrow
                N.cursor_left();
                break;
            case 77: // Right arrow
                N.cursor_right();
                break;
            default:
                break;
        }
    }else{
        switch (ch) {
            case 27: // Escape key
                exit(0);
                break;
            case 13: // Enter key
                N.in('\n');
                break;
            case 8: // Backspace key
                N.del();
                break;
            case 19: // Ctrl + S
                N.saveToFile("save.txt");
                break;
            case 12: // Ctrl + L
                N.loadFromFile("save.txt", N);
                break;
            default:
                N.in(char(ch));
                break;
        }
    }
}
void notepad(){
    Notepad N;
    N.loadDictionary("dictionary.txt");
    while(1){
        system("cls");
        N.spellCheck();
        N.connect();
        cout<<" _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl<<endl<<"\t  Notepad"<<endl<<endl;
        N.display();
        handleInput(N);
    }
}
int main(){
    notepad();
    return 0;
}