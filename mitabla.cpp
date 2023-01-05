#include <iostream>
#include <vector>
#include "abb.cpp"

using namespace std;

template <typename K, typename V>
struct entrada{
    K clave;
    V valor;
};

template <typename K, typename V>
using tabla = Abb<entrada<K,V>>;

struct ClaveNoEncontrada: public std::exception{
    const char * what() const throw(){
        return "No se ha encontrado la clave en esta tabla" ;
    }
};


//template <class K, class V> std::ostream& operator<<(std::ostream& os, tabla<K,V> t);


//IMPLEMENTACIONES:
template <typename K, typename V>
bool operator <=(entrada<K,V> e1, entrada<K,V> e2){
    return e1.clave <= e2.clave;
}

template <typename K, typename V>
bool operator ==(entrada<K,V> e1, entrada<K,V> e2){
    return e1.clave == e2.clave;
}

template <typename K, typename V>
ostream operator <<(ostream & os, entrada<K,V> e){
    os << "(" << e.clave << "," << e.valor << ")";
    return os;
}

template <typename K, typename V>
tabla<K,V> tabla_vacia(){
    return abb_vacio<entrada<K,V>>();
}

template <typename K, typename V>
bool es_tabla_vacia(tabla<K,V> t){
    return t == NULL;
}

template <typename K, typename V>
bool esta_clave(tabla<K,V> t, K c){
    tabla<K,V> actual = t;
    entrada<K,V> e;
    e.clave = c;
    bool result = false;
    while(!es_tabla_vacia(actual)){
        if(actual->dato == e){
            actual = tabla_vacia<K,V>();
            result = true;
        }
        else if(actual->dato <= e){
            actual = actual->hijo_dcho;
        }
        else{
            actual = actual->hijo_izdo;
        }
    }
    return result;
}

int combinar(int n, int m){
    return n+m;
}

template<typename K, typename V>
void modificar(tabla<K,V> & t, K c, V v){
    entrada<K,V> e;
    e.clave = c;
    if(!esta_clave<K,V>(t,c)){
        ClaveNoEncontrada();
    }
    else if(t->dato == e){
        t->dato.valor = v;
    }
    else if(t->dato <= e){
        modificar(t->hijo_dcho,c,v);
    }
    else{
        modificar(t->hijo_izdo,c,v);
    }
}

template<typename K, typename V>
void aniadir(tabla<K,V> & t, entrada<K,V> e){
    insertar(t,e);
}

template <typename K, typename V>
void aniadir(tabla<K,V> & t, K c, V v){
    entrada<K,V> e;
    if(esta_clave<K,V>(t,c)){
        e.clave = c;
        e.valor = combinar(v,consultar(t,c));
    }
    else{
        e.clave = c;
        e.valor = v;
    }
    aniadir(t,e);
}


template <typename K, typename V>
tabla<K,V> consultar_nodo(tabla<K,V> & t, K c){
    entrada<K,V> e;
    e.clave = c;
    if(!esta_clave<K,V>(t,c)){
        throw ClaveNoEncontrada();
    }
    else if(t->dato == e){
        return t;
    }
    else if(t->dato <= e){
        return consultar_nodo(t->hijo_dcho,c);
    }
    else{
        return consultar_nodo(t->hijo_izdo,c);
    }
}

template <typename K, typename V>
V consultar(tabla<K,V> & t, K c){
    return consultar_nodo(t,c)->dato.valor;
}

template <typename K, typename V>
void mostrar(tabla<K,V> t){
    if(!es_tabla_vacia(t)){
        mostrar<K,V>(t->hijo_izdo);
        cout<<" -------"<<endl;
        cout<<"| "<<t->dato.clave<<" | "<<t->dato.valor<<" |"<<endl;
        mostrar<K,V>(t->hijo_dcho);
    }
}

template <typename K, typename V>
void mostrar(entrada<V,K> e){
    cout<<"("<< e.clave << "," << e.valor << ")" << endl;
}

template <typename K, typename V>
entrada<K,V> mayor(tabla<K,V> t){
    tabla<K,V> actual = t;
    while(!es_tabla_vacia(actual->hijo_dcho)){
        actual = actual->hijo_dcho;
    }
    return actual->dato;
}

template <typename K, typename V>
void eliminar(tabla<K,V> & t, K c){
    entrada<K,V> e;
    e.clave = c;
    if(!esta_clave(t,c)){
        throw ClaveNoEncontrada();
    }
    else{
        if(t->dato == e){
            if(es_tabla_vacia(t->hijo_dcho)){
                t = t->hijo_izdo;
            }
            else{
                entrada<K,V> m = mayor<K,V>(t);
                t->dato = m;
                eliminar(t->hijo_izdo, m.clave);
            }
        }
        else if(t->dato <= e){
            eliminar(t->hijo_dcho,c);
        }
        else{
            eliminar(t->hijo_izdo,c);
        }
    }
}

/*
int main(){
    tabla<char,int> t = tabla_vacia<char,int>();
    aniadir<char,int>(t,'a',3);
    aniadir<char,int>(t,'b',4);
    aniadir<char,int>(t,'c',7);
    cout<<"Esta es la tabla original: "<<endl;
    mostrar(t);
    eliminar<char,int>(t,'c');
    cout<<"Aqui deberia haberse eliminado la c: "<<endl;
    mostrar(t);
    return 0;
}
*/