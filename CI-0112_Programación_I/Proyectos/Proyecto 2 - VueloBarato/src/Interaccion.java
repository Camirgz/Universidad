import java.util.Scanner;
import java.io.File;
import javax.swing.JFileChooser;
import java.util.InputMismatchException;

public class Interaccion {
    public static void Interaccion() {
        System.out.println("=== Bienvenid@ al sistema de búsqueda de vuelos baratos ===\n");
        System.out.println("Seleccione una carpeta con los vuelos de cada aerolínea\n");

        // Crear un objeto JFileChooser para que el usuario seleccione una carpeta
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        int returnValue = fileChooser.showOpenDialog(null);
        boolean continuar = true;

        if (returnValue == JFileChooser.APPROVE_OPTION) {
                File selectedFolder = fileChooser.getSelectedFile();
                String carpeta = selectedFolder.getAbsolutePath();

                Busqueda correr = new Busqueda();

                correr.CargarInformacion(carpeta);
                System.out.println("Se ha cargado la información\n");
                
                
                boolean busqueda = true;
                
                while (busqueda == true) {
                    System.out.println("==== Inicio de Búsqueda ====");

                    Scanner in = new Scanner(System.in);
                    
                    System.out.println("Ingrese la ciudad de salida: ");
                    String ciudadSalida = ciudadSalida();

                    System.out.println("Ingrese la ciudad de llegada: ");
                    String ciudadLlegada = ciudadLlegada();
                    
                    System.out.println("Ingrese la fecha de inicio (DD-MM-AAAA): ");
                    String fecha = fecha();
                        
                    System.out.println("Cuántas escalas permite como máximo: ");
                    int cant_escalas = cantidadEscalas();

                    if (cant_escalas == 0) {
                        correr.VueloMasBaratoDirecto(ciudadSalida, ciudadLlegada, fecha);
                    } else {
                        System.out.println("Permite cruce de aerolíneas? (S/N): ");
                        char permite = PreguntarSioNo();

                        if (permite == 'N') {
                            correr.VueloMasBaratoEscalasSolo(ciudadSalida, ciudadLlegada, fecha, cant_escalas);
                        }

                        else{
                            correr.VueloMasBaratoEscalasAerolineas(ciudadSalida, ciudadLlegada, fecha, cant_escalas);
                        }
                    }
                    
                    System.out.println("¿Desea hacer otra búsqueda? (S/N): ");

                    char respuesta = PreguntarSioNo();
                    
                    if (respuesta == 'N'){
                        busqueda = false;
                        break;
                    } else{
                        busqueda = true;
                    }
                }

                System.out.println("Se ignoraron los siguientes vuelos:  \n" + correr.getIgnorados());

                continuar = false;
            } else {
                System.out.println("Por favor, seleccione una carpeta.");
                Interaccion();
            }
        }
        
    public static int cantidadEscalas(){
        Scanner in = new Scanner (System.in);
        boolean continuar = true;
        String entrada = "";
        int cantidadEscalas = 0;
        int validaciones =0;
        
        while (continuar){
            validaciones = 0;
            entrada = in.nextLine();
            
            try{
                cantidadEscalas = Integer.parseInt(entrada);
                if (cantidadEscalas<0){
                    validaciones++;
                }
            } catch (NumberFormatException e){
                validaciones++;
            } catch (InputMismatchException error){
                validaciones++;
            }
            
            if (validaciones!=0){
                System.out.println("Ingrese un número válido");
                continuar = true;
            } else{
                break;
            }
        }
        return cantidadEscalas;
    }
        
    public static String ciudadSalida(){
        Scanner in = new Scanner (System.in);
        boolean continuar = true;
        String ciudadSalida = "";
        int validaciones = 0;
        
        while (continuar == true){
            validaciones = 0;
            ciudadSalida = in.nextLine().trim().toUpperCase();
            if (ciudadSalida.equals("")){
                validaciones++;
            }
            
            if (ciudadSalida.length()>3 || ciudadSalida.length()<3){
                validaciones++;
            }
            
            if (validaciones !=0){
                continuar = true;
                System.out.println("Ingrese una entrada válida");
            }
            else{
                break;
            }
        }
        return ciudadSalida;
    }
    
    public static String ciudadLlegada(){
        Scanner in = new Scanner (System.in);
        boolean continuar = true;
        String ciudadLlegada = "";
        int validaciones = 0;
        
        while (continuar == true){
            validaciones = 0;
            ciudadLlegada = in.nextLine().trim().toUpperCase();
            if (ciudadLlegada.equals("")){
                validaciones++;
            }
            
            if (ciudadLlegada.length()>3 || ciudadLlegada.length()<3){
                validaciones++;
            }
            
            if (validaciones !=0){
                continuar = true;
                System.out.println("Ingrese una entrada válida");
            }
            else{
                break;
            }
        }
        return ciudadLlegada;
    }
    
    public static String fecha(){
        Scanner in = new Scanner (System.in);
        boolean continuar = true;
        String fecha = "";
        int validaciones = 0;
        
        while (continuar == true){
            validaciones = 0;
            fecha = in.nextLine().trim().toUpperCase();
            
            if (fecha.length()!=10){
                validaciones++;
            }
            else{
                
                if (fecha.charAt(2) != ('/') && fecha.charAt(5) != ('/')) {
                    validaciones++;
                }
                
                if (fecha.equals("")){
                    validaciones++;
                }
                
                try {
                    int dia = Integer.parseInt(fecha.substring(0,2));
                    int mes = Integer.parseInt(fecha.substring(3,5));
                    int year = Integer.parseInt(fecha.substring(6,9));
                    
                    if (dia<0 || dia>31){
                        validaciones++;
                    }
                    if (mes<0 || mes>12){
                        validaciones++;
                    }
                    if (year<0){
                        validaciones++;
                    }
                    
                } catch (InputMismatchException error){
                    validaciones++;
                } catch (IndexOutOfBoundsException e){
                    validaciones++;
                } catch (NumberFormatException err){
                    validaciones++;
                }
            }
            
            if (validaciones != 0 ){
                System.out.println("Ingrese una entrada válida");
                continuar = true;
            }
            else {
                continuar = false;
                break;
            }
        }
        
        return fecha;
    }
    
    public static char PreguntarSioNo(){
        Scanner in = new Scanner (System.in);
        boolean continuar = true;
        char respuesta = '\0';
        int validaciones = 0;
    
        while (continuar == true){
            String entrada = in.nextLine();
            if (entrada.length()<0 || entrada.length()>1){
                validaciones++;
            } else{
                if (entrada.equalsIgnoreCase("S")){
                    respuesta = 'S';
                }
                else if (entrada.equalsIgnoreCase("N")){
                    respuesta = 'N';
                }
                else{
                    validaciones++;
                }
            }
            
            if (validaciones !=0){
                System.out.println("Ingrese una entrada válida");
                continuar = true;
            }
            
            else{
                continuar = false;
                break;
            }
        }
        return respuesta;
    }
        
    }
