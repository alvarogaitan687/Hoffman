#include <iostream>

using namespace std;

const string FLECHA = "↓";

struct par_int{
    int primero;
    int segundo;
};

par_int new_par(int fst, int snd){
    par_int result;
    result.primero = fst;
    result.segundo = snd;
    return result;
}

bool operator <=(par_int e1, par_int e2){
    return (e1.segundo <= e2.segundo);
}

ostream & operator <<(ostream& o, par_int x){
    o<<'('<<x.primero<<','<<x.segundo<<')';
    return o;
}

void mostrar(par_int e){
    cout << "("<<e.primero<<","<<e.segundo<<")";
};

template <typename T>
struct nodo_sec{
    T dato;
    nodo_sec<T> * sig;
};

template <typename T>
struct secuencia{
    nodo_sec<T> * primero;
    nodo_sec<T> * anterior;
};

template <typename T>
secuencia<T> crear(){
    secuencia s;
    s.primero = new nodo_sec<T>;
    s.anterior = s.primero;
    return s;
}





int main(){
    return 0;
}