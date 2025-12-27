
import java.util.Scanner;
import java.util.Random;

public class CerdoMetodos {

    //Variables Globales
    //Puntaje de Jugadores
    int J1 = 0;
    int J2 = 0;
    int J3 = 0;
    int J4 = 0;
    int J5 = 0;
    int J6 = 0;

    //Partidas Ganadas
    int J1G = 0;
    int J2G = 0;
    int J3G = 0;
    int J4G = 0;
    int J5G = 0;
    int J6G = 0;

    //Otras

    int turno = 1;
    int valorDado = 0;
    int entradaJugadores = 0;
    int cantidadPuntos = 15;

    boolean detenerTurno = false;
    boolean validadorEntrada = false;
    boolean hayGanador = false;
    boolean otraRonda = true;
    int cantidadJugadores=0;

    //Iniciar Imports
    Scanner in = new Scanner(System.in);
    Random random = new Random();

    //Métodos
    //Imprimir Tablero
    public void imprimirPuntajes(int entradaJugadoresValidada) {
        switch (entradaJugadoresValidada) {
            case 2: {
                System.out.println("J1: " + J1 + " J2: " + J2);
                break;
            }
            case 3: {
                System.out.println("J1: " + J1 + " J2: " + J2 + " J3: " + J3);
                break;
            }
            case 4: {
                System.out.println("J1: " + J1 + " J2: " + J2 + " J3: " + J3 + " J4: " + J4);
                break;
            }
            case 5: {
                System.out.println("J1: " + J1 + " J2: " + J2 + " J3: " + J3 + " J4: " + J4 + " J5: " + J5);
                break;
            }
            case 6: {
                System.out.println("J1: " + J1 + " J2: " + J2 + " J3: " + J3 + " J4: " + J4 + " J5: " + J5 + " J6: " + J6);
                break;
            }
        }
    }

    //Tirar dado
    public int tirarDado() {
        valorDado = random.nextInt(6) + 1;
        return valorDado;
    }

    //Turno
    public void cambioTurno() {
        if (turno != cantidadJugadores) {
            turno += 1;
        } else {
            turno = 1;
        }
    }

    //Quién gana?
    public void ganador() {
        if (J1 >= cantidadPuntos) {
            System.out.println("Felicidades J1 ha ganado!");
            ++J1G;
        }
        if (J2 >=cantidadPuntos) {
            System.out.println("Felicidades J2 ha ganado!");
            ++J2G;
        }
        if (J3 >= cantidadPuntos) {
            System.out.println("Felicidades J3 ha ganado!");
            ++J3G;
        }
        if (J4 >= cantidadPuntos) {
            System.out.println("Felicidades J4 ha ganado!");
            ++J4G;
        }
        if (J5 >= cantidadPuntos) {
            System.out.println("Felicidades J5 ha ganado!");
            ++J5G;
        }
        if (J6 >= cantidadPuntos) {
            System.out.println("Felicidades J6 ha ganado!");
            ++J6G;
        }
    }

    //Hay ganador?
    public void hay_ganador() {
        if (J1 < cantidadPuntos && J2 < cantidadPuntos && J3 < cantidadPuntos && J4 < cantidadPuntos && J5 < cantidadPuntos && J6 < cantidadPuntos) {
            hayGanador = false;
        } else {

            detenerTurno = true;
            hayGanador = true;
            valorDado = 80;
        }
    }

    //Puntos a Sumar
    public void sumadorPuntos(int turno, int puntos) {
        switch (turno) {
            case 1: {
                J1 += puntos;
                break;
            }
            case 2: {
                J2 += puntos;
                break;
            }
            case 3: {
                J3 += puntos;
                break;
            }
            case 4: {
                J4 += puntos;
                break;
            }
            case 5: {
                J5 += puntos;
                break;
            }
            case 6: {
                J6 += puntos;
                break;
            }
        }
    }

