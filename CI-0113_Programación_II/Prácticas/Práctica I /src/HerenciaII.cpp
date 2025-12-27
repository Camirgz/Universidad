//Ejercicio IV
#include <iostream>
#include <string>
using namespace std;

class Persona{
    public:
        //Atributos
        string nombre;
        string apellido;
        int edad;

        //Metodos
        virtual void presentarse(){
            cout << "Hola, mi nombre es " << nombre << " " << apellido <<
             " y tengo " << edad << " años" << endl;
        }
};

class Estudiante: public Persona{
    public:
        //Atributos
        string carrera;
        int semestre;

        //Metodos
        void presentarse() override{
            Persona::presentarse();
            cout << "Soy estudiante de la carrera de " << carrera << 
            " y estoy en el semestre " << semestre << endl;
        }
};

class Profesor: public Persona{
    public:
        //Atributos
        string materia;
        int antiguedad;

        //Metodos
        void presentarse() override{
            Persona::presentarse();
            cout << "Soy profesor de la materia de " << materia << 
            " y tengo " << antiguedad << " años de antiguedad" << endl;
        }
};

int main(){
    //Instancias de cada clase
    Estudiante estudiante;
    estudiante.nombre = "Camila";
    estudiante.apellido = "Rodriguez";
    estudiante.edad = 19;
    estudiante.carrera = "Ingenieria en Sistemas";
    estudiante.semestre = 4;
    estudiante.presentarse();

    cout  << "\n" <<endl; //Salto de linea

    Profesor profesor;
    profesor.nombre = "Arianna";
    profesor.apellido = "Aguila";
    profesor.edad = 46;
    profesor.materia = "Matematicas";
    profesor.antiguedad = 4;
    profesor.presentarse();
}