//Ejercicio I 
#include <iostream>
using namespace std;

class Vehiculo{
    public:
        //Atributos
        string marca;
        string modelo;
        int anio;

        //Metodos
        virtual void imprimir(){
            cout << "Vehiculo" << endl;
            cout << "Marca: " << marca << endl;
            cout << "Modelo: " << modelo << endl;
            cout << "Año: " << anio << endl;
        }
};

//Subclases con herencia
class Carro: public Vehiculo{
    public:
        int puertas;

    //SobreEscrbir metodo
    void imprimir() override {
        Vehiculo::imprimir();
        cout << "Carro" << endl;
        cout << "Puertas: " << puertas << endl;
    }
};

class Motocicleta: public Vehiculo{
    public:
        int tipo;
    
    //SobreEscrbir metodo
    void imprimir() override{
        Vehiculo::imprimir();
        cout << "Motocicleta" << endl;
        cout << "Tipo: " << tipo << endl;
    }
};


//Funcion main
int main(){

    //Instancias de cada clase
    Carro carro;
    carro.marca = "Toyota";
    carro.modelo = "Corolla";
    carro.anio = 2020;
    carro.puertas = 4;
    carro.imprimir();

    cout  << "\n" <<endl; //Salto de linea

    Motocicleta moto;
    moto.marca = "Honda";
    moto.modelo = "CBR";
    moto.anio = 2021;
    moto.tipo = 1;
    moto.imprimir();

    return 0;
}