package Tarea1;

import java.util.Scanner;

public class main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Solicitar al usuario los datos de entrada
        System.out.println("Ingrese el monto de la inversión en dólares:");
        double montoInicial = scanner.nextDouble();

        System.out.println("Ingrese la tasa de interés anual (%):");
        double tasaInteres = scanner.nextDouble();

        System.out.println("Ingrese la cantidad de años:");
        int numAnios = scanner.nextInt();

        // Calcular el monto final
        double montoFinal = montoInicial * Math.pow(1 + (tasaInteres / 100), numAnios);

        // Determinar la retención
        double retencion;
        if (montoFinal < 10000) {
            retencion = 0.025;
        } else if (montoFinal < 15000) {
            retencion = 0.05;
        } else if (montoFinal < 20000) {
            retencion = 0.075;
        } else {
            retencion = 0.1;
        }

        // Aplicar la retención
        double montoDespuesRetencion = montoFinal * (1 - retencion);

        // Redondear el monto final a dos decimales usando Math.round
        montoDespuesRetencion = Math.round(montoDespuesRetencion * 100.0) / 100.0;

        // Enseñar el monto final después de la retención
        System.out.println("El monto final después de " + numAnios + " años es: " + Math.round(montoDespuesRetencion * 100.0) / 100.0 + " dólares");

    }
}
