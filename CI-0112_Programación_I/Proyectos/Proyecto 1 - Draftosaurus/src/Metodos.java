import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.Random;

public class Metodos{

    //Variable Inicial
    String bolsa_de_dinosaurios = "ttttttttvvvvvvvvaaaaaaaabbbbbbbbddddddddssssssss";

    //Metodo para elegir 6 especies de manera aleatoria
    public String SeleccionadorDeDinosaurios() {

        //Variables
        String letrasSeleccionadas = "";
        Random random = new Random();

        //Extractor de letras
        for (int i = 0; i < 6; i++) {
            int indiceAleatorio = random.nextInt(bolsa_de_dinosaurios.length());
            char letra = bolsa_de_dinosaurios.charAt(indiceAleatorio);
            letrasSeleccionadas += letra;
            bolsa_de_dinosaurios = bolsa_de_dinosaurios.substring(0, indiceAleatorio) +
                    bolsa_de_dinosaurios.substring(indiceAleatorio + 1);
        }
        return letrasSeleccionadas;
    }

    //Sirve para conseguir el dinosaurio ingresado
    public static String ConseguidorDeDinosaurio(String zona1, String zona2, String zona3, String zona4, String zona5, String zona6, String zona7, String baraja){
        char dino = '\0';
        char zona = '\0';
        System.out.println("(1) Bosque de la semejanza: [" + zona1 + "]");
        System.out.println("(2) Prado de la diferencia: [" + zona2 + "]");
        System.out.println("(3) Pradera del amor: [" + zona3 + "]");
        System.out.println("(4) Trio frondoso: [" + zona4 + "]");
        System.out.println("(5) Rey de la selva: [" + zona5 + "]");
        System.out.println("(6) Isla solitaria: [" + zona6 + "]");
        System.out.println("(7) Rio: [" + zona7 + "]");
        System.out.println("Estos son sus dinosaurios: " + baraja);
        dino = PreguntarDinosaurio(baraja);
        zona = PreguntarZona(zona1, zona2, zona3, zona4, zona5, zona6, zona7, dino);
        String DinoNuevo = "" + dino + zona;
        return DinoNuevo;
    }

    public static char PreguntarZona(String zona1, String zona2, String zona3, String zona4, String zona5, String zona6, String zona7, char dino){
        Scanner in = new Scanner (System.in);
        int continuar = 0;
        String entrada = "";
        do {
            continuar = 0;
            System.out.println("¿En cuál zona lo desea colocar?: ");
            entrada = in.nextLine();
            if (entrada.equals("1")){
                if (zona1.length() == 0){
                    continuar = 0;
                }
                else {
                    if (zona1.length()>=6){
                        System.out.println("Entrada inválida. Ya no se pueden poner más dinosaurios en la zona");
                        continuar = continuar +1;
                    }
                    else {
                        if (zona1.charAt(0) == dino){
                            continuar = 0;
                        }
                        else {
                            System.out.println("Entrada inválida. El dinosaurio tiene que ser igual a los otros en la zona");
                            continuar = continuar +1;
                        }
                    }
                }
            }
            else if (entrada.equals("2")){
                if (zona2.length()>=6){
                    System.out.println("Entrada inválida. Ya no se pueden poner más dinosaurios en la zona");
                    continuar = continuar +1;
                }
                else {
                    continuar = 0;
                    for (int i = 0; i<zona2.length(); i++){
                        if (zona2.charAt(i)==dino){
                            System.out.println("Entrada inválida. El dinosaurio no puede ser igual a los otros en la zona");
                            continuar = continuar +1;
                        }
                    }
                }
            }
            else if (entrada.equals("3")){
                if (zona3.length() < 6){
                    continuar = 0;
                }
                else {
                    System.out.println("Entrada inválida. Ya no se pueden poner más dinosaurios en la zona");
                    continuar = continuar +1;
                }
            }
            else if (entrada.equals("4")){
                if (zona4.length() < 3){
                    continuar = 0;
                }
                else {
                    System.out.println("Entrada inválida. Ya no se pueden poner más dinosaurios en la zona");
                    continuar = continuar +1;
                }
            }
            else if (entrada.equals("5")){
                if (zona5.length() == 0){
                    continuar = 0;
                }
                else {
                    System.out.println("Entrada inválida. Ya hay un dinosaurio.");
                    continuar = continuar +1;
                }
            }
            else if (entrada.equals("6")){
                if (zona6.length() == 0){
                    continuar = 0;
                }
                else {
                    System.out.println("Entrada inválida. Ya hay un dinosaurio.");
                    continuar = continuar +1;
                }
            }
            else if (entrada.equals("7")){
                continuar = 0;
            }
            else {
                System.out.println("Entrada inválida. Ingrese una zona válida");
                continuar = continuar +1;
            }
        } while (continuar > 0);
        return entrada.charAt(0);
    }

