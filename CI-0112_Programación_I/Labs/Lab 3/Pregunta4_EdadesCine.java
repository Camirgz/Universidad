//Import
import java.util.*;

//Class
class Pregunta4_EdadesCine {

    //Método propio correr()
    public static void correr() {

        //Iniciar Scanner
        Scanner in = new Scanner(System.in);

        //Variables
        int contador = 0; //"Errores"
        int total = -1;
        int temp = 0;
        boolean mayoresEdad = false;

        //Comprobar Entrada
        try {
            total = in.nextInt();

        } catch (InputMismatchException error) {
            contador++;
        }

        if (total == 0) {
            determinar_clasificaciones(21, true);
        } else if (contador == 0) {

            int[] edades = new int[total];

            for (int i = 0; i < total; i++) {
                try {
                    edades[i] = in.nextInt();
                } catch (InputMismatchException error) {
                    contador++;
                }
            }

            //Método del boxeador¿?
            for (int i = 0; i < edades.length - 1; i++) {

                if (edades[i] > edades[i + 1]) {
                    temp = edades[i]; //Cambiar al mayor
                    edades[i] = edades[i + 1];
                    edades[i + 1] = temp; //temp va  a ser el mayor
                }
                //Verificar si es adulto
                if (edades[i] >= 18) {
                    mayoresEdad = true;
                }
            }

            if (contador == 0) {
                //Edades [0] va a ser el de menor edad
                determinar_clasificaciones(edades[0], mayoresEdad);
            } else {
                System.out.println("Entrada invalida");
            }
        } else {
            System.out.println("Entrada invalida");
        }
    }

    //Metodo ya hecho Profe
    public static void determinar_clasificaciones(int menor_edad, boolean mayoresEdad) {

        //Siempre se imprime
        System.out.println("TP");

        if ((menor_edad < 18 && mayoresEdad) || menor_edad > 18) {
            System.out.println("STP");
        }
        if (menor_edad > 12) {
            System.out.println("12+");
        }
        if (menor_edad > 14) {
            System.out.println("14+");
        }
        if (menor_edad > 18) {
            System.out.println("18+");
        }
    }
    //Main Profe
    public class Solution {

        public static void main(String args[]) {
            Pregunta4_EdadesCine.correr();
        }
    }

}
