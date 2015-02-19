/* (C) Programmed by:
   Antonio Jimenez Martínez


Programa: Busca Minas
Version:0.4

El juego del buscaminas comienza con un tablero de F filas y
C columnas, donde se ocultan N minas. Inicialmente no se
sabe nada sobre lo que hay debajo de cada casilla, pudiendo
ser una casilla sin mina o con mina.
El problema consiste en localizar las minas sin detonar
ninguna de ellas.
Si el juego continúa y llega el momento en que todas las casillas se han abierto (excepto las
que contienen una mina), no quedarán casillas por abrir y, por tanto, se habrá ganado el
juego.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>      // std::setw
#include <cstdlib> // rand, srand
#include <ctime> // time
using namespace std;


class tablero {

private:

    //un tablero esta formado por dos matrices (usuario y privada
	vector<int> matriz;
    string matrizs;
    int fil, col, N;//fila,columna,numero de bombas
	vector <int> numerosal;//vector de numero aleatorios para colocar als bombas


public:

    //constructor
    tablero(int f,int c,int b) {//constructor por defecto
        fil=f;
		col=c;
		N=b;
		matrizs.resize(fil*col,'*');
		matriz.resize(fil*col,0);
		numerosaleatorios();
		ponerbombas();
		poner12345678();
		mostrarmatrizs();
    }
	

	void abrirycomprobar(const int &posicion)
	{
		int nast1=calcularnasterizcos();
		int nast2;
		if(matriz.at(posicion)!=9)
		{
		    if(matriz.at(posicion)!=0)//si la posicio tiene bombas alrededor mostrmaos la cantidad de bombas que tiene.
		        matrizs.at(posicion)= (matriz.at(posicion)+'0');
		    if(matriz.at(posicion)==0)
		    {
		        matrizs.at(posicion)= (matriz.at(posicion)+' ');//lo ponemos vacio
		        comprobarentorno2(posicion);//comprobamos si podemos abrir lo de arededor.
		        nast2=calcularnasterizcos();
		        while(nast2<nast1)
		        {
		            comprobarespacios();
		            nast1=nast2;
		            nast2=calcularnasterizcos();
		        }

		    }
		}
	}


	//comprueba si has ganado o has perdido.
	bool seguir(bool &continuar,const int &posicion)
	{
		if(matriz.at(posicion)==9)
		{
		    matrizs.at(posicion)='X';
		    cout<<"Lo siento, has perdido."<<endl;
		    cout<<"El tablero ha quedado asi: "<<endl;
		    continuar=false;
		}


		int nasterizcos=calcularnasterizcos();
		if(nasterizcos==N)
		{
		    continuar=false;
		    cout<<"Enhorabuena, has ganado."<<endl;
		}
		mostrarmatrizs();
	}


	

	//muestra la matriz de digitos
	void mostrarmatriz()
	{
		cout<<setw(6);
		for(int i=0; i<col; i++)
		{
		    cout<<i<<"  ";
		}
		cout<<endl;
		for(int i=0; i<col; i++)
		{
		    cout<<"----";
		}
		cout<<endl;
		for (int f=0; f<fil; f++)
		{
		    if(f<10) cout<<f<<setw(3)<<"|";
			else cout<<f<<setw(2)<<"|";
		    for (int c=0; c<col; c++){
		    	if(c<10)    cout <<setw(2)<<matriz[f*col+c] << "|";
				else 		cout <<setw(3)<<matriz[f*col+c] << "|";
			}
		    cout << endl;
		}
		for(int i=0; i<col; i++)
		{
		    cout<<"----";
		}
		cout<<endl;

	}

	//muestra la matriz que se muestra al usuario.
	void mostrarmatrizs()
	{
		cout<<setw(6);

		for(int i=0; i<col; i++)
		{
		    cout<<i<<"  ";
		}
		cout<<endl;
		for(int i=0; i<col; i++)
		{
		    cout<<"----";
		}
		cout<<endl;
		for (int f=0; f<fil; f++)
		{
		    if(f<10) cout<<f<<setw(3)<<"|";
			else cout<<f<<setw(2)<<"|";
		    for (int c=0; c<col; c++){
		    	if(c<10)    cout <<setw(2)<<matrizs[f*col+c] << "|";
				else 		cout <<setw(3)<<matrizs[f*col+c] << "|";
			}
		    cout << endl;
		}
		for(int i=0; i<col; i++)
		{
		    cout<<"----";
		}
		cout<<endl;

	}


	//marca la posicion, modificnado el asterizco por una interrogacion.
	void marcar(const int posicion)
	{
		bool aux=true;
		if(matrizs.at(posicion)=='?' && aux)
		{
		    matrizs.at(posicion)='*';
		    aux=false;
		}

		if(matrizs.at(posicion)=='*' && aux)
		    matrizs.at(posicion)='?';

	}

	//devuelve el valor de la posicion pos en matriz usuario
	char calcular_posicion(int pos){
		return matrizs.at(pos);
	}



private:

	//crea un vector de numero aleatorios entre [0,fil*col],sin numero repetidos
	void numerosaleatorios()
	{
		srand (time(0));
		int n;
		for(int i=0; i<N; i++){
		    if(i==0){
				numerosal.push_back(rand()%(fil*col));
			}
			else{
				n=rand()%(fil*col);
				while(find(n)){
					 n=rand()%(fil*col);
				}
				numerosal.push_back(n);
			}
		}

	}

	//calcula la cantidad de bombas que tiene la posicion a alrededor.
	int comprobarentorno(const int &a)
	{
		int frec;
		bool aux=true;
		if(aux)
		{
		    if(a>0 && a<(fil-1))
		    {
		        frec=comprobarentornoarriba(a);
		        aux=false;
		    }

		    if(a<(matriz.size()-1) && a>(matriz.size()-fil))
		    {
		        frec=comprobarentornoabajo(a);
		        aux=false;
		    }
		    if(a!=0 && (a%fil)==0 && a<(matriz.size()-fil))
		    {
		        frec=comprobarentornoizq(a);
		        aux=false;
		    }
		    if(a!=(matriz.size()-1) && (a%fil)==(fil-1) && a!=(fil-1))
		    {
		        frec=comprobarentornoder(a);
		        aux=false;
		    }
		    if(a==0)
		    {
		        frec=comprobarentorno0(a);
		        aux=false;
		    }
		    if(a==(fil-1))
		    {
		        frec=comprobarentornofil(a);
		        aux=false;
		    }
		    if(a==(matriz.size()-fil))
		    {
		        frec=comprobarentornosizefil(a);
		        aux=false;
		    }
		    if(a==(matriz.size()-1))
		    {
		        frec=comprobarentornosize(a);
		        aux=false;
		    }
		}
		if(aux)
		    frec=comprobarentornotodo(a);
		return frec;
	}


	//comprueba si puede abir lo de alrededor de la posicon.
	void comprobarentorno2(const int &a)
	{
		bool aux=true;
		if(aux)
		{
		    if(a>0 && a<(fil-1))
		    {

		        abrir(a+1);
		        abrir(a-1);
		        abrir(a+fil+1);
		        abrir(a+fil-1);
		        abrir(a+fil);
		        aux=false;
		    }

		    if(a<(matriz.size()-1) && a>(matriz.size()-fil))
		    {
		        abrir(a+1);
		        abrir(a-1);
		        abrir(a-fil+1);
		        abrir(a-fil-1);
		        abrir(a-fil);
		        aux=false;

		    }
		    if(a!=0 && (a%fil)==0 && a<(matriz.size()-fil))
		    {
		        abrir(a+1);
		        abrir(a+fil+1);
		        abrir(a+fil);
		        abrir(a-fil+1);
		        abrir(a-fil);
		        aux=false;
		    }
		    if(a!=(matriz.size()-1) && (a%fil)==(fil-1) && a!=(fil-1))
		    {

		        abrir(a-1);
		        abrir(a+fil-1);
		        abrir(a+fil);
		        abrir(a-fil-1);
		        abrir(a-fil);
		        aux=false;
		    }
		    if(a==0)
		    {
		        abrir( a+1);
		        abrir( a+fil+1);
		        abrir( a+fil);
		        aux=false;
		    }
		    if(a==(fil-1))
		    {
		        abrir( a-1);
		        abrir( a+fil-1);
		        abrir( a+fil);
		        aux=false;
		    }
		    if(a==(matriz.size()-fil))
		    {
		        abrir( a+1);
		        abrir( a-fil+1);
		        abrir( a-fil);

		        aux=false;
		    }
		    if(a==(matriz.size()-1))
		    {
		        abrir( a-1);
		        abrir( a-fil-1);
		        abrir( a-fil);

		        aux=false;
		    }
		}
		if(aux)
		{
		    abrir( a+1);
		    abrir( a-1);
		    abrir( a+fil+1);
		    abrir( a+fil-1);
		    abrir( a+fil);
		    abrir( a-fil+1);
		    abrir( a-fil-1);
		    abrir( a-fil);
		}


	}
	
	//comprueba que alrededor de todas las pociones con espacion, no haya casillas sin abrir.
	void comprobarespacios()
	{
		for(int i =0; i<matrizs.size(); i++)
		{
		    if(matrizs.at(i)==' ')
		        comprobarentorno2(i);
		}
	}	


	//calcula el numero de asteristo o interrogaciones que hay en el tablero de texto.
	int calcularnasterizcos ()
	{
		int nasterizcos=0;
		for(int i=0; i<matrizs.size(); i++)
		{
		    if(matrizs.at(i)=='*' || matrizs.at(i)=='?')
		        nasterizcos++;
		}
		return nasterizcos;

	}
	

	

	//esta subfuncion de comprobar entorno se aplica unicamente a la esquna inferior izquierda
	int  comprobarentornosizefil(const int &a)
	{
		int frec=0;
		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil+1)==9)
		    frec++;
		return frec;
	}
	//esta subfuncion de comprobar entorno se aplica unicamente a la esquna inferior derecha
	int  comprobarentornosize(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil-1)==9)
		    frec++;
		return frec;
	}

	//esta subfuncion de comprobar entorno se aplica unicamente a la esquna superior derecha
	int  comprobarentornofil(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a-1+fil)==9)
		    frec++;
		return frec;
	}

	//esta subfuncion de comprobar entorno se aplica unicamente a la esquna superior izquierda
	int  comprobarentorno0(const int &a)
	{
		int frec=0;

		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a+fil+1)==9)
		    frec++;
		return frec;
	}

	//esta subfuncion de comprobar entorno se aplica unicamente a la columna de la izquierda
	int  comprobarentornoder(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil-1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a-1+fil)==9)
		    frec++;
		return frec;
	}

	//esta subfuncion de comprobar entorno se aplica unicamente a la columna de la derecha
	int  comprobarentornoizq(const int &a)
	{
		int frec=0;
		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil+1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a+fil+1)==9)
		    frec++;
		return frec;
	}

	//esta subfuncion de comprobar entorno se aplica unicamente a la primera fila
	int  comprobarentornoarriba(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a+fil+1)==9)
		    frec++;
		if(matriz.at(a-1+fil)==9)
		    frec++;
		return frec;
	}


	//esta subfuncion de comprobar entorno se aplica unicamente a la ultima fila
	int  comprobarentornoabajo(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil-1)==9)
		    frec++;
		if(matriz.at(a-fil+1)==9)
		    frec++;

		return frec;
	}



	//esta subfuncion de comprobar entorno se aplica a las 4 posiciones de alrededor.
	int  comprobarentornotodo(const int &a)
	{
		int frec=0;
		if(matriz.at(a-1)==9)
		    frec++;
		if(matriz.at(a+1)==9)
		    frec++;
		if(matriz.at(a-fil)==9)
		    frec++;
		if(matriz.at(a-fil-1)==9)
		    frec++;
		if(matriz.at(a-fil+1)==9)
		    frec++;
		if(matriz.at(a+fil)==9)
		    frec++;
		if(matriz.at(a+fil+1)==9)
		    frec++;
		if(matriz.at(a-1+fil)==9)
		    frec++;
		return frec;
	}


	//modificamos el tablero de digitos, de manera manera que en las posiciones diferentes de 9 (BOMBA), claculamos las bombas que tienen alrededor.
	//De manera que si es un 1, esa posicion tendra una bomba a su alrededor; si es un 2 tendras dos bombas a su alrededor y asi sucesivamente hasta 8 que es el 	maximo numero de bombas que puede tener una posicion alrededor.
	void poner12345678()
	{
		int b;
		for(int i=0; i<matriz.size(); i++)
		{
		    if(matriz.at(i)!=9)
		    {
		        b=comprobarentorno(i);
		        matriz.at(i)=b;
		    }

		}
	}
	
	
	//compruba si un numero esta en un vector
	//devuelve true si el numero esta y false en caso contrario
	bool find(int n)
	{
		for(int i=0; i<numerosal.size(); i++)
		{
		    if(n==numerosal[i]) return true;
		}
		return false;
	}

	//comprobamos que tiene la posicion. Es decir, si no es una bomba, comprobamos las bobas que tiene alrededor y las marcamos. 
	void abrir(const int &posicion)
	{
		if(matriz.at(posicion)!=9)
		{
		    if(matriz.at(posicion)!=0)
		        matrizs.at(posicion)= (matriz.at(posicion)+'0');
		    if(matriz.at(posicion)==0)
		    {
		        matrizs.at(posicion)= (matriz.at(posicion)+' ');
		    }
		}
	}

	//marca en el tablero las casillas con las bombas.
	//A las bombas se le asigna el digito 9
	void ponerbombas()
	{
		for(int i=0; i<numerosal.size(); i++)
		{
		    matriz.at(numerosal.at(i))=9;
		}
	}


    

};


