// =================================================================
//
// File: main.cpp
// Author: Itzel Hernández Vargas
// Date: 18/09/2022
//
// =================================================================
#include <iostream>
#include <vector> 
#include "header.h"
#include <string>
#include <fstream>
#include "double_linked_list.h"

using namespace std;


//Insertion que acomoda a partir del mes

template <class T>
void insertionSortMes(std::vector<T> &v) {

	for(int i = 1; i < v.size(); i++){
		for(int j = i; j > 0 && stoi(v[j].substr(3,2)) < stoi(v[j - 1].substr(3,2)); j--){
			swap(v, j, j - 1);
		}
	}
}

//insertion sort que acomoda a partir del día 
template <class T>
void insertionSortDia(std::vector<T> &v) {

	for(int i = 1; i < v.size(); i++){
		for(int j = i; j > 0 && stoi(v[j].substr(0,2)) < stoi(v[j - 1].substr(0,2)) && stoi(v[j].substr(3,2)) == stoi(v[j - 1].substr(3,2)) ; j--){
			swap(v, j, j - 1);
		}
	}
}

//insertion sort que acomoda a partir de la hora 
template <class T>
void insertionSortHora(std::vector<T> &v) {

	for(int i = 1; i < v.size(); i++){
		for(int j = i; j > 0 && stoi(v[j].substr(9,2)) < stoi(v[j - 1].substr(9,2)) && stoi(v[j].substr(3,2)) == stoi(v[j - 1].substr(3,2)) && stoi(v[j].substr(0,2)) == stoi(v[j - 1].substr(0,2)); j--){
			swap(v, j, j - 1);
		}
	}
}

//insertion sort que acomoda a partir del minuto
template <class T>
void insertionSortMinuto(std::vector<T> &v) {

	for(int i = 1; i < v.size(); i++){
		for(int j = i; j > 0 && stoi(v[j].substr(12,2)) < stoi(v[j - 1].substr(12,2)) && stoi(v[j].substr(3,2)) == stoi(v[j - 1].substr(3,2)) && stoi(v[j].substr(0,2)) == stoi(v[j - 1].substr(0,2))&& stoi(v[j].substr(9,2)) == stoi(v[j - 1].substr(9,2)); j--){
			swap(v, j, j - 1);
		}
	}
}


int main(int argc, char* argv[]) {

  ifstream inputFile;
  ofstream outputFile;

  inputFile.open(argv[1]);
  outputFile.open(argv[2]);
  
  int n;
  string prefix;
  

  //se introducen los datos
  inputFile >> n >> prefix;

  
  //se crea el arreglo donde se almacena la base de datos
  string base[n];

  //introduce valores de la base de datos
  for (int i = 0; i < n; i++){
    getline(inputFile  >> ws, base[i]);
  }

//en este vector se almacenan los datos que cumplan con el prefix
  vector <string> seleccionados;
  
  //recorre el arreglo buscando los strings que cumplan con el prefix y los añade al vector seleccionados 
  for(int i = 0; i < n; i++){

    //sequential search
    if ((base[i])[17] == prefix[0] && (base[i])[18] == prefix[1] && (base[i])[19] == prefix[2]){
      seleccionados.push_back(base[i]);
    }
  
  }


  insertionSortMes(seleccionados);
  insertionSortDia(seleccionados);
  insertionSortHora(seleccionados);
  insertionSortMinuto(seleccionados);
  
  n = seleccionados.size();


DoubleLinkedList<string> lista_R;
DoubleLinkedList<string> lista_M;

vector<string> meses;
int cont_mes = 0;
meses = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

for (int mes = 1; mes <= 12; mes++){

  lista_M.clear();
  lista_R.clear();

  for (int i = 0; i < n; i++){

    if(stoi(seleccionados[i].substr(3,2)) == mes && seleccionados[i].substr(15,1) =="M"){
      lista_M.push_back(seleccionados[i]);
    }

    else if(stoi(seleccionados[i].substr(3,2)) == mes && seleccionados[i].substr(15,1) =="R"){
      lista_R.push_back(seleccionados[i]);
    }
  }
  if(lista_M.length() == 0){
    outputFile << meses[cont_mes]<<endl <<"R "<<lista_R.length() << ": " << lista_R.toString()<<endl;

  }
  else if(lista_R.length() == 0 ){
    outputFile << meses[cont_mes]<< endl << "M "<<lista_M.length() <<": "  << lista_M.toString()<<endl;

  }

  else{
    outputFile << meses[cont_mes]<< endl << "M "<<lista_M.length() <<": "  << lista_M.toString()<<endl <<"R "<<lista_R.length() << ": " << lista_R.toString()<<endl;
  }
 
  cont_mes++;

}

  inputFile.close();
  outputFile.close();
  
}