    public static char PreguntarDinosaurio(String baraja){
        Scanner in = new Scanner (System.in);
        int continuar = 0;
        String entrada = "";
        do{
            continuar = 0;
            System.out.println("¿Cuál desea colocar?: ");
            entrada = in.nextLine().toLowerCase();
            if (entrada.length()>1){
                System.out.println("Entrada inválida. Ingrese sólo un dinosaurio.");
                continuar = continuar +1;
            }
            else if (entrada.length()<1){
                System.out.println("Entrada inválida. Ingrese algún dinosaurio.");
                continuar = continuar +1;
            }
            else {
                for (int i = 0; i<baraja.length(); i++){
                    if (baraja.charAt(i)==entrada.charAt(0)){
                        continuar = 0;
                        break;
                    }
                    continuar = continuar +1;
                }
                if (continuar > 0){
                    System.out.println("Entrada inválida. Ingrese un dinosaurio de su baraja");
                }
            }
        } while (continuar > 0);
        char dinosaurio = entrada.charAt(0);
        return dinosaurio;
    }

    //Más variables
    //_1 significa jugador 1
    String zona1_1 = "";
    String zona2_1 = "";
    String zona3_1 = "";
    String zona4_1 = "";
    String zona5_1 = "";
    String zona6_1 = "";
    String zona7_1 = "";

    //variables del jugador 2
    String zona1_2 = "";
    String zona2_2 = "";
    String zona3_2 = "";
    String zona4_2 = "";
    String zona5_2 = "";
    String zona6_2 = "";
    String zona7_2 = "";

    //corre una ronda
    public void Ronda(){
        String baraja1 = SeleccionadorDeDinosaurios();
        String baraja2 = SeleccionadorDeDinosaurios();
        for(int i = 0; i<12; i++){
            char LetraDino = TurnadorDeEnunciado(i, baraja1, baraja2);
            if ((i%2==0)&&(i==2||i==6||i==10)){
                baraja2 = EliminarDino (baraja2, LetraDino);
            }
            if ((i%2==0)&&(i==0||i==4||i==8)){
                baraja1 = EliminarDino (baraja1, LetraDino);
            }
            if ((i%2!=0)&&(i==3||i==7||i==11)){
                baraja1 = EliminarDino (baraja1, LetraDino);
            }
            if ((i%2!=0)&&(i==1||i==5||i==9)){
                baraja2 = EliminarDino (baraja2, LetraDino);
            }
        }
    }

    //sirve para poner el tablero correcto de cada jugador
    public char TurnadorDeEnunciado (int i, String baraja1, String baraja2){
        String DinoNuevo = "";
        if (i%2==0){
            System.out.println("====== Es el turno de jugador 1 ======");
            if (i==2||i==6||i==10){
                baraja1 = Drafting(baraja1, baraja2);
            }
            DinoNuevo = ConseguidorDeDinosaurio(zona1_1, zona2_1, zona3_1, zona4_1, zona5_1, zona6_1, zona7_1, baraja1);
            char LetraDino = Concatenar1(DinoNuevo);
            return LetraDino;
        }
        else {
            System.out.println("====== Es el turno de jugador 2 ======");
            if (i==3||i==7||i==11){
                baraja2 = Drafting(baraja2, baraja1);
            }
            DinoNuevo = ConseguidorDeDinosaurio(zona1_2, zona2_2, zona3_2, zona4_2, zona5_2, zona6_2, zona7_2, baraja2);
            char LetraDino = Concatenar2(DinoNuevo);
            return LetraDino;
        }
    }

    //sirve para eliminar el dino de la baraja después de ser ingresado
    public static String EliminarDino (String baraja1, char LetraDino){
        for (int i = 0; i<baraja1.length(); i++){
            if (baraja1.charAt(i)==LetraDino){
                baraja1 = baraja1.substring(0, i) + baraja1.substring(i+1);
                break;
            }
        }
        return baraja1;
    }

    //sirve para intercambiar las barajas
    public static String Drafting(String baraja1, String baraja2){
        String temporal = "";
        temporal = baraja2;
        baraja2 = baraja1;
        baraja1 = temporal;
        return baraja1;
    }

    //sirve para agregar el dinosaurio ingresado a la zona correcta en el tablero de jugador 1
    public char Concatenar1 (String DinoNuevo){
        char dino = DinoNuevo.charAt(0);
        char zona = DinoNuevo.charAt(1);

        if (zona == '1'){
            zona1_1 = zona1_1 + dino;
        }
        else if (zona == '2'){
            zona2_1 = zona2_1 + dino;
        }
        else if (zona == '3'){
            zona3_1 = zona3_1 + dino;
        }
        else if (zona == '4'){
            zona4_1 = zona4_1 + dino;
        }
        else if (zona == '5'){
            zona5_1 = zona5_1 + dino;
        }
        else if (zona == '6'){
            zona6_1 = zona6_1 + dino;
        }
        else if (zona == '7'){
            zona7_1 = zona7_1 + dino;
        }
        return dino;
    }

