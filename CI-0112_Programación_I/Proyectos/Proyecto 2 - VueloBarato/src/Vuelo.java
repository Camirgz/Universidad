public class Vuelo{
    private double precio;
    private String ciudadSalida;
    private String ciudadLlegada;
    private String horaSalida;
    private String horaLlegada;
    private String fechaSalida;
    private String fechaLlegada;
    private String codigoVuelo;
    private int asientos;
    
    public Vuelo (double precio, String ciudadSalida, String ciudadLlegada, String horaSalida, String horaLlegada, String fechaSalida, String fechaLlegada, String codigoVuelo, int asientos) {
        this.precio = precio;
        ciudadSalida = ciudadSalida.trim().toUpperCase();
        this.ciudadSalida = ciudadSalida;
        ciudadLlegada = ciudadLlegada.trim().toUpperCase();
        this.ciudadLlegada = ciudadLlegada;
        this.horaSalida = horaSalida;
        this.horaLlegada = horaLlegada;
        this.fechaSalida = fechaSalida;
        this.fechaLlegada = fechaLlegada;
        this.codigoVuelo = codigoVuelo;
        this.asientos = asientos;
    }
    
    public String imprimirVuelo (){
        return "Codigo de vuelo: " + this.codigoVuelo + "\nPrecio: " + this.precio + "\nCiudad de salida: " + this.ciudadSalida + "\nFecha de salida: " + this.fechaSalida + "\nTiempo de salida: " + this.horaSalida + "\nCiudad de llegada: " + this.ciudadLlegada + "\nFecha de llegada: " + this.fechaLlegada + "\nTiempo de llegada: " + this.horaLlegada + "\nAsientos disponibles: " + this.asientos;
    }
    
    public String getCiudadSalida (){
        return this.ciudadSalida;
    }
    
    public String getCiudadLlegada (){
        return this.ciudadLlegada;
    }
    
    public double getPrecio (){
        return this.precio;
    }
    
    public String getFechaSalida(){
        return this.fechaSalida;
    }
    
    public String getFechaLlegada(){
        return this.fechaLlegada;
    }
    
    public String getHoraSalida(){
        return this.horaSalida;
    }
    
    public String getHoraLlegada(){
        return this.horaLlegada;
    }
    
    public String getCodigoVuelo(){
        return this.codigoVuelo;
    }
    
    public int getAsientos(){
        return this.asientos;
    }
}
