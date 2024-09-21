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
    Node(T d, Node<T>* p) : data(d), next(p) {}
    void print() {
        cout << data << "->";
    }
};

template <class T, class O>
class List {
public:
    Node<T>* head;
    O comp;
public:
    List(T d) {
        head = new Node<T>(d, nullptr);
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

    bool find(T d, Node<T>*& elementoEncontrado) {
        Node<T>* current = head;
        elementoEncontrado = nullptr;
        Node<T>* previous = nullptr;

        while (current && comp(current->data, d)) {
            previous = current;
            current = current->next;
        }

        elementoEncontrado = previous;

        if (current && current->data == d)
            return true;

        return false;
    }

    void add(T d) {
        Node<T>* elementoEncontradoAdd;
        if (find(d, elementoEncontradoAdd)) {
            cout << "Repetido\n";
            return;
        }

        Node<T>* newNode = new Node<T>(d, nullptr);

        if (elementoEncontradoAdd == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            newNode->next = elementoEncontradoAdd->next;
            elementoEncontradoAdd->next = newNode;
        }
    }

    void del(T d) {
        Node<T>* elementoEncontradoAnterior;
        if (find(d, elementoEncontradoAnterior)) {
            Node<T>* toDelete = (elementoEncontradoAnterior) ? elementoEncontradoAnterior->next : head;
            if (elementoEncontradoAnterior)
                elementoEncontradoAnterior->next = toDelete->next;
            else
                head = toDelete->next;

            delete toDelete;
        }
        else {
            cout << "No encontrado\n";
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
