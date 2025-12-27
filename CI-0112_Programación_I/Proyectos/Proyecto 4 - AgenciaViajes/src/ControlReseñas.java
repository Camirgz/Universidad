
// Imports
import java.io.IOException; // Catch
import java.nio.charset.StandardCharsets; // Charset
import java.nio.file.Files; // Files
import java.nio.file.Path; // Path para manejar rutas de archivos
import java.nio.file.Paths; // Paths para crear rutas de archivos
import java.nio.file.StandardOpenOption; // Opciones de apertura de archivos
import java.time.LocalDateTime; // LocalDateTime para manejar fechas y horas
import java.time.format.DateTimeFormatter; // Formateador de fechas
import java.util.ArrayList; // ArrayList para manejar listas dinamicas
import java.util.List; // List para manejar colecciones de elementos

public class ControlReseñas {

    // Atiributos
    private static final String archivoBD = "data\\Comentarios.txt";
    private static final String separador = "----------------------------------------";
    private static final String encabezado = "======== Reseñas ========";
    private static final DateTimeFormatter formatoFecha = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    // Ruta del archivo de reseñas
    private final Path archivoReseñas;

    // Constructor
    public ControlReseñas() {
        this.archivoReseñas = Paths.get(archivoBD);
    }

    // ==================== METODOS PUBLICOS ====================
    // Guarda una reseña en el archivo de reseñas.
    public boolean guardarReseña(Reseña reseña) {
        try {
            List<String> lineas = leerArchivo(); // Leer las lineas actuales del archivo
            int idReseña = obtenerSiguienteId(lineas); // Definir idReseña como el siguiente ID disponible

            agregarReseñaALineas(lineas, reseña, idReseña); // Agregar la reseña al array de lineas
            escribirArchivo(lineas); // ReEscribir las lineas actualizadas en el archivo

            System.out.println("Reseña registrada exitosamente (ID: " + idReseña + ")");
            return true;

        } catch (IOException e) {
            System.err.println("Error al guardar la reseña: " + e.getMessage());
            return false;
        }
    }

