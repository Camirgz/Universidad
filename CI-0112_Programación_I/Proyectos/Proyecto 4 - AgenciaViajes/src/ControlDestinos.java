import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.NumberFormat;
import java.text.ParseException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class ControlDestinos {

    private static final String archivoDisponibles = "data\\Destinos.txt";
    private static final String archivoUsuarios = "data\\Usuarios.txt";
    public static final DateTimeFormatter formatoFecha = DateTimeFormatter.ofPattern("[dd/MM/yyyy][dd-MM-yyyy]");

    // Metodo para parsear numeros con coma decimal
    private double parseMonto(String montoStr) {
        try {
            NumberFormat format = NumberFormat.getInstance(Locale.getDefault());
            return format.parse(montoStr).doubleValue();
        } catch (ParseException e) {
            try {
                return Double.parseDouble(montoStr.replace(',', '.'));
            } catch (NumberFormatException ex) {
                return 0.0;
            }
        }
    }

    // Metodo para formatear numeros al guardar
    private String formatMonto(double monto) {
        return String.format(Locale.US, "%.2f", monto);
    }

    public LocalDate parseFecha(String fechaStr) throws DateTimeParseException {
        fechaStr = fechaStr.trim();
        if (fechaStr.contains("-")) {
            fechaStr = fechaStr.replace("-", "/");
        }
        return LocalDate.parse(fechaStr, formatoFecha);
    }

    // ==================== METODOS PARA DESTINOS DISPONIBLES ====================

    public boolean agregarDestinoDisponible(BufferedWriter escritor, String origen, String pais, String ciudad,
            double monto) {
        String nuevaLinea = String.format(Locale.US, "%s -> %s;%s;%.2f", origen, pais, ciudad, monto);
        File archivo = new File(archivoDisponibles);

        try {
            // Si el archivo existe, verificamos si la linea ya esta
            if (archivo.exists()) {
                try (BufferedReader reader = new BufferedReader(new FileReader(archivo))) {
                    String linea;
                    while ((linea = reader.readLine()) != null) {
                        if (linea.equals(nuevaLinea)) {
                            return false; // Ya existe
                        }
                    }
                }
            }

            // Escribimos al final (append = true)
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(archivo, true))) {
                writer.write(nuevaLinea);
                writer.newLine();
            }

            return true;

        } catch (IOException e) {
            System.err.println("Error al agregar destino disponible: " + e.getMessage());
            return false;
        }
    }

    public List<String> listarDestinosDisponibles() {
        List<String> resultados = new ArrayList<>();
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoDisponibles));

            for (int i = 0; i < lineas.size(); i++) {
                String linea = lineas.get(i).trim();

                if (linea.isEmpty()) {
                    continue;
                }

                try {
                    String[] partes = linea.split(" -> ");
                    if (partes.length != 2)
                        continue;

                    String[] destinoPartes = partes[1].split(";");
                    if (destinoPartes.length != 3)
                        continue;

                    String pais = destinoPartes[0].trim();
                    String ciudad = destinoPartes[1].trim();
                    String montoStr = destinoPartes[2].trim().replace(',', '.');

                    try {
                        double monto = Double.parseDouble(montoStr);
                        resultados.add(String.format("%d. Pais: %s, Ciudad: %s, Monto: %.2f",
                                i + 1, pais, ciudad, monto));
                    } catch (NumberFormatException e) {
                        System.err.println("Monto invalido en linea " + (i + 1));
                    }
                } catch (Exception e) {
                    System.err.println("Error procesando linea " + (i + 1));
                }
            }
        } catch (IOException e) {
            resultados.add("Error al leer archivo de destinos");
        }

        return resultados.isEmpty() ? List.of("No hay destinos disponibles") : resultados;
    }

    public String buscarDestinoPorId(int id) {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoDisponibles));
            if (id >= 1 && id <= lineas.size()) {
                String[] partes = lineas.get(id - 1).split(" -> ")[1].split(";");
                String montoStr = partes[2].replace(',', '.');
                return String.format("Pais: %s, Ciudad: %s, Monto: %s",
                        partes[0], partes[1], montoStr);
            }
            return "ID no valido";
        } catch (Exception e) {
            return "Error al buscar destino";
        }
    }

    private boolean existeDestinoDisponible(String pais, String ciudad, double monto) {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoDisponibles));
            for (String linea : lineas) {
                String[] partes = linea.split(" -> ")[1].split(";");
                String montoStr = partes[2].replace(',', '.');
                if (partes[0].equals(pais) && partes[1].equals(ciudad) &&
                        Double.parseDouble(montoStr) == monto) {
                    return true;
                }
            }
            return false;
        } catch (IOException e) {
            return false;
        }
    }

    // ==================== METODOS PARA DESTINOS DE USUARIO ====================

    /**
     * Guarda un destino de usuario usando el objeto Destinos
     */
    public boolean guardarDestino(Destinos destino) {
        if (destino == null || destino.getUsuario() == null) {
            System.err.println("Error: Destino o usuario no valido");
            return false;
        }

        try {
            // Convertir el costo de String a double
            double monto = Double.parseDouble(destino.getCosto().replace(',', '.'));

            // Parsear la fecha (asumiendo que viene en formato dd/MM/yyyy o dd-MM-yyyy)
            LocalDate fecha = parseFecha(destino.getfecha());

            // Verificar si existe el destino disponible
            if (!existeDestinoDisponible(destino.getPais(), destino.getCiudad(), monto)) {
                System.err.println("Error: El destino no esta disponible");
                return false;
            }

            List<String> lineas = Files.exists(Paths.get(archivoUsuarios))
                    ? Files.readAllLines(Paths.get(archivoUsuarios))
                    : new ArrayList<>();

            // Calcular el proximo ID
            int proximoId = obtenerProximoId(lineas);

            // Formato: id;usuario;pais;ciudad;monto;fecha
            String nuevaLinea = String.format("%d;%s;%s;%s;%s;%s",
                    proximoId,
                    destino.getUsuario().getNombre(),
                    destino.getPais(),
                    destino.getCiudad(),
                    formatMonto(monto),
                    fecha.format(DateTimeFormatter.ofPattern("dd/MM/yyyy")));

            // Verificar si ya existe este destino para el usuario
            if (existeDestinoParaUsuario(lineas, destino.getUsuario().getNombre(),
                    destino.getPais(), destino.getCiudad())) {
                System.err.println("Error: El usuario ya tiene este destino registrado");
                return false;
            }

            lineas.add(nuevaLinea);
            Files.write(Paths.get(archivoUsuarios), lineas);
            return true;

        } catch (IOException e) {
            System.err.println("Error al guardar destino: " + e.getMessage());
            return false;
        } catch (NumberFormatException e) {
            System.err.println("Error: Costo invalido");
            return false;
        } catch (DateTimeParseException e) {
            System.err.println("Error: Fecha invalida");
            return false;
        }
    }

    /**
     * Metodo alternativo que mantiene compatibilidad con fechas de inicio y fin
     */
    public boolean agregarDestinoUsuario(String usuario, String pais, String ciudad, double monto,
            LocalDate fechaInicio, LocalDate fechaFin) {
        try {
            if (!existeDestinoDisponible(pais, ciudad, monto)) {
                return false;
            }

            List<String> lineas = Files.exists(Paths.get(archivoUsuarios))
                    ? Files.readAllLines(Paths.get(archivoUsuarios))
                    : new ArrayList<>();

            int proximoId = obtenerProximoId(lineas);

            // Formato con fechas de inicio y fin:
            // id;usuario;pais;ciudad;monto;fechaInicio;fechaFin
            String nuevaLinea = String.format("%d;%s;%s;%s;%s;%s;%s",
                    proximoId,
                    usuario,
                    pais,
                    ciudad,
                    formatMonto(monto),
                    fechaInicio.format(DateTimeFormatter.ofPattern("dd/MM/yyyy")),
                    fechaFin.format(DateTimeFormatter.ofPattern("dd/MM/yyyy")));

            if (existeDestinoParaUsuario(lineas, usuario, pais, ciudad)) {
                return false;
            }

            lineas.add(nuevaLinea);
            Files.write(Paths.get(archivoUsuarios), lineas);
            return true;
        } catch (IOException e) {
            System.err.println("Error al agregar destino a usuario: " + e.getMessage());
            return false;
        }
    }

    public List<String> listarDestinosUsuario(String usuario) {
        List<String> resultados = new ArrayList<>();
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoUsuarios));
            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length >= 6 && partes[1].equals(usuario)) {
                    double monto = parseMonto(partes[4]);

                    if (partes.length == 6) {
                        // Formato con una sola fecha
                        resultados.add(String.format(
                                "ID: %s - Pais: %s, Ciudad: %s, Monto: %.2f, Fecha: %s",
                                partes[0], partes[2], partes[3], monto, partes[5]));
                    } else if (partes.length == 7) {
                        // Formato con fechas de inicio y fin
                        resultados.add(String.format(
                                "ID: %s - Pais: %s, Ciudad: %s, Monto: %.2f, Fechas: %s a %s",
                                partes[0], partes[2], partes[3], monto, partes[5], partes[6]));
                    }
                }
            }
        } catch (IOException e) {
            resultados.add("Error al leer archivo");
        }
        return resultados;
    }

    public List<Destinos> obtenerDestinosUsuario(String usuario) {
        List<Destinos> destinos = new ArrayList<>();
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoUsuarios));
            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length >= 6 && partes[1].equals(usuario)) {
                    Destinos destino = new Destinos();
                    destino.setPais(partes[2]);
                    destino.setCiudad(partes[3]);
                    destino.setcosto(partes[4]);
                    destino.setfecha(partes[5]);
                    destinos.add(destino);
                }
            }
        } catch (IOException e) {
            System.err.println("Error al obtener destinos del usuario: " + e.getMessage());
        }
        return destinos;
    }

    public boolean eliminarDestinoUsuario(String usuario, int idDestino) {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoUsuarios));
            List<String> nuevasLineas = new ArrayList<>();
            boolean eliminado = false;

            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length >= 6 &&
                        partes[1].equals(usuario) &&
                        Integer.parseInt(partes[0]) == idDestino) {
                    eliminado = true;
                } else {
                    nuevasLineas.add(linea);
                }
            }

            if (eliminado) {
                Files.write(Paths.get(archivoUsuarios), nuevasLineas);
                return true;
            }
            return false;
        } catch (IOException e) {
            System.err.println("Error al eliminar destino: " + e.getMessage());
            return false;
        } catch (NumberFormatException e) {
            System.err.println("Error al procesar ID: " + e.getMessage());
            return false;
        }
    }

    // ==================== METODOS AUXILIARES PRIVADOS ====================

    private int obtenerProximoId(List<String> lineas) {
        int maxId = 0;
        for (String linea : lineas) {
            try {
                String[] partes = linea.split(";");
                if (partes.length > 0) {
                    int id = Integer.parseInt(partes[0]);
                    maxId = Math.max(maxId, id);
                }
            } catch (NumberFormatException e) {
                // Ignorar lineas con formato incorrecto
            }
        }
        return maxId + 1;
    }

    private boolean existeDestinoParaUsuario(List<String> lineas, String usuario, String pais, String ciudad) {
        for (String linea : lineas) {
            String[] partes = linea.split(";");
            if (partes.length >= 6 &&
                    partes[1].equals(usuario) &&
                    partes[2].equals(pais) &&
                    partes[3].equals(ciudad)) {
                return true;
            }
        }
        return false;
    }

    // ==================== INICIALIZACION ====================

    public void inicializarDestinosDisponibles() {
        // Verificar si el archivo ya existe y tiene contenido REAL
        try (BufferedReader lector = new BufferedReader(new FileReader(archivoDisponibles))) {
            long lineasConContenido = lector.lines()
                    .filter(linea -> linea != null && !linea.trim().isEmpty())
                    .count();

            if (lineasConContenido > 0) {
                // Si el archivo ya tiene contenido, no hacemos nada
                return;
            } else {
                System.out.println("El archivo existe pero esta vacio. Procediendo con la inicializacion...");
            }
        } catch (FileNotFoundException e) {
            System.out.println("El archivo no existe. Creando y inicializando...");
        } catch (IOException e) {
            System.err.println("Error al verificar archivo existente: " + e.getMessage());
            System.out.println("Procediendo con la inicializacion de todas formas...");
        }

        // Inicializacion
        System.out.println("Inicializando destinos disponibles...");
        System.out.println("Ruta del archivo: " + Paths.get(archivoDisponibles).toAbsolutePath());

        int destinosAgregados = 0;

        // Usar BufferedWriter en modo append = true
        try (BufferedWriter escritor = new BufferedWriter(new FileWriter(archivoDisponibles, true))) {
            // Destinos principales
            if (agregarDestinoDisponible(escritor, "Principal", "Francia", "Paris", 1200.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Italia", "Roma", 1100.50))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Espanna", "Madrid", 950.75))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Japon", "Tokio", 2500.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "EEUU", "Nueva York", 1500.25))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Australia", "Sidney", 3000.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Brasil", "Rio de Janeiro", 800.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Canada", "Toronto", 1700.50))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Alemania", "Berlin", 1300.75))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Reino Unido", "Londres", 1400.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Portugal", "Lisboa", 900.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Grecia", "Atenas", 1000.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Holanda", "Amsterdam", 1250.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Suiza", "Zurich", 1800.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Argentina", "Buenos Aires", 750.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Mexico", "Ciudad de Mexico", 850.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "China", "Pekin", 2200.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Corea del Sur", "Seul", 2300.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Tailandia", "Bangkok", 1600.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "India", "Nueva Delhi", 1900.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Sudafrica", "Ciudad del Cabo", 2000.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Egipto", "El Cairo", 1100.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Marruecos", "Marrakech", 1050.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Turquia", "Estambul", 1150.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Peru", "Lima", 700.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Chile", "Santiago", 850.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Colombia", "Bogota", 650.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Nueva Zelanda", "Auckland", 2800.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Noruega", "Oslo", 2100.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Principal", "Suecia", "Estocolmo", 1950.00))
                destinosAgregados++;

            // Conexiones entre destinos
            if (agregarDestinoDisponible(escritor, "Paris", "Francia", "Lyon", 200.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Madrid", "Espanna", "Barcelona", 150.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Roma", "Italia", "Venecia", 180.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Berlin", "Alemania", "Munich", 120.00))
                destinosAgregados++;
            if (agregarDestinoDisponible(escritor, "Londres", "Reino Unido", "Edimburgo", 250.00))
                destinosAgregados++;
        } catch (IOException e) {
            System.err.println("Error al escribir los destinos: " + e.getMessage());
            return;
        }

        System.out.println("\nProceso de inicializacion completado. Destinos agregados: " + destinosAgregados);

    }

    // Agregar nuevos metodos
    public String obtenerNombreDestino(int id) {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoDisponibles));
            if (id > 0 && id <= lineas.size()) {
                String[] partes = lineas.get(id - 1).split(" -> ")[1].split(";");
                return partes[0] + ", " + partes[1];
            }
        } catch (Exception e) {
            // Manejar error
        }
        return "Destino Desconocido";
    }

    public double obtenerPrecioDestino(int id) {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(archivoDisponibles));
            if (id > 0 && id <= lineas.size()) {
                String[] partes = lineas.get(id - 1).split(" -> ")[1].split(";");
                return Double.parseDouble(partes[2]);
            }
        } catch (Exception e) {
            // Manejar error
        }
        return 0.0;
    }

}