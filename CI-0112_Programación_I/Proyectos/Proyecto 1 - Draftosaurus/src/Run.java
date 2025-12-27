public class Run{
    public static void Correr (){
        //instancias
        Metodos empezar = new Metodos();

        System.out.println("====== ¡Bienvenido a Draftosaurus! ======\n");
        empezar.Ronda();
        System.out.println("\n====== Fin de la primera ronda. Queda 1 más ======\n");
        empezar.Ronda();
        System.out.println("\n====== Fin del juego. ======\n");
        System.out.println("====== Así queda el tablero de jugador 1 ======\n");
        empezar.MostradorDeTableroFinal1();
        System.out.println("\n====== Así queda el tablero de jugador 2 ======\n");
        empezar.MostradorDeTableroFinal2();
        int puntos_jugador1 = empezar.CalculadorDePuntos1();
        System.out.println("\nPuntaje P1: " + puntos_jugador1);
        int puntos_jugador2 = empezar.CalculadorDePuntos2();
        System.out.println("Puntaje P2: " + puntos_jugador2);
        if (puntos_jugador1>puntos_jugador2){
            System.out.println("\nGANA JUGADOR 1. FELICIDADES!");
        }
        else if (puntos_jugador1<puntos_jugador2){
            System.out.println("\nGANA JUGADOR 2. FELICIDADES!");
        }
        else if (puntos_jugador1==puntos_jugador2){
            System.out.println("\nFUE UN EMPATE. FELICIDADES A LOS DOS!");
        }
    }
}