    //sirve para agregar el dinosaurio a la zona correcta en el tablero de jugador 2
    public char Concatenar2 (String DinoNuevo){
        char dino = DinoNuevo.charAt(0);
        char zona = DinoNuevo.charAt(1);

        if (zona == '1'){
            zona1_2 = zona1_2 + dino;
        }
        else if (zona == '2'){
            zona2_2 = zona2_2 + dino;
        }
        else if (zona == '3'){
            zona3_2 = zona3_2 + dino;
        }
        else if (zona == '4'){
            zona4_2 = zona4_2 + dino;
        }
        else if (zona == '5'){
            zona5_2 = zona5_2 + dino;
        }
        else if (zona == '6'){
            zona6_2 = zona6_2 + dino;
        }
        else if (zona == '7'){
            zona7_2 = zona7_2 + dino;
        }
        return dino;
    }

    //sirve para mostrar el tablero final de jugador 1
    public void MostradorDeTableroFinal1(){
        System.out.println("(1) Bosque de la semejanza: [" + zona1_1 + "]");
        System.out.println("(2) Prado de la diferencia: [" + zona2_1 + "]");
        System.out.println("(3) Pradera del amor: [" + zona3_1 + "]");
        System.out.println("(4) Trio frondoso: [" + zona4_1 + "]");
        System.out.println("(5) Rey de la selva: [" + zona5_1 + "]");
        System.out.println("(6) Isla solitaria: [" + zona6_1 + "]");
        System.out.println("(7) Rio: [" + zona7_1 + "]");
    }

    //sirve para mostrar el tablero final de jugador 2
    public void MostradorDeTableroFinal2(){
        System.out.println("(1) Bosque de la semejanza: [" + zona1_2 + "]");
        System.out.println("(2) Prado de la diferencia: [" + zona2_2 + "]");
        System.out.println("(3) Pradera del amor: [" + zona3_2 + "]");
        System.out.println("(4) Trio frondoso: [" + zona4_2 + "]");
        System.out.println("(5) Rey de la selva: [" + zona5_2 + "]");
        System.out.println("(6) Isla solitaria: [" + zona6_2 + "]");
        System.out.println("(7) Rio: [" + zona7_2 + "]");
    }

