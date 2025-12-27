#include <iostream>
#include <string>

using namespace std;

class Llanta {
public:
    double* primVuelta = new double;
    double* degradacion = new double;
    double* tiempoAcum = new double;

    Llanta() {
        *degradacion = 0;
        *tiempoAcum = 0;
    }

    virtual ~Llanta() {
        delete primVuelta;
        delete degradacion;
        delete tiempoAcum;
    }

    virtual double calcTiempo(int vueltas) const = 0;

    double getPrimVuelta() const {
        return *primVuelta;
    }
};

class Suave : public Llanta {
public:
    Suave() {
        *primVuelta = 78.8;
    }

    double calcTiempo(int vueltas) const override {
        for (int i = 0; i < vueltas; i++) {
            double aSumar = *primVuelta + *degradacion;
            *tiempoAcum += aSumar;
            *degradacion += 0.15;
        }
        return *tiempoAcum;
    }
};

class Media : public Llanta {
public:
    Media() {
        *primVuelta = 80.0;
    }

    double calcTiempo(int vueltas) const override {
        for (int i = 0; i < vueltas; i++) {
            double aSumar = *primVuelta + *degradacion;
            *tiempoAcum += aSumar;
            *degradacion += 0.10;
        }
        return *tiempoAcum;
    }
};

class Dura : public Llanta {
public:
    Dura() {
        *primVuelta = 82.0;
    }

    double calcTiempo(int vueltas) const override {
        for (int i = 0; i < vueltas; i++) {
            double aSumar = *primVuelta + *degradacion;
            *tiempoAcum += aSumar;
            *degradacion += 0.04;
        }
        return *tiempoAcum;
    }
};

class Equipo {
public:
    string nombre;
    bool calificado = true;
    double* duracionTotal = new double;
    Equipo* siguiente = nullptr;

    Equipo(int vueltasTotales, int tCambio) {
        *duracionTotal = 0;

        cout << "Ingrese el nombre del equipo: ";
        cin.ignore();
        getline(cin, nombre);

        cout << "Cantidad de juegos de llantas: ";
        int juegos;
        cin >> juegos;

        int vueltasRestantes = vueltasTotales;

        for (int i = 0; i < juegos; i++) {
            cout << "Juego " << i + 1 << ": tipo de llanta [S: Suave, M: Media, H: Dura]: ";
            char tipo;
            cin >> tipo;

            if (vueltasRestantes > 0) {
                cout << "¿Cuántas vueltas hará con esta llanta? (Vueltas restantes: "
                     << vueltasRestantes << "): ";
                int vueltas;
                cin >> vueltas;

                if (vueltas > vueltasRestantes) {
                    cout << "Error: No puede exceder las vueltas restantes. Intente de nuevo." << endl;
                    i--;  // Volver a pedir la llanta
                    continue;
                }

                vueltasRestantes -= vueltas;

                if (tipo == 'S') {
                    Suave llantaSuave;
                    *duracionTotal += llantaSuave.calcTiempo(vueltas) + tCambio;
                } else if (tipo == 'M') {
                    Media llantaMedia;
                    *duracionTotal += llantaMedia.calcTiempo(vueltas) + tCambio;
                } else if (tipo == 'H') {
                    Dura llantaDura;
                    *duracionTotal += llantaDura.calcTiempo(vueltas) + tCambio;
                } else {
                    calificado = false;
                    cout << "Equipo " << nombre << " descalificado por tipo de llanta inválido." << endl;
                }
            } else {
                cout << "No quedan vueltas restantes." << endl;
                break;
            }
        }

        if (vueltasRestantes > 0) {
            calificado = false;
            cout << "Equipo " << nombre << " descalificado por no completar todas las vueltas." << endl;
        }
    }

    ~Equipo() {
        delete duracionTotal;
    }

    double getDuracionTotal() const {
        return *duracionTotal;
    }
};

class Lista {
private:
    Equipo* cabeza = nullptr;

public:
    ~Lista() {
        while (cabeza != nullptr) {
            Equipo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void agregarEquipo(Equipo* nuevoEquipo) {
        if (cabeza == nullptr) {
            cabeza = nuevoEquipo;
        } else {
            Equipo* temp = cabeza;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoEquipo;
        }
    }

    void comparar() {
        Equipo* ganador = nullptr;
        Equipo* temp = cabeza;

        while (temp != nullptr) {
            if (temp->calificado) {
                if (ganador == nullptr || temp->getDuracionTotal() < ganador->getDuracionTotal()) {
                    ganador = temp;
                }
            }
            temp = temp->siguiente;
        }

        if (ganador != nullptr) {
            cout << "Equipo " << ganador->nombre << " ganaría la carrera en "
                 << ganador->getDuracionTotal() << " s" << endl;
        } else {
            cout << "Ningún equipo está calificado para ganar." << endl;
        }
    }
};

int main() {
    Lista lista;

    cout << "¡Bienvenido!" << endl;
    cout << "Cantidad de vueltas: ";
    int vueltasTotales;
    cin >> vueltasTotales;

    cout << "Duración cambio de llantas (en segundos): ";
    int tCambio;
    cin >> tCambio;

    bool condicional = true;
    while (condicional) {
        cout << "Opción [1: Equipo | 2: Ganador | 3: Salir]: ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            Equipo* equipo = new Equipo(vueltasTotales, tCambio);
            lista.agregarEquipo(equipo);
        } else if (opcion == 2) {
            lista.comparar();
        } else if (opcion == 3) {
            condicional = false;
        } else {
            cout << "Opción inválida" << endl;
        }
    }

    cout << "Gracias por usar el programa." << endl;
    return 0;
}