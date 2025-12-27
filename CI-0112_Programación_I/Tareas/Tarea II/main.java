package Tarea2;

import java.util.Scanner;


public class main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Ingrese el número de vértices del polígono: ");
        int n = scanner.nextInt();

        //Inicializar arrays
        double[] xCoords = new double[n];
        double[] yCoords = new double[n];

        System.out.println("Ingrese las coordenadas, primero X, de enter y luego Y, de cada vértice:");

        //Llenar array
        for (int i = 0; i < n; i++) {
            System.out.print("Vértice " + (i + 1) + ": ");
            xCoords[i] = scanner.nextDouble();
            yCoords[i] = scanner.nextDouble();
        }

        double[] centroid = calcularCentroide(xCoords, yCoords);
        System.out.println("Coordenada del centro de gravedad: (" + centroid[0] + ", " + centroid[1] + ")");
    }

    public static double[] calcularCentroide(double[] xCoords, double[] yCoords) {
        int n = xCoords.length;
        double area = 0;
        double sumX = 0;
        double sumY = 0;

        for (int i = 0; i < n; i++) {
            //Se van cambiando con cada iteración
            double xi = xCoords[i];
            double yi = yCoords[i];
            double xi1 = xCoords[(i + 1) % n];
            double yi1 = yCoords[(i + 1) % n];

            // Sumar al área
            area += (xi * yi1 - xi1 * yi);

            // Sumar para las coordenadas del centroide
            sumX += (xi + xi1) * (xi * yi1 - xi1 * yi);
            sumY += (yi + yi1) * (xi * yi1 - xi1 * yi);
        }

        area /= 2;  // Dividir por 2 el área
        sumX /= 6 * area;
        sumY /= 6 * area;

        // Redondear a dos decimales
        sumX = Math.round(sumX * 100.0) / 100.0;
        sumY = Math.round(sumY * 100.0) / 100.0;

        return new double[]{sumX, sumY};
    }
}

