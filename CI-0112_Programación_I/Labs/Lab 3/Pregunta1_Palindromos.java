import java.util.*;

public class Pregunta1_Palindromos {
    // Método para ver si es palíndromo
    public static boolean esPalindromo(String palabra) {
        // Modificar str
        palabra = palabra.replaceAll(" ", "").toLowerCase();
        palabra = palabra.replaceAll(",",""); //Eliminar si el palindromo tiene
        int largo = palabra.length();

        // Arreglos
        char[] palabra_vector = new char[largo];
        char[] alrevez_vector = new char[largo];

        // String a Vector palabra
        for (int i = 0; i < largo; i++) {
            palabra_vector[i] = palabra.charAt(i);
        }

        // String a Vector palabra al revés
        for (int i = largo - 1, j = 0; i >= 0; i--, j++) {
            alrevez_vector[j] = palabra.charAt(i);
        }

        // Comparar si son iguales
        for (int i = 0; i < largo; i++) {
            if (palabra_vector[i] != alrevez_vector[i]) {
                return false;
            }
        }
        return true;
    }

    // main
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String entrada = scanner.nextLine();
        int contador = 0;

        while (!entrada.equals(".")) {
            if (esPalindromo(entrada)) {
                System.out.println(entrada);
                contador += 1;
            }
            entrada = scanner.nextLine();
        }
        System.out.println(contador);
    }
}