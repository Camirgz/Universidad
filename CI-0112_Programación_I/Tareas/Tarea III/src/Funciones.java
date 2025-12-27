package Tarea3;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Funciones {

    public static int obtenerNumero(Scanner sc, String mensaje) {
        int numero = 0;
        while (true) {
            try {
                System.out.print(mensaje);
                numero = sc.nextInt();
                return numero;
            } catch (InputMismatchException e) {
                System.out.println("Por favor, ingrese un número válido.");
                sc.nextLine(); //limpar scanner;
            }
        }
    }
}
