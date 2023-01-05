#include <iostream>
#include <fstream>
#include "mitabla.cpp"
#include <string>

using namespace std;

void registrar(tabla<char,int> & t, char c){
    if(esta_clave<char,int>(t,c)){
        int nuevo = consultar<char,int>(t,c) +1;
        //cout<<"esta clave "<<c<<" cuyo valor actual es "<<nuevo-1<<endl;
        modificar<char,int>(t,c,nuevo);
    }
    else{
        //cout<<"no esta clave"<<c<<endl;
        aniadir<char,int>(t,c,1);
    }
}

void frecuencias(tabla<char,int> & t, string texto){
    for(int i=0; i<texto.length();i++){
        registrar(t,texto[i]);
    }
}


int main(){
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
    mostrar(t);
    return 0;
}