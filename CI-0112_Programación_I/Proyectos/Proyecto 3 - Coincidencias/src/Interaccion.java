import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Interaccion{
    
    Lista sospechosos = new Lista();
    Lista historial = new Lista();
    
    public void interaccion(){
        System.out.println("=== Bienvenido al sistema de sospechosos del OIJ ===");
        CargarArchivos();
        MenuPrincipal();
    }
    
    public void CargarArchivos() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Seleccione un archivo CSV");
        fileChooser.setFileFilter(new FileNameExtensionFilter("Archivos CSV (*.csv)", "csv"));

        int userSelection = fileChooser.showOpenDialog(null);

        if (userSelection == JFileChooser.APPROVE_OPTION) {
            String csvFile = fileChooser.getSelectedFile().getAbsolutePath();
            
            try {
                BufferedReader br = new BufferedReader(new FileReader(csvFile));
                String line;

                while ((line = br.readLine()) != null) {
                    String[] datos = line.split(",");
                    
                    if (validaciones(datos)) {
                        sospechosos.agregar(datos);
                    }
                }

                System.out.println("El archivo fue validado");
            } catch (IOException e) {
                System.out.println("Error tipo: " + e.getMessage());
                System.out.println("Intente de nuevo");
                CargarArchivos(); // Vuelve a llamar a la función en caso de error
            }
        } else {
            System.out.println("Operación cancelada por el usuario");
        }
    }
    
    public String[] PedirEntradas(){
        Scanner scanner = new Scanner (System.in);
        
        System.out.println("\nIngrese los datos del sospechoso/a por buscar");
        
        String nombre;
        String provincia;
        String canton;
        String edad;
        String genero;
        String estadoCivil;
        String colorPelo;
        String altura;

        while(true){
            System.out.println("Ingrese nombre por buscar: ");
            nombre = scanner.nextLine();
            if(strings(nombre)){
                break;
            }
        }

        while(true){
            System.out.println("Ingrese provincia por buscar: ");
            provincia = scanner.nextLine();
            if (strings(provincia)) {
                break;
            }
        }

        while(true){
            System.out.println("Ingrese canton por buscar: ");
            canton = scanner.nextLine();
            if (strings(canton)) {
                break;
            }
        }

        while(true){
            System.out.println("Ingrese edad por buscar (18-100): ");
            edad = scanner.nextLine();
            if(edad(edad)){
                break;
            }
        }

        while(true){
            System.out.println("Ingrese genero por buscar (Masculino, femenino, otro): ");
            genero = scanner.nextLine();
            if(genero(genero)){
                break;
            }
        }
        
        while(true){
            System.out.println("Ingrese el estado civil (Casad@, solter@, viud@ o divorciad@): ");
            estadoCivil = scanner.nextLine();
            if (estadoCivil(estadoCivil)){
                break;
            }
        }

        while(true){
            System.out.println("Ingrese color de pelo por buscar (Negr@, moren@, castann@ y rubi@): ");
            colorPelo = scanner.nextLine();
            if (pelo(colorPelo)) {
                break;
            }
        }

        while(true){
            System.out.println("Ingrese altura por buscar (100-200): ");
            altura = scanner.nextLine();
            if(altura(altura)){
                break;
            }
        }
        
        String [] entradas = {nombre, provincia, canton, edad, genero, estadoCivil, colorPelo, altura};
        return entradas;
    }
    
    public void MenuPrincipal (){
        Scanner scanner = new Scanner (System.in);
        int cantidad_busquedas = 0;
        
        while(true){
            System.out.println("\n== MENU PRINCIPAL ==");
            System.out.println("Ingrese [S] para salir, [B] para buscar o [H] para ver el historial");
            String entrada = scanner.nextLine();
            if(input(entrada)){
                if(entrada.equalsIgnoreCase("B")){
                    String [] entradas = PedirEntradas();
                    cantidad_busquedas++;
                    String print = "" + entradas[0] + ", " + entradas[1] + ", " + entradas[2] + ", " + entradas[3] + ", " + entradas[4] + ", " + entradas[5] + ", " + entradas[6] + ", " + entradas[7];
                    print = print.toUpperCase();
                    System.out.println("\n== RESULTADOS DE MEJOR A PEOR COINCIDENCIA ==");
                    historial.agregarHistorial(sospechosos.Busqueda(entradas, sospechosos), print, cantidad_busquedas);
                    //metodo para hacer el arbol binario a partir del sistema de puntos.
                    System.out.println("-Fin------------------------------------------");
                    
                    if (historial.buscarNodo(cantidad_busquedas).getBusqueda().getContadorTemporal()>0){
                        
                        while(true){
                            String accion;
                            while(true){
                                System.out.println("\nIngrese T para terminar la búsqueda, o M si desea eliminar una sospecha: ");
                                accion = scanner.nextLine();
                                if (accion(accion)){
                                    break;
                                }
                            }
                            
                            if (accion.equalsIgnoreCase("T")){
                                break;
                            }
                            
                            String nodo;
                            while(true){
                                System.out.println("¿Cuál sospecha desea eliminar?: ");
                                nodo = scanner.nextLine();
                                if (numero_busqueda(nodo, historial.buscarNodo(cantidad_busquedas).getBusqueda().getContadorTemporal())){
                                    break;
                                }
                            }
                    
                            historial.buscarNodo(cantidad_busquedas).getBusqueda().eliminar(Integer.parseInt(nodo));

                            System.out.println("\n== RESULTADOS DE MEJOR A PEOR COINCIDENCIA ==");
                            historial.buscarNodo(cantidad_busquedas).getBusqueda().imprimir();
                            System.out.println("-Fin------------------------------------------");
                        
                        }
                    }
                }
                if (entrada.equalsIgnoreCase("H")){
                    if (cantidad_busquedas==1){
                        System.out.println("\nSe ha realizado 1 búsqueda");
                    } else{
                        System.out.println("\nSe han realizado " + cantidad_busquedas + " búsquedas");
                    }
                    historial.imprimirBusqueda();
                    //metodo para mostrar la lista de historial.
                    if (cantidad_busquedas>0){
                        String numero_busqueda;
                        while (true){
                            System.out.println("\nIngrese el numero de búsqueda para ver los resultados arrojados: ");
                            numero_busqueda = scanner.nextLine();
                            if (numero_busqueda(numero_busqueda, cantidad_busquedas)){
                                break;
                            }
                        }
                        System.out.println("\n== RESULTADOS DE MEJOR A PEOR COINCIDENCIA ==");
                        historial.imprimirHistorial(Integer.parseInt(numero_busqueda));
                        System.out.println("-Fin------------------------------------------");
                    }
                }
                if (entrada.equalsIgnoreCase("S")){
                    System.out.println("\n== FIN DEL PROGRAMA ==");
                    break;
                }
            }
        }
    }
    
    public boolean strings(String nombre) {
        for (char caracter : nombre.toCharArray()) {
            if (Character.isDigit(caracter)) {
                return false;
            }
        }
        return true;
    }
    
    public boolean accion(String accion){
        if (accion.length()>1 || accion.length()<1){
            return false;
        } else{
            if (accion.equalsIgnoreCase("T")){
                return true;
            } else if (accion.equalsIgnoreCase("M")){
                return true;
            } else{
                return false;
            }
        }
    }
    
    public boolean numero_busqueda(String numero, int cantidad_busquedas){
        try{
            int numero_busqueda = Integer.parseInt(numero);
            if (numero_busqueda>0 && numero_busqueda<=cantidad_busquedas){
                return true;
            }
            return false;
        } catch (NumberFormatException e){
            return false;
        }
    }

    public boolean edad(String edadStr) {
        try{
            int edad = Integer.parseInt(edadStr);
            if (edad >= 18 && edad <= 100) {
                return true;
            }
            return false;
        } catch (NumberFormatException e){
            return false;
        }
    }

    public boolean genero(String genero) {
        genero = genero.toLowerCase();
        genero = genero.trim();
        if (genero.equals("masculino")) {
            return true;
        } else if (genero.equals("femenino")) {
            return true;
        } else if (genero.equals("otro")) {
            return true;
        }
        return false;
    }

    public boolean estadoCivil(String estadoCivil) {
        estadoCivil = estadoCivil.toLowerCase();
        estadoCivil = estadoCivil.trim();
        if (estadoCivil.equals("casado")||estadoCivil.equals("casada")) {
            return true;
        } else if (estadoCivil.equals("soltero")||estadoCivil.equals("soltera")) {
            return true;
        } else if (estadoCivil.equals("viudo")|| estadoCivil.equals("viuda")) {
            return true;
        } else if (estadoCivil.equals("divorciado") || estadoCivil.equals("divorciada")) {
            return true;
        }
        return false;
    }

    public boolean pelo(String pelo) {
        pelo = pelo.toLowerCase();
        pelo = pelo.trim();
        if (pelo.equals("negro") || pelo.equals("negra")) {
            return true;
        } else if (pelo.equals("moreno") || pelo.equals("morena")) {
            return true;
        } else if (pelo.equals("castanno") || pelo.equals("castanna")) {
            return true;
        } else if (pelo.equals("rubio") || pelo.equals("rubia")) {
            return true;
        }
        return false;
    }

    public boolean altura(String alturaStr) {
        int altura = Integer.parseInt(alturaStr);
        if (altura >= 100 && altura <= 200) {
            return true;
        }
        return false;
    }

    public boolean input(String input){
        if (input.equalsIgnoreCase("S")||input.equalsIgnoreCase("B")||input.equalsIgnoreCase("H")){
            return true;
        }
        return false;
    }

    public boolean validaciones(String[] array) {
        try {
            //Validaciones
            int contador = 0;
            if (array.length != 8) {
                contador++;
            }
            if (!strings(array[0])) {
                contador++;
            }
            if (!strings(array[1])) {
                contador++;
            }
            if (!strings(array[2])) {
                contador++;
            }
            if (!edad(array[3])) {
                contador++;
            }
            if (!genero(array[4])) {
                contador++;
            }
            if (!estadoCivil(array[5])) {
                contador++;
            }
            if (!pelo(array[6])) {
                contador++;
            }
            if (!altura(array[7])) {
                contador++;
            }
            //Return
            if (contador == 0) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            return false;
        }
    }
}
