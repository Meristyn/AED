#include <iostream>
#include <cstdlib>
#include <ctime>

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
        top = nullptr;
        capacity = d;
    }

    void print() {
        cout << "[";
        if (!top) {
            cout << "lista vacia]";
            return;
        }
        for (T* i = data; i < top; i++) {
            cout << *i << ", ";
        }
        cout << *top << "]";
    }

    bool findEnNodo(T d, T*& elementoEncontrado) {
        if (!top) {
            elementoEncontrado = nullptr;
            return false;
        }
        elementoEncontrado = nullptr;
        T* ele = data;
        for (ele; ele <= top && (oper(*ele, d) || *ele == d); ele++) {
            elementoEncontrado = ele;
        }
        if (!elementoEncontrado) {
            return false;
        }
        else if (*elementoEncontrado == d) {
            return true;
        }
        return  false;
    }

    bool necesitaOtroNodo() {
        return (top - data >= capacity - 1);
    }

    bool hayElementoDesbordado(T* elementoInicial, T& elementoDesbordado) {
        if (!necesitaOtroNodo() || !top) {
            insert(elementoDesbordado, nullptr);
            return false;
        }

        T ele_reemplazo = elementoDesbordado;
        elementoDesbordado = *top;

        for (T* shift = top; shift > elementoInicial; shift--) {
            *shift = *(shift - 1);
        }

        *elementoInicial = ele_reemplazo;
        return true;
    }

    bool hayNodoParaEliminar(T* ElementoActual, Node<T, O>*& NodoAnteriorAEliminar) {
        bool falta_mover = false;
        T ele_final;
        if (next) {
            ele_final = *next->data;
            falta_mover = true;
            NodoAnteriorAEliminar = this;
        }
        else {
            delete NodoAnteriorAEliminar->next;
            NodoAnteriorAEliminar->next = nullptr;
            return falta_mover;
        }
        for (T* shift = ElementoActual; shift < top; shift++) {
            *(shift) = *(shift + 1);
        }
        *top = ele_final;
        return falta_mover;
    }

    bool del(T* elementoActual) {
        bool falta_mover = false;
        T ele_final = *top;
        for (T* shift = elementoActual; shift < top; shift++) {
            *(shift) = *(shift + 1);
        }
        if (next) {
            ele_final = *next->data;
            falta_mover = true;
        }
        else {
            top--;
        }
        *top = ele_final;
        return falta_mover;
    }

    void insert(T d, T* elementoAnterior) {
        if (!top) {
            *data = d;
            top = data;
            return;
        }
        if (!elementoAnterior) {
            for (T* current = top + 1; current > data; --current) {
                *current = *(current - 1);
            }
            *data = d;
        }
        else {
            for (T* current = top + 1; current > elementoAnterior + 1; --current) {
                *current = *(current - 1);
            }
            *(elementoAnterior + 1) = d;
        }
        top++;
        return;
    }

    ~Node() {
        delete[] data;
    }
};

template <class T, class O>
struct List {

    Node<T, O>* head;
    Node<T, O>* end;
    int elementosPorNodo;
    O comp;

    List(int d) {
        elementosPorNodo = d;
        head = nullptr;
        end = nullptr;
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
        if (!current->top) {
            elementoEncontradoEnElNodo = nullptr;
            return false;
        }

        for (current; current && (comp(*(current->data), d) || *(current->data) == d); current = current->next) {
            nodoEncontrado = current;
        }

        if (nodoEncontrado->findEnNodo(d, elementoEncontradoEnElNodo)) {
            return true;
        }
        if (!elementoEncontradoEnElNodo) {
            return false;
        }
        return false;
    }

