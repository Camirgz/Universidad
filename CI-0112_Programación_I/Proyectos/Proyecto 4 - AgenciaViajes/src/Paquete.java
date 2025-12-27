import java.util.List;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

public class Paquete {

    // Atributos
    private String destino;
    private String pais;
    private String ciudad;
    private String hotelAsociado;
    private String tipoViaje;
    private String fechaInicio;
    private String fechaFin;
    private String descripcion;
    private double precioPaquete;
    private List<ServicioExtra> serviciosExtra;
    private Usuario usuario;
    private static final java.nio.file.Path PATH_PAQUETES = java.nio.file.Paths.get("data\\Paquetes.txt");

    
    // Constructor
    public Paquete() {
        this.serviciosExtra = new ArrayList<>();
        
    }

    public void setDestino(String destino) {
        this.destino = destino;
    }

    public String getPais() {
        return pais;
    }

    public void setPais(String pais) {
        this.pais = pais;
    }

    public String getCiudad() {
        return ciudad;
    }

    public void setCiudad(String ciudad) {
        this.ciudad = ciudad;
    }

    public String getHotelAsociado() {
        return hotelAsociado;
    }

    public void setHotelAsociado(String hotelAsociado) {
        this.hotelAsociado = hotelAsociado;
    }

    public String getTipoViaje() {
        return tipoViaje;
    }

    public void setTipoViaje(String tipoViaje) {
        this.tipoViaje = tipoViaje;
    }

    public String getFechaInicio() {
        return fechaInicio;
    }

    public void setFechaInicio(String fechaInicio) {
        this.fechaInicio = fechaInicio;
    }

    public String getFechaFin() {
        return fechaFin;
    }

    public void setFechaFin(String fechaFin) {
        this.fechaFin = fechaFin;
    }

    public String getDescripcion() {
        return descripcion;
    }

    public void setDescripcion(String descripcion) {
        this.descripcion = descripcion;
    }

    public double getPrecioPaquete() {
        return precioPaquete;
    }

    public void setPrecioPaquete(double precioPaquete) {
        this.precioPaquete = precioPaquete;
    }

    public String getDestino() {
        return destino;
    }


    public List<ServicioExtra> getServiciosExtra() {
        return serviciosExtra;
    }

    public void setServiciosExtra(List<ServicioExtra> serviciosExtra) {
        this.serviciosExtra = serviciosExtra;
    }

    public Usuario getUsuario() {
        return usuario;
    }

    public void setUsuario(Usuario usuario) {
        this.usuario = usuario;
    }

    public double getPrecioTotal() {
        double total = precioPaquete;
        for (ServicioExtra servicio : serviciosExtra) {
            total += servicio.getPrecio();
        }
        return total;
    }

    /** Lee todas las lineas del archivo, creando el archivo si no existe */
    private List<String> leerArchivo() {
        try {
            if (Files.notExists(PATH_PAQUETES)) {
                Files.createDirectories(PATH_PAQUETES.getParent());
                Files.createFile(PATH_PAQUETES);
            }
            return Files.readAllLines(PATH_PAQUETES);
        } catch (IOException e) {
            System.err.println("Error al leer el archivo de paquetes: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    /** Sobrescribe el archivo con la lista de paquetes */
    private void escribirArchivo(List<String> lineas) {
        try {
            Files.write(PATH_PAQUETES, lineas, StandardOpenOption.TRUNCATE_EXISTING);
        } catch (IOException e) {
            System.err.println("Error al escribir el archivo de paquetes: " + e.getMessage());
        }
    }
}
