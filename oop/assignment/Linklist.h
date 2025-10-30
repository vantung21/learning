#ifndef LINKLIST_H
#define LINKLIST_H

#include<iostream>
using namespace std;

inline bool Ascending(int a, int b) { return a < b; }   // tang
inline bool Descending(int a, int b) { return a > b; } // giam

class Linklist;
class Node{
    private:
        int data;
        Node* next;
    public:
        Node(int x  = 0): data(x), next(NULL){}
        friend class Linklist;
        friend ostream& operator << (ostream& out, Linklist& l);
};

class Linklist{
    private:
        Node* head;
        Node* tail;
    public:
        Linklist();
        ~Linklist();
        Linklist(const Linklist &l);
        void addfirst(int x);
        void addlast(int x);
        void addafter(int y, int x);
        void removefirst();
        void removelast();
        void removeafter(int y);
        void insert(int x);
        void remove(int x);
        friend ostream& operator << (ostream& out, Linklist& l);
        void sort(bool (*cmp)(int, int));
};

#endif