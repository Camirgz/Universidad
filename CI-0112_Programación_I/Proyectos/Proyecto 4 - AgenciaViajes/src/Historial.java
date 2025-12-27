import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Historial {
    private static Historial instancia;
    private static final String ARCHIVO_HISTORIAL = "data/Historial.txt";
    private static final DateTimeFormatter FORMATO_FECHA = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");
    private final Path rutaArchivo;

    private Historial() {
        this.rutaArchivo = Paths.get(ARCHIVO_HISTORIAL);
        inicializarArchivo();
    }

    public static Historial getInstancia() {
        if (instancia == null) {
            instancia = new Historial();
        }
        return instancia;
    }

    /**
     * Registra una accion realizada por un usuario
     */
    public boolean registrarAccion(Usuario usuario, String accion) {
        if (usuario == null || usuario.getNombre() == null || usuario.getNombre().trim().isEmpty()) {
            System.err.println("Error: Usuario no valido para registrar accion");
            return false;
        }

        if (accion == null || accion.trim().isEmpty()) {
            System.err.println("Error: Accion no valida");
            return false;
        }

        try {
            String fechaHora = LocalDateTime.now().format(FORMATO_FECHA);
            String lineaRegistro = String.format("Usuario:%s | Fecha:%s | Accion:%s", 
                                                usuario.getNombre(), fechaHora, accion);

            escribirEnArchivo(lineaRegistro);
            return true;

        } catch (Exception e) {
            System.err.println("Error al registrar accion: " + e.getMessage());
            return false;
        }
    }

    /**
     * Obtiene el historial completo de un usuario
     */
    public String obtenerHistorialCompleto(Usuario usuario) {
        if (usuario == null || usuario.getNombre() == null || usuario.getNombre().trim().isEmpty()) {
            return "Error: Usuario no valido";
        }

        try {
            File archivo = rutaArchivo.toFile();
            if (!archivo.exists() || archivo.length() == 0) {
                return "El usuario " + usuario.getNombre() + " no tiene historial registrado.";
            }

            List<String> lineas = leerArchivo();
            String nombreUsuario = usuario.getNombre();
            
            List<String> accionesUsuario = lineas.stream()
                    .filter(linea -> linea != null && !linea.trim().isEmpty())
                    .filter(linea -> linea.startsWith("Usuario:" + nombreUsuario + " |"))
                    .collect(Collectors.toList());

            if (accionesUsuario.isEmpty()) {
                return "El usuario " + nombreUsuario + " no tiene historial registrado.";
            }

            StringBuilder historial = new StringBuilder();
            historial.append("=== HISTORIAL DE ").append(nombreUsuario.toUpperCase()).append(" ===\n\n");

            for (String linea : accionesUsuario) {
                String lineaFormateada = formatearLinea(linea);
                historial.append(lineaFormateada).append("\n");
            }

            return historial.toString();

        } catch (Exception e) {
            return "Error al leer el historial: " + e.getMessage();
        }
    }

    /**
     * Busca historial por fecha especifica
     */
    public String buscarHistorialPorFecha(Usuario usuario, String fechaBusqueda) {
        if (usuario == null || usuario.getNombre() == null || usuario.getNombre().trim().isEmpty()) {
            return "Error: Usuario no valido";
        }

        if (fechaBusqueda == null || fechaBusqueda.trim().isEmpty()) {
            return "Error: Fecha de busqueda no valida";
        }

        try {
            File archivo = rutaArchivo.toFile();
            if (!archivo.exists() || archivo.length() == 0) {
                return "El usuario " + usuario.getNombre() + " no tiene historial registrado.";
            }

            List<String> lineas = leerArchivo();
            String nombreUsuario = usuario.getNombre();
            
            List<String> accionesFecha = lineas.stream()
                    .filter(linea -> linea != null && !linea.trim().isEmpty())
                    .filter(linea -> linea.startsWith("Usuario:" + nombreUsuario + " |"))
                    .filter(linea -> linea.contains(fechaBusqueda))
                    .collect(Collectors.toList());

            if (accionesFecha.isEmpty()) {
                return "No se encontraron acciones para " + nombreUsuario + " en la fecha " + fechaBusqueda;
            }

            StringBuilder resultado = new StringBuilder();
            resultado.append("=== HISTORIAL DE ").append(nombreUsuario.toUpperCase())
                    .append(" - ").append(fechaBusqueda).append(" ===\n\n");

            for (String linea : accionesFecha) {
                String lineaFormateada = formatearLinea(linea);
                resultado.append(lineaFormateada).append("\n");
            }

            return resultado.toString();

        } catch (Exception e) {
            return "Error al buscar historial por fecha: " + e.getMessage();
        }
    }

    /**
     * Limpia completamente el historial de un usuario
     */
    public boolean limpiarHistorial(Usuario usuario) {
        if (usuario == null || usuario.getNombre() == null || usuario.getNombre().trim().isEmpty()) {
            System.err.println("Error: Usuario no valido para limpiar historial");
            return false;
        }

        try {
            File archivo = rutaArchivo.toFile();
            if (!archivo.exists() || archivo.length() == 0) {
                System.out.println("El usuario " + usuario.getNombre() + " no tiene historial para limpiar");
                return true;
            }

            List<String> lineas = leerArchivo();
            String nombreUsuario = usuario.getNombre();
            
            List<String> lineasRestantes = lineas.stream()
                    .filter(linea -> linea != null && !linea.trim().isEmpty())
                    .filter(linea -> !linea.startsWith("Usuario:" + nombreUsuario + " |"))
                    .collect(Collectors.toList());

            // Reescribir el archivo sin las lineas del usuario
            escribirTodasLasLineas(lineasRestantes);
            
            System.out.println("Historial de " + nombreUsuario + " limpiado exitosamente");
            return true;

        } catch (Exception e) {
            System.err.println("Error al limpiar historial: " + e.getMessage());
            return false;
        }
    }

    /**
     * Obtiene la lista de usuarios que tienen historial
     */
    public List<String> obtenerListaUsuarios() {
        List<String> usuarios = new ArrayList<>();

        try {
            File archivo = rutaArchivo.toFile();
            if (!archivo.exists() || archivo.length() == 0) {
                return usuarios;
            }

            List<String> lineas = leerArchivo();
            
            usuarios = lineas.stream()
                    .filter(linea -> linea != null && !linea.trim().isEmpty())
                    .filter(linea -> linea.startsWith("Usuario:"))
                    .map(this::extraerNombreUsuario)
                    .filter(nombre -> !nombre.isEmpty())
                    .distinct()
                    .collect(Collectors.toList());

        } catch (Exception e) {
            System.err.println("Error al obtener lista de usuarios: " + e.getMessage());
        }

        return usuarios;
    }

    // ==================== METODOS PRIVADOS ====================

    private void inicializarArchivo() {
        try {
            Path directorio = rutaArchivo.getParent();
            if (directorio != null && !Files.exists(directorio)) {
                Files.createDirectories(directorio);
            }

            File archivo = rutaArchivo.toFile();
            if (!archivo.exists()) {
                archivo.createNewFile();
            }
        } catch (IOException e) {
            System.err.println("Error al inicializar archivo de historial: " + e.getMessage());
        }
    }

    private void escribirEnArchivo(String linea) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(
                new FileWriter(rutaArchivo.toFile(), StandardCharsets.UTF_8, true))) {
            writer.write(linea);
            writer.newLine();
            writer.flush();
        }
    }

    private void escribirTodasLasLineas(List<String> lineas) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(
                new FileWriter(rutaArchivo.toFile(), StandardCharsets.UTF_8, false))) {
            for (String linea : lineas) {
                writer.write(linea);
                writer.newLine();
            }
            writer.flush();
        }
    }

    private List<String> leerArchivo() throws IOException {
        List<String> lineas = new ArrayList<>();
        
        try (BufferedReader reader = new BufferedReader(
                new FileReader(rutaArchivo.toFile(), StandardCharsets.UTF_8))) {
            String linea;
            while ((linea = reader.readLine()) != null) {
                // Filtrar lineas vacias o con solo espacios
                if (!linea.trim().isEmpty()) {
                    lineas.add(linea);
                }
            }
        }
        
        return lineas;
    }

    private String formatearLinea(String linea) {
        try {
            // Formato: "Usuario:nombre | Fecha:dd-MM-yyyy HH:mm:ss | Accion:descripcion"
            String[] partes = linea.split(" \\| ");
            if (partes.length >= 3) {
                String fecha = partes[1].replace("Fecha:", "").trim();
                String accion = partes[2].replace("Accion:", "").trim();
                return "• " + fecha + " - " + accion;
            }
        } catch (Exception e) {
            // Si hay error en el formateo, devolver la linea original
            System.err.println("Error al formatear linea: " + e.getMessage());
        }
        return "• " + linea;
    }

    private String extraerNombreUsuario(String linea) {
        try {
            int inicio = linea.indexOf("Usuario:") + "Usuario:".length();
            int fin = linea.indexOf(" |", inicio);
            
            if (inicio >= 0 && fin > inicio) {
                return linea.substring(inicio, fin).trim();
            }
        } catch (Exception e) {
            System.err.println("Error al extraer nombre de usuario: " + e.getMessage());
        }
        return "";
    }
}