    void manejarDesbordamiento(T d, Node<T, O>* nodoEncontradoEnAdd, T* elementoEncontradoEnAdd) {

        if (end->necesitaOtroNodo()) {
            Node<T, O>* nuevoNodo = new Node<T, O>(elementosPorNodo, nullptr);
            end->next = nuevoNodo;
            end = nuevoNodo;
        }

        if (elementoEncontradoEnAdd == nodoEncontradoEnAdd->top) {
            nodoEncontradoEnAdd = nodoEncontradoEnAdd->next;
            elementoEncontradoEnAdd = nodoEncontradoEnAdd->data;
        }
        else if (elementoEncontradoEnAdd) {
            elementoEncontradoEnAdd++;
        }
        else {
            elementoEncontradoEnAdd = nodoEncontradoEnAdd->data;
        }

        T* elementoInicial = elementoEncontradoEnAdd;
        Node<T, O>* current = nodoEncontradoEnAdd;
        T elementoDesbordado = d;

        while (current->hayElementoDesbordado(elementoInicial, elementoDesbordado) && current->next) {
            current = current->next;
            elementoInicial = current->data;
        }
    }

    void add(T d) {

        if (!head) {
            head = end = new Node<T, O>(elementosPorNodo, nullptr);
        }
        Node<T, O>* nodoEncontradoEnAdd;
        T* elementoEncontradoEnAdd;

        if (find(d, nodoEncontradoEnAdd, elementoEncontradoEnAdd)) {
            cout << "\nRepetido\n";
            return;
        }

        if (nodoEncontradoEnAdd->necesitaOtroNodo()) {
            manejarDesbordamiento(d, nodoEncontradoEnAdd, elementoEncontradoEnAdd);
        }
        else {
            nodoEncontradoEnAdd->insert(d, elementoEncontradoEnAdd);
        }
    }

    void del(T d) {
        Node<T, O>* nodoEncontradoEnDel;
        T* elementoEncontradoEnDel;
        if (!find(d, nodoEncontradoEnDel, elementoEncontradoEnDel)) {
            cout << "\nEl elemento no existe\n";
            return;
        }

        if (end->data == end->top) {
            if (elementoEncontradoEnDel == end->data) {
                Node<T, O>* current = head;
                for (current; current->next != nodoEncontradoEnDel; current = current->next) {}
                delete current->next;
                current->next = nullptr;
            }
            Node<T, O>* NodoAnteriorAEliminar;
            while (nodoEncontradoEnDel->hayNodoParaEliminar(elementoEncontradoEnDel, NodoAnteriorAEliminar)) {
                nodoEncontradoEnDel = nodoEncontradoEnDel->next;
                elementoEncontradoEnDel = nodoEncontradoEnDel->data;
            }
            end = NodoAnteriorAEliminar;
        }
        else {
            while (nodoEncontradoEnDel->del(elementoEncontradoEnDel)) {
                nodoEncontradoEnDel = nodoEncontradoEnDel->next;
                elementoEncontradoEnDel = nodoEncontradoEnDel->data;
            }
        }
    }
};

int main() {
    srand(time(NULL));
    List<int, asc<int>> lista(3);

    //PRUEBA PARA REVISIÓN


    //IMPRIME ESTRUCTURA EN BLANCO
    lista.print();

    //INGRESA 1 2 3 4 5
    lista.add(1);
    lista.add(2);
    lista.add(3);
    lista.add(4);
    lista.add(5);
    lista.print();

    //INGRESA 6 7 8 9
    lista.add(6);
    lista.add(7);
    lista.add(8);
    lista.add(9);
    lista.print();

    //BORRA 2 4 6 8
    lista.del(2);
    lista.del(4);
    lista.del(6);
    lista.del(8);
    lista.print();

    /*for (int i = 0; i < 13; i++) {
        int num = rand() % 100;
        cout << "Anadiendo " << num << "\n";
        lista.add(num);
        lista.print();
    }
    lista.print();

    for (int i = 0; i < 20; i++) {
        int num = rand() % 100;
        cout << "Eliminando " << num << "\n";
        lista.del(num);
        lista.print();
    }*/

    cout << "\n\n\n\t\tFIN DEL PROGRAMA\n\n";
    return 0;
}
