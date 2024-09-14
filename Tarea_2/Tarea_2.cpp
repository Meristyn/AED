#include <iostream>
using namespace std;

template <class T> class asc {
public:
    bool operator() (T a, T b) { return a < b; }
};

template <class T> class desc {
public:
    bool operator() (T a, T b) { return a > b; }
};

template <class T>
class Node {
public:
    T data;
    Node<T>* next;
    Node(T d, Node<T>* p) {
        data = d;
        next = p;
    }
    void print() {
        cout << data << "->";
    }
};

template <class T, class O>
class List {
public:
    Node<T>* head;
    Node<T>* end;
    O comp;
public:
    List(T d) {
        head = end = new Node<T>(d, nullptr);
    }
    ~List() {
        while (head) {
            Node<T>* p = head->next;
            delete head;
            head = p;
        }
    }
    void print() {
        Node<T>* current = head;
        while (current) {
            current->print();
            current = current->next;
        }
        cout << "FIN\n";
    }

    Node<T>* findprev(T d) {
        Node<T>* prev = nullptr;
        Node<T>* current = head;

        while (current && comp(current->data, d)) {
            prev = current;
            current = current->next;
        }
        return prev;
    }

    bool find(T d) {
        Node<T>* current = head;
        while (current) {
            if (current->data == d)
                return true;
            current = current->next;
        }
        return false;
    }

    void add(T d) {
        if (find(d)) {
            cout << "Repetido\n";
            return;
        }

        Node<T>* prev = findprev(d);
        Node<T>* newNode = new Node<T>(d, nullptr);

        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = prev->next;
            prev->next = newNode;
            if (newNode->next == nullptr) {
                end = newNode;
            }
        }
    }

    void del(T d) {
        Node<T>* prev = findprev(d);
        if (prev == nullptr || prev->next == nullptr) {
            cout << "No encontrado\n";
        }
        else {
            Node<T>* toDelete = prev->next;
            if (toDelete == end) {
                end = prev;
            }
            prev->next = toDelete->next;
            delete toDelete;
        }
    }
};

int main() {
    List<int, asc<int>> H(4);
    H.add(5);
    H.add(4);
    H.add(8);
    H.add(6);
    H.print();
    return 0;
}
