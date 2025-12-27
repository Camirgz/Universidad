import java.util.Scanner;
public class Pregunta7_AnnosBiciestos{
    public static void main (String[]args){
        Scanner in = new Scanner (System.in);

        int entrada = in.nextInt();
        int verdad = 0;

        if (entrada % 100 == 0 && entrada % 400 == 0){
            System.out.println("BISIESTO");
        }

        if (entrada % 100 == 0 && entrada % 400 != 0){
            System.out.println("NO BISIESTO");
        }

        if (entrada % 100 != 0 && entrada % 4 == 0){
            System.out.println("BISIESTO");
        }

        if (entrada % 100 != 0 && entrada % 4 != 0){
            System.out.println("NO BISIESTO");
        }
    }
}
