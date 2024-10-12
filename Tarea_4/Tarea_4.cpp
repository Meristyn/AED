#include <iostream>
using namespace std;

template <class T> struct Node
{
    T data;
    Node<T>* next;
    Node(T value, Node<T>* nextNode = nullptr)
        : data(value), next(nextNode) {}
    void operator=(const T& other) { data = other; return; }
};

template <class T> struct Pila {

    Node<T>* top = nullptr;
    Pila() = default;
    void push(T value);
    bool pop(T& value);
    void print();
};

template<class T>
void Pila<T>::push(T value)
{
    top = new Node<T>(value, top);
}

template<class T>
bool Pila<T>::pop(T& value)
{
    if (top) {
        Node<T>* temp = top;
        value = top->data;
        top = top->next;
        delete temp;
        return true;
    }
    return false;
}

template<class T>
void Pila<T>::print()
{
    Node<T>* current = top;
    cout << "top->";
    for (current; current; current = current->next) cout << current->data << "->";
    cout << "null\n";
}


int main()
{
    Pila<int> pila;
    pila.print();
    pila.push(5);
    pila.print();
    pila.push(3);
    pila.print();
    int valorpop;
    bool xd = pila.pop(valorpop);
    cout << "Elimino elemento: " << valorpop << " y es " << xd << endl;
    pila.print();
    xd = pila.pop(valorpop);
    cout << "Elimino elemento: " << valorpop << " y es " << xd << endl;
    pila.print();
}