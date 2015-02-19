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

#include "tablero.h"
using namespace std;




void estructurarordenes(const int &col,const string &cadena,string &cadenatexto,int &posicion);
int convertir(const string &c);
void dividir(const string &cadena,string &c,int &pos);
void pasaraminusculas (string &cadena);
void leerorden(const int &col,string &cadena,string &cadenatexto,int &posicion);
bool seguir(const int &fil,const int &col,const vector<int> &matriz,bool &continuar,const int &posicion,const int &N,string &matrizs);




int main()
{
	
    bool continuar=true;
    int fil, col, N;
    string fila,columna,bombas;
    cout<<"Di el numero de filas, columnas y bombas."<<endl;
    getline(cin,fila);
    getline(cin,columna);
    getline(cin,bombas);
    fil=convertir(fila);
    col=convertir(columna);
    N=convertir(bombas);
    while(N<5 || N>(fil*col*0.5))
    {
        cout<<"El numero de bombas deber ser mayor que 5 y menor que el el cincuenta por ciento del tablero: "<<endl;
        getline(cin,bombas);
        N=convertir(bombas);
    }
	tablero t(fil,col,N);
    int posicion;
    string cadena,cadenatexto;

    while (continuar)
    {
        leerorden(col,cadena,cadenatexto,posicion);
		if(cadena=="exit"){
			cout<<"Salimos del juego."<<endl;
			exit(-1);

		}
        if(cadenatexto=="a" || cadenatexto=="abrir")
        {
            cout<<"abre"<<endl;
            if(t.calcular_posicion(posicion)=='*')
                t.abrirycomprobar(posicion);
            t.seguir(continuar,posicion);
        }

        if(cadenatexto=="m" || cadenatexto=="marcar")
        {
            cout<<"marcar"<<endl;
            t.marcar(posicion);
            t.mostrarmatrizs();
        }
        cadenatexto.clear();
    }
	return 0;

}



//leer la orden y la posicon de actuacion
void leerorden(const int &col,string &cadena,string &cadenatexto,int &posicion)
{
    cout<<"Dime accion (abrir - marcar) y posicion (fil y col) o exit:";
    getline(cin,cadena);
    estructurarordenes(col,cadena,cadenatexto,posicion);
    pasaraminusculas(cadenatexto);
}





//convierte una cadena de texto en mayusculas a minustulas
void pasaraminusculas (string &cadena)
{
    for(int i=0; i<cadena.size(); i++)
        cadena.at(i)=tolower(cadena.at(i));

}
void dividir(const string &cadena,string &c,int &pos)
{
    for(int i=pos+2; i<cadena.size() &&cadena.at(i)!=' '; i++)
    {
        c+=cadena.at(i);
        pos=i;
    }
}

//transforma de string a int
int convertir(const string &c)
{
    int coe=1,suma=0;
    for(int i=(c.size()-1); i>=0; i--)
    {
        suma+=(c.at(i)-'0')*coe;
        coe*=10;
    }
    return suma;
}


//convierte de la cadena de la orden en: la orden de abrir o marcar y la posicon de actuacion.
void estructurarordenes(const int &col,const string &cadena,string &cadenatexto,int &posicion)
{
    string cadenan1,cadenan2;
    int pos=-2,a,b;
    dividir(cadena,cadenatexto,pos);
    dividir(cadena,cadenan1,pos);
    dividir(cadena,cadenan2,pos);
    a=convertir(cadenan1);
    b=convertir(cadenan2);
    posicion=a*col+b;
}





