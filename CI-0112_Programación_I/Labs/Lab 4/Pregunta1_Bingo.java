import java.util.*;
class Pregunta1_Bingo {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String[] numbers = in.nextLine().split("-");
        String[][] game = { in.nextLine().split(" "), in.nextLine().split(" "), in.nextLine().split(" "), in.nextLine().split(" "), in.nextLine().split(" ") };
        System.out.print(check(numbers, game));
    }

    //Metodo Principal
    public static String check(String[] winners, String[][] game) {
        // Bingo(LLeno)
        boolean bingo = true;
        for (int i = 0; i < game.length; i++) {
            for (int j = 0; j < game[i].length; j++) {
                boolean encontrado = false;
                for (int k = 0; k < winners.length; k++) {
                    if (game[i][j].equals(winners[k])) {
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    bingo = false;
                    break;
                }
            }
            //Romper Ciclo Completo
            if (!bingo) {
                break;
            }
        }

        //Vuelta
        if (bingo) {
            return "BINGO";
        }

        // Esquinas
        boolean esquinas = (contieneNumero(winners, game[0][0])) &&
                (contieneNumero(winners, game[0][4])) &&
                (contieneNumero(winners, game[4][0])) &&
                (contieneNumero(winners, game[4][4]));
        if (esquinas) {
            return "ESQUINAS";
        }

        // Verificar si se completó una línea
        if (completoLinea(winners, game)) {
            return "LINEA";
        }

        //EL MAYOR ELSE
        return "NADA";
    }

    //Otros Metodos

    //Metodo para saber si la coordenada contienen algun numero ganador
    public static boolean contieneNumero(String[] winners, String coordenada) {
        //Bucle for each
        for (String num : winners) {
            if (num.equals(coordenada)) {
                return true;
            }
        }
        return false;
    }

    //Metodo para saber si hay un gane por linea
    public static boolean completoLinea(String[] winners, String[][] game) {
        // Verificar si se completó una línea horizontal
        for (int i = 0; i < game.length; i++) {
            boolean lineaHorizontal = true;
            for (int j = 0; j < game[i].length; j++) {
                //Verificar si todas las coordenadas de la linea fueron numeros llamados
                if (!contieneNumero(winners, game[i][j])) {
                    lineaHorizontal = false;
                    break;
                }
            }
            if (lineaHorizontal) {
                return true;
            }
        }

        // Verificar si se completó una línea vertical
        for (int j = 0; j < game[0].length; j++) {
            boolean lineaVertical = true;
            for (int i = 0; i < game.length; i++) {
                //Verificar si todas las coordenadas de la linea fueron numeros llamados
                if (!contieneNumero(winners, game[i][j])) {
                    lineaVertical = false;
                    break;
                }
            }
            if (lineaVertical) {
                return true;
            }
        }

        //Si no hay ni linea vertical u horizontal
        return false;
    }
}


