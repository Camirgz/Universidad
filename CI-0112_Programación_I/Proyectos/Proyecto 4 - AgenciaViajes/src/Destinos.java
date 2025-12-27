public class Destinos {

    private String pais;
    private String ciudad;
    private String fecha;
    private String costo;
    private Usuario usuario;

    public Destinos(Usuario usuario, String pais, String ciudad, String costo, String fechaInicio, String fechaFin) {
        this.usuario = usuario;
        this.pais = pais;
        this.ciudad = ciudad;
        this.costo = costo;
        this.fecha = fechaInicio + " - " + fechaFin;
    }

    public Destinos() {
    }

    public String getPais() {
        return pais;
    }

    public String getCiudad() {
        return ciudad;
    }

    public String getfecha() {
        return fecha;
    }

    public String getCosto() {
        return costo;
    }

    public Usuario getUsuario() {
        return usuario;
    }

    public void setPais(String pais) {
        this.pais = pais;
    }

    public void setCiudad(String ciudad) {
        this.ciudad = ciudad;
    }

    public void setfecha(String fecha) {
        this.fecha = fecha;
    }

    public void setcosto(String costo) {
        this.costo = costo;
    }
}
