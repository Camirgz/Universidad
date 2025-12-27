#include <iostream>
#include <ctime>
#include <cstdlib> // Usar <cstdlib> en lugar de <stdlib.h>
#define MAX_REGISTROS 100

using namespace std;

/*************** Modelo ***************/
class Libro {
public:
    int codigo;
    string titulo;
    string autor;
    int anyo;

    Libro() {}
    Libro(int codigo, string titulo, string autor, int anyo);
};

Libro::Libro(int codigo, string titulo, string autor, int anyo) {
    this->codigo = codigo;
    this->titulo = titulo;
    this->autor = autor;
    this->anyo = anyo;
}

class Estudiante {
public:
    int carnet;
    string nombre;
    string apellidos;
    string correo;

    Estudiante() {}
    Estudiante(int carnet, string nombre, string apellidos, string correo);
};

Estudiante::Estudiante(int carnet, string nombre, string apellidos, string correo) {
    this->carnet = carnet;
    this->nombre = nombre;
    this->apellidos = apellidos;
    this->correo = correo;
}

class Prestamo {
public:
    int codLibro;
    int carnetEst;
    string fechaPrestamo;
    string estadoPrestamo;

    Prestamo() {}
    Prestamo(int codLibro, int carnetEst, string fechaPrestamo, string estadoPrestamo);
};

Prestamo::Prestamo(int codLibro, int carnetEst, string fechaPrestamo, string estadoPrestamo) {
    this->codLibro = codLibro;
    this->carnetEst = carnetEst;
    this->fechaPrestamo = fechaPrestamo;
    this->estadoPrestamo = estadoPrestamo;
}

/*************** Controlador ***************/
class Controlador {
public:
    static Libro libros[MAX_REGISTROS];
    static Estudiante estudiantes[MAX_REGISTROS];
    static Prestamo prestamos[MAX_REGISTROS];

    static int indiceLibros; // índice para la "tabla" de libros
    static int indiceEstudiantes; // índice para estudiantes
    static int indicePrestamos; // índice para préstamos

    static bool IngresarLibro(string titulo, string autor, int anyo);
    static bool IngresarEstudiante(string nombre, string apellidos, string correo);
    static bool RegistrarPrestamo(int codLibro, int carnetEst);

    static Estudiante EstudianteMasFiel();
    static Libro LibroMasPrestado(); // Nuevo método
};

Libro Controlador::libros[MAX_REGISTROS];
Estudiante Controlador::estudiantes[MAX_REGISTROS];
Prestamo Controlador::prestamos[MAX_REGISTROS];

int Controlador::indiceLibros = 0;
int Controlador::indiceEstudiantes = 0;
int Controlador::indicePrestamos = 0;

bool Controlador::IngresarLibro(string titulo, string autor, int anyo) {
    if (Controlador::indiceLibros == MAX_REGISTROS) {
        return false;
    }

    int nuevoCodigo = Controlador::indiceLibros + 1;
    Libro nuevoLibro = Libro(nuevoCodigo, titulo, autor, anyo);
    Controlador::libros[Controlador::indiceLibros] = nuevoLibro;
    Controlador::indiceLibros++;
    return true;
}

bool Controlador::IngresarEstudiante(string nombre, string apellidos, string correo) {
    if (indiceEstudiantes == MAX_REGISTROS) {
        return false;
    }

    int nuevoCarnet = indiceEstudiantes + 1;
    Estudiante nuevoEstudiante = Estudiante(nuevoCarnet, nombre, apellidos, correo);
    estudiantes[Controlador::indiceEstudiantes] = nuevoEstudiante;
    indiceEstudiantes++;
    return true;
}

bool Controlador::RegistrarPrestamo(int codLibro, int carnetEst) {
    // Verificar existencia del libro
    bool existeLibro = false;
    for (int i = 0; i < indiceLibros; i++) {
        if (libros[i].codigo == codLibro) {
            existeLibro = true;
            break;
        }
    }
    if (!existeLibro) {
        cout << "El libro con el código " << codLibro << " no existe." << endl;
        return false;
    }

    // Verificar existencia del estudiante
    bool existeEstudiante = false;
    for (int i = 0; i < indiceEstudiantes; i++) {
        if (estudiantes[i].carnet == carnetEst) {
            existeEstudiante = true;
            break;
        }
    }
    if (!existeEstudiante) {
        cout << "El estudiante con el carnet " << carnetEst << " no existe." << endl;
        return false;
    }

    // Obtener la fecha y hora actual
    time_t timestamp = time(nullptr);
    struct tm* datetime = localtime(&timestamp);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", datetime);
    string fechaPrestamo(buffer);

    // Registrar el préstamo
    if (indicePrestamos < MAX_REGISTROS) {
        Prestamo nuevoPrestamo = Prestamo(codLibro, carnetEst, fechaPrestamo, "Recien ingresado");
        prestamos[indicePrestamos] = nuevoPrestamo;
        indicePrestamos++;
        return true;
    } else {
        cout << "No se pueden registrar más préstamos." << endl;
        return false;
    }
}


