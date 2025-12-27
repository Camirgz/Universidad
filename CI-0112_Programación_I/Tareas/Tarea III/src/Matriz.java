package Tarea3;

import java.util.Random;

class Matriz {
    private int[][] matriz;

    // Método para obtener la matriz
    public int[][] getMatriz() {
        return this.matriz;
    }

    // Constructor
    public Matriz(int M, int N) {
        matriz = new int[M][N];
        llenarMatrizAleatoriamente();
    }

    // Método para llenar la matriz con valores aleatorios entre 1 y 9
    private void llenarMatrizAleatoriamente() {
        Random rand = new Random();
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[0].length; j++) {
                matriz[i][j] = rand.nextInt(9) + 1; // Valores entre 1 y 9
            }
        }
    }

    // Método para multiplicar esta matriz por otra matriz
    public int[][] multiplicar(Matriz otraMatriz) {

        int[][] otraMatrizData = otraMatriz.getMatriz();

        if (matriz[0].length != otraMatrizData.length) {
            System.out.println("No se pueden multiplicar las matrices. Dimensiones incompatibles.");
            return new int[0][0]; // Matriz vacía
        }

        int filas = matriz.length;
        int columnas = otraMatrizData[0].length;
        int[][] resultado = new int[filas][columnas];

        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                for (int k = 0; k < matriz[0].length; k++) {
                    resultado[i][j] += matriz[i][k] * otraMatrizData[k][j];
                }
            }
        }
        return resultado;
    }

    // Método para imprimir la matriz en pantalla
    public void imprimirMatriz() {
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[0].length; j++) {
                System.out.print(matriz[i][j] + " ");
            }
            System.out.println();
        }
    }
}
