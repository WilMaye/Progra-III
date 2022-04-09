#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <MMSystem.h>

using namespace std;
void lectura();


struct nodo{
    string pl = "";
    struct nodo *izq, *der;
};

typedef struct nodo *Arbol;

Arbol crearNodo(string pl){
	Arbol nuevoNodo = new(struct nodo);
	nuevoNodo->pl = pl;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;
	
	return nuevoNodo;
}

Arbol arbol = NULL;

void insertar(Arbol &arbol, string pl){
    if(arbol==NULL){
        arbol = crearNodo(pl);
    }
    else if(strcasecmp( pl.c_str(), arbol->pl.c_str() ) < 0)
        insertar(arbol->izq, pl);
    else if (strcasecmp( pl.c_str(), arbol->pl.c_str() ) > 0)
        insertar(arbol->der, pl);
}

void ingresardatos(){
    //Arbol arbol = NULL; 
	int n;  // numero de nodos del arbol
    string pl; // elemento a insertar en cada nodo
    cout << " Numero de nodos del arbol:  ";
    cin >> n;
    cout << endl;
    
    for(int i=0; i<n; i++){
        cout << " Palabra del nodo " << i+1 << ": ";
        cin >> pl;
        insertar(arbol, pl);
    }	
    
}

void lectura(){
	
	ifstream archivo;
	string palabra;
	
	archivo.open("palabras.txt", ios::in);
	
	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){
		getline(archivo, palabra);
		insertar(arbol, palabra);
	}
	
	archivo.close();
}

void play(string pl1){
    
    string archivo = pl1+ ".wav";
    cout<<PlaySound((LPCSTR)archivo.c_str(),NULL,SND_FILENAME | SND_ASYNC);
    
}

bool buscar(Arbol &arbol,string pl){
	if(arbol != NULL){
		if(strcasecmp( pl.c_str(), arbol->pl.c_str() ) == 0){
			cout << "Si existe la palabra, reproduciendo audio"<< endl;
			play(pl);
		}else if( strcasecmp( pl.c_str(), arbol->pl.c_str() ) > 0 ){
			return buscar(arbol->der,pl);
		}else if(strcasecmp(pl.c_str(), arbol->pl.c_str() ) < 0){
			return buscar(arbol->izq,pl);
		}else{
			cout << "No se encontro la palabra"<< endl;
		}
	}
}

void searchdatos(){
	string pl1; // elemento a insertar en cada nodo
    cout << "Ingrese la palabra a buscar:  ";
    cin >> pl1;
    buscar(arbol, pl1);
}

int main(){

	lectura();
	// creado Arbol
int opt;
do{
	system("cls");
	cout << "ARBOL BINARIO DE BUSQUEDA"<<endl;
	cout <<"1 Ingresar Datos al Arbol"<<endl;
	cout <<"2 Buscar palabra"<<endl;
	cout <<"Ingrese una Opcion"<<endl;
	cin>>opt;
	
	switch(opt){
		case 1: system("cls");ingresardatos();break;
		case 2: system("cls");searchdatos(); cout<<"."<<endl;system("pause"); break;
		default: cout<<"opcion no valida"<<endl;
	}

}while (opt!=2);

    cout << endl << endl;

    system("pause");
    return 0;
}

