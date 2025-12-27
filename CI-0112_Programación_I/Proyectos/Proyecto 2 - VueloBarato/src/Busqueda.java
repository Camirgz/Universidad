import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Busqueda{
    private Aerolinea [] aerolineas;
    private String ignorados = "";
    
    public void CargarInformacion(String carpeta){
        File folder = new File(carpeta);
        File[] archivos = folder.listFiles();
        
        this.aerolineas = new Aerolinea [50];
        int cantidadLineas = 0;
        
        String line = "";
        String entero = "";
        for (int i = 0; i<archivos.length; i++) {
            if (archivos[i].isFile()) {
                try (BufferedReader br = new BufferedReader(new FileReader(archivos[i]))) {
                    while ((line = br.readLine()) != null) {
                        String[] partes = line.split(",");
                        if (partes.length == 9) {
                            if (vueloValido(partes)) {
                                cantidadLineas++;
                                if (entero.equals("")){
                                    entero = entero + line;
                                }
                                else{
                                    entero = entero + ";" + line;
                                }
                            } else {
                                annadirIgnorado(line);
                            }
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Error al leer el archivo: " + e.getMessage());
                }
            }
            
            String [] datos = entero.split(";");
            
            aerolineas[i] = new Aerolinea (archivos[i].getName(), datos);
        }
    }
    
    public void VueloMasBaratoEscalasAerolineas(String ciudadSalida, String ciudadLlegada, String fechaSalida, int escalasMaximas){
        System.out.println("Próximamente disponible");
    }
    
    public void VueloMasBaratoEscalasSolo(String ciudadSalida, String ciudadLlegada, String fechaSalida, int escalasMaximas){
        System.out.println("Próximamente disponible");
    }
    
    public void VueloMasBaratoDirecto(String ciudadSalida, String ciudadLlegada, String fechaSalida){
        String imprimir = "";
        
        for (int i = 0; i<aerolineas.length; i++){
            if (aerolineas[i]!=null){
                String barato_aerolinea = aerolineas[i].VueloDirecto(ciudadSalida, ciudadLlegada, fechaSalida);
                if (barato_aerolinea != null){
                    if (imprimir.equals("")){
                        imprimir = imprimir + barato_aerolinea;
                    }
                    else{
                        imprimir = imprimir + ";" + barato_aerolinea;
                    }
                }
            }
        }
        
        if (imprimir.equals("")){
            System.out.println("No hay vuelos disponibles. Intente cambiar su lugar de partida, su destino, o la fecha.\n");
        }
        else{
            String [] vuelos_imprimir = imprimir.split(";");
            for (int i = 0; i<vuelos_imprimir.length; i++){
                System.out.println(vuelos_imprimir[i]);
            }
        }
        
    }
    
    public boolean vueloValido(String[] vuelo) {
        return precioValidado(vuelo) && ciudadesValidas(vuelo) && validadorHorario(vuelo) && codigoValidado(vuelo) && asientosValidado(vuelo);
    }

    public boolean precioValidado(String[] vuelo) {
        String precioStr = vuelo[0];
        double precioDouble;
        boolean devolver = true;
        
        try {
            precioDouble = Double.parseDouble(precioStr);
            if (precioDouble >= 0) {
                devolver = true;
            }
        } catch (NumberFormatException e) {
            devolver =  false;
        }
        return devolver;
    }

    public boolean ciudadesValidas(String[] vuelo) {
        String ciudadSalida = vuelo[1];
        String ciudadLlegada = vuelo[2];
        
        boolean devolver = true;
        
        if (ciudadSalida.trim().length() == 3 && ciudadLlegada.trim().length() == 3) {
            ciudadSalida = ciudadSalida.trim().toUpperCase();
            ciudadLlegada = ciudadLlegada.trim().toUpperCase();
            if (!ciudadSalida.equals(ciudadLlegada)) {
                devolver = true;
            }else{
                devolver = false;
            }
        } else{
            devolver = false;
        }
        
        return devolver;
    }

    public boolean validadorHorario(String[] vuelo) {
        String horaSalida = vuelo[3];
        String horaLlegada = vuelo[4];
        String fechaSalida = vuelo[5];
        String fechaLlegada = vuelo[6];

        try {
            if (horaSalida.matches("\\d{2}:\\d{2}") && horaLlegada.matches("\\d{2}:\\d{2}") &&
                    fechaSalida.matches("\\d{2}/\\d{2}/\\d{4}") && fechaLlegada.matches("\\d{2}/\\d{2}/\\d{4}")) {

                String[] horaSalidaParts = horaSalida.split(":");
                String[] horaLlegadaParts = horaLlegada.split(":");
                String[] fechaSalidaParts = fechaSalida.split("/");
                String[] fechaLlegadaParts = fechaLlegada.split("/");

                int horaSalidaHH = Integer.parseInt(horaSalidaParts[0]);
                int horaLlegadaHH = Integer.parseInt(horaLlegadaParts[0]);
                int horaSalidaMM = Integer.parseInt(horaSalidaParts[1]);
                int horaLlegadaMM = Integer.parseInt(horaLlegadaParts[1]);

                int fechaSalidaDD = Integer.parseInt(fechaSalidaParts[0]);
                int fechaLlegadaDD = Integer.parseInt(fechaLlegadaParts[0]);
                int fechaSalidaMM = Integer.parseInt(fechaSalidaParts[1]);
                int fechaLlegadaMM = Integer.parseInt(fechaLlegadaParts[1]);
                int fechaSalidaAA = Integer.parseInt(fechaSalidaParts[2]);
                int fechaLlegadaAA = Integer.parseInt(fechaLlegadaParts[2]);

                boolean mismoDia;
                boolean diaSgte;

                if (fechaSalidaDD == fechaLlegadaDD && fechaSalidaMM == fechaLlegadaMM && fechaSalidaAA == fechaLlegadaAA) {
                    mismoDia = true;
                } else {
                    mismoDia = false;
                }

                if (fechaSalidaDD == fechaLlegadaDD - 1 && fechaSalidaMM == fechaLlegadaMM && fechaSalidaAA == fechaLlegadaAA) {
                    diaSgte = true;
                } else {
                    diaSgte = false;
                }

                if ((mismoDia && horaSalidaHH < horaLlegadaHH) || (diaSgte && horaSalidaHH > horaLlegadaHH)) {
                    return true;
                } else {
                    return false;
                }
            }
        } catch (NumberFormatException e) {
            return false;
        }
        return false;
    }

    public boolean codigoValidado(String[] vuelo) {
        String codigoVuelo = vuelo[7];
        if (codigoVuelo.matches("^[A-Z]{2}\\d{3}$")) {
            return true;
        } else {
            return false;
        }
    }

    public boolean asientosValidado(String[] vuelo) {
        String asientosStr = vuelo[8];
        try {
            int asientos = Integer.parseInt(asientosStr);
            if (asientos > 0) {
                return true;
            }
        } catch (NumberFormatException e) {
            return false;
        }
        return false;
    }

    public void annadirIgnorado(String vuelo) {
        this.ignorados = this.ignorados + "\n" + vuelo + "\n";
    }
    
    public String getIgnorados (){
        return ignorados;
    }
}
