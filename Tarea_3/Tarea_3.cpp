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

template <class T, class O>
struct Node {
public:
    T* data;
    T* top;
    Node<T, O>* next;
    O oper;
    int capacity = 0;
    Node(int d, Node<T, O>* p) {
        data = new T[d];
        next = p;
        top = data;
        capacity = d;
    }
    void print() {
        cout << "[";
        for (T* i = data; i < top - 1; i++) {
            cout << *i << ", ";
        }
        cout << *(top - 1) << "]";
    }

    bool findEnNodo(T d, T*& elementoEncontrado) {
        T* current = data;
        elementoEncontrado = current;
        for (T* current = data; current < top; current++) {
            if (oper(*current, d)) {
                elementoEncontrado = current;
            }
            else if (*current == d) {
                elementoEncontrado = current;
                return true;
            }
        }
        return false;
    }

    bool necesitaOtroNodo() {
        if (top - data < capacity) {
            return false;
        }
        return true;
    }

    void insertSimple(T d, T* elementoAnterior) {
        //Aquí tengo un acceso malo de memoria porque top está fuera de los límites de la lista y *current empieza estando afuera
        for (T* current = top; current > elementoAnterior; --current) {
            *current = *(current - 1);
        }
        *elementoAnterior = d;
        top++;
        return;
    }

    bool insertComplejo(T d, T* elementoAnterior, T& ultimoElemento) {
        if (!next && elementoAnterior == top - 1) {
            Node<T, O>* nuevoNodo = new Node<T, O>(capacity, nullptr);
            next = nuevoNodo;
            *(next->data) = d;
            next->top++;
            return false;
        }
        ultimoElemento = *(top - 1);
        for (T* current = top; current > elementoAnterior; --current) {
            *current = *(current - 1);
        }
        *elementoAnterior = d;
        return true;
    }

    void delSimple(T* elementoAEliminar) {
        for (T* current = elementoAEliminar; current < top - 1; ++current) {
            *current = *(current + 1);
        }
        top--;
    }

    bool delComplejo(T* elementoAEliminar) {
        delSimple(elementoAEliminar);

        if (next && next->data != next->top) {
            *(top) = *(next->data);
            top++;
            next->delSimple(next->data);
            return false;
        }

        return true;
    }


    ~Node() {
        delete[] data;
    }
};

template <class T, class O>
struct List {

    Node<T, O>* head;
    T* last;
    int elementosPorNodo;
    O comp;

    List(int d) {
        elementosPorNodo = d;
        head = new Node<T, O>(elementosPorNodo, nullptr);
        last = head->data;
    }
    ~List() {
        while (head) {
            Node<T, O>* p = head->next;
            delete head;
            head = p;
        }
    }
    void print() {
        Node<T, O>* current = head;
        cout << "HEAD->";
        while (current) {
            current->print();
            current = current->next;
            cout << "->";
        }
        cout << "FIN\n";
    }

    bool find(T d, Node<T, O>*& nodoEncontrado, T*& elementoEncontradoEnElNodo) {
        Node<T, O>* current = head;
        nodoEncontrado = current;
        elementoEncontradoEnElNodo = current->data;
        T current_last = *((current->top) - 1);
        while (current) {
            current_last = *((current->top) - 1);
            if (comp(d, current_last) || current_last == d) {
                if (current->findEnNodo(d, elementoEncontradoEnElNodo)) {
                    nodoEncontrado = current;
                    return true;
                }
            }
            current = current->next;
        }
        return false;
    }

    void add(T d) {
        Node<T, O>* nodoEncontradoEnAdd;
        T* elementoEncontradoEnAdd;
        if (find(d, nodoEncontradoEnAdd, elementoEncontradoEnAdd)) {
            cout << "Repetido\n";
            return;
        }

        if (nodoEncontradoEnAdd->necesitaOtroNodo()) {
            T ultimoElementoDelNodo;
            while (nodoEncontradoEnAdd && nodoEncontradoEnAdd->insertComplejo(d, elementoEncontradoEnAdd, ultimoElementoDelNodo)) {
                if (nodoEncontradoEnAdd->next) {
                    add(ultimoElementoDelNodo);
                    return;
                }
                else {
                    Node<T, O>* nuevoNodo = new Node<T, O>(elementosPorNodo, nullptr);
                    nodoEncontradoEnAdd->next = nuevoNodo;
                    *(nuevoNodo->data) = ultimoElementoDelNodo;
                    nuevoNodo->top++;
                    last = nuevoNodo->data;
                    return;
                }
            }
        }
        else {
            nodoEncontradoEnAdd->insertSimple(d, elementoEncontradoEnAdd);
            last = nodoEncontradoEnAdd->top - 1;
            return;

        }
    }

    void del(T d) {
        Node<T, O>* nodoEncontrado;
        T* elementoEncontrado;

        if (find(d, nodoEncontrado, elementoEncontrado)) {
            if (nodoEncontrado->next == nullptr && nodoEncontrado->top - nodoEncontrado->data > 1) {
                nodoEncontrado->delSimple(elementoEncontrado);
            }
            else {
                if (!nodoEncontrado->delComplejo(elementoEncontrado)) {
                    nodoEncontrado = nodoEncontrado->next;
                    Node<T, O>* nodoPrevio = head;
                    while (nodoPrevio->next && nodoPrevio->next != nodoEncontrado) {
                        nodoPrevio = nodoPrevio->next;
                    }
                    nodoPrevio->next = nodoEncontrado->next;
                    delete nodoEncontrado;
                }
            }
        }
        else {
            cout << "\nNo existe en la lista\n";
        }
    }
};

int main() {
    List<int, asc<int>> H(5);
    H.add(6);
    H.add(5);
    H.add(4);
    H.add(3);
    H.add(2);
    H.add(1);
    H.print();
    H.del(2);
    H.print();
    return 0;
}