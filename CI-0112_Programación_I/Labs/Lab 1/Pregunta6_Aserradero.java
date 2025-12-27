import java.util.Scanner;
public class Pregunta6_Aserradero {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        // Entrada
        double longitudTronco = in.nextDouble();
        // Validación de entrada
        if (longitudTronco < 0 || longitudTronco > 60) {
            System.out.println("Entrada invalida");
        }
        // Convertir longitud a centímetros
        double longitudCentimetros = longitudTronco * 100;
        // Cálculo de tucas y desecho con residuo
        int tucasTipoA = (int) (longitudCentimetros / 150);
        int tucasTipoB = (int) ((longitudCentimetros % 150) / 27);
        int tucasTipoC = (int) (((longitudCentimetros % 150) % 27) / 6);
        int desechoCentimetros = (int) (((longitudCentimetros % 150) % 27) %
                6);
        // Cálculo de ganancia en dólares sin decimales (int)
        int gananciaTotalDolares = tucasTipoA * 95 + tucasTipoB * 12 +
                tucasTipoC * 2;
        // Salida
        System.out.println("Tipo A: " + tucasTipoA);
        System.out.println("Tipo B: " + tucasTipoB);
        System.out.println("Tipo C: " + tucasTipoC);
        System.out.println("Desecho: " + desechoCentimetros + " cm");
        System.out.println("Ganancia: " + gananciaTotalDolares + " dolares");
    }
}

