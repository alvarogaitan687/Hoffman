#include <iostream>
#include <fstream>
#include <vector>
#include "frecuencias.cpp"
#include "colasprioridad.cpp"

using namespace std;

void mostrar_vector(vector<bool> v);
template <typename K, typename V> class Nodo;
template <typename K, typename V> using AHuff = Nodo<K,V>*;
template <typename K, typename V> class Nodo;
template <typename K, typename V> bool es_vacio(AHuff<K,V> a);
template <typename K, typename V> void actCode(AHuff<K,V> & a, bool digito);
template <typename K, typename V> AHuff<K,V> enramar(AHuff<K,V> izdo, AHuff<K,V> dcho);
template <typename K, typename V> void crear_cola(ColaP<AHuff<K,V>,V> & c, tabla<K,V> t);
template <typename K, typename V> ColaP<AHuff<K,V>,V> iniciar_cola(tabla<K,V> t);
template <typename K, typename V> void iteracion(ColaP<AHuff<K,V>,V> & c);
template <typename K, typename V> AHuff<K,V> crear_ahuff(tabla<K,V> t);
void mostrar_vector(vector<bool> v);
template <typename K, typename V> void mostrar(AHuff<K,V> a, int n);
template <typename K, typename V> void tablaCod(AHuff<K,V> a, tabla<K,V> & t);
tabla<char,int> leer();

template <typename K, typename V>
class Nodo{
    public:
        V valor;
        K clave;
        vector<bool> codigo;
        Nodo* hijo_izdo;
        Nodo* hijo_dcho;
        Nodo(){};
        Nodo(V v, vector<bool> cod){
            valor = v;
            codigo = cod;
        }
        Nodo(V v, vector<bool> cod, AHuff<K,V> izdo, AHuff<K,V> dcho){
            valor =v;
            hijo_izdo = izdo;
            hijo_dcho = dcho;
            codigo = cod;
        }
        Nodo(V v, vector<bool> cod, K c){
            valor = v;
            codigo = cod;
            clave = c;
        }
        bool es_hoja(){
            return (hijo_dcho == NULL && hijo_izdo == NULL);
        }
};

template <typename K, typename V>
using AHuff = Nodo<K,V>*;

template <typename K, typename V>
bool es_vacio(AHuff<K,V> a){
    return a == NULL;
}

template <typename K, typename V>
void actCode(AHuff<K,V> & a, bool digito){
    int i = 0;
    if(!es_vacio(a)){
        (a->codigo).push_back(digito);
        mostrar_vector(a->codigo);
        cout<<endl;
        if(!es_vacio(a->hijo_izdo)){
            actCode<K,V>(a->hijo_izdo,digito);
        }
        if(!es_vacio(a->hijo_dcho)){
            actCode<K,V>(a->hijo_dcho,digito);
        }
    }
}


template <typename K, typename V>
AHuff<K,V> enramar(AHuff<K,V> izdo, AHuff<K,V> dcho){
    actCode<K,V>(izdo,false);
    actCode<K,V>(dcho,true);
    vector<bool> cod;
    AHuff<K,V> result = new Nodo<K,V>(izdo->valor+dcho->valor, cod, izdo, dcho);
    return result;
}

template <typename K, typename V>
void crear_cola(ColaP<AHuff<K,V>,V> & c, tabla<K,V> t){
    if(!es_tabla_vacia<K,V>(t)){
        if(!es_tabla_vacia(t->hijo_izdo)){
            crear_cola<K,V>(c,t->hijo_izdo);
        }
        vector<bool> cod;
        AHuff<K,V> a = new Nodo<K,V>(t->dato.valor, cod, t->dato.clave);
        aniadir<AHuff<K,V>,V>(c, a, a->valor);
        if(!es_tabla_vacia(t->hijo_dcho)){
            crear_cola<K,V>(c,t->hijo_dcho);
        }
    }
}

template <typename K, typename V>
ColaP<AHuff<K,V>,V> iniciar_cola(tabla<K,V> t){
    ColaP<AHuff<K,V>,V> c = cola_vacia<AHuff<K,V>,V>();
    crear_cola<K,V>(c,t);
    return c;
}

template <typename K, typename V>
void iteracion(ColaP<AHuff<K,V>,V> & c){
    AHuff<K,V> menor1 = menor_elem(c).elemento;
    V prioridad1 = menor_elem(c).prioridad;
    eliminar(c,menor1,prioridad1);
    AHuff<K,V> menor2 = menor_elem(c).elemento;
    V prioridad2 = menor_elem(c).prioridad;
    eliminar(c,menor2,prioridad2);
    mostrar(c);
    aniadir(c,enramar<K,V>(menor1,menor2),prioridad1+prioridad2);
}

template <typename K, typename V>
AHuff<K,V> crear_ahuff(tabla<K,V> t){
    ColaP<AHuff<K,V>,V> c = iniciar_cola(t);
    while(longitud<AHuff<K,V>,V>(c)>1){
        iteracion<K,V>(c);
    }
    AHuff<K,V> result = menor_elem<AHuff<K,V>,V>(c).elemento;
    return result;
}

void mostrar_vector(vector<bool> v){
    for(bool b:v){
        cout<<b;
    }
}

template <typename K, typename V>
void mostrar(AHuff<K,V> a, int n){
    if(!es_vacio(a)){
        mostrar(a->hijo_izdo, n+1);
        for(int i = 0; i<n;i++){
            cout<<"   ";
        }
        cout<<"("<<a->valor<<","<<a->clave<<",";
        mostrar_vector(a->codigo);
        cout<<")"<<endl<<endl;
        mostrar(a->hijo_dcho, n+1);
    }
}

template <typename K, typename V>
void tablaCod(AHuff<K,V> a, tabla<K,V> & t){
    if(!es_vacio(a)){
        tablaCod(a->hijo);
    }
}

tabla<char,int> leer(){
    string name;
    string myText;
    tabla<char,int> t;
    t = tabla_vacia<char,int>();
    cout<<"Indique el nombre del archivo "<<endl;
    cin>>name;
    ifstream myFile(name);
    while(getline(myFile,myText)){
        frecuencias(t,myText);
    }
    myFile.close();
    return t;
}

int main(){
    tabla<char,int> t;
    t = leer();
    int i = 0;
    AHuff<char,int> a = crear_ahuff<char,int>(t);
    mostrar<char,int>(a,i);
    return 0;
}