Estudiante Controlador::EstudianteMasFiel() {
    // Inicializar contadores
    int contadores[MAX_REGISTROS] = {0};

    // Contar el número de préstamos por estudiante
    for (int i = 0; i < indicePrestamos; i++) {
        Prestamo p = prestamos[i];
        for (int j = 0; j < indiceEstudiantes; j++) {
            if (p.carnetEst == estudiantes[j].carnet) {
                contadores[j]++;
                break;
            }
        }
    }

    // Encontrar el estudiante con el máximo número de préstamos
    int maximo = 0;
    Estudiante estudiante;
    estudiante.carnet = -1;

    for (int i = 0; i < indiceEstudiantes; i++) {
        if (contadores[i] > maximo) {
            maximo = contadores[i];
            estudiante = estudiantes[i];
        }
    }

    return estudiante;
}

// Implementación del método LibroMasPrestado
Libro Controlador::LibroMasPrestado() {
    // Inicializar el arreglo de contadores
    int contadores[MAX_REGISTROS] = {0};

    // Contar cuántas veces se ha prestado cada libro
    for (int i = 0; i < indicePrestamos; i++) {
        Prestamo p = prestamos[i];
        for (int j = 0; j < indiceLibros; j++) {
            if (libros[j].codigo == p.codLibro) {
                contadores[j]++;
                break;
            }
        }
    }

    // Encontrar el libro con el mayor número de préstamos
    int maxPrestamos = 0;
    Libro libroMasPrestado;
    libroMasPrestado.codigo = -1; // En caso de que no haya libros

    for (int i = 0; i < indiceLibros; i++) {
        if (contadores[i] > maxPrestamos) {
            maxPrestamos = contadores[i];
            libroMasPrestado = libros[i];
        }
    }

    return libroMasPrestado;
}

/*************** Vista ***************/
class GUI {
public:
    static void MenuPrincipal();

    static void MenuLibros();
    static void IngresarLibro();
    static void MostrarLibros();

    static void MenuEstudiantes();
    static void IngresarEstudiante();
    static void MostrarEstudiantes();

    static void MenuPrestamos();
    static void RegistrarPrestamo();
    static void MostrarPrestamos();

    static void MenuReportes();
    static void EstudianteMasFiel();
    static void LibroMasPrestado();
};

