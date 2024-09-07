#include <iostream>
using namespace std;

template <class T, class O> struct Bubble {
    void operator() (T* ini, T* fin) {
        bool sigue = true;
        O op;
        while (ini < fin && sigue) {
            sigue = false;
            for (T* p = ini; p < fin; p++) {
                if (op(*p, *(p + 1))) {
                    swap(*p, *(p + 1));
                    sigue = true;
                }
            }
            fin--;
        }
    }
};

template <class T> class asc {
public:
    bool operator() (T a, T b) { return a > b; }
};

template <class T> class desc {
public:
    bool operator() (T a, T b) { return a < b; }
};

int main()
{
    int A[6] = { 6,5,3,4,2,1 };
    Bubble<int, asc<int>> b;
    b(A, (A + 5));

    for (int i = 0; i < 6; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;


    return 0;
}
