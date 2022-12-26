#include <iostream>



using namespace std;

const string FLECHA = "↓";


struct par_int{
  int primero ;
  int segundo ;
};

par_int new_par(int p,int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

bool operator <=(par_int e1,par_int e2){
  return e1.segundo<=e2.segundo;
};

ostream & operator<<(ostream & o, par_int e){
    o << "("<<e.primero<<","<<e.segundo<<")";
    return o;
};

void mostrar(par_int e){
    cout << "("<<e.primero<<","<<e.segundo<<")";
};


template <typename T>
struct Nodo_sec{
       T dato;
       Nodo_sec<T> * sig;
};

template <typename T>
struct Secuencia{
  Nodo_sec<T> * primero;
  Nodo_sec<T> * anterior; //puntero al anterior al actual
};

template <typename T>
Secuencia<T> crear(){
  Secuencia<T> s;
  s.primero = new Nodo_sec<T>;
  s.anterior = s.primero;
  return s;
};

template <typename T>
void insertar(Secuencia<T>& s,T e){
  Nodo_sec<T> * new_node = new Nodo_sec<T>;
  new_node->dato = e;
  new_node->sig = s.anterior->sig;
  s.anterior->sig = new_node;
  s.anterior = new_node;
};


template <typename T>
void eliminar(Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    Nodo_sec<T> * aux = s.anterior->sig;
    s.anterior->sig = aux->sig;
    delete aux;
  }
  else{
    throw runtime_error(" final de la  secuencia");
  }
};

template <typename T>
T actual(const Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    return s.anterior->sig->dato;
  }
  else{
    throw runtime_error(" final de la  secuencia");
  }
};

template<typename T>
void avanzar(Secuencia<T>& s){
  if(s.anterior->sig != NULL){
    s.anterior = s.anterior->sig;
  }
  else{
    throw runtime_error("final de la  secuencia");
  }
}


template<typename T>
void reiniciar(Secuencia<T>& s){
  s.anterior = s.primero;
}

template<typename T>
bool fin(Secuencia<T> s){
  return s.anterior->sig == NULL;
}

template<typename T>
void liberar(Secuencia<T> & s){
  reiniciar(s);
  while(!fin(s))
      eliminar(s);
  delete s.primero;
}

template<typename T>  // debe existir una procedimiento void mostrar(T dato) que mande
                      //la representación de dato a cout
void mostrar(Secuencia<T> s){
    Nodo_sec<T> * aux = s.primero;
    while(aux->sig != NULL){
      if(aux == s.anterior){
        cout << FLECHA;
      }
      mostrar(aux->sig->dato);
      cout <<  " ";
      aux = aux->sig;
    }
    cout << endl;
}

template<typename T>  //el operador << debe estar definido para datos de tipo T
                      //redefinición de << para secuencias
ostream &  operator<<(ostream & o, Secuencia<T> s){
    Nodo_sec<T> * aux = s.primero;
    while(aux->sig != NULL){
      if(aux == s.anterior){
        o << FLECHA;
      }
      o << aux->sig->dato;
      o <<  " ";
      aux = aux->sig;
    }
    o << endl;
    return o;
}

//template <T> // T debe tener definido el operador <=
//void ordenar(Secuencia<T>& s) //ordena la secuencia s,00

int main(){
    Secuencia<par_int> s = crear<par_int>();
    for(int i = 0; i< 100; i++){
      int n = rand() % 50;
      insertar(s,new_par(i,n));
    }
    reiniciar(s);
    //ordenar(s)
    for(int i = 0;i<25;i++){
      avanzar(s);
    }
    cout << s;
    liberar(s);
    return 0;
}
