
public class ServicioExtra {
    private String tipo; 
    private String descripcion;
    private double precio;

    // Modificar constructor
    public ServicioExtra(String descripcion, double precio) {
        this.tipo = "Servicio";
        this.descripcion = descripcion;
        this.precio = precio;
    }
    
    // Getters y Setters
    public String getTipo() { return tipo; }
    public void setTipo(String tipo) { this.tipo = tipo; }

    public void setDescripcion(String descripcion) { this.descripcion = descripcion; }

    public double getPrecio() { return precio; }
    public void setPrecio(double precio) { this.precio = precio; }

    public String getDescripcion() {
        return descripcion;
    }


    @Override
    public String toString() {
        return String.format("%s: %s ($%.2f)", tipo, descripcion, precio);
    }

    
}
