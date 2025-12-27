import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class ControlReservas {

    private static final String DIRECTORIO_DATOS = "data";
    private static final String archivo = DIRECTORIO_DATOS + "/Reservas.txt";

    public boolean agregarReserva(Reservas reserva) {
        try {
            // Crear el directorio si no existe
            Path directorioPath = Paths.get(DIRECTORIO_DATOS);
            if (!Files.exists(directorioPath)) {
                Files.createDirectories(directorioPath);
                System.out.println("Directorio 'data' creado exitosamente.");
            }

            Path archivoPath = Paths.get(archivo);
            List<String> lineas = Files.exists(archivoPath) ? Files.readAllLines(archivoPath) : new ArrayList<>();

            int nuevoId = obtenerSiguienteId(lineas);
            String nuevaLinea = String.format(
                    "ID: %d | Hotel: %s | Tipo: %s | Fechas: %s a %s | Descripcion: %s | Precio: %.2f | Usuario: %s",
                    nuevoId,
                    reserva.getNombreHotel() != null ? reserva.getNombreHotel() : "Sin hotel",
                    reserva.getTipoReserva() != null ? reserva.getTipoReserva() : "Sin tipo",
                    reserva.getFechaInicio() != null ? reserva.getFechaInicio() : "Sin fecha",
                    reserva.getFechaFin() != null ? reserva.getFechaFin() : "Sin fecha",
                    reserva.getDescripcion() != null ? reserva.getDescripcion() : "Sin descripcion",
                    reserva.getPrecioTotal(),
                    reserva.getUsuario() != null ? reserva.getUsuario().getNombre() : "Sin usuario");

            lineas.add(nuevaLinea);
            
            // Escribir todas las lineas al archivo
            Files.write(archivoPath, lineas, StandardOpenOption.CREATE, StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING);
            
            System.out.println("Reserva agregada exitosamente con ID: " + nuevoId);
            return true;
            
        } catch (IOException e) {
            System.err.println("Error al guardar reserva: " + e.getMessage());
            System.err.println("Causa: " + e.getCause());
            e.printStackTrace();
            return false;
        } catch (Exception e) {
            System.err.println("Error inesperado al guardar reserva: " + e.getMessage());
            e.printStackTrace();
            return false;
        }
    }

    public boolean editarReserva(String id, String nuevaFechaInicio, String nuevaFechaFin, String nuevoTipo) {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                System.out.println("No hay reservas registradas.");
                return false;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            boolean encontrado = false;

            for (int i = 0; i < lineas.size(); i++) {
                String linea = lineas.get(i);
                if (linea.startsWith("ID: " + id + " |")) {
                    // Extraer informacion existente
                    String[] partes = linea.split(" \\| ");
                    if (partes.length >= 7) {
                        String hotel = partes[1].substring(7); // Quitar "Hotel: "
                        String descripcion = partes[4].substring(13); // Quitar "Descripcion: "
                        String precio = partes[5].substring(8); // Quitar "Precio: "
                        String usuario = partes[6].substring(9); // Quitar "Usuario: "

                        // Crear nueva linea con campos actualizados
                        String nuevaLinea = String.format(
                                "ID: %s | Hotel: %s | Tipo: %s | Fechas: %s a %s | Descripcion: %s | Precio: %s | Usuario: %s",
                                id, hotel, nuevoTipo, nuevaFechaInicio, nuevaFechaFin, descripcion, precio, usuario);

                        lineas.set(i, nuevaLinea);
                        encontrado = true;
                        break;
                    }
                }
            }

            if (encontrado) {
                Files.write(archivoPath, lineas, StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING);
                System.out.println("Reserva editada exitosamente.");
                return true;
            } else {
                System.out.println("No se encontro reserva con ID: " + id);
                return false;
            }
        } catch (IOException e) {
            System.err.println("Error al editar reserva: " + e.getMessage());
            return false;
        }
    }

    public List<String> listarReservasUsuario(String nombreUsuario) {
        Path archivoPath = Paths.get(archivo);
        List<String> reservasUsuario = new ArrayList<>();

        try {
            if (!Files.exists(archivoPath)) {
                return reservasUsuario;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            for (String linea : lineas) {
                if (linea.contains("Usuario: " + nombreUsuario)) {
                    reservasUsuario.add(linea);
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer reservas: " + e.getMessage());
        }

        return reservasUsuario;
    }

    public List<String> listarTodasReservas() {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                return new ArrayList<>();
            }
            return Files.readAllLines(archivoPath);
        } catch (IOException e) {
            System.err.println("Error al leer reservas: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public boolean eliminarReserva(String id) {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                System.out.println("No hay reservas registradas.");
                return false;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            List<String> nuevasLineas = lineas.stream()
                    .filter(linea -> !linea.startsWith("ID: " + id + " |"))
                    .collect(Collectors.toList());

            if (nuevasLineas.size() < lineas.size()) {
                Files.write(archivoPath, nuevasLineas, StandardOpenOption.WRITE, StandardOpenOption.TRUNCATE_EXISTING);
                System.out.println("Reserva eliminada exitosamente.");
                return true;
            } else {
                System.out.println("No se encontro reserva con ID: " + id);
                return false;
            }
        } catch (IOException e) {
            System.err.println("Error al eliminar reserva: " + e.getMessage());
            return false;
        }
    }

    private int obtenerSiguienteId(List<String> lineas) {
        int maxId = 0;
        for (String linea : lineas) {
            if (linea.startsWith("ID: ")) {
                try {
                    String idStr = linea.substring(4, linea.indexOf(" |"));
                    int id = Integer.parseInt(idStr);
                    maxId = Math.max(maxId, id);
                } catch (NumberFormatException | StringIndexOutOfBoundsException e) {
                    // Ignorar lineas mal formateadas
                }
            }
        }
        return maxId + 1;
    }

    // Metodo para verificar si el sistema de archivos esta funcionando correctamente
    public boolean verificarSistemaArchivos() {
        try {
            Path directorioPath = Paths.get(DIRECTORIO_DATOS);
            if (!Files.exists(directorioPath)) {
                Files.createDirectories(directorioPath);
            }
            
            Path archivoPath = Paths.get(archivo);
            if (!Files.exists(archivoPath)) {
                Files.createFile(archivoPath);
            }
            
            return Files.isWritable(archivoPath);
        } catch (IOException e) {
            System.err.println("Error al verificar sistema de archivos: " + e.getMessage());
            return false;
        }
    }
}