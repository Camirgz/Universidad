package Pregunta2;

import java.util.*;

public class Solution {
    public static void main(String args[] ) throws Exception {
        Scanner in = new Scanner (System.in);

        Arbol numeros = new Arbol();

        while (in.hasNext()){
            String linea = in.nextLine();
            int numero = Integer.parseInt(linea);
            numeros.insertar(numero);
        }

        numeros.imprimir();

    }
}