  
/*
Autor:    Ichel Alejandra Delgado, reorg. Nicolás Sabogal
Programa: Reorganización Movimiento Puzzle Quince
Fecha:    17/01/2021
*/

//---------------------------------Librerías------------------------------------
#include <iostream>     //Imput y Output
#include <clocale>      //Cambio del localismo para tildes
#include <cstdlib>      //Uso de rand() y srand()
#include <ctime>        //Uso de time para generar la semilla

//--------------------------------Constantes------------------------------------
#define clear() system("CLS")	//limpia la pantalla.
#define N       4               //Orden del puzzle.

//-----------------------Prototipo de funciones---------------------------------
void crear(int puzzle[][N]);		    //Genera una permutación aleatoria con números 0-N^2.
void format(int puzzle[][N]);		    //Asigna -1 en todos los elementos de la matriz.
bool check(int puzzle[][N], int temp);  //Revisa si un número ya está en la matriz.
bool impos(int puzzle[][N]);            //Revisa si es posible resolver la matriz deslizando sus elementos.
int sacaInver(int puzzle[][N]);         //Cuenta cuántas inversiones hay en la matriz.
int ceroEnI(int puzzle[][N]);           //Identifica en que fila está el cero.
void mostrar(int puzzle[][N]);		    //Imprime la matriz.
bool mover(int puzzle[][N], char tecla);//Mueve las fichas en el puzzle.

//-----------------------------------Main---------------------------------------
using namespace std;                                //Evita escribir std:: cada vez que se refiere una librería.

int main(){
    //Herramientas
	setlocale(LC_ALL, "spanish");			        //Permite el uso de carácteres especiales.
	srand(time(NULL));                              //Crea una semilla aleatoria para rand().
	//Menú principal.
	char respuesta='\0';
	cout <<"¡Bienvenido!\nEn este programa podrá generar y comprobar la solubilidad de un puzzle \"quince\".\n"<<endl;
	cout <<"1. Empezar   2. Salir\n"<<endl;
	do{
		cout <<"Respuesta: ";
		cin >>respuesta;                	        //Si el usuario ingresa 1, imprime un puzzle.
		if(respuesta!='1'&respuesta!='2')           //Si elige 2, salta a la línea 66.
			cout <<"ERROR: El número ingresado no es correcto.\n";
	}while(respuesta!='1'&respuesta!='2');          //Si ingresa otro número devuelve error y lo intenta de nuevo.
	if(respuesta=='1')							
		respuesta='s';                              //Remplaza el 1 con una s para iniciar el bucle.
	//Impresión del puzzle.
	while(respuesta=='s'){                          //Mientras respuesta sea s,
		clear();                                    //Limpia la pantalla
		int puzzle[N][N]={0};                       //Crea una variable para el puzzle.
		crear(puzzle);                              //Crea una permutación para el puzzle.
		cout <<endl;                                //Imprime una margen.
		mostrar(puzzle);                            //Imprime el puzzle.
		//Solubilidad.
		cout <<endl<<"Este puzzle es ";             //Imprime si el puzzle es
		if(impos(puzzle))
            cout <<"insoluble."<<endl;              //insoluble
		else{
			cout <<"soluble."<<endl<<endl;	        //o soluble.
			cout <<"¿Desea resolver el puzzle? (s/n): ";
			cin >>respuesta;
			while(respuesta!='s'&&respuesta!='n'){	//devuelve error, y lo intenta de nuevo.
				cout <<"ERROR: Por favor ingrese un carácter válido (s/n) ";
				cin >>respuesta;
			}
			if(respuesta=='s'){
				char tecla='\0';
				int contador=0;
                while(1){
					clear();
					cout<<endl;
					mostrar(puzzle);
					cout <<endl<<"Movimientos realizados: "<<contador<<endl;
					cout <<endl<<"Arriba: w    Izquierda: a    Abajo: s    Derecha: d "<<endl;
					cout <<endl<<"Siguiente movimiento: ";
					cin >>tecla;
					if(mover(puzzle, tecla))
					    contador++;
				}
				//Terminado
                clear();
				cout <<endl;
				mostrar(puzzle);
				cout <<endl<<"¡Felicitaciones! ¡Lo hizo!"<<endl;
				cout <<endl<<"Movimientos: "<<contador<<endl;
			}
		}
        //¿Repetir?
		cout <<endl<<"¿Desea intentarlo de nuevo? (s/n) ";
		cin >>respuesta;			                //Si el usuario ingresa algo diferente a s o n,
		while(respuesta!='s'&&respuesta!='n'){	    //devuelve error, y lo intenta de nuevo.
			cout <<"ERROR: Por favor ingrese un carácter válido (s/n) ";
			cin >>respuesta;
		}
	}
	//Salida del programa.
	cout <<endl;
	cout <<"Â¡Gracias por utilizar este programa! Presione una tecla para salir. ";
	cin.get();
	cin.ignore();                               	//Limpia el buffer.
	return 0;                                   	//Termina el programa.
}
//---------------------------Desarrollo de funciones----------------------------
void crear(int puzzle[][N]){//--------------------------------------------------
	format(puzzle);                     	//Asigna -1 a toda la matriz.
	int temp=0;                         	//Crea una variable temporal para los números.
	for(int i=0; i<N; i++)			    	//Se repite para cada fila de la matriz.	  
		for(int j=0; j<N; j++){         	//Se repite para cada elemento de la fila.
			do
				temp=rand()%(N*N);          //Crea un número aleatorio entre 0 y (N^2)-1.
			while(check(puzzle, temp));	    //Hasta encontrar uno que no esté en la matriz.
			puzzle[i][j]=temp;		        //Y lo asigna al elemento.
		}
}

