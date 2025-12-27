import java.util.Scanner;
public class Pregunta4_EncontrarTalla {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int Talla = in.nextInt();
        in.nextLine();
        String Sexo = in.nextLine();
        if (Talla <= 37 && Sexo.equals("H")) {
            System.out.println("XS");
        }

        else if (Talla <= 39 && Sexo.equals("H")) {
            System.out.println("S");
        }

        else if (Talla <= 42 && Sexo.equals("H")) {
            System.out.println("M");
        }

        else if (Talla <= 46 && Sexo.equals("H")) {
            System.out.println("L");
        }

        else if (Talla <= 50 && Sexo.equals("H")) {
            System.out.println("XL");
        }

        else if (Talla >= 81 && Talla <= 84 && Sexo.equals("M")) {
            System.out.println("XS");
        }

        else if (Talla >= 85 && Talla <= 89 && Sexo.equals("M")) {
            System.out.println("S");
        }

        else if (Talla >= 90 && Talla <= 94 && Sexo.equals("M")) {
            System.out.println("M");
        }

        else if (Talla >= 95 && Talla <= 103 && Sexo.equals("M")) {
            System.out.println("L");
        }

        else if (Talla >= 104 && Talla <= 114 && Sexo.equals("M")) {
            System.out.println("XL");
        }

        else if (!Sexo.equals("H") && !Sexo.equals("M")) {
            System.out.println("Entrada invalida");
        }

        else if (Sexo.equals("H") && (Talla < 36 || Talla > 50)) {
            System.out.println("No hay ropa adecuada en esta tienda");
        }

        else if (Sexo.equals("M") && (Talla < 81 || Talla > 114)) {
            System.out.println("No hay ropa adecuada en esta tienda");
        }
    }
}