package Pregunta3;

import java.util.*;

class Competencia{
    Lista competidores = new Lista();

    public void interaccion(){
        Scanner in = new Scanner (System.in);

        while(in.hasNext()){
            String linea = in.nextLine();
            String [] datos = linea.split("-");
            if (datos[0].equalsIgnoreCase("INSCRIBIR")){
                competidores.agregar(new Competidora (datos[1], datos[2], datos[3]));
            } else if (datos[0].equalsIgnoreCase("DESINSCRIBIR")){
                competidores.eliminar(datos[1]);
            } else if (linea.equalsIgnoreCase("IMPRIMIR")){
                competidores.imprimir();}
        }
    }
}