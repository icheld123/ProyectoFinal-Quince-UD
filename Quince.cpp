/*
Autor:    Nicolás David Sabogal Velásquez
Programa: Generación de un puzzle "quince" Primer acercamiento
Fecha:    18/12/2020
*/

//Declaro librerías
#include <iostream> //Imput y Output
#include <clocale>  //Cambio del localismo para tildes
#include <cstdlib>  //Uso de rand() y srand()
#include <ctime>    //Uso de time para generar la semilla

#define P_MAX 4

//Evito escribir std:: cada vez
using namespace std;

//Prototipo funciones
void format(int puzzle[][P_MAX]);			//Asigna 0 en todos los elementos de la matriz
void crear(int puzzle[][P_MAX]);			//Genera una permutación aleatoria
bool check(int temp,int puzzle[][P_MAX]);   //Revisa si un número ya está en la matriz
void mostrar(int puzzle[][P_MAX]);			//Presenta la matriz

int main(){
	//Cambio el localismo
	setlocale(LC_ALL, "spanish");
	
	//Semilla pseudoaleatoria
	srand(time('\0'));
	
	char respuesta='s';
	while(respuesta=='s'){
		//Borro la pantalla
		system("CLS");
		
		//Presentación
		cout <<"¡Bienvenido!\nÉste es un puzzle \"quice\":\n"<<endl;
				
		//Delcaro e inicializo variables
		int puzzle[P_MAX][P_MAX]={0};
		
		//Generación del puzzle
		format(puzzle);
		crear(puzzle);
		
		//Presentación del puzzle
		mostrar(puzzle);
		cout <<endl;
		
		//Revisa si se repite
		cout <<"¿Desea generar otro? (s/n) ";
		cin >>respuesta;
		while(respuesta!='s'&&respuesta!='n'){
			cout <<"ERROR: Por favor ingrese un carácter válido (s/n) ";
			cin >>respuesta;
		}
		cout <<endl;
	}
	cout <<"¡Gracias por utilizar este programa! Presione una tecla para salir. ";
	cin.get();
	cin.ignore();
	
	return 0;
}

void format(int puzzle[][P_MAX]){
	for(int i=0;i<P_MAX;i++)				  //Se ejecuta para cada elemento de la matriz
		for(int j=0;j<P_MAX;j++)
			puzzle[i][j]=0;					  //Asigna 0 al elemento
}

void crear(int puzzle[][P_MAX]){
	int temp=0;
	for(int i=0; i<P_MAX; i++)				  //Se ejecuta para cada elemento de la matriz
		for(int j=0; j<P_MAX; j++){
			if(i==P_MAX-1&j==P_MAX-1) break;  //No se ejecuta para el último elemento
			do temp=rand()%(P_MAX*P_MAX-1)+1; //Genera un número aleatorio entre 1-15
			while(check(temp, puzzle));		  //Si el número está en la matriz, busca otro
			puzzle[i][j]=temp;				  //Guarda el número en el elemento
		}
}

bool check(int temp, int puzzle[][P_MAX]){
	bool repetido=0;
	for(int i=0; i<P_MAX; i++)				   //Se ejecuta para cada elemento de la matriz
		for(int j=0; j<P_MAX; j++){
			if(temp==puzzle[i][j]) repetido=1; //Compara temp con el elemento
		}
	return repetido;
}

void mostrar(int puzzle[][P_MAX]){
	for(int i=0;i<P_MAX;i++){
		cout <<" ";
		for(int j=0;j<P_MAX;j++){
			//Si el elemento es 0, muestra tres espacios
			if(puzzle[i][j]==0) cout <<"   ";
			//Si el elemento es menor a 9 pone un espacio antes
			else cout <<(puzzle[i][j]>9?"\0":" ")<<puzzle[i][j]<<" ";
		}
		cout <<endl;
	}
}
