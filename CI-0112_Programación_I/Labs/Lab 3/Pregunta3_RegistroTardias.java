//Imports
import java.util.Scanner;

//Clases
public class Pregunta3_RegistroTardias {

    //Metodo
    public static int Tardias(String[] horasRegistro) {

        //Iniciar contador de Tardias
        int contador = 0;

        //Ciclo for
        for (String hora : horasRegistro) {

            // Validar
            if (hora.matches("\\d{2}:\\d{2}")) {

                // Dividir la horas y minutos)
                String[] partesHora = hora.split(":");
                int horas = Integer.parseInt(partesHora[0]);
                int minutos = Integer.parseInt(partesHora[1]);

                // Comparar con hora de entrada
                if (horas >= 24 && minutos > 0) {
                    System.out.println("Entrada invalida");
                    return -1;
                } else if (horas > 7 || (horas == 7 && minutos > 0)) {
                    contador++;
                }

            } else {
                // Hora con formato incorrecto
                System.out.println("Entrada invalida");
                return -1;
            }
        }
        return contador;
    }

    //Main
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

        String[] horas = input.split(",");

        // Contar llegadas tarde
        int contador = Tardias(horas);

        //Hay Tardiass
        if (contador >= 0) {
            System.out.println(contador);
        }
    }
}