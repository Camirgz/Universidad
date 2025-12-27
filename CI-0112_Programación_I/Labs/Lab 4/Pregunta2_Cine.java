import java.util.*;
class Pregunta2_Cine{
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in) ;
        char[][] theatre = new char[12][10];
        for (int i=0; i<12; i++)
            theatre[i] = in.nextLine().toCharArray();
        System.out.print(longest_string(theatre));
    }

    public static int longest_string(char[][] state) {
        // Líneas Horizontales
        int temporal_H = 0;
        int masLargo = 0;
        for (int i = 0; i < state.length; i++) {
            temporal_H = 0; // Reiniciar cada vez que cambia de fila
            for (int j = 0; j < state[i].length; j++) {
                if (state[i][j] == 'O') {
                    temporal_H++;
                    if (temporal_H > masLargo) {
                        masLargo = temporal_H;
                    }
                } else {
                    temporal_H = 0;
                }
            }
        }

        // Líneas Verticales
        int temporal_V = 0;
        for (int j = 0; j < state[0].length; j++) {
            temporal_V = 0; // Reiniciar cada vez que cambia de columna
            for (int i = 0; i < state.length; i++) {
                if (state[i][j] == 'O') {
                    temporal_V++;
                    if (temporal_V > masLargo) {
                        masLargo = temporal_V;
                    }
                } else {
                    temporal_V = 0;
                }
            }
        }
        return masLargo;
    }
}
