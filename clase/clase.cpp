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
    T* data;
    T* top;
    int num_ele;
    Node<T>* next;
    Node(int d, Node<T>* p) {
        T* data = new T[d];
        next = p;
        num_ele = d;
        top = &data[d - 1];
    }
    void print() {
        cout << "[";
        for (int i = 0; i < num_ele - 1; i++) {
            cout << data[i] << ", ";
        }
        cout << data[num_ele - 1] << "]";
    }
    ~Node() {
        delete[] data;
    }
};

template <class T, class O>
class List {
public:
    Node<T>* head;
    T* last_ele;
    int n;
    int nodos = 1;
    O comp;
public:
    List(int d) {
        n = d;
        head = new Node<T>(n, nullptr);
    }
    ~List() {
        while (head) {
            Node<T>* p = head->next;
            delete head;
            head = p;
        }
    }
    void print() {
        Node<T>* current = head->next;
        cout << "HEAD->";
        while (current) {
            current->print();
            current = current->next;
            cout << "->";
        }
        cout << "FIN\n";
    }

    Node<T>* findprev(T d) {
        int mitad = nodos / 2;
        int primero = 0;
        int ultimo = nodos - 1;
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
        }
    }

    void del(T d) {
        Node<T>* prev = findprev(d);
        if (prev == nullptr || prev->next == nullptr) {
            cout << "No encontrado\n";
        }
        else {
            Node<T>* toDelete = prev->next;
            prev->next = toDelete->next;
            delete toDelete;
        }
    }
};

int main() {
    List<int, asc<int>> H(-1);
    H.add(5);
    H.add(4);
    H.add(8);
    H.add(6);
    H.add(6);
    H.print();
    H.del(4);
    H.print();
    return 0;
}