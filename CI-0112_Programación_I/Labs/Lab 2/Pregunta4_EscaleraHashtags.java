import java.util.Scanner;

public class Pregunta4_EscaleraHashtags {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        try {
            // Entrada
            String cantidad = in.nextLine();
            int cant_gradas = Integer.parseInt(cantidad);
            if (cant_gradas >= 0) {

                for (int i = 1; i <= cant_gradas; i++) {
                    // Espacios
                    for (int j = 0; j < cant_gradas - i; j++) {
                        System.out.print(" ");
                    }

                    // Hashtags
                    for (int k = 0; k < i; k++) {
                        System.out.print("#");
                    }

                    // Siguiente grada
                    System.out.println();
                }
            } else {
                System.out.println("Entrada invalida");
            }
        } catch (Exception e) {
            System.out.println("Entrada invalida");
        }
    }
}