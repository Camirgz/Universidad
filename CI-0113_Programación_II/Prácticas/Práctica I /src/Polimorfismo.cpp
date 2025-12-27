// Ejercicio III
#include <iostream>
using namespace std;

//Clase abstracta
class Animal{
    public:
        //Metodo virtual puro
        virtual string sonido() = 0;
};

//Subclases
//Clase Perro hereda de Animal
class Perro : public Animal{
    public:
        //Implementacion del metodo virtual
        string sonido() //Polimorfismo de metodo sonido
        {
            return "Guau";
        }
};

//Clase Gato hereda de Animal
class Gato : public Animal{
    public:
        //Implementacion del metodo virtual
        string sonido()
        {
            return "Miau";
        }
};

//Funcion que recibe un arreglo de punteros a objetos de la clase Animal
void procesar(Animal *lista[], int n){
    //Ciclo para recorrer el arreglo de punteros
    for (int i = 0; i < n; i++)
    {
        cout << lista[i]->sonido() << endl; //Imprimir el sonido de cada animal
    }
}

int main(){
    Animal *animales[] = {new Gato(), new Perro(), new Gato()}; //Arreglo de punteros a objetos
    procesar(animales, 3); //Llamada a la funcion que recibe el arreglo de punteros

    //Liberar memoria
    for (int i = 0; i < 3; i++)
    {
        delete animales[i];
    }
}