/* (C) Programmed by:
   Antonio Jimenez Martínez


Programa: Busca Minas
Version:0.3

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

void ponerbombas(vector<int> &matriz,const vector<int> &numerosal);
void mostrarmatriz(const vector<int> &matriz,const int &fil,const int &col);
void poner12345678(const int fil,vector<int> &matriz);
int  comprobarentorno(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornosizefil(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornosize(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornofil(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentorno0(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornoabajo(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornoder(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornoizq(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornotodo(const vector<int> &matriz,const int &a,const int fil);
int  comprobarentornoarriba(const vector<int> &matriz,const int &a,const int fil);
void mostrarmatrizs(const string &matrizs,const int &fil,const int &col);
void estructurarordenes(const int &col,const string &cadena,string &cadenatexto,int &posicion);
int convertir(const string &c);
void dividir(const string &cadena,string &c,int &pos);
void pasaraminusculas (string &cadena);
void leerorden(const int &col,string &cadena,string &cadenatexto,int &posicion);
bool seguir(const int &fil,const int &col,const vector<int> &matriz,bool &continuar,const int &posicion,const int &N,string &matrizs);
void abrirycomprobar(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &posicion);
void marcar(string &matrizs,const int posicion);
void comprobarentorno2(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &a);
void abrir(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &posicion);
void comprobarespacios(const int &fil,const int &col,const vector<int> &matriz,string & matrizs);
int calcularnasterizcos (const string &matrizs);
void numerosaleatorios(const int fil,const int col,const int tamano,vector <int> &numerosal);
bool find(const vector <int> &numerosal,int n);




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
    int posicion;
    vector<int> matriz(fil*col,0);
    string matrizs(fil*col,'*');
    string cadena,cadenatexto;
    vector <int> numerosal;
    numerosaleatorios(fil,col,N,numerosal);
    ponerbombas(matriz,numerosal);
    poner12345678(fil,matriz);
    mostrarmatrizs(matrizs,fil,col);

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
            if(matrizs.at(posicion)=='*')
                abrirycomprobar(fil,col,matriz,matrizs,posicion);
            seguir(fil,col,matriz,continuar,posicion,N,matrizs);
        }

        if(cadenatexto=="m" || cadenatexto=="marcar")
        {
            cout<<"marcar"<<endl;
            marcar(matrizs,posicion);
            mostrarmatrizs(matrizs,fil,col);
        }
        cadenatexto.clear();
    }
	return 0;

}

void abrirycomprobar(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &posicion)
{
    int nast1=calcularnasterizcos(matrizs);
    int nast2;
    if(matriz.at(posicion)!=9)
    {
        if(matriz.at(posicion)!=0)//si la posicio tiene bombas alrededor mostrmaos la cantidad de bombas que tiene.
            matrizs.at(posicion)= (matriz.at(posicion)+'0');
        if(matriz.at(posicion)==0)
        {
            matrizs.at(posicion)= (matriz.at(posicion)+' ');//lo ponemos vacio
            comprobarentorno2(fil,col,matriz,matrizs,posicion);//comprobamos si podemos abrir lo de arededor.
            nast2=calcularnasterizcos(matrizs);
            while(nast2<nast1)
            {
                comprobarespacios(fil,col,matriz,matrizs);
                nast1=nast2;
                nast2=calcularnasterizcos(matrizs);
            }

        }
    }
}

//comprueba que alrededor de todas las pociones con espacion, no haya casillas sin abrir.
void comprobarespacios(const int &fil,const int &col,const vector<int> &matriz,string & matrizs)
{
    for(int i =0; i<matrizs.size(); i++)
    {
        if(matrizs.at(i)==' ')
            comprobarentorno2(fil,col,matriz,matrizs,i);
    }
}

//comprobamos que tiene la posicion. Es decir, si no es una bomba, comprobamos las bobas que tiene alrededor y las marcamos. 
void abrir(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &posicion)
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


//comprueba si puede abir lo de alrededor de la posicon.
void comprobarentorno2(const int &fil,const int &col,const vector<int> &matriz,string & matrizs,const int &a)
{
    bool aux=true;
    if(aux)
    {
        if(a>0 && a<(fil-1))
        {

            abrir(fil,col,matriz,matrizs,a+1);
            abrir(fil,col,matriz,matrizs,a-1);
            abrir(fil,col,matriz,matrizs,a+fil+1);
            abrir(fil,col,matriz,matrizs,a+fil-1);
            abrir(fil,col,matriz,matrizs,a+fil);
            aux=false;
        }

        if(a<(matriz.size()-1) && a>(matriz.size()-fil))
        {
            abrir(fil,col,matriz,matrizs,a+1);
            abrir(fil,col,matriz,matrizs,a-1);
            abrir(fil,col,matriz,matrizs,a-fil+1);
            abrir(fil,col,matriz,matrizs,a-fil-1);
            abrir(fil,col,matriz,matrizs,a-fil);
            aux=false;

        }
        if(a!=0 && (a%fil)==0 && a<(matriz.size()-fil))
        {
            abrir(fil,col,matriz,matrizs,a+1);
            abrir(fil,col,matriz,matrizs,a+fil+1);
            abrir(fil,col,matriz,matrizs,a+fil);
            abrir(fil,col,matriz,matrizs,a-fil+1);
            abrir(fil,col,matriz,matrizs,a-fil);
            aux=false;
        }
        if(a!=(matriz.size()-1) && (a%fil)==(fil-1) && a!=(fil-1))
        {

            abrir(fil,col,matriz,matrizs,a-1);
            abrir(fil,col,matriz,matrizs,a+fil-1);
            abrir(fil,col,matriz,matrizs,a+fil);
            abrir(fil,col,matriz,matrizs,a-fil-1);
            abrir(fil,col,matriz,matrizs,a-fil);
            aux=false;
        }
        if(a==0)
        {
            abrir(fil,col,matriz,matrizs,a+1);
            abrir(fil,col,matriz,matrizs,a+fil+1);
            abrir(fil,col,matriz,matrizs,a+fil);
            aux=false;
        }
        if(a==(fil-1))
        {
            abrir(fil,col,matriz,matrizs,a-1);
            abrir(fil,col,matriz,matrizs,a+fil-1);
            abrir(fil,col,matriz,matrizs,a+fil);
            aux=false;
        }
        if(a==(matriz.size()-fil))
        {
            abrir(fil,col,matriz,matrizs,a+1);
            abrir(fil,col,matriz,matrizs,a-fil+1);
            abrir(fil,col,matriz,matrizs,a-fil);

            aux=false;
        }
        if(a==(matriz.size()-1))
        {
            abrir(fil,col,matriz,matrizs,a-1);
            abrir(fil,col,matriz,matrizs,a-fil-1);
            abrir(fil,col,matriz,matrizs,a-fil);

            aux=false;
        }
    }
    if(aux)
    {
        abrir(fil,col,matriz,matrizs,a+1);
        abrir(fil,col,matriz,matrizs,a-1);
        abrir(fil,col,matriz,matrizs,a+fil+1);
        abrir(fil,col,matriz,matrizs,a+fil-1);
        abrir(fil,col,matriz,matrizs,a+fil);
        abrir(fil,col,matriz,matrizs,a-fil+1);
        abrir(fil,col,matriz,matrizs,a-fil-1);
        abrir(fil,col,matriz,matrizs,a-fil);
    }


}

//marca la posicion, modificnado el asterizco por una interrogacion.
void marcar(string &matrizs,const int posicion)
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


//calcula el numero de asteristo o interrogaciones que hay en el tablero de texto.
int calcularnasterizcos (const string &matrizs)
{

    int nasterizcos=0;
    for(int i=0; i<matrizs.size(); i++)
    {
        if(matrizs.at(i)=='*' || matrizs.at(i)=='?')
            nasterizcos++;
    }
    return nasterizcos;

}

//comprueba si has ganado o has perdido.
bool seguir(const int &fil,const int &col,const vector<int> &matriz,bool &continuar,const int &posicion,const int &N,string &matrizs)
{
    if(matriz.at(posicion)==9)
    {
        matrizs.at(posicion)='X';
        cout<<"Lo siento, has perdido."<<endl;
        cout<<"El tablero ha quedado asi: "<<endl;
        continuar=false;
    }


    int nasterizcos=calcularnasterizcos(matrizs);
    if(nasterizcos==N)
    {
        continuar=false;
        cout<<"Enhorabuena, has ganado."<<endl;
    }
    mostrarmatrizs(matrizs,fil,col);
}

//leer la orden y la posicon de actuacion
void leerorden(const int &col,string &cadena,string &cadenatexto,int &posicion)
{
    cout<<"Dime accion (abrir - marcar) y posicion (fil y col) o exit:";
    getline(cin,cadena);
    estructurarordenes(col,cadena,cadenatexto,posicion);
    pasaraminusculas(cadenatexto);
}


//marca en el tablero las casillas con las bombas.
//A las bombas se le asigna el digito 9
void ponerbombas(vector<int> &matriz,const vector<int> &numerosal)
{
    for(int i=0; i<numerosal.size(); i++)
    {
        matriz.at(numerosal.at(i))=9;
    }
}

//calcula la cantidad de bombas que tiene la posicion a alrededor.
int comprobarentorno(const vector<int> &matriz,const int &a,const int fil)
{
    int frec;
    bool aux=true;
    if(aux)
    {
        if(a>0 && a<(fil-1))
        {
            frec=comprobarentornoarriba(matriz,a,fil);
            aux=false;
        }

        if(a<(matriz.size()-1) && a>(matriz.size()-fil))
        {
            frec=comprobarentornoabajo(matriz,a,fil);
            aux=false;
        }
        if(a!=0 && (a%fil)==0 && a<(matriz.size()-fil))
        {
            frec=comprobarentornoizq(matriz,a,fil);
            aux=false;
        }
        if(a!=(matriz.size()-1) && (a%fil)==(fil-1) && a!=(fil-1))
        {
            frec=comprobarentornoder(matriz,a,fil);
            aux=false;
        }
        if(a==0)
        {
            frec=comprobarentorno0(matriz,a,fil);
            aux=false;
        }
        if(a==(fil-1))
        {
            frec=comprobarentornofil(matriz,a,fil);
            aux=false;
        }
        if(a==(matriz.size()-fil))
        {
            frec=comprobarentornosizefil(matriz,a,fil);
            aux=false;
        }
        if(a==(matriz.size()-1))
        {
            frec=comprobarentornosize(matriz,a,fil);
            aux=false;
        }
    }
    if(aux)
        frec=comprobarentornotodo(matriz,a,fil);
    return frec;
}


//esta subfuncion de comprobar entorno se aplica unicamente a la esquna inferior izquierda
int  comprobarentornosizefil(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornosize(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornofil(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentorno0(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornoder(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornoizq(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornoarriba(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornoabajo(const vector<int> &matriz,const int &a,const int fil)
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
int  comprobarentornotodo(const vector<int> &matriz,const int &a,const int fil)
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
//De manera que si es un 1, esa posicion tendra una bomba a su alrededor; si es un 2 tendras dos bombas a su alrededor y asi sucesivamente hasta 8 que es el maximo numero de bombas que puede tener una posicion alrededor.
void poner12345678(const int fil,vector<int> &matriz)
{
    int b;
    for(int i=0; i<matriz.size(); i++)
    {
        if(matriz.at(i)!=9)
        {
            b=comprobarentorno(matriz,i,fil);
            matriz.at(i)=b;
        }

    }
}


//muestra la matriz de digitos
void mostrarmatriz(const vector<int> &matriz,const int &fil,const int &col)
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
void mostrarmatrizs(const string &matrizs,const int &fil,const int &col)
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


//compruba si un numero esta en un vector
//devuelve true si el numero esta y false en caso contrario
bool find(const vector <int> &numerosal,int n)
{
    for(int i=0; i<numerosal.size(); i++)
    {
        if(n==numerosal[i]) return true;
    }
    return false;
}


//crea un vector de numero aleatorios entre [0,fil*col],sin numero repetidos
void numerosaleatorios(const int fil,const int col,const int tamano,vector <int> &numerosal)
{
    srand (time(0));
	int n;
    for(int i=0; i<tamano; i++){
        if(i==0){
			numerosal.push_back(rand()%(fil*col));
		}
		else{
			n=rand()%(fil*col);
			while(find(numerosal,n)){
				 n=rand()%(fil*col);
			}
			numerosal.push_back(n);
		}
	}

}