    public static int ContadorDeDinosaurios(String zona1, String zona2, String zona3, String zona4, String zona5, String zona6, String zona7, char dinosaurio){
        int cantidad_de_dinosaurios = 0;
        for (int i = 0; i<zona1.length(); i++){
            if (zona1.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona2.length(); i++){
            if (zona2.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona3.length(); i++){
            if (zona3.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona4.length(); i++){
            if (zona4.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona5.length(); i++){
            if (zona5.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona6.length(); i++){
            if (zona6.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        for (int i = 0; i<zona7.length(); i++){
            if (zona7.charAt(i) == dinosaurio){
                cantidad_de_dinosaurios = cantidad_de_dinosaurios + 1;
            }
        }
        return cantidad_de_dinosaurios;
    }

    public int CalculadorDePuntos1(){
        int puntos = 0;
        //zona1
        if (zona1_1.length() == 1){
            puntos = puntos + 2;
        }
        else if (zona1_1.length() == 2){
            puntos = puntos + 4;
        }
        else if (zona1_1.length() == 3){
            puntos = puntos + 8;
        }
        else if (zona1_1.length() == 4){
            puntos = puntos + 12;
        }
        else if (zona1_1.length() == 5){
            puntos = puntos + 18;
        }
        else if (zona1_1.length() == 6){
            puntos = puntos + 24;
        }

        //zona2
        if (zona2_1.length() == 1){
            puntos = puntos + 1;
        }
        else if (zona2_1.length() == 2){
            puntos = puntos + 3;
        }
        else if (zona2_1.length() == 3){
            puntos = puntos + 6;
        }
        else if (zona2_1.length() == 4){
            puntos = puntos + 10;
        }
        else if (zona2_1.length() == 5){
            puntos = puntos + 15;
        }
        else if (zona2_1.length() == 6){
            puntos = puntos + 21;
        }

        //zona3

        puntos += praderaAmor(zona3_1);

        //zona4
        if (zona4_1.length() == 3){
            puntos = puntos + 7;
        }

        //zona5
        if (zona5_1.length()!=0){
            char dino_rey = zona5_1.charAt(0);
            int dino_jugador1 = ContadorDeDinosaurios(zona1_1, zona2_1, zona3_1, zona4_1, zona5_1, zona6_1, zona7_1, dino_rey);
            int dino_jugador2 = ContadorDeDinosaurios(zona1_2, zona2_2, zona3_2, zona4_2, zona5_2, zona6_2, zona7_2, dino_rey);
            if (dino_jugador1>=dino_jugador2){
                puntos = puntos + 7;
            }
        }
        //zona6
        if (zona6_1.length()!=0){
            char dino_solitario = zona6_1.charAt(0);
            int cantidad_de_iguales = ContadorDeDinosaurios(zona1_1, zona2_1, zona3_1, zona4_1, zona5_1, zona6_1, zona7_1, dino_solitario);
            if (cantidad_de_iguales == 1){
                puntos = puntos + 7;
            }
        }
        //zona7
        int cantidad_rio = zona7_1.length();
        puntos = puntos + (cantidad_rio);

        //T-Rex
        int cantidad_de_trex = ContadorDeDinosaurios(zona1_1, zona2_1, zona3_1, zona4_1, zona5_1, zona6_1, zona7_1, 't');
        puntos = puntos + (cantidad_de_trex);

        return puntos;
    }

    public int CalculadorDePuntos2(){
        int puntos = 0;
        //zona1
        if (zona1_2.length() == 1){
            puntos = puntos + 2;
        }
        else if (zona1_2.length() == 2){
            puntos = puntos + 4;
        }
        else if (zona1_2.length() == 3){
            puntos = puntos + 8;
        }
        else if (zona1_2.length() == 4){
            puntos = puntos + 12;
        }
        else if (zona1_2.length() == 5){
            puntos = puntos + 18;
        }
        else if (zona1_2.length() == 6){
            puntos = puntos + 24;
        }

        //zona2
        if (zona2_2.length() == 1){
            puntos = puntos + 1;
        }
        else if (zona2_2.length() == 2){
            puntos = puntos + 3;
        }
        else if (zona2_2.length() == 3){
            puntos = puntos + 6;
        }
        else if (zona2_2.length() == 4){
            puntos = puntos + 10;
        }
        else if (zona2_2.length() == 5){
            puntos = puntos + 15;
        }
        else if (zona2_2.length() == 6){
            puntos = puntos + 21;
        }

        //zona3

        puntos += praderaAmor(zona3_2);

        //zona4
        if (zona4_2.length() == 3){
            puntos = puntos + 7;
        }

        //zona5
        if(zona5_2.length()!=0){
            char dino_rey = zona5_2.charAt(0);
            int dino_jugador1 = ContadorDeDinosaurios(zona1_1, zona2_1, zona3_1, zona4_1, zona5_1, zona6_1, zona7_1, dino_rey);
            int dino_jugador2 = ContadorDeDinosaurios(zona1_2, zona2_2, zona3_2, zona4_2, zona5_2, zona6_2, zona7_2, dino_rey);
            if (dino_jugador2>=dino_jugador1){
                puntos = puntos + 7;
            }
        }
        //zona6
        if (zona6_2.length()!=0){
            char dino_solitario = zona6_2.charAt(0);
            int cantidad_de_iguales = ContadorDeDinosaurios(zona1_2, zona2_2, zona3_2, zona4_2, zona5_2, zona6_2, zona7_2, dino_solitario);
            if (cantidad_de_iguales == 1){
                puntos = puntos + 7;
            }
        }

        //zona7
        int cantidad_rio = zona7_2.length();
        puntos = puntos + (cantidad_rio);

        //T-Rex
        int cantidad_de_trex = ContadorDeDinosaurios(zona1_2, zona2_2, zona3_2, zona4_2, zona5_2, zona6_2, zona7_2, 't');
        puntos = puntos + (cantidad_de_trex);

        return puntos;
    }

    //Método para calcular los puntos en pradera del amor
    public static int praderaAmor(String cadena) {

        int puntos = 0;

        //Variables
        int cantT = 0;
        int cantV = 0;
        int cantA = 0;
        int cantD = 0;
        int cantB = 0;
        int cantS = 0;

        //Contar Cantidad de Dinosaurios por especie
        for (int i = 0; i < cadena.length(); i++) {
            char dinoActual = cadena.charAt(i);
            switch (dinoActual) {
                case ('t'): {
                    cantT++;
                    break;
                }
                case ('v'): {
                    cantV++;
                    break;
                }
                case ('a'): {
                    cantA++;
                    break;
                }
                case ('d'): {
                    cantD++;
                    break;
                }
                case ('b'): {
                    cantB++;
                    break;
                }
                case ('s'): {
                    cantS++;
                    break;
                }
            }
        }

        puntos += (cantT / 2) * 5;
        puntos += (cantV / 2) * 5;
        puntos += (cantA / 2) * 5;
        puntos += (cantD / 2) * 5;
        puntos += (cantB / 2) * 5;
        puntos += (cantS / 2) * 5;

        return puntos;
    }

}
