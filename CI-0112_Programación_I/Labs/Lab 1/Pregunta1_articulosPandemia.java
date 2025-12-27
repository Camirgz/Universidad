import java.util.Scanner;
public class Pregunta1_articulosPandemia {
    public static void main(String[]args)
    {
        Scanner in = new Scanner(System.in);

        float Mascarilla = in.nextInt();
        Mascarilla = Mascarilla*650;

        float Careta = in.nextInt();
        Careta = Careta*3500;

        float Guantes = in.nextInt();
        Guantes = Guantes*100;

        float Alcohol = in.nextInt();
        Alcohol = Alcohol*2750;

        float Total = Alcohol + Guantes + Careta + Mascarilla + 2500;

        System.out.println(Total);
    }
}
