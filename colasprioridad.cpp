#include <iostream>

using namespace std;

//Ord debe tener un orden definido, 
//como lo queremos usar con los AHuff y las tablas de frecuencia, en este caso Ord sería int y Elem char
template <typename Elem, typename Ord>
struct NodoP{
    Ord prioridad;
    Elem elemento;
    NodoP<Elem,Ord>* siguiente;
};

template <typename Elem, typename Ord>
using ColaP = NodoP<Elem,Ord>*;

//Queremos una función que no scree una cola con priorida vacia
template <typename Elem, typename Ord>
ColaP<Elem,Ord> cola_vacia(){
    return NULL;
}

//Necesitamos una funcion que nos indique si una cola esta vacia.
template <typename Elem, typename Ord>
bool es_cola_vacia(ColaP<Elem,Ord> c){
    return c == NULL;
}

//Vamos a crear una funcion que nos permita añadir un elemento a la cola.
template <typename Elem, typename Ord>
void aniadir(ColaP<Elem,Ord> & c, Elem e, Ord n){
    ColaP<Elem,Ord> nuevo = new NodoP<Elem,Ord>;
    nuevo->elemento = e;
    nuevo->prioridad = n;
    if(es_cola_vacia(c)){
        c = nuevo;
        nuevo->siguiente = NULL;
    }
    else if(c->prioridad>n){
        nuevo->siguiente = c;
        c = nuevo;
    }
    else{
        aniadir(c->siguiente,e,n);
    }
}

//Vamos a crear una función que permita eliminar un elemento de una cola.
template <typename Elem, typename Ord>
void eliminar(ColaP<Elem,Ord> & c, Elem e, Ord n){
    ColaP<Elem,Ord> actual = c;
    NodoP<Elem,Ord>* aux;
    if(c->prioridad == n && c->elemento == e){
        aux = c;
        c = actual->siguiente;
        delete aux;
    }
    else{
        while((!es_cola_vacia(actual->siguiente)) && actual->siguiente->prioridad<=n && actual->siguiente->elemento!=e){
            actual = actual->siguiente;
        }
        aux = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        delete aux;
    }
}

//Vamos a crear una funcion que nos devuelva el primer nodo (será util para AHuff)
template <typename Elem, typename Ord>
NodoP<Elem,Ord> menor_elem(ColaP<Elem,Ord> c){
    return *c;
}

//Nos servirá para AHuff un afunción que nos devuelva el numero de elementos que tiene la colaP

template <typename Elem, typename Ord>
int longitud(ColaP<Elem,Ord> c){
    int i = 0;
    ColaP<Elem,Ord> copia = c;
    while(!es_cola_vacia(copia)){
        i++;
        copia = copia->siguiente;
    }
    return i;
}

//Creamos una función que nos muestra la cola por pantalla y asi poder hacer pruebas
template <typename Elem, typename Ord>
void mostrar(ColaP<Elem,Ord> c){
    ColaP<Elem,Ord> actual = c;
    while(!es_cola_vacia(actual)){
        cout<<"("<<actual->elemento<<","<<actual->prioridad<<")"<<" -> ";
        actual = actual->siguiente;
    }
    cout<<endl;
}

/*
int main(){
    bool seguir = true;
    ColaP<char,int> c = cola_vacia<char,int>(); 
    cout<<"Se ha creado una cola vacia "<<endl;
    while(seguir){
        int opt;
        cout<<"Indique quiere hacer: "<<endl;
        cout<<"[1] Añadir un elemento a la cola"<<endl;
        cout<<"[2] Eliminar un elemento de la cola"<<endl;
        cout<<"[3] Salir"<<endl;
        cin>>opt;
        if(opt == 1){
            int i;
            char l;
            cout<<"Que elemento desea añadir"<<endl;
            cin>>l;
            cout<<"Indique la prioridad"<<endl;
            cin>>i;
            aniadir<char,int>(c,l,i);
            cout<<"La cola queda de la siguiente manera: "<<endl;
            mostrar<char,int>(c);
            cout<<"El menor elemento es: "<<endl;
            cout<<"("<<menor_elem<char,int>(c).elemento<<","<<menor_elem<char,int>(c).prioridad<<")"<<endl;
        }
        else if( opt == 2 ){
            int i;
            char l;
            cout<<"Que elemento desea eliminar"<<endl;
            cin>>l;
            cout<<"Indique la prioridad"<<endl;
            cin>>i;
            eliminar<char,int>(c,l,i);
            cout<<"La cola queda de la siguiente manera: "<<endl;
            mostrar<char,int>(c);
            cout<<"El menor elemento es: "<<endl;
            cout<<"("<<menor_elem<char,int>(c).elemento<<","<<menor_elem<char,int>(c).prioridad<<")"<<endl;
        }
        else{
            cout<<"Adiós"<<endl;
            seguir = false;
        }
    }
    return 0;
}
*/