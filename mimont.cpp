#include <iostream>

using namespace std;

int CAP_INIC = 10;

template <typename T>
struct monticulo_max{
    T* datos = new T[CAP_INIC];
    int cap = CAP_INIC;
    int tam=0;
};

template <typename T> 
void duplicar_cap(monticulo_max<T> & m){
    T* newdatos=new T[m.cap*2];
    for(int i=0;i<m.tam;i++){
        newdatos[i] = m.datos[i];
    }
    delete[] m.datos;
    m.datos = newdatos;
    m.cap=m.cap*2;
}

template <typename T>
void flotar(monticulo_max<T> & m, int pos){
    int i = pos;
    while(i > 0 && m.datos[i] > m.datos[(i-1)/2]){
        swap(m.datos[i],m.datos[(i-1)/2]);
        i = (i-1)/2;
    }
}

template <typename T>
void insertar(monticulo_max<T> & m, T e){
    if(m.tam == m.cap){
        duplicar_cap(m);
    }
    m.datos[m.tam] = e;
    flotar(m,m.tam);
    m.tam++;
}

//mio
template <typename T>
void hundir(monticulo_max<T> & m, int pos){
    bool seguir = true;
    int i=pos;
    int hijo_izq;
    int hijo_der;
    int sig;
    while(seguir){
        hijo_izq = 2*i+1;
        hijo_der = 2*i+2;
        if(hijo_izq < m.tam){
            sig = i;
            if(m.datos[hijo_izq] > m.datos[i]){
                sig = hijo_izq;
            }
            if(hijo_der < m.tam && m.datos[hijo_der] > m.datos[sig]){
                sig = hijo_der;
            }
            if(sig == i){
                seguir = false;
            }
            else{
                swap(m.datos[i],m.datos[sig]);
                i=sig;
            }
        }
        else{
            seguir = false;
        }
    }
}

template <typename T>
T max(const monticulo_max<T> & m){
    return m.datos[0];
}

template <typename T>
void eliminar_max(monticulo_max<T> & m){
    swap(m.datos[0],m.datos[m.tam-1]);
    m.tam--;
    hundir(m,0);
}

template <typename T>
void liberar(monticulo_max<T> & m){
    delete[] m.datos;
}

template <typename T>
ostream & operator <<(ostream & o, monticulo_max<T> & m){
    for(int i = 0; i<m.tam-1; i++){
        o<<m.datos[i]<<',';
    }
    o<<m.datos[m.tam-1]<<endl;
    return o;
}

template <typename T>
void heap_sort(T* ar, int tam){
    monticulo_max<T> m;
    for(int i = 0; i<tam; i++){
        insertar(m, ar[i]);
    }
    for(int i = 0; i<tam; i++){
        ar[i]=max(m);
        eliminar_max(m);
    }
    liberar(m);
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
	// cout << m <<endl;
	while(m.tam!=0){
	    cout<<max(m)<<",";
	    eliminar_max(m);
	}
	cout << endl;
    /*
	int a[] = {1,2,4,556,3,4,2,34,121,4,8,9,3};
	heap_sort(a,13);
	mostrar(a,13);
    */
}