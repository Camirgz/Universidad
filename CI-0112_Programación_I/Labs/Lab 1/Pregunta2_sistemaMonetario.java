import java.util.Scanner;
public class Pregunta2_sistemaMonetario{
    public static void main(String[]args)
    {
        Scanner in = new Scanner (System.in);

        double Libras = in.nextDouble();
        Libras = Libras * 100;

        double Chelines = in.nextDouble();
        Chelines = (Chelines/20)*100;

        double Peniques = in.nextDouble();

        Peniques = (Peniques/ 12) /20*100;
        double Total = Libras +Chelines + Peniques;
        System.out.println(Total);
    }
}
