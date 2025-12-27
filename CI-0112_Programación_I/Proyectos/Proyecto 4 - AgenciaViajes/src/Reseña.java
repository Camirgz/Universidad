public class Reseña {

    // Atributos
    private String reseña;
    private String tipoServicio;
    private String nombreServicio;
    private String usuario;
    private int puntuacion;

    // Constructor
    public Reseña(String reseña, String tipoServicio, String nombreServicio, String usuario, int puntuacion) {
        this.reseña = reseña;
        this.tipoServicio = tipoServicio;
        this.nombreServicio = nombreServicio;
        this.usuario = usuario;
        this.puntuacion = puntuacion;
    }

    // Getters y Setters
    public String getReseña() {
        return reseña;
    }

    public void setReseña(String reseña) {
        this.reseña = reseña;
    }

    public String getTipoServicio() {
        return tipoServicio;
    }

    public void setTipoServicio(String tipoServicio) {
        this.tipoServicio = tipoServicio;
    }

    public String getNombreServicio() {
        return nombreServicio;
    }

    public void setNombreServicio(String nombreServicio) {
        this.nombreServicio = nombreServicio;
    }

    public String getUsuario() {
        return usuario;
    }

    public void setUsuario(String usuario) {
        this.usuario = usuario;
    }

    public int getPuntuacion() {
        return puntuacion;
    }

    public void setPuntuacion(int puntuacion) {
        this.puntuacion = puntuacion;
    }

}
