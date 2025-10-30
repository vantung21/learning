#include <iostream>
using namespace std;
template <typename T> class LinkList;

template <typename T>
ostream& operator<<(ostream &out, const LinkList<T> &list);

template <typename T>
class LinkList{
    private:
        struct node{
            T data;
            node *next;
        };
        node *head;
        node *tail;
    public:
        LinkList();
        ~LinkList();
        LinkList(const LinkList &other);

        void addfirst(T value);
        void addlast(T value);
        void addat(int index, T value);
        void removefirst();
        void removelast();
        void removeat(int index);
        void remove(T value);
        friend ostream& operator<< <>(ostream &out, const LinkList<T> &list);
        T& operator[](int index);
        void sapxep(bool (*cmp)(T, T));
        int search(T value);
};
template <typename T>
LinkList<T>::LinkList() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
LinkList<T>::~LinkList() {
    node *current = head;
    while (current != nullptr) {
        node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename T>
LinkList<T>::LinkList(const LinkList &other) {
    head = nullptr;
    tail = nullptr;
    node *current = other.head;
    while (current != nullptr) {
        addlast(current->data);
        current = current->next;
    }
}

template <typename T>
void LinkList<T>::addfirst(T value) {
    node *newNode = new node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}

template <typename T>
void LinkList<T>::addlast(T value) {
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

template <typename T>
void LinkList<T>::addat(int index, T value) {
    if (index < 0) {
        throw out_of_range("Index cannot be negative");
    }
    if (index == 0) {
        addfirst(value);
        return;
    }
    node *newNode = new node;
    newNode->data = value;
    node *current = head;
    for (int i = 0; i < index - 1 && current != nullptr; i++) {
        current = current->next;
    }
    if (current == nullptr) {
        throw out_of_range("Index out of range");
    }
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr) {
        tail = newNode;
    }
}

template <typename T>
void LinkList<T>::removefirst() {
    if (head == nullptr) {
        throw out_of_range("List is empty");
    }
    node *temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
        tail = nullptr;
    }
}

template <typename T>
void LinkList<T>::removelast() {
    if (head == nullptr) {
        throw out_of_range("List is empty");
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    node *current = head;
    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
}

template <typename T>
void LinkList<T>::removeat(int index) {
    if (index < 0) {
        throw out_of_range("Index cannot be negative");
    }
    if (index == 0) {
        removefirst();
        return;
    }
    node *current = head;
    for (int i = 0; i < index - 1 && current != nullptr; i++) {
        current = current->next;
    }
    if (current == nullptr || current->next == nullptr) {
        throw out_of_range("Index out of range");
    }
    node *temp = current->next;
    current->next = temp->next;
    if (temp == tail) {
        tail = current;
    }
    delete temp;
}

template <typename T>
void LinkList<T>::remove(T value) {
    if (head == nullptr) {
        throw out_of_range("List is empty");
    }
    if (head->data == value) {
        removefirst();
        return;
    }
    node *current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }
    if (current->next == nullptr) {
        throw out_of_range("Value not found in the list");
    }
    node *temp = current->next;
    current->next = temp->next;
    if (temp == tail) {
        tail = current;
    }
    delete temp;
}

template <typename T>
ostream& operator<<(ostream &out, const LinkList<T> &list) {
    typename LinkList<T>::node *current = list.head;
    out << "[";
    while (current != nullptr) {
        out << current->data;
        current = current->next;
        if (current != nullptr) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

template <typename T>
T& LinkList<T>::operator[](int index) {
    if (index < 0) {
        throw out_of_range("Index cannot be negative");
    }
    node *current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    if (current == nullptr) {
        throw out_of_range("Index out of range");
    }
    return current->data;
}

template <typename T>
bool ascending(T a, T b) {
    return a < b;
};

template <typename T>
bool descending(T a, T b) {
    return a > b;
};

template <typename T>
void LinkList<T>::sapxep(bool (*cmp)(T, T)) {
    if (head == nullptr) {
        return;
    }
    for (node *i = head; i != nullptr; i = i->next) {
        for (node *j = i->next; j != nullptr; j = j->next) {
            if (cmp(j->data, i->data)) {
                T temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

template <typename T>
int LinkList<T>::search(T value) {
    node *current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; 
}
int main(){
    LinkList<int> list;
    list.addlast(5);
    list.addlast(2);
    list.addlast(8);
    list.addfirst(1);
    cout << list << endl;
    list.addat(2, 3);
    cout << list << endl;
    list.removeat(3);
    cout << list << endl;
    list.removefirst();
    cout << list << endl;
    list.removelast();
    cout << list << endl;
    list.remove(3);
    cout << list << endl;
    list.addlast(7);
    list.addlast(4);
    list.addlast(6);
    cout << list << endl;
    list.sapxep(ascending);
    cout << "sap xep tang dan: " << list << endl;
    list.sapxep(descending);
    cout << "sap xep giam dan: " << list << endl;
    int index = list.search(4);
    if (index != -1) {
        cout << "4 found at index: " << index << endl;
    } else {
        cout << "4 not found in the list" << endl;
    }
    return 0;
}