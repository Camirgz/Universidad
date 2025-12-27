//Ejercicio IV
#include <iostream>
#include <string>
using namespace std;

class Persona{
    public:
        //Atributos
        string nombre;
        int edad;

        //Metodos
        virtual void presentarse() = 0;
};

class Estudiante: public Persona{
    public:
        //Atributos
        string carrera;
        int semestre;

        //Metodos
        void estudiar() {
        }
};

class Profesor: public Persona{
    public:
        //Atributos
        string materia;
        int antiguedad;

        //Metodos
        void ensenar() {
        }
};
