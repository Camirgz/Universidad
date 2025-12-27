public class Sesion {
    // Atributos
    private static Sesion instancia;
    private Usuario usuarioActual;
    private Administrador administradorActual;
    private String tipoSesionActual; // "USUARIO", "ADMINISTRADOR", o null
    
    // Constructor privado (Singleton)
    private Sesion() {
        this.usuarioActual = null;
        this.administradorActual = null;
        this.tipoSesionActual = null;
    }
    
    // Metodo para obtener la instancia unica
    public static Sesion getInstancia() {
        if (instancia == null) {
            instancia = new Sesion();
        }
        return instancia;
    }
    
    // Manejo de la sesion del usuario
    public void setSesionUsuario(Usuario usuario) {
        cerrarSesion(); // Cerrar cualquier sesion activa
        this.usuarioActual = usuario;
        this.tipoSesionActual = "USUARIO";
    }
    
    // Manejo de la sesion del administrador
    public void setSesionAdministrador(Administrador administrador) {
        cerrarSesion(); // Cerrar cualquier sesion activa
        this.administradorActual = administrador;
        this.tipoSesionActual = "ADMINISTRADOR";
    }
    
    // Cerrar sesion (tanto usuario como administrador)
    public void cerrarSesion() {
        this.usuarioActual = null;
        this.administradorActual = null;
        this.tipoSesionActual = null;
    }
    
    // Getters
    public Usuario getUsuarioActual() {
        return usuarioActual;
    }
    
    public Administrador getAdministradorActual() {
        return administradorActual;
    }
    
    public String getTipoSesionActual() {
        return tipoSesionActual;
    }
    
    // Metodos de verificacion
    public boolean haySesionActiva() {
        return tipoSesionActual != null;
    }
    
    public boolean esSesionUsuario() {
        return "USUARIO".equals(tipoSesionActual);
    }
    
    public boolean esSesionAdministrador() {
        return "ADMINISTRADOR".equals(tipoSesionActual);
    }
    
    // Metodo para obtener informacion de la sesion actual
    public String getInfoSesion() {
        if (!haySesionActiva()) {
            return "No hay sesion activa";
        }
        
        if (esSesionUsuario()) {
            return "Usuario: " + usuarioActual.getNombre(); // Asumiendo que Usuario tiene getNombre()
        } else if (esSesionAdministrador()) {
            return "Administrador: " + administradorActual.getNombre(); // Asumiendo que Administrador tiene getNombre()
        }
        
        return "Sesion desconocida";
    }
}