void format(int puzzle[][N]){//-------------------------------------------------
	for(int i=0;i<N;i++)		        	//Se repite para cada fila de la matriz.
		for(int j=0;j<N;j++)            	//Se repite para cada elemento de la fila.
			puzzle[i][j]=-1;            	//Asigna -1 al elemento.
}

bool check(int puzzle[][N], int temp){//----------------------------------------
	for(int i=0; i<N; i++)			    	//Se repite para cada fila de la matriz.
		for(int j=0; j<N; j++)          	//Se repite para cada elemento de la fila.
			if(temp==puzzle[i][j])      	//Si el elemento es igual a temp,
				return 1;                   //Regresa 1.
	return 0;                           	//Si no encuentra temp, regresa 0.
}

bool impos(int puzzle[][N]){//--------------------------------------------------
	int inver=sacaInver(puzzle);            //Cuenta cuántas inversiones hay en el puzzle.
	if(N%2==1&inver%2==0)                   //Si el puzzle es de orden impar,
		return 0;                           //y las inversiones son par, regresa 0.
	if(N%2==0){                             //Si el puzzle es de orden par,
		if(ceroEnI(puzzle)%2==1&inver%2==0) //el 0 está en en una fila inpar,
			return 0;                       //y las inversiones son par, regresa 0.
		if(ceroEnI(puzzle)%2==0&inver%2==1) //el 0 está en una fila par,
			return 0;                       //y las inversiones son impar, regresa 0.
	}
	return 1;                               //Si no, regresa 1.
}

int sacaInver(int puzzle[][N]){//-----------------------------------------------
    int inver=0;
    for(int i1=0; i1<N; i1++)                               //Se repite para cada fila de la matriz.
        for(int j1=0; j1<N; j1++)                           //Se repite para cada elemento de la fila.
            for(int i2=i1; i2<N; i2++)                      //Se repite para cada fila mayor o igual a la fila 1.
                for(int j2=(i1==i2?j1+1:0); j2<N; j2++){    //Se repite para cada elemento después del elemento 1.
                    if(puzzle[i1][j1]==0|puzzle[i2][j2]==0) //Si alguno de los dos elementos es 0,
                        continue;                           //Lo salta.
                    if(puzzle[i1][j1]>puzzle[i2][j2])       //Si el elemento 1 es mayor al elemento 2,
                        inver++;                            //Aumenta el contador de inversiones en 1.
                }                               
    return inver;                                           //Regresa el conteo de inversiones.
}

int ceroEnI(int puzzle[][N]){//-------------------------------------------------
	for(int i=0; i<N; i++)              	//Se repite para cada fila de la matriz.
		for(int j=0; j<N; j++)          	//Se repite para cada elemento de la fila.
			if(puzzle[i][j]==0)         	//Si encuentra 0,
				return i;	    	        //regresa la fila en la que lo encontró.
}

void mostrar(int puzzle[][N]){//------------------------------------------------
	for(int i=0;i<N;i++){               	//Se repite para cada fila de la matriz.
		cout <<" ";                     	//Imprime una sangría.
		for(int j=0;j<N;j++){           	//Se repite para cada elemento de la fila.
            if(puzzle[i][j]<10)         	//Si el elemento tiene sólo un dígito,
                cout <<" ";             	//Imprime un espacio para tabular.
            if(puzzle[i][j]>0)          	//Si el elemento es mayor a 0,
                cout <<puzzle[i][j];    	//Imprime el elemento.
            else                        	//Si no,
                cout <<" ";             	//Imprime un espacio.
            cout <<" ";                 	//Imprime un espacio para el siguiente elemento.
		}
		cout <<endl;                    	//Salto de línea para la siguiente fila.
	}
}

bool mover(int puzzle[][N], char tecla){//--------------------------------------
	int blankPosX=0, blankPosY=0;
	for (int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			if(puzzle[i][j]==0){
				blankPosX=j;
				blankPosY=i;
			}
	switch(tecla){
		case 'w':	//mueve hacia arriba
			if(blankPosY<N-1){
				puzzle[blankPosY][blankPosX]=puzzle[blankPosY+1][blankPosX];
				puzzle[blankPosY+1][blankPosX]=0;
				blankPosY=blankPosY+1;
				return 1;
			}
		case 'a':	//mueve izquierda
			if(blankPosX<N-1){
				puzzle[blankPosY][blankPosX]=puzzle[blankPosY][blankPosX+1];
				puzzle[blankPosY][blankPosX+1]=0;
				blankPosX=blankPosX+1;
				return 1;
			}
		case 's':	//mueve abajo
			if(blankPosY>0){
				puzzle[blankPosY][blankPosX]=puzzle[blankPosY-1][blankPosX];
				puzzle[blankPosY-1][blankPosX]=0;
				blankPosY=blankPosY-1;
				return 1;
			}
		case 'd':	//mueve derecha
			if(blankPosX>0){
				puzzle[blankPosY][blankPosX]=puzzle[blankPosY][blankPosX-1];
				puzzle[blankPosY][blankPosX-1]=0;
				blankPosX=blankPosX-1;
				return 1;					
			}
    }
    return 0;
}
