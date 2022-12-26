#include<iostream>

using namespace std;

int CAP_INIC = 10;


template <typename T>
struct monticulo_max{
    T * datos = new T[CAP_INIC];
    int cap = CAP_INIC;
    int tam = 0;
};

template <typename T>
void duplicar_cap(monticulo_max<T> & m){
    T* new_datos = new T[m.cap*2];
    for(int i = 0;i<m.tam;i++){
        new_datos[i] = m.datos[i]; 
    }
    delete[] m.datos;
    m.datos = new_datos;
    m.cap = m.cap*2;
}

/*swap está definida en std como:
template <T typename>
void swap(T & a,T & b){
     T aux = a;
     a = b;
     b = aux;
}
*/

template <typename T>
void flotar(monticulo_max<T> & m, int pos){
    int i = pos;
    while(i > 0 && m.datos[i] > m.datos[(i-1)/2]){
        swap(m.datos[i],m.datos[(i-1)/2]);
        i = (i-1)/2;
    }
}

template <typename T>
void insertar(monticulo_max<T> & m,T e){
    if(m.tam == m.cap){
        duplicar_cap(m);
    }
    m.datos[m.tam] = e;
    flotar(m,m.tam);
    m.tam++;
}

template <typename T>
void hundir(monticulo_max<T> & m, int pos){
    int i = pos;
    bool seguir = true;
    int hijo_izdo;
    int hijo_dcho;
    int sig;
    while(seguir){
        hijo_izdo = 2*i + 1;
        hijo_dcho = 2*i + 2;
        if(hijo_izdo < m.tam){
            sig = i;
            if(m.datos[hijo_izdo] > m.datos[i]){
                sig = hijo_izdo;
            }
            if(hijo_dcho <m.tam && m.datos[hijo_dcho]>m.datos[sig]){
                sig = hijo_dcho;
            }
            if(sig == i){
                seguir = false;   
            }
            else{
                swap(m.datos[sig],m.datos[i]);
                i = sig;
            }
        }
        else{ /*Estamos en una hoja*/
            seguir = false;
        }
    }
}

template <typename T>
T max(const monticulo_max<T> & m){
    return m.datos[0];
}

template <typename T>
void elimina_max(monticulo_max<T> & m){
    swap(m.datos[0],m.datos[m.tam-1]);
    m.tam--;
    hundir(m,0);
}

template <typename T>
void liberar(monticulo_max<T> & m){
    delete[] m.datos;
}

template <typename T>
ostream &  operator <<(ostream & o, const monticulo_max<T> & m){
    for(int i = 0;i<m.tam;i++){
        o << m.datos[i]<<",";
    }
    o <<endl;
    return o;
}

template <typename T>
void heap_sort(T* ar,int tam){
    monticulo_max<T> m;
    for(int i = 0;i<tam;i++){
        insertar(m,ar[i]);
    }
    for(int i = 0;i<tam;i++){
        ar[i] = max(m);
        elimina_max(m);
    }
    liberar(m);
}



template <typename T>
void flotar(T datos[], int pos){
    int i = pos;
    while(i > 0 && datos[i] > datos[(i-1)/2]){
        swap(datos[i],datos[(i-1)/2]);
        i = (i-1)/2;
    }
}

template <typename T>
void hundir(T datos[] , int pos, int tam){
    int i = pos;
    bool seguir = true;
    int hijo_izdo;
    int hijo_dcho;
    int sig;
    while(seguir){
        hijo_izdo = 2*i + 1;
        hijo_dcho = 2*i + 2;
        if(hijo_izdo < tam){
            sig = i;
            if(datos[hijo_izdo] > datos[i]){
                sig = hijo_izdo;
            }
            if(hijo_dcho <tam && datos[hijo_dcho]>datos[sig]){
                sig = hijo_dcho;
            }
            if(sig == i){
                seguir = false;   
            }
            else{
                swap(datos[sig],datos[i]);
                i = sig;
            }
        }
        else{ /*Estamos en una hoja*/
            seguir = false;
        }
    }
}

template <typename T>
void heap_sort_in_situ(T* ar,int tam){
    for(int i = 0;i<tam;i++){
        flotar(ar,i);
    }
    int ultimo = tam - 1;
    while(ultimo!=0){
        swap(ar[0],ar[ultimo]);
        hundir(ar,0,ultimo);
        ultimo--;
    }
}

template <typename T>
void  mostrar(T datos[], int tam){
    for(int i = 0;i<tam;i++){
        cout << datos[i]<<",";
    }
    cout <<endl;
}

int main(){
	monticulo_max<int> m;
	for(int i = 0;i<30;i++){
	    insertar(m,rand()%30);
	}
//	cout << m;
	while(m.tam!=0){
	    cout<<max(m)<<",";
	    elimina_max(m);
	}
	cout << endl;

//	int   a[] = {1,2,4,556,3,4,2,34,121,4,8,9,3};
//	heap_sort(a,13);
//	mostrar(a,13);
//	int   b[] = {1,2,4,556,3,4,2,34,121,4,8,9,3};
//	heap_sort_in_situ(b,13);
//	mostrar(b,13);
//	liberar(m);
}


