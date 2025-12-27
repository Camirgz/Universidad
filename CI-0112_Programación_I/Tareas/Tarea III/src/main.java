package Tarea3;

import java.util.Scanner;

public class main {
    public static void main(String[] args) {

        // Instancias
        Funciones funciones = new Funciones();
        Scanner sc = new Scanner(System.in);

        // Pedir datos de las matrices
        System.out.println("=== Matriz 1 ===");
        int filas1 = Funciones.obtenerNumero(sc, "Hola! \nIngrese el número de filas: ");
        int columnas1 = Funciones.obtenerNumero(sc, "Ingrese el número de columnas: ");

        System.out.println("\n=== Matriz 2 ===");
        int filas2 = Funciones.obtenerNumero(sc,  "Ingrese el número de filas: ");
        int columnas2 = Funciones.obtenerNumero(sc, "Ingrese el número de columnas: ");

        // Imprimiendo las matrices y el resultado
        System.out.println("Matriz 1:");
        Matriz matriz1 = new Matriz(filas1,columnas1);
        matriz1.imprimirMatriz();

        System.out.println("\nMatriz 2:");
        Matriz matriz2 = new Matriz(filas2, columnas2);
        matriz2.imprimirMatriz();

        System.out.println("\nResultado de la multiplicación:");
        int[][] resultado = matriz1.multiplicar(matriz2);

        if (resultado.length > 0) {
            for (int i = 0; i < resultado.length; i++) {
                for (int j = 0; j < resultado[0].length; j++) {
                    System.out.print(resultado[i][j] + " ");
                }
                System.out.println();
            }
        }
    }
}