//Ejercicio II
#include <iostream>
#include <string>

using namespace std;

class DispositivoElectronico{

    public:

    //Atributos abstractos
    virtual int duracionBateria() const = 0;
    virtual string especificaciones() const = 0;

    //Destructor para la clase abstracta
    virtual ~DispositivoElectronico() = default;
};

class Smartphone: public DispositivoElectronico{
    public:
        //Atributos
        string marca;
        string modelo;
        int anio;
        int bateria;

        //Metodos
        int duracionBateria() const override{
            return bateria;
        }

        string especificaciones() const override{
            return "Marca: " + marca + 
            "\nModelo: " + modelo + 
            "\nAño: " + to_string(anio) + 
            "\nBateria: " + to_string(bateria) + " mAh";
        }
};

class Laptop: public DispositivoElectronico{
    public:
        //Atributos
        string marca;
        string modelo;
        int anio;
        int bateria;
        int pantalla;

        //Metodos
        int duracionBateria() const override{
            return bateria;
        }

        string especificaciones() const override{
            return "Marca: " + marca + 
            "\nModelo: " + modelo + 
            "\nAño: " + to_string(anio) + 
            "\nBateria: " + to_string(bateria) + " mAh" + 
            "\nPantalla: " + to_string(pantalla) + " pulgadas";
        }
};

int main(){

    cout << "\n" << endl;

    //Instancias de cada clase
    Smartphone smart;
    smart.marca = "Apple";
    smart.modelo = "iPhone 15";
    smart.anio = 2023;
    smart.bateria = 4000;
    cout << smart.especificaciones() << endl;

    cout  << "\n" <<endl; //Salto de linea

    Laptop lap;
    lap.marca = "Dell";
    lap.modelo = "Inspiron 15";
    lap.anio = 2022;
    lap.bateria = 5000;
    lap.pantalla = 15;
    cout << lap.especificaciones() << endl;

    return 0;
}