void GUI::MenuPrincipal() {
    while (true) {
        cout << "=======" << endl; // Para Windows; usa system("clear") en Unix
        cout << "Sistema de Prestamo" << endl;
        cout << "1. Libros" << endl;
        cout << "2. Estudiantes" << endl;
        cout << "3. Prestamos" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore(); // Cuando leemos int, a veces queda un '\n' en el buffer

        switch (opcion) {
            case 1:
                MenuLibros();
                break;
            case 2:
                MenuEstudiantes();
                break;
            case 3:
                MenuPrestamos();
                break;
            case 4:
                MenuReportes();
                break;
            case 5:
                exit(0);
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }
}

void GUI::MenuLibros() {
    while (true) {
        cout << "=======" << endl; // Para Windows; usa system("clear") en Unix
        cout << "Menu Libros" << endl;
        cout << "1. Ingresar libro" << endl;
        cout << "2. Mostrar libros" << endl;
        cout << "3. Volver" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                IngresarLibro();
                break;
            case 2:
                MostrarLibros();
                break;
            case 3:
                return;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }
}

void GUI::IngresarLibro() {
    cout << "Ingrese el titulo del libro: ";
    string titulo;
    getline(cin, titulo);

    cout << "Ingrese el autor del libro: ";
    string autor;
    getline(cin, autor);

    cout << "Ingrese el anio de publicacion: ";
    int anyo;
    cin >> anyo;
    cin.ignore(); // Limpiar el buffer

    if (Controlador::IngresarLibro(titulo, autor, anyo)) {
        cout << "Libro ingresado correctamente." << endl;
    } else {
        cout << "Error al ingresar el libro." << endl;
    }
    cout << "=====" << endl;
}

void GUI::MostrarLibros() {
    cout << "=======" << endl;
    cout << "Libros disponibles:" << endl;
    for (int i = 0; i < Controlador::indiceLibros; i++) {
        Libro libro = Controlador::libros[i];
        cout << "Codigo: " << libro.codigo << endl;
        cout << "Titulo: " << libro.titulo << endl;
        cout << "Autor: " << libro.autor << endl;
        cout << "Anio: " << libro.anyo << endl;
        cout << "-----------------" << endl;
    }
    system("pause");
}

void GUI::MenuEstudiantes() {
    while (true) {
        cout << "=======" << endl;
        cout << "Menu Estudiantes" << endl;
        cout << "1. Ingresar estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Volver" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                IngresarEstudiante();
                break;
            case 2:
                MostrarEstudiantes();
                break;
            case 3:
                return;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }
}

void GUI::IngresarEstudiante() {
    cout << "Ingrese el nombre del estudiante: ";
    string nombre;
    getline(cin, nombre);

    cout << "Ingrese los apellidos del estudiante: ";
    string apellidos;
    getline(cin, apellidos);

    cout << "Ingrese el correo del estudiante: ";
    string correo;
    getline(cin, correo);

    if (Controlador::IngresarEstudiante(nombre, apellidos, correo)) {
        cout << "Estudiante ingresado correctamente." << endl;
    } else {
        cout << "Error al ingresar el estudiante." << endl;
    }
    system("pause");
}

void GUI::MostrarEstudiantes() {
    cout << "=======" << endl;
    cout << "Estudiantes disponibles:" << endl;
    for (int i = 0; i < Controlador::indiceEstudiantes; i++) {
        Estudiante estudiante = Controlador::estudiantes[i];
        cout << "Carnet: " << estudiante.carnet << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellidos: " << estudiante.apellidos << endl;
        cout << "Correo: " << estudiante.correo << endl;
        cout << "-----------------" << endl;
    }
    system("pause");
}

void GUI::MenuPrestamos() {
    while (true) {
        cout << "=======" << endl;
        cout << "Menu Prestamos" << endl;
        cout << "1. Registrar prestamo" << endl;
        cout << "2. Mostrar prestamos" << endl;
        cout << "3. Volver" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                RegistrarPrestamo();
                break;
            case 2:
                MostrarPrestamos();
                break;
            case 3:
                return;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }
}

void GUI::RegistrarPrestamo() {
    cout << "Ingrese el codigo del libro: ";
    int codLibro;
    cin >> codLibro;
    cin.ignore(); // Limpiar el buffer

    cout << "Ingrese el carnet del estudiante: ";
    int carnetEst;
    cin >> carnetEst;
    cin.ignore(); // Limpiar el buffer

    if (Controlador::RegistrarPrestamo(codLibro, carnetEst)) {
        cout << "Prestamo registrado correctamente." << endl;
    } else {
        cout << "Error al registrar el prestamo." << endl;
    }
    system("pause");
}

void GUI::MostrarPrestamos() {
    cout << "=======" << endl;
    cout << "Prestamos realizados:" << endl;
    for (int i = 0; i < Controlador::indicePrestamos; i++) {
        Prestamo prestamo = Controlador::prestamos[i];
        cout << "Codigo del libro: " << prestamo.codLibro << endl;
        cout << "Carnet del estudiante: " << prestamo.carnetEst << endl;
        cout << "Fecha de prestamo: " << prestamo.fechaPrestamo << endl;
        cout << "Estado: " << prestamo.estadoPrestamo << endl;
        cout << "-----------------" << endl;
    }
    system("pause");
}

void GUI::MenuReportes() {
    while (true) {
        cout << "=======" << endl;
        cout << "Menu Reportes" << endl;
        cout << "1. Estudiante mas fiel" << endl;
        cout << "2. Libro mas prestado" << endl;
        cout << "3. Volver" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                EstudianteMasFiel();
                break;
            case 2:
                LibroMasPrestado();
                break;
            case 3:
                return;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }
}

void GUI::EstudianteMasFiel() {
    Estudiante estudiante = Controlador::EstudianteMasFiel();
    if (estudiante.carnet != -1) {
        cout << "Estudiante mas fiel:" << endl;
        cout << "Carnet: " << estudiante.carnet << endl;
        cout << "Nombre: " << estudiante.nombre << endl;
        cout << "Apellidos: " << estudiante.apellidos << endl;
        cout << "Correo: " << estudiante.correo << endl;
    } else {
        cout << "No se encontraron estudiantes." << endl;
    }
    system("pause");
}

void GUI::LibroMasPrestado() {
    Libro libro = Controlador::LibroMasPrestado();
    if (libro.codigo != -1) {
        cout << "Libro mas prestado:" << endl;
        cout << "Codigo: " << libro.codigo << endl;
        cout << "Titulo: " << libro.titulo << endl;
        cout << "Autor: " << libro.autor << endl;
        cout << "Anio: " << libro.anyo << endl;
    } else {
        cout << "No se encontraron libros." << endl;
    }
    system("pause");
}

/*************** Main ***************/
int main() {
    GUI::MenuPrincipal();
    return 0;
}
