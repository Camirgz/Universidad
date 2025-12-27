import java.util.Scanner;

public class Pregunta2_ExamenAdmision {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String entrada_respuesta = in.nextLine();
        String entrada_solucion = in.nextLine();

        int nota_final = calcularNota(entrada_respuesta, entrada_solucion);

        if (nota_final >= 0) {
            System.out.println(nota_final);
        } else {
            System.out.println("Entrada invalida");
        }
    }

    public static int calcularNota(String respuesta, String solucion) {
        respuesta = respuesta.replaceAll("NR", "Z").toLowerCase();
        solucion = solucion.toLowerCase();

        String[] respuesta_vector = respuesta.split("-");
        String[] solucion_vector = solucion.split("-");

        int largo_respuesta = respuesta_vector.length;
        int largo_solucion = solucion_vector.length;

        if (largo_respuesta != largo_solucion) {
            return -1; // Longitudes diferentes, no se puede calcular la nota.
        }

        int nota_final = 0;

        for (int i = 0; i < largo_respuesta; i++) {
            if (respuesta_vector[i].equals(solucion_vector[i])) {
                nota_final += 1;
            }
        }

        return (nota_final * 100) / largo_respuesta;
    }
}