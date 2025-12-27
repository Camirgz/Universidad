import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class ControlServicios {
    private static final String ARCHIVO_SERVICIOS = "data\\Servicios.txt";
    private List<ServicioExtra> servicios = new ArrayList<>();

    public ControlServicios() {
        Path path = Paths.get(ARCHIVO_SERVICIOS);
        if (!Files.exists(path)) {
            crearArchivoPredeterminado();
        }
        cargarServicios();
    }

    private void crearArchivoPredeterminado() {
        try {
            List<String> lineas = new ArrayList<>();
            lineas.add("Servicio a la habitacion;25.00");
            lineas.add("Spa y masajes;60.00");
            lineas.add("Desayuno buffet;15.00");
            lineas.add("Limpieza de habitacion extra;10.00");
            lineas.add("Acceso al gimnasio;8.00");
            lineas.add("Uso de piscina privada;20.00");
            lineas.add("Transporte al aeropuerto;35.00");
            lineas.add("Excursion guiada;50.00");
            lineas.add("Lavanderia;12.00");
            lineas.add("Alquiler de bicicletas;18.00");
            Files.write(Paths.get(ARCHIVO_SERVICIOS), lineas);
        } catch (IOException e) {
            System.err.println("Error al crear archivo de servicios: " + e.getMessage());
        }
    }

    private void cargarServicios() {
        try {
            List<String> lineas = Files.readAllLines(Paths.get(ARCHIVO_SERVICIOS));
            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length == 2) {
                    String descripcion = partes[0].trim();
                    double precio = Double.parseDouble(partes[1].trim());
                    servicios.add(new ServicioExtra(descripcion, precio));
                }
            }
        } catch (IOException e) {
            System.err.println("Error al cargar servicios: " + e.getMessage());
        }
    }

    public List<ServicioExtra> obtenerServicios() {
        return new ArrayList<>(servicios);
    }
}