    public List<String> obtenerReseñasUsuario(String nombreUsuario) {
        try {
            List<String> lineas = leerArchivo();
            return extraerReseñasDeUsuario(lineas, nombreUsuario);
        } catch (IOException e) {
            System.err.println("Error al leer las reseñas: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public List<String> obtenerTodasLasReseñas() {
        try {
            List<String> lineas = leerArchivo();
            return extraerTodasLasReseñas(lineas);
        } catch (IOException e) {
            System.err.println("Error al leer las reseñas: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public String buscarReseñaPorId(String idResena) {
        try {
            List<String> lineas = leerArchivo();
            return extraerReseñaPorId(lineas, idResena);
        } catch (IOException e) {
            return "Error al buscar reseña: " + e.getMessage();
        }
    }

    // ==================== METODOS PRIVADOS ====================

    private List<String> leerArchivo() throws IOException {
        if (!Files.exists(archivoReseñas) || Files.size(archivoReseñas) == 0) {
            List<String> lineasNuevas = new ArrayList<>();
            lineasNuevas.add(encabezado);
            lineasNuevas.add("");
            return lineasNuevas;
        }
        return Files.readAllLines(archivoReseñas, StandardCharsets.UTF_8);
    }

    private void escribirArchivo(List<String> lineas) throws IOException {
        Files.write(archivoReseñas, lineas, StandardCharsets.UTF_8,
                StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
    }

    private int obtenerSiguienteId(List<String> lineas) {
        int maxId = 0;
        for (int i = lineas.size() - 1; i >= 0; i--) {
            String linea = lineas.get(i);
            if (linea.startsWith("ID: ")) {
                try {
                    maxId = Integer.parseInt(linea.substring(4).trim());
                    break;
                } catch (NumberFormatException e) {
                    // Continuar buscando
                }
            }
        }
        return maxId + 1;
    }

    private void agregarReseñaALineas(List<String> lineas, Reseña reseña, int id) {
        // Agregar separador si no es la primera reseña
        if (lineas.size() > 2 && !lineas.get(lineas.size() - 1).isEmpty()) {
            lineas.add("");
            lineas.add(separador);
            lineas.add("");
        }

        lineas.add("ID: " + id);
        lineas.add("Usuario: " + reseña.getUsuario());
        lineas.add("Tipo de Servicio: " + reseña.getTipoServicio());
        lineas.add("Servicio: " + reseña.getNombreServicio());
        lineas.add("Fecha: " + LocalDateTime.now().format(formatoFecha));
        lineas.add("Estrellas: " + reseña.getPuntuacion());
        lineas.add("Reseña: " + reseña.getReseña());
        lineas.add("");
    }

    private List<String> extraerReseñasDeUsuario(List<String> lineas, String nombreUsuario) {
        List<String> reseñasUsuario = new ArrayList<>();
        StringBuilder reseñaActual = new StringBuilder();
        boolean esReseñaDelUsuario = false;
        String idActual = "";

        for (String linea : lineas) {
            if (linea.startsWith("ID: ")) {
                if (esReseñaDelUsuario && reseñaActual.length() > 0) {
                    reseñasUsuario.add(reseñaActual.toString().trim());
                }
                idActual = linea.substring(4).trim();
                reseñaActual = new StringBuilder();
                esReseñaDelUsuario = false;
            } else if (linea.startsWith("Usuario: ")) {
                String usuario = linea.substring(9).trim();
                esReseñaDelUsuario = usuario.equalsIgnoreCase(nombreUsuario);
                if (esReseñaDelUsuario) {
                    reseñaActual.append("ID: ").append(idActual).append("\n");
                    reseñaActual.append(linea).append("\n");
                }
            } else if (esReseñaDelUsuario) {
                reseñaActual.append(linea).append("\n");
            }
        }

        // Agregar la ultima reseña si corresponde
        if (esReseñaDelUsuario && reseñaActual.length() > 0) {
            reseñasUsuario.add(reseñaActual.toString().trim());
        }

        if (reseñasUsuario.isEmpty()) {
            System.out.println("No se encontraron reseñas para el usuario: " + nombreUsuario);
        }

        return reseñasUsuario;
    }

    private List<String> extraerTodasLasReseñas(List<String> lineas) {
        List<String> todasLasReseñas = new ArrayList<>();
        StringBuilder reseñaActual = new StringBuilder();
        boolean enReseña = false;

        for (String linea : lineas) {
            if (linea.startsWith("ID: ")) {
                if (enReseña && reseñaActual.length() > 0) {
                    todasLasReseñas.add(reseñaActual.toString().trim());
                }
                reseñaActual = new StringBuilder();
                enReseña = true;
            }

            if (enReseña) {
                reseñaActual.append(linea).append("\n");

                if (linea.trim().isEmpty() || linea.equals(separador)) {
                    todasLasReseñas.add(reseñaActual.toString().trim());
                    reseñaActual = new StringBuilder();
                    enReseña = false;
                }
            }
        }

        // Agregar la ultima reseña si el archivo no termina con separador
        if (enReseña && reseñaActual.length() > 0) {
            todasLasReseñas.add(reseñaActual.toString().trim());
        }

        if (todasLasReseñas.isEmpty()) {
            System.out.println("No se encontraron reseñas en la base de datos.");
        }

        return todasLasReseñas;
    }

    private String extraerReseñaPorId(List<String> lineas, String idResena) {
        StringBuilder reseñaEncontrada = new StringBuilder();
        boolean encontrada = false;
        boolean enReseña = false;

        for (String linea : lineas) {
            if (linea.startsWith("ID: " + idResena)) {
                encontrada = true;
                enReseña = true;
                reseñaEncontrada.append(linea).append("\n");
                continue;
            }

            if (enReseña) {
                if (linea.startsWith("ID: ")) {
                    break; // Nueva reseña encontrada
                }
                reseñaEncontrada.append(linea).append("\n");

                if (linea.trim().isEmpty() || linea.equals(separador)) {
                    break; // Fin de la reseña actual
                }
            }
        }

        return encontrada ? reseñaEncontrada.toString().trim() : "No se encontro reseña con ID: " + idResena;
    }
}