#include <iostream>
#include <stdlib.h>

#define MAX_REGISTROS 100

using namespace std;

/*************** Modelo ***************/
class Curso {
public:
    int codigo;
    string nombre;
    int creditos;
    int cupos;

    Curso() {}
    Curso(int codigo, string nombre, int creditos, int cupos);
};

Curso::Curso(int codigo, string nombre, int creditos, int cupos) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->creditos = creditos;
    this->cupos = cupos;
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

class Matricula {
public:
    int codCurso;
    int carnetEst;
    string fechaMatricula;
    string estadoMatricula;

    Matricula() {}
    Matricula(int codCurso, int carnetEst, string fechaMatricula, string estadoMatricula);
};

Matricula::Matricula(int codCurso, int carnetEst, string fechaMatricula, string estadoMatricula) {
    this->codCurso = codCurso;
    this->carnetEst = carnetEst;
    this->fechaMatricula = fechaMatricula;
    this->estadoMatricula = estadoMatricula;
}

/*************** Controlador ***************/
class Controlador {
public:
    static Curso cursos[MAX_REGISTROS];
    static Estudiante estudiantes[MAX_REGISTROS];
    static Matricula matricula[MAX_REGISTROS];

    static int indiceCursos;
    static int indiceEstudiantes;
    static int indiceMatricula;

    static bool IngresarCurso(string nombre, int creditos, int cupos);
    static bool IngresarEstudiante(string nombre, string apellidos, string correo);
    static bool IngresarMatricula(int codCurso, int carnetEst);
    static bool RegistrarEstudianteEnCurso(int codCurso, int carnetEst);
    static Curso CursoMasMatriculado();
    static Estudiante EstudianteConMasCreditos();
};

Curso Controlador::cursos[MAX_REGISTROS];
Estudiante Controlador::estudiantes[MAX_REGISTROS];
Matricula Controlador::matricula[MAX_REGISTROS];

int Controlador::indiceCursos = 0;
int Controlador::indiceEstudiantes = 0;
int Controlador::indiceMatricula = 0;

bool Controlador::IngresarCurso(string nombre, int creditos, int cupos) {
    if (Controlador::indiceCursos == MAX_REGISTROS) {
        return false;
    }

    int nuevoCodigo = Controlador::indiceCursos + 1;
    Curso nuevoCurso = Curso(nuevoCodigo, nombre, creditos, cupos);
    Controlador::cursos[Controlador::indiceCursos] = nuevoCurso;
    Controlador::indiceCursos++;
    return true;
}

bool Controlador::IngresarEstudiante(string nombre, string apellidos, string correo) {
    if (Controlador::indiceEstudiantes == MAX_REGISTROS) {
        return false;
    }

    int nuevoCarnet = Controlador::indiceEstudiantes + 1;
    Estudiante nuevoEstudiante = Estudiante(nuevoCarnet, nombre, apellidos, correo);
    Controlador::estudiantes[Controlador::indiceEstudiantes] = nuevoEstudiante;
    Controlador::indiceEstudiantes++;
    return true;
}

bool Controlador::IngresarMatricula(int codCurso, int carnetEst) {
    if (Controlador::indiceMatricula == MAX_REGISTROS) {
        return false;
    }

    Matricula nuevaMatricula = Matricula(codCurso, carnetEst, "2024-09-08", "Activa");
    Controlador::matricula[Controlador::indiceMatricula] = nuevaMatricula;
    Controlador::indiceMatricula++;
    return true;
}

bool Controlador::RegistrarEstudianteEnCurso(int codCurso, int carnetEst) {
    // Buscar el curso por código
    for (int i = 0; i < indiceCursos; i++) {
        if (cursos[i].codigo == codCurso) {
            // Verificar si hay cupos disponibles
            if (cursos[i].cupos > 0) {
                // Reducir el cupo del curso
                cursos[i].cupos--;

                // Registrar la matrícula
                return IngresarMatricula(codCurso, carnetEst);
            } else {
                cout << "No hay cupos disponibles para este curso." << endl;
                return false;
            }
        }
    }
    cout << "Curso no encontrado." << endl;
    return false;
}