    //Juego
    public void juego() {
        String entrada = "";
        int puntos = 0;
        while (!detenerTurno) {
            imprimirPuntajes(cantidadJugadores);
            System.out.print("<<Turno de J" + turno + ">>    ");
            System.out.println("El valor del dado es: " + valorDado);
            if (valorDado < 6) {
                System.out.println("Ingrese [D] para lanzar, o [P] para plantarse: "); //D de dado ;3
                entrada = in.next();
                puntos += valorDado;
                validadorEntrada = false; // Restablece validadorEntrada a false
                while (!validadorEntrada) {

                    if (entrada.equalsIgnoreCase("D")) {
                        validadorEntrada = true;
                        valorDado = tirarDado();
                        hay_ganador();
                    } else if (entrada.equalsIgnoreCase("P")) {
                        sumadorPuntos(turno, puntos);
                        System.out.println("Ha decidido plantarse, avanza " + puntos + " casillas");
                        puntos = 0;
                        cambioTurno();
                        valorDado = tirarDado();
                        hay_ganador();
                        break;
                    } else {
                        System.out.println("Entrada inválida, vuelva a ingresar un valor");
                        System.out.println("Ingrese [D] para lanzar, o [P] para plantarse: "); //D de dado ;3
                        entrada = in.next();
                    }
                }
            }
            if (valorDado == 6) {
                cambioTurno();
                imprimirPuntajes(cantidadJugadores);
                puntos = 0;
                validadorEntrada = true;
                System.out.println("El valor del dado es: " + valorDado);
                System.out.println("Fin del turno, sin puntos");
                valorDado = tirarDado();
                hay_ganador();
            }
        }
        ganador();
    }

    //Cantidad de Jugadores
    public int cantidadJugadores() {
        do {
            System.out.print("Ingrese la cantidad de jugadores: ");
            String entrada = in.nextLine();

            try {
                cantidadJugadores = Integer.parseInt(entrada);

                if (cantidadJugadores >= 2 && cantidadJugadores <= 6) {
                    break; // Salir del ciclo si el número está en el rango deseado
                } else {
                    System.out.println("Número fuera de rango. Debe estar entre 2 y 6.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Entrada inválida. Debe ser un número.");
            }
        } while (true);
        return cantidadJugadores;
    }

    //Hay otro ronda?
    public boolean otraRonda() {
        String entradaRonda ="";
        while (true) {
            System.out.println("Ingrese [R] para repetir y [S] para salir");
            entradaRonda = in.next();
            if (entradaRonda.equalsIgnoreCase("R")) {
                return true;
            } else if (entradaRonda.equalsIgnoreCase("S")) {
                return false;
            } else {
                System.out.println("Entrada inválida. Por favor, ingrese 'R' para repetir o 'S' para salir.");
            }
        }
    }


    //Cantidad final de ganadores
    public void ganadores(int entradaJugadoresValidada) {
        System.out.println("Partidas ganadas:");
        switch (entradaJugadoresValidada) {
            case 2: {
                System.out.println("J1: " + J1G + " J2: " + J2G);
                break;
            }
            case 3: {
                System.out.println("J1: " + J1G + " J2: " + J2G + " J3: " + J3G);
                break;
            }
            case 4: {
                System.out.println("J1: " + J1G + " J2: " + J2G + " J3: " + J3G + " J4: " + J4G);
                break;
            }
            case 5: {
                System.out.println("J1: " + J1G + " J2: " + J2G + " J3: " + J3G + " J4: " + J4G + " J5: " + J5G);
                break;
            }
            case 6: {
                System.out.println("J1: " + J1G + " J2: " + J2G + " J3: " + J3G + " J4: " + J4G + " J5: " + J5G + " J6: " + J6G);
                break;
            }
            default:
                System.out.println("Opción no reconocida.");
                break;

        }
    }

    public void restablecer() {
        J1 = 0;
        J2 = 0;
        J3 = 0;
        J4 = 0;
        J5 = 0;
        J6 = 0;


        //Otras

        turno = 1;
        valorDado = 0;
        entradaJugadores = 0;
        cantidadPuntos = 10;

        detenerTurno = false;
        validadorEntrada = false;
        hayGanador = false;
        otraRonda = true;
    }

    //Método Final
    public void Ronda() {
        cantidadJugadores = cantidadJugadores();
        boolean jugar = true;
        do {
            while (!hayGanador) {
                restablecer();
                System.out.println("=== Inicio de la partida ===");
                valorDado = tirarDado();
                juego();
                System.out.println("=== Fin de la partida ===");
                jugar = otraRonda();
                if(!jugar){
                    break;
                }
            }
            restablecer();
        } while (jugar);
        ganadores(cantidadJugadores);
    }

}