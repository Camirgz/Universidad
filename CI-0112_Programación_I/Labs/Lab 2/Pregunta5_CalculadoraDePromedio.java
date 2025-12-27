import java.util.Scanner;

public class Pregunta5_CalculadoraDePromedio {
    public static void main(String[] args) {
        
        // Scanner
        Scanner in = new Scanner(System.in);
        
        // Variables
        int total_creditos = 0;
        double total_puntos = 0;
        double promedio = 0;
        
        // Ciclo
        while (true) {
            // Entrada de la nota
            String notaStr = in.nextLine();
            
            // Salida?
            if (notaStr.equals("?")) {
                break;
            } 
            
            else {
                // Conversión de la nota
                try {
                    double nota = Double.parseDouble(notaStr);
                    
                    // Entrada de los créditos
                    String creditosStr = in.nextLine();
                    int creditos = Integer.parseInt(creditosStr);
                    
                    // Validación de créditos
                    if (creditos >= 0) {
                        // Cálculo de puntos ponderados por materia
                        total_puntos += nota * creditos;
                        total_creditos += creditos;
                    } else {
                        System.out.println("Entrada invalida");
                        return; // Salir del programa si los créditos son inválidos
                    }
                } catch (NumberFormatException e) {
                    System.out.println("Entrada invalida");
                    return; // Salir del programa si la entrada es inválida
                }
            }
        }
        
        if (total_creditos >= 0) {
            
            //Solucion a limite que tiende a 0/0 (calculo profe)
            if (total_creditos == 0 && total_puntos == 0){
                System.out.println("0.00");
            }
            
            else{
                  promedio = total_puntos / total_creditos;
                // Redondeo e impresión con dos decimales y nueva línea
                System.out.printf("%.2f", promedio);
            }
          
            }
            else {
            System.out.println("Entrada invalida");
            }
    }
}