Curso Controlador::CursoMasMatriculado() {
    int maxMatriculas = 0;
    Curso cursoMasMatriculado;

    int contadorMatriculas[MAX_REGISTROS] = {0};

    for (int i = 0; i < indiceMatricula; i++) {
        int codCurso = matricula[i].codCurso;
        contadorMatriculas[codCurso - 1]++;
    }

    for (int i = 0; i < indiceCursos; i++) {
        if (contadorMatriculas[i] > maxMatriculas) {
            maxMatriculas = contadorMatriculas[i];
            cursoMasMatriculado = cursos[i];
        }
    }

    return cursoMasMatriculado;
}

Estudiante Controlador::EstudianteConMasCreditos() {
    int maxCreditos = 0;
    Estudiante estudianteConMasCreditos;

    int contadorCreditos[MAX_REGISTROS] = {0};

    for (int i = 0; i < indiceMatricula; i++) {
        int carnetEst = matricula[i].carnetEst;
        int codCurso = matricula[i].codCurso;

        for (int j = 0; j < indiceCursos; j++) {
            if (cursos[j].codigo == codCurso) {
                contadorCreditos[carnetEst - 1] += cursos[j].creditos;
                break;
            }
        }
    }

    for (int i = 0; i < indiceEstudiantes; i++) {
        if (contadorCreditos[i] > maxCreditos) {
            maxCreditos = contadorCreditos[i];
            estudianteConMasCreditos = estudiantes[i];
        }
    }

    return estudianteConMasCreditos;
}

/*************** Vista ***************/
class GUI {
public:
    static void MenuPrincipal();
    static void MenuCursos();
    static void MenuIngresarCurso();
    static void MenuMostrarCursos();
    static void MenuEstudiantes();
    static void MenuIngresarEstudiante();
    static void MenuMostrarEstudiantes();
    static void MenuMatriculas();
    static void MenuRegistrarEstudianteEnCurso();
    static void MenuReportes();
};

void GUI::MenuPrincipal() {
    while (true) {
        cout << "=======" << endl;;
        cout << "Sistema de Matricula" << endl;
        cout << "1. Cursos" << endl;
        cout << "2. Estudiantes" << endl;
        cout << "3. Matriculas" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            GUI::MenuCursos();
        } else if (opcion == 2) {
            GUI::MenuEstudiantes();
        } else if (opcion == 3) {
            GUI::MenuMatriculas();
        } else if (opcion == 4) {
            GUI::MenuReportes();
        } else if (opcion == 5) {
            break;
        }
    }
}

void GUI::MenuCursos() {
    bool continuar = true;
    while (continuar) {
        cout << "=======" << endl;;
        cout << "Sistema de Matricula - Cursos" << endl;
        cout << "1. Ingresar Curso" << endl;
        cout << "2. Mostrar Cursos" << endl;
        cout << "3. Regresar" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            GUI::MenuIngresarCurso();
        } else if (opcion == 2) {
            GUI::MenuMostrarCursos();
        } else if (opcion == 3) {
            continuar = false;
        }
    }
}

void GUI::MenuIngresarCurso() {
    cout << "Digite el nombre del curso" << endl;
    string nombre;
    getline(cin, nombre, '\n');
    cout << "Digite la cantidad de creditos del curso" << endl;
    int creditos;
    cin >> creditos;
    cin.ignore();
    cout << "Digite la cantidad de cupos disponibles del curso" << endl;
    int cupos;
    cin >> cupos;
    cin.ignore();

    bool respuesta = Controlador::IngresarCurso(nombre, creditos, cupos);
    cout << "Resultado del ingreso: " << respuesta << endl;
    cout << "=======" << endl;;
}

void GUI::MenuMostrarCursos() {
    cout << "=======" << endl;;
    for (int i = 0; i < Controlador::indiceCursos; i++) {
        Curso c = Controlador::cursos[i];
        cout << "Codigo: " << c.codigo;
        cout << ", nombre: " << c.nombre;
        cout << ", creditos: " << c.creditos;
        cout << ", cupos: " << c.cupos << endl;
    }
    cout << "=======" << endl;;
}

