import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class ControlPaquetes {

    private static final String archivo = "data\\Paquetes.txt";

    public boolean agregarPaquete(Paquete paquete) {
        Path archivoPath = Paths.get(archivo);
        try {
            List<String> lineas = Files.exists(archivoPath) ? Files.readAllLines(archivoPath) : new ArrayList<>();

            int nuevoId = obtenerSiguienteId(lineas);

            // Convertir servicios extra a string
            String serviciosStr = paquete.getServiciosExtra().stream()
                    .map(ServicioExtra::toString)
                    .collect(Collectors.joining("; "));

            String nuevaLinea = String.format(
                    "ID: %d | Destino: %s, %s | Hotel: %s | Tipo: %s | Fechas: %s a %s | Descripcion: %s | Precio Base: %.2f | Servicios: %s | Precio Total: %.2f | Usuario: %s",
                    nuevoId,
                    paquete.getCiudad(),
                    paquete.getPais(),
                    paquete.getHotelAsociado(),
                    paquete.getTipoViaje(),
                    paquete.getFechaInicio(),
                    paquete.getFechaFin(),
                    paquete.getDescripcion(),
                    paquete.getPrecioPaquete(),
                    serviciosStr.isEmpty() ? "Ninguno" : serviciosStr,
                    paquete.getPrecioTotal(),
                    paquete.getUsuario() != null ? paquete.getUsuario().getNombre() : "Sin usuario");

            lineas.add(nuevaLinea);
            Files.write(archivoPath, lineas);
            
            return true;
        } catch (IOException e) {
            System.err.println("Error al guardar paquete: " + e.getMessage());
            return false;
        }
    }

    // NUEVO: Método para reservar un paquete (crear una copia con usuario asignado)
    public boolean reservarPaquete(Paquete paqueteBase, Usuario usuario) {
        if (paqueteBase == null || usuario == null) {
            System.err.println("Error: Paquete o usuario no válido");
            return false;
        }

        Path archivoPath = Paths.get(archivo);
        try {
            List<String> lineas = Files.exists(archivoPath) ? Files.readAllLines(archivoPath) : new ArrayList<>();

            // Verificar si ya existe una reserva de este paquete para este usuario
            String destino = paqueteBase.getCiudad() + ", " + paqueteBase.getPais();
            String nombreUsuario = usuario.getNombre();

            boolean yaReservado = lineas.stream()
                    .anyMatch(linea -> linea.contains("Destino: " + destino) && 
                                     linea.contains("Usuario: " + nombreUsuario));

            if (yaReservado) {
                System.out.println("Ya tienes este paquete reservado: " + destino);
                return false;
            }

            // Crear una copia del paquete con el usuario asignado
            Paquete paqueteReservado = clonarPaquete(paqueteBase);
            paqueteReservado.setUsuario(usuario);
            
            return agregarPaquete(paqueteReservado);

        } catch (IOException e) {
            System.err.println("Error al reservar paquete: " + e.getMessage());
            return false;
        }
    }

    // Método mejorado que combina ambos enfoques
    public boolean guardarPaquete(Paquete paquete) {
        Path archivoPath = Paths.get(archivo);
        try {
            List<String> lineas = Files.exists(archivoPath) ? Files.readAllLines(archivoPath) : new ArrayList<>();
            boolean existe = false;

            // Verificar si ya existe un paquete con el mismo usuario y destino
            String emailUsuario = paquete.getUsuario() != null ? paquete.getUsuario().getEmail() : "";
            String destino = paquete.getCiudad() + ", " + paquete.getPais();

            for (String linea : lineas) {
                if (linea.contains("Usuario: " + (paquete.getUsuario() != null ? paquete.getUsuario().getNombre() : "Sin usuario")) &&
                    linea.contains("Destino: " + destino)) {
                    existe = true;
                    break;
                }
            }

            if (!existe) {
                // Usar el método existente para mantener consistencia
                return agregarPaquete(paquete);
            } else {
                System.out.println("El paquete ya existe para el usuario " + 
                    (paquete.getUsuario() != null ? paquete.getUsuario().getNombre() : "Sin usuario") + 
                    " con destino " + destino);
                return false;
            }

        } catch (IOException e) {
            System.err.println("Error al verificar/guardar paquete: " + e.getMessage());
            return false;
        }
    }

    // Método alternativo con formato simplificado (basado en tu código original)
    public boolean guardarPaqueteSimple(Paquete paquete) {
        try {
            List<String> lineas = leerArchivo();
            boolean existe = false;

            // Verificar si ya existe un paquete con el mismo usuario y destino
            String emailUsuario = paquete.getUsuario() != null ? paquete.getUsuario().getEmail() : "";
            String destino = paquete.getCiudad() + ", " + paquete.getPais();

            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length >= 2 && partes[0].equals(emailUsuario) && partes[1].equals(destino)) {
                    existe = true;
                    break;
                }
            }

            if (!existe) {
                String nuevaLinea = String.format("%s;%s;%s;%s;%s;%s;%s;%s;%.2f",
                        emailUsuario,
                        destino,
                        paquete.getPais(),
                        paquete.getCiudad(),
                        paquete.getHotelAsociado(),
                        paquete.getTipoViaje(),
                        paquete.getFechaInicio(),
                        paquete.getFechaFin(),
                        paquete.getPrecioTotal());

                lineas.add(nuevaLinea);
                escribirArchivo(lineas);
                System.out.println("Paquete guardado exitosamente.");
                return true;
            } else {
                System.out.println("El paquete ya existe para el usuario " + emailUsuario + " con destino " + destino);
                return false;
            }
        } catch (Exception e) {
            System.err.println("Error al guardar paquete: " + e.getMessage());
            return false;
        }
    }

    public boolean editarFechasPaquete(String id, String nuevaFechaInicio, String nuevaFechaFin) {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                System.out.println("No hay paquetes registrados.");
                return false;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            boolean encontrado = false;

            for (int i = 0; i < lineas.size(); i++) {
                String linea = lineas.get(i);
                if (linea.startsWith("ID: " + id + " |")) {
                    String nuevaLinea = linea.replaceAll(
                            "Fechas: [^|]+ a [^|]+",
                            "Fechas: " + nuevaFechaInicio + " a " + nuevaFechaFin);

                    lineas.set(i, nuevaLinea);
                    encontrado = true;
                    break;
                }
            }

            if (encontrado) {
                Files.write(archivoPath, lineas);
                System.out.println("Fechas actualizadas para el paquete con ID: " + id);
                return true;
            } else {
                System.out.println("Paquete con ID " + id + " no encontrado.");
                return false;
            }

        } catch (IOException e) {
            System.err.println("Error al editar fechas del paquete: " + e.getMessage());
            return false;
        }
    }

    public boolean eliminarPaquete(String id) {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                System.out.println("No hay paquetes registrados.");
                return false;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            List<String> nuevasLineas = lineas.stream()
                    .filter(linea -> !linea.startsWith("ID: " + id + " |"))
                    .collect(Collectors.toList());

            if (lineas.size() == nuevasLineas.size()) {
                System.out.println("Paquete con ID " + id + " no encontrado.");
                return false;
            }

            Files.write(archivoPath, nuevasLineas);
            System.out.println("Paquete con ID " + id + " eliminado exitosamente.");
            return true;
        } catch (IOException e) {
            System.err.println("Error al eliminar paquete: " + e.getMessage());
            return false;
        }
    }

    public List<String> listarPaquetesUsuario(String nombreUsuario) {
        Path archivoPath = Paths.get(archivo);
        List<String> paquetesUsuario = new ArrayList<>();

        try {
            if (!Files.exists(archivoPath)) {
                return paquetesUsuario;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            for (String linea : lineas) {
                if (linea.contains("Usuario: " + nombreUsuario)) {
                    paquetesUsuario.add(linea);
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer paquetes: " + e.getMessage());
        }

        return paquetesUsuario;
    }

    // NUEVO: Método para listar solo paquetes disponibles (sin usuario asignado)
    public List<String> listarPaquetesDisponibles() {
        Path archivoPath = Paths.get(archivo);
        List<String> paquetesDisponibles = new ArrayList<>();

        try {
            if (!Files.exists(archivoPath)) {
                return paquetesDisponibles;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            for (String linea : lineas) {
                if (linea.contains("Usuario: Sin usuario")) {
                    paquetesDisponibles.add(linea);
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer paquetes disponibles: " + e.getMessage());
        }

        return paquetesDisponibles;
    }

    public List<String> listarTodosPaquetes() {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                System.out.println("No hay paquetes registrados.");
                return new ArrayList<>();
            }
            return Files.readAllLines(archivoPath);
        } catch (IOException e) {
            System.err.println("Error al leer paquetes: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    // Métodos auxiliares para el formato simplificado
    private List<String> leerArchivo() {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                return new ArrayList<>();
            }
            return Files.readAllLines(archivoPath);
        } catch (IOException e) {
            System.err.println("Error al leer archivo: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    private void escribirArchivo(List<String> lineas) {
        Path archivoPath = Paths.get(archivo);
        try {
            // Crear directorios si no existen
            Files.createDirectories(archivoPath.getParent());
            Files.write(archivoPath, lineas);
        } catch (IOException e) {
            System.err.println("Error al escribir archivo: " + e.getMessage());
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
                    // Ignorar líneas mal formateadas
                }
            }
        }
        return maxId + 1;
    }

    // NUEVO: Método auxiliar para clonar un paquete
    private Paquete clonarPaquete(Paquete original) {
        Paquete copia = new Paquete();
        copia.setCiudad(original.getCiudad());
        copia.setPais(original.getPais());
        copia.setHotelAsociado(original.getHotelAsociado());
        copia.setTipoViaje(original.getTipoViaje());
        copia.setFechaInicio(original.getFechaInicio());
        copia.setFechaFin(original.getFechaFin());
        copia.setDescripcion(original.getDescripcion());
        copia.setPrecioPaquete(original.getPrecioPaquete());
        copia.setServiciosExtra(new ArrayList<>(original.getServiciosExtra()));
        // NO copiar el usuario - se asignará después
        return copia;
    }

    // MEJORADO: Método que verifica si ya existen paquetes predeterminados
    public void inicializarPaquetesPredeterminados() {
        // Verificar si ya existen paquetes predeterminados
        if (existenPaquetesPredeterminados()) {
            System.out.println("Los paquetes predeterminados ya están inicializados.");
            return;
        }

        System.out.println("Inicializando paquetes predeterminados...");
        List<Paquete> paquetes = new ArrayList<>();

        Paquete p1 = new Paquete();
        p1.setCiudad("Paris");
        p1.setPais("Francia");
        p1.setHotelAsociado("Hotel Lumière");
        p1.setTipoViaje("Romantico");
        p1.setFechaInicio("2025-07-10");
        p1.setFechaFin("2025-07-17");
        p1.setDescripcion("Viaje romantico en Paris con cena en la Torre Eiffel.");
        p1.setPrecioPaquete(1299);
        p1.setServiciosExtra(List.of(new ServicioExtra("Cena romantica en la Torre Eiffel", 1299)));
        p1.setUsuario(null);
        paquetes.add(p1);

        Paquete p2 = new Paquete();
        p2.setCiudad("Tokio");
        p2.setPais("Japon");
        p2.setHotelAsociado("Sakura Inn");
        p2.setTipoViaje("Cultural");
        p2.setFechaInicio("2025-08-05");
        p2.setFechaFin("2025-08-15");
        p2.setDescripcion("Explora Akihabara y templos milenarios.");
        p2.setPrecioPaquete(1590);
        p2.setServiciosExtra(List.of(new ServicioExtra("Tour guiado por Akihabara y templos", 1590)));
        p2.setUsuario(null);
        paquetes.add(p2);

        Paquete p3 = new Paquete();
        p3.setCiudad("Cancun");
        p3.setPais("Mexico");
        p3.setHotelAsociado("Sol y Arena Resort");
        p3.setTipoViaje("Aventura");
        p3.setFechaInicio("2025-06-20");
        p3.setFechaFin("2025-06-27");
        p3.setDescripcion("Disfruta del mar y nada con delfines.");
        p3.setPrecioPaquete(980);
        p3.setServiciosExtra(List.of(new ServicioExtra("Nado con delfines", 980)));
        p3.setUsuario(null);
        paquetes.add(p3);

        Paquete p4 = new Paquete();
        p4.setCiudad("Roma");
        p4.setPais("Italia");
        p4.setHotelAsociado("Colosseo Hotel");
        p4.setTipoViaje("Historico");
        p4.setFechaInicio("2025-09-01");
        p4.setFechaFin("2025-09-10");
        p4.setDescripcion("Conoce el Coliseo con entrada VIP.");
        p4.setPrecioPaquete(1120);
        p4.setServiciosExtra(List.of(new ServicioExtra("Entrada VIP al Coliseo", 1120)));
        p4.setUsuario(null);
        paquetes.add(p4);

        Paquete p5 = new Paquete();
        p5.setCiudad("Nueva York");
        p5.setPais("Estados Unidos");
        p5.setHotelAsociado("Manhattan Dream");
        p5.setTipoViaje("Urbano");
        p5.setFechaInicio("2025-11-10");
        p5.setFechaFin("2025-11-20");
        p5.setDescripcion("Sobrevuela la ciudad en helicoptero.");
        p5.setPrecioPaquete(1785);
        p5.setServiciosExtra(List.of(new ServicioExtra("Helicoptero sobre la ciudad", 1785)));
        p5.setUsuario(null);
        paquetes.add(p5);

        Paquete p6 = new Paquete();
        p6.setCiudad("El Cairo");
        p6.setPais("Egipto");
        p6.setHotelAsociado("Nilo Palace");
        p6.setTipoViaje("Exotico");
        p6.setFechaInicio("2025-10-05");
        p6.setFechaFin("2025-10-15");
        p6.setDescripcion("Crucero por el Nilo con cena incluida.");
        p6.setPrecioPaquete(1040);
        p6.setServiciosExtra(List.of(new ServicioExtra("Crucero por el Nilo con cena incluida", 1040)));
        p6.setUsuario(null);
        paquetes.add(p6);

        Paquete p7 = new Paquete();
        p7.setCiudad("Sidney");
        p7.setPais("Australia");
        p7.setHotelAsociado("Harbour Blue Hotel");
        p7.setTipoViaje("Aventura");
        p7.setFechaInicio("2025-12-01");
        p7.setFechaFin("2025-12-10");
        p7.setDescripcion("Clases de surf en Bondi Beach.");
        p7.setPrecioPaquete(1460);
        p7.setServiciosExtra(List.of(new ServicioExtra("Clases de surf en Bondi Beach", 1460)));
        p7.setUsuario(null);
        paquetes.add(p7);

        Paquete p8 = new Paquete();
        p8.setCiudad("Barcelona");
        p8.setPais("España");
        p8.setHotelAsociado("Gaudi Boutique");
        p8.setTipoViaje("Gastronomico");
        p8.setFechaInicio("2025-07-25");
        p8.setFechaFin("2025-08-01");
        p8.setDescripcion("Tour de tapas y show de flamenco.");
        p8.setPrecioPaquete(990);
        p8.setServiciosExtra(List.of(new ServicioExtra("Tour de tapas y flamenco", 990)));
        p8.setUsuario(null);
        paquetes.add(p8);

        Paquete p9 = new Paquete();
        p9.setCiudad("Reikiavik");
        p9.setPais("Islandia");
        p9.setHotelAsociado("Hilton Reykjavik");
        p9.setTipoViaje("Aventura");
        p9.setFechaInicio("2025-03-15");
        p9.setFechaFin("2025-03-22");
        p9.setDescripcion("Experiencia unica viendo auroras boreales.");
        p9.setPrecioPaquete(1650);
        p9.setServiciosExtra(List.of(new ServicioExtra("Tour de auroras boreales", 1650)));
        p9.setUsuario(null);
        paquetes.add(p9);

        // Guardar todos los paquetes predeterminados
        for (Paquete paquete : paquetes) {
            agregarPaquete(paquete);
        }
        
        System.out.println("Paquetes predeterminados inicializados correctamente.");
    }

    // NUEVO: Método para verificar si ya existen paquetes predeterminados
    private boolean existenPaquetesPredeterminados() {
        Path archivoPath = Paths.get(archivo);
        try {
            if (!Files.exists(archivoPath)) {
                return false;
            }

            List<String> lineas = Files.readAllLines(archivoPath);
            
            // Verificar si existe al menos uno de los paquetes predeterminados
            // Por ejemplo, verificar si existe Paris, Francia
            return lineas.stream()
                    .anyMatch(linea -> linea.contains("Destino: Paris, Francia") && 
                                     linea.contains("Usuario: Sin usuario"));

        } catch (IOException e) {
            System.err.println("Error al verificar paquetes predeterminados: " + e.getMessage());
            return false;
        }
    }
}