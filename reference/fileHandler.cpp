/*
*----------------------------------------
* fileHandler.cpp
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3069 - Computacion Paralela y Distribuida
* Autor: M Novella
*
* References:
* "Predicates" - The C++ Standard Library (Josuttis) pp.226-227
* "Shared Objects and Synchronization" - The Art of
* Multiprocessor Programming (Herlihy & Shavit) pp.3-5
* "Ch 14 File Processing" - C++ How to Program
* (Deittel & Deittel) pp.602-621
* ---------------------------------------
* Busca los números primos en un rango de 10^n dentro de un archivo
* y escribe los resultados a otro archivo
*----------------------------------------
* Compile:
* gcc fileHandler.cpp -o fileHandler -lstdc++ -lm
*/

#include <unistd.h>     //std lib
#include <iostream>
#include <cmath>
#include <fstream>      //fstream, ofstream, ifstream
#include <string>       //string

#define INFILE "numeros.csv"
#define OUTFILE "primos.csv"

using namespace std;

//Funciton prototypes
bool isPrime(int number);
//void outputLine(int primeNumber);

int main(int argc, char * argv[]) {

    //Valores iniciales default
    int exponente = 2;

    int primeNumber;
    char expChar;

    //UX input rango de números: exponente
    cout<<"Ingrese un exponente base 10 para el rango de números: ";
    cin>>expChar;

    //Offset para procesar ASCII - chars inician en val=48
    exponente =int(expChar) - 48;
    long limit = pow(10,exponente);

    cout<<"Buscaremos los primos entre 0 y "<<limit<<endl;

    /*----------
     *Constructor del manejador de archivos
     *
     *  in/out - fstream <identificador>("<archivo>",modo)
     *  out only - ofstream <identificador>("<archivo>",modo)
     *  in only - ifstream <identificador>("<archivo>")
     *
     *  modos:
     *      ios::app - append to file
     *      ios::out - new/overwrite file
     *      ios::binary - nontext input & output
     *      ios::in - read from file
     */
    ofstream escribirNumeros(INFILE,ios::out);
    if( escribirNumeros.bad() ) {
        cerr<<"Falló la creación del archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }

    //Llenamos el archivo INFILE con números
    for(int i=0; i<limit;i++){
        escribirNumeros<<i<<",";
    }
    escribirNumeros<<limit<<endl;
    escribirNumeros.close();    //Cerramos el archivo si no lo vamos a usar nuevamente

    //Constructores para lectura de archivo y escritura de resultados
    //Esta es otra forma de realizar el manejo de arhivos
    ifstream leerNumeros;
    leerNumeros.open(INFILE);
    if( leerNumeros.bad() ) {
        cerr<<"No se pudo leer el archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }

    ofstream escribirPrimos;
    escribirPrimos.open(OUTFILE);
    if( escribirPrimos.bad() ) {
        cerr<<"No se pudo crear el archivo "<<OUTFILE<<endl;
        exit(EXIT_FAILURE);
    }

    //Probamos que un número sea primo y lo escribimos al archivo OUTFILE
    string ch;
    while(getline(leerNumeros,ch,',')) {

        int numero = stoi(ch);  //Debemos convertir el string a int

        if(isPrime(numero)) {
            cout<<ch<<" ";
            escribirPrimos<<ch<<" ";
        }
    }
    cout<<endl;



    return 0;
}

/*-----------
 * isPrime - test for a prime number
 */
bool isPrime(int number){
    if (number == 0 || number == 1)
	{
		return false;
	}
	int divisor;
	for (divisor = number/2; number%divisor != 0; --divisor)
	{
		;
	}
	if (divisor != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
} /*isPrime*/

/*-----------
 * outputLine - format text in line form and output to ifstream
 */
// void outputLine(int primeNumber){
//     long primeLong = (long)primeNumber;
// 	double primeRoot = (double)primeLong;

// 	cout<<primeNumber<<" "<<endl;
// }