void GUI::MenuEstudiantes() {
    bool seguir = true;
    while (seguir) {
        cout << "=======" << endl;;
        cout << "Sistema de Matricula - Estudiantes" << endl;
        cout << "1. Ingresar Estudiante" << endl;
        cout << "2. Mostrar Estudiantes" << endl;
        cout << "3. Regresar" << endl;
        
        int opcion = 0;
        cin >> opcion;
        cin.ignore();
        
        if (opcion == 1) {
            GUI::MenuIngresarEstudiante();
        }
        else if (opcion == 2) {
            GUI::MenuMostrarEstudiantes();
        }
        else if (opcion == 3) {
            seguir = false;
        }
    }
}

void GUI::MenuIngresarEstudiante() {
    cout << "Digite el nombre del estudiante" << endl;
    string nombre;
    getline(cin, nombre, '\n');
    cout << "Digite los apellidos del estudiante" << endl;
    string apellidos;
    getline(cin, apellidos, '\n');
    cout << "Digite el correo del estudiante" << endl;
    string correo;
    getline(cin, correo, '\n');
    
    bool respuesta = Controlador::IngresarEstudiante(nombre, apellidos, correo);
    
    cout << "Resultado del ingreso: " << respuesta << endl;
    cout << "=======" << endl;;
}

void GUI::MenuMostrarEstudiantes() {
    cout << "=======" << endl;;
    for (int i = 0; i < Controlador::indiceEstudiantes; i++) {
        Estudiante e = Controlador::estudiantes[i];
        cout << "Carnet: " << e.carnet;
        cout << ", nombre: " << e.nombre;
        cout << ", apellidos: " << e.apellidos;
        cout << ", correo: " << e.correo << endl;
    }
    cout << "=======" << endl;;
}

void GUI::MenuMatriculas() {
    bool continuar = true;
    while (continuar) {
        cout << "=======" << endl;;
        cout << "Sistema de Matricula - Matriculas" << endl;
        cout << "1. Registrar Estudiante en Curso" << endl;
        cout << "2. Regresar" << endl;

        int opcion = 0;
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            GUI::MenuRegistrarEstudianteEnCurso();
        } else if (opcion == 2) {
            continuar = false;
        }
    }
}

void GUI::MenuRegistrarEstudianteEnCurso() {
    cout << "Digite el carnet del estudiante" << endl;
    int carnet;
    cin >> carnet;
    cin.ignore();
    cout << "Digite el codigo del curso" << endl;
    int codigoCurso;
    cin >> codigoCurso;
    cin.ignore();

    bool respuesta = Controlador::RegistrarEstudianteEnCurso(codigoCurso, carnet);

    cout << "Resultado de la matricula: " << (respuesta ? "Exito" : "Error") << endl;
    cout << "=======" << endl;;
}

void GUI::MenuReportes() {
    cout << "=======" << endl;;
    Curso cursoMasMatriculado = Controlador::CursoMasMatriculado();
    Estudiante estudianteConMasCreditos = Controlador::EstudianteConMasCreditos();
    
    cout << "Reporte de Matricula" << endl;
    cout << "Curso con mas matriculas: " << cursoMasMatriculado.nombre << endl;
    cout << "Estudiante con mas creditos: " << estudianteConMasCreditos.nombre << " " << estudianteConMasCreditos.apellidos << endl;
    cout << "Cursos disponibles despues de matriculas:" << endl;
    
    for (int i = 0; i < Controlador::indiceCursos; i++) {
        Curso c = Controlador::cursos[i];
        cout << "Codigo: " << c.codigo << ", Nombre: " << c.nombre << ", Cupos restantes: " << c.cupos << endl;
    }
    cout << "=======" << endl;;
}

/*************** main ***************/
int main() {
    GUI::MenuPrincipal();
    return 0;
}
