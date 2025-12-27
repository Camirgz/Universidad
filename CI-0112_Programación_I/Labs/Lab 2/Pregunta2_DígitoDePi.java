import java.util.Scanner;

public class Pregunta2_DígitoDePi{
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int terminos = in.nextInt();
        int impar = 1;
        double pi = 0;

        if (terminos < 0) {
            System.out.println("Entrada invalida");
        } else {
            for (int i = 1; i <= terminos; i++) {
                if (i % 2 == 0) {
                    pi = pi - (4.0 / impar); // Restar para términos pares
                } else {
                    pi = pi + (4.0 / impar); // Sumar para términos impares
                }
                impar += 2;
            }

            
            System.out.printf("%.5f%n", pi);
        }
    }
}