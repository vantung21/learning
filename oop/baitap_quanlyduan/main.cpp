#include <iostream>
#include "LinkedList.h"
#include "Exception.h"
#include "ResearchProject.h"

using namespace std;

int main(){
    system("clear || cls");
    LinkedList<ResearchProject*> list;
    list.loadFromFile("projects.txt");
    int choice;

    do{
        cout << "\n=========== RESEARCH PROJECT MANAGEMENT ===========\n";
        cout << "1. Add new project\n2. Delete by ID\n3. Search by ID\n";
        cout << "4. Display all\n";
        cout << "5. Statistics\n";
        cout << "6. Sort by Year\n7. Sort by Author\n";
        cout << "8. Calculate total funding and duration of Research Grants\n";
        cout << "9. Save to file\n10. Exit\n";
        cout << "===================================================\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        try{
            if(choice == 1){
                int id, year;
                string title;
                string author;
                cout << "Enter ID: " ; cin >> id; cin.ignore();
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin , author);
                cout << "Enter Year: "; cin >> year;
                cin.ignore();
                if(year < 2000 || year > 2025){
                    throw InvalidYearException(year);
                }
                cout << "Type (1=Journal, 2=Conference, 3=Grant): ";
                int type; cin >> type; cin.ignore();

                ResearchProject* p = NULL;
                if(type == 1){
                    string jname; int impact;
                    cout << "Journal Name: "; getline(cin, jname);
                    cout << "Impact Factor: "; cin >> impact;
                    if (impact < 0) throw InvalidValueException("impact factor");
                    p = new JournalPaper(id, title, author, year, jname, impact);
                }
                else if (type == 2) {
                    string conf, loc;
                    cout << "Conference Name: "; getline(cin, conf);
                    cout << "Location: "; getline(cin, loc);
                    p = new ConferencePaper(id, title, author, year, conf, loc);
                }
                else if (type == 3) {
                    double budget; int duration;
                    cout << "Budget (million VND): "; cin >> budget;
                    cout << "Duration (months): "; cin >> duration;
                    if (budget < 0) throw InvalidValueException("budget");
                    p = new ResearchGrant(id, title, author, year, budget, duration);
                }
                else {
                    cout << "Invalid type.\n";
                    continue;
                }
                list.add(p);
                cout << "Added successfully!\n";
            }
            else if(choice == 2){
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;  cin.ignore();
                list.removeByID(id);
            }
            else if(choice == 3){
                int id;
                cout << "Enter ID to search: ";
                cin >> id; cin.ignore();
                ResearchProject* p = list.searchByID(id);
                if(p != NULL){
                    p->display();
                }
                else{
                    cout << "Not found.\n";
                }
            }
            else if(choice == 4){
                list.showList();
            }
            else if(choice == 5){
                list.statistics();
            }
            else if(choice == 6){
                list.sortByYear();
                cout << "Sorted by Year.\n";
            }
            else if(choice == 7){
                list.sortByAuthor();
                cout << "Sorted by Author.\n";
            }
            else if(choice == 8){
                list.calculateTotalFundingAndDuration();
            }
            else if(choice == 9){
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                list.saveToFile(filename);
                cout << "Saved to " << filename << endl;
            }
            else if(choice == 10){
                break;
            }
        }
        catch(exception &e){
            cout << e.what() <<endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        getchar();
        system("clear || cls");
    }while(choice != 10);

    list.saveToFile("projects.txt");
    cout << "END\n";
    return 0;
}