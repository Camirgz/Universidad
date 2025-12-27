import java.util.Scanner;

public class Pregunta1_Aguinaldo {
    public static void main(String[] args) {

        // Inicializacion de Variables
        Scanner in = new Scanner(System.in);
        int contador = 0;
        int salida = 0;
        double total = 0;
        double entrada_num = 0; // Cambiar a double para manejar decimales

        // Ciclo condicional
        while (contador < 14 && salida == 0) {
            String entrada = in.nextLine();

            // Terminar Ciclo
            if (entrada.equals("YA")) {
                salida += 1;
                break;
            }

            try {
                // Entrada
                entrada_num = Double.parseDouble(entrada); // Cambiar a Double

                // Verificar si es un número decimal
                if (entrada_num == Math.floor(entrada_num)) {
                    // Es un número entero
                    if (entrada_num >= 0) {
                        total += entrada_num;
                        contador += 1;
                    } else {
                        salida += 2;
                    }
                } else {
                    // Es un número decimal, considerarlo como entrada inválida
                    salida += 2;
                }
            } catch (NumberFormatException e) {
                salida += 2; // Entrada no es un número
            }
        }
        
        if (salida == 1 && contador < 13) {
            total = total / 12;
            total *= 100;
            int momentaneo = (int) Math.round(total);
            total = momentaneo / 100.0;
            System.out.println(total);
        }
        if (salida > 1 || contador >= 13) {
            System.out.println("Entrada invalida");
        }
    }
}