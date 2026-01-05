#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <fstream>
#include "Exception.h"
#include "ResearchProject.h"

using namespace std;

template<typename T>
struct node{
    T data;
    node* next;
    node(T x): data(x), next(NULL) {}
};

template <typename T>
class LinkedList{
    private:
        node<T>* head;
    public:
        LinkedList();
        ~LinkedList();
        bool exists(int ID) const;
        void add(T x);
        void remove(T x);
        void removeByID(int id);
        T search(T x);
        T searchByID(int id);
        void showList();
        void saveToFile(const string& filename) const;
        void loadFromFile(const string& filename);
        void statistics() const; //thong ke so luong
        void sortByYear();
        void sortByAuthor();
        //Tính tổng kinh phí và thời gian nghiên cứu của các ResearchGrant.
        void calculateTotalFundingAndDuration() const;

};

template<typename T>
LinkedList<T>::LinkedList(): head(NULL) {}

template<typename T>
LinkedList<T>::~LinkedList(){
    while(head){
        node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
bool LinkedList<T>::exists(int ID) const{
    node<T>* curr = head;
    while(curr){
        if(curr->data->getID() == ID){
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<typename T>
void LinkedList<T>::add(T x){
    if(exists(x->getID())){
        throw DuplicateIDException(to_string(x->getID()));
    }
    node<T>* temp = new node<T>(x);
    temp->next = head;
    head = temp;
}

template<typename T>
void LinkedList<T>::remove(T x){
    if(head == NULL){
        cout << "Danh sach rong! \n";
        return;
    }
    node<T>* curr = head;
    if(curr->data == x){
        head = curr->next;
        delete curr;
        return;
    }
    while(curr->next && curr->next->data != x){
        curr = curr->next;
    }
    if(curr->next == NULL){
        cout << " khong tim thay phan tu can xoa! \n";
    }
    else if(curr->next->data == x){
        node<T>* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::removeByID(int id){
    if(head == NULL){
        cout << "List is empty!\n";
        return;
    }
    node<T>* curr = head;
    if(curr->data->getID() == id){
        head = curr->next;
        delete curr;
        cout << "Deleted!\n";
        return;
    }
    while(curr->next && curr->next->data->getID() != id){
        curr = curr->next;
    }
    if(curr->next == NULL){
        cout << "Not found\n";
    }
    else if(curr->next->data->getID() == id){
        node<T>* temp = curr->next;
        curr->next = temp->next;
        delete temp;
        cout << "Deleted!\n";
    }
}

template<typename T>
T LinkedList<T>::search(T x){
    node<T>* curr = head;
    while(curr){
        if(curr->data == x){
            return curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

template<typename T>
T LinkedList<T>::searchByID(int id){
    node<T>* curr = head;
    while(curr){
        if(curr->data->getID() == id){
            return curr->data;;
        }
        curr = curr->next;
    }
    return NULL;
}

template<typename T>
void LinkedList<T>::showList(){
    if(head == NULL){
        cout << "Danh sach rong! \n";
        return;
    }
    node<T>* curr = head;
    while(curr){
        curr->data->display();
        curr = curr->next;
    }
}

template<typename T>
void LinkedList<T>::saveToFile(const string& filename) const{
    ofstream fout(filename);
    if(!fout.is_open()){
        cout << "Could not open file: " << filename << endl;
        return;
    }
    node<T>* curr = head;
    while(curr){
        T p = curr->data;
        fout << p->getType() << "|"
                << p->getID() << "|"
                << p->getTitle() << "|"
                << p->getAuthor() << "|"
                << p->getYear() << "|";
        if(p->getType() == "JournalPaper"){
            JournalPaper* jp = static_cast<JournalPaper*>(p);
            fout << jp->getJournalPaper() << "|"
                 << jp->getImpactFactor() << "\n";
        }
        else if(p->getType() == "ConferencePaper"){
            ConferencePaper* cp = static_cast<ConferencePaper*>(p);
            fout << cp->getConfer() << "|"
                 << cp->getLoca() << "\n";
        }
        else if(p->getType() == "ResearchGrant"){
            ResearchGrant* rg = static_cast<ResearchGrant*>(p);
            fout << rg->getBudget() << "|"
                 << rg->getDuration() << "\n";
        }
        curr = curr->next;
    }
    fout.close();
}

template<typename T>
void LinkedList<T>::loadFromFile(const string& filename){
    ifstream fin(filename);
    if(!fin.is_open()){
        cout << "Could not open file: " << filename << endl;
        return;
    }
    string type;
    while(getline(fin, type, '|')){
        int id, year;
        string title, author;
        fin >> id; fin.ignore();
        getline(fin, title, '|');
        getline(fin, author, '|');
        fin >> year; fin.ignore();

        ResearchProject* p = NULL;
        if(type == "JournalPaper"){
            string jname; int impact;
            getline(fin, jname, '|');
            fin >> impact; fin.ignore();
            p = new JournalPaper(id, title, author, year, jname, impact);
        }
        else if(type == "ConferencePaper"){
            string conf, loc;
            getline(fin, conf, '|');
            getline(fin, loc);
            p = new ConferencePaper(id, title, author, year, conf, loc);
        }
        else if(type == "ResearchGrant"){
            double budget; int duration;
            fin >> budget; fin.ignore();
            fin >> duration; fin.ignore();
            p = new ResearchGrant(id, title, author, year, budget, duration);
        }
        if(p) {
            try {
                add(p);
            } catch (const DuplicateIDException& e) {
                cout << e.what() << endl;
                delete p; // Avoid memory leak
            }
        }
        
    }
    fin.close();
}

template<typename T>
//thong ke so luong moi loai cong trinh
void LinkedList<T>::statistics() const{
    int journalCount = 0;
    int conferenceCount = 0;
    int grantCount = 0;
    node<T>* curr = head;
    while(curr){
        string type = curr->data->getType();
        if(type == "JournalPaper"){
            journalCount++;
        }
        else if(type == "ConferencePaper"){
            conferenceCount++;
        }
        else if(type == "ResearchGrant"){
            grantCount++;
        }
        curr = curr->next;
    }
    cout << "Statistics:\n";
    cout << "Journal Papers: " << journalCount << "\n";
    cout << "Conference Papers: " << conferenceCount << "\n";
    cout << "Research Grants: " << grantCount << "\n";
}

template<typename T>
void LinkedList<T>::sortByYear(){
    if(head == NULL || head->next == NULL){
        return;
    }
    for(node<T>* i = head; i != NULL; i = i->next){
        for(node<T>* j = i->next; j != NULL; j = j->next){
            if(i->data->getYear() > j->data->getYear()){
                T temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

template<typename T>
void LinkedList<T>::sortByAuthor(){
    if(head == NULL || head->next == NULL){
        return;
    }
    for(node<T>* i = head; i != NULL; i = i->next){
        for(node<T>* j = i->next; j != NULL; j = j->next){
            if(i->data->getAuthor() > j->data->getAuthor()){
                T temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

template<typename T>
void LinkedList<T>::calculateTotalFundingAndDuration() const{
    double totalBudget = 0;
    int totalDuration = 0;
    node<T>* curr = head;
    while(curr){
        if(curr->data->getType() == "ResearchGrant"){
            ResearchGrant* rg = static_cast<ResearchGrant*>(curr->data);
            totalBudget += rg->getBudget();
            totalDuration += rg->getDuration();
        }
        curr = curr->next;
    }
    cout << "Total Budget for Research Grants: " << totalBudget << " million VND\n";
    cout << "Total Duration for Research Grants: " << totalDuration << " months\n";
}


#endif