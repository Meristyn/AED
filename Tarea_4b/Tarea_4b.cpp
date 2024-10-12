#include <iostream>
using namespace std;

template <class T> struct Node
{
    T data;
    Node<T>* next;
    Node(T value, Node<T>* nextNode = nullptr)
        : data(value), next(nextNode) {}
};

template <class T> struct Cola {

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    Cola() = default;
    void push(T value);
    bool pop(T& value);
    void print();
};

template<class T>
void Cola<T>::push(T value)
{
    if (!head) {
        head = new Node<T>(value);
        tail = head;
        return;
    }
    tail->next = new Node<T>(value);
    tail = tail->next;
}

template<class T>
bool Cola<T>::pop(T& value)
{
    if (head) {
        Node<T>* temp = head;
        value = head->data;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp;
        return true;
    }
    return false;
}

template<class T>
void Cola<T>::print()
{
    if (!head) {
        cout << "head->null\t" << "tail->null\n";
        return;
    }
    Node<T>* current = head;
    cout << "top";
    for (current; current; current = current->next) cout << "->" << current->data;
    cout << "<-tail\n";
}


int main()
{
    Cola<int> cola;
    cola.print();
    cola.push(5);
    cola.print();
    cola.push(3);
    cola.print();
    int valorpop;
    bool xd = cola.pop(valorpop);
    cout << "Elimino elemento: " << valorpop << " y es " << xd << endl;
    cola.print();
    xd = cola.pop(valorpop);
    cout << "Elimino elemento: " << valorpop << " y es " << xd << endl;
    cola.print();
}