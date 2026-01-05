#ifndef RESEARCHPROJECT_H
#define RESEARCHPROJECT_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class ResearchProject{
    protected:
        int id;             // ma cong trinh (duy nhat)
        string title;        //ten cong trinh
        string author;       // ten tac gia chinh
        int year;           // nam cong bo hoac hoan thanh
    public:
        ResearchProject(int id, string title, string author, int year): id(id), title(title), author(author), year(year){}
        virtual void display() = 0;
        virtual ~ResearchProject(){}
        virtual string getType() = 0;
        int getID(){ return id;}
        string getTitle(){return title;}
        string getAuthor(){return author;}
        int getYear(){return year;}
};
void ResearchProject::display(){
    //cout << "ID: " << id << endl << "Title: " << title << endl << "Author: " << author << endl << "Year: " << year << endl;
    cout << setw(5) << right << "ID: " << id << ","
         << setw(10) << right << "Title: " << title << ","
         << setw(10) << right << "Author: " << author << ","
         << setw(10) << right << "Year: " << year <<",";
}


// bai bao dang tap chi
class JournalPaper : public ResearchProject {
    private:
        string journalName;  // ten tap chi 
        int impactFactor;   // chi so anh huong
    public:
        JournalPaper(int id, string title, string author, int year, string journalName, int impactFactor)
        : ResearchProject(id,title,author, year), journalName(journalName), impactFactor(impactFactor) {}
        ~JournalPaper(){}
        void display();
        string getJournalPaper(){return journalName;}
        int getImpactFactor(){return impactFactor;}
        string getType(){return "JournalPaper";}
};

void JournalPaper::display(){
    cout << setw(15) << left << "Journal_Paper";
    ResearchProject::display();
    cout << setw(15) << "Journal name: " << journalName << ","  << setw(15) << "Impact factor: " << impactFactor << endl;
}

//bai bao  hoi nghi
class ConferencePaper : public ResearchProject {
    private:
        string conferenceName;   //ten hoi nghi 
        string location;         // dia diem to chuc
    public:
        ConferencePaper(int id, string title, string author, int year, string conferenceName, string location)
        : ResearchProject(id,title,author, year), conferenceName(conferenceName), location(location) {}
        ~ConferencePaper(){}
        void display();
        string getConfer(){return conferenceName;}
        string getLoca(){return location;}
        string getType(){return "ConferencePaper";}
};

void ConferencePaper::display(){
    cout << setw(15) << left << "Conference_Paper";
    ResearchProject::display();
    cout << setw(15) << "Conference name: " << conferenceName << "," << setw(15) << "Location: " << location  << endl;
}

// de tai/ du an nghien cuu co kinh phi
class ResearchGrant : public ResearchProject {
    private:
        int budget;         //kinh phi (trieu dong)
        int duration;       //thoi gian thuc hien (thang)
    public:
        ResearchGrant(int id, string title, string author, int year, int budget, int duration)
        : ResearchProject(id,title,author, year), budget(budget), duration(duration) {}
        ~ResearchGrant() {}
        void display();
        int getBudget(){return budget;}
        int getDuration(){return duration;}
        string getType(){return "ResearchGrant";}
};

void ResearchGrant::display(){
    cout << setw(15) << left << "Research_Grant";
    ResearchProject::display();
    cout << setw(15) << "Budget: " << budget << "," << setw(15) << "Duration: " << duration << endl;
}

#endif 