import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Administrador {

    // Atributos
    private String nombre;
    private String email;
    private String contraseña;
    private String rol;
    private int id;
    private String archivoAdmin = "data\\Administradores.txt";

    // Constructor
    public Administrador(String nombre, String email, String contraseña, int id, String rol) {
        this.nombre = nombre;
        this.email = email;
        this.contraseña = contraseña;
        this.id = id;
        this.rol = "Administrador";
        guardarAdministrador(this);
    }

    // Metodos auxiliares
    public boolean verificarContraseña(String contraseña) {
        return this.contraseña.equals(contraseña);
    }

    public void mostrarDatos() {
        System.out.println("Administrador: " + nombre);
        System.out.println("Email: " + email);
        System.out.println("ID: " + id);
        System.out.println("Rol: " + rol);
    }

    public void cambiarContraseña(String nuevaContraseña) {
        this.contraseña = nuevaContraseña;
    }

    // Getters y Setters
    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getContraseña() {
        return contraseña;
    }

    public void setContraseña(String contraseña) {
        this.contraseña = contraseña;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getRol() {
        return rol;
    }

    public void setRol(String rol) {
        this.rol = rol;
    }

    public void guardarAdministrador(Administrador administrador) {
        Path path = Paths.get(archivoAdmin);
        List<String> lineas = new ArrayList<>();
        boolean existe = false;

        // 1) Leer todas las lineas (si el archivo existe) y buscar duplicado por ID
        if (Files.exists(path)) {
            try (BufferedReader br = Files.newBufferedReader(path)) {
                String linea;
                while ((linea = br.readLine()) != null) {
                    lineas.add(linea);
                    String[] partes = linea.split(";");
                    // indice 4 = id en el formato: nombre;email;contraseña;rol;id
                    if (partes.length == 5 && partes[4].equals(String.valueOf(administrador.getId()))) {
                        existe = true;
                    }
                }
            } catch (IOException e) {
                System.err.println("Error al leer archivo de administradores: " + e.getMessage());
                return;
            }
        }

        // 2) Si no existe, formatear y añadir
        if (!existe) {
            String nuevaLinea = String.format("%s;%s;%s;%s;%d",
                    administrador.getNombre(),
                    administrador.getEmail(),
                    administrador.getContraseña(),
                    administrador.getRol(),
                    administrador.getId());
            lineas.add(nuevaLinea);

            // 3) Reescribir el archivo completo con la nueva linea
            try (BufferedWriter bw = Files.newBufferedWriter(path)) {
                for (String l : lineas) {
                    bw.write(l);
                    bw.newLine();
                }
            } catch (IOException e) {
                System.err.println("Error al guardar administrador: " + e.getMessage());
            }
        } 
    }

}