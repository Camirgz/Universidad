import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Usuario {

    
    // Atributos
    private String nombre;
    private String email;
    private String contraseña;
    private String rol;
    private double saldo;
    private int id;
    private int pin;
    private String archivoUsuario = "data\\Usuarios.txt";

    // Constructor
    public Usuario(String nombre, String email, String contraseña, String rol, double saldo, int id, int pin) {
        this.nombre = nombre;
        this.email = email;
        this.contraseña = contraseña;
        this.rol = rol;
        this.saldo = saldo;
        this.id = id;
        this.pin = pin;
        guardarUsuario(this);
    }

    // Metodos Auxiliares
    public void addSaldo(double cantidad) {
        this.saldo += cantidad;
    }

    public void restarSaldo(double cantidad) {
        if (cantidad <= this.saldo) {
            this.saldo -= cantidad;
        } else {
            System.out.println("Saldo insuficiente.");
        }
    }

    public boolean verificarPin(int pin) {
        if (this.pin == pin) {
            System.out.println("PIN correcto.");
            return true;
        } else {
            System.out.println("PIN incorrecto.");
            return false;
        }
    }

    public boolean verificarContraseña(String contraseña) {
        if (this.contraseña.equals(contraseña)) {
            System.out.println("Contraseña correcta.");
            return true;
        } else {
            System.out.println("Contraseña incorrecta.");
            return false;
        }
    }

    public void mostrarDatos() {
        System.out.println("Nombre: " + nombre);
        System.out.println("Email: " + email);
        System.out.println("Rol: " + rol);
        System.out.println("Saldo: " + saldo);
        System.out.println("ID: " + id);
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

    public String getRol() {
        return rol;
    }

    public void setRol(String rol) {
        this.rol = rol;
    }

    public double getSaldo() {
        return saldo;
    }

    public void setSaldo(double saldo) {
        this.saldo = saldo;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getPin() {
        return pin;
    }

    public void setPin(int pin) {
        this.pin = pin;
    }

    public void guardarUsuario(Usuario usuario) {
        Path path = Paths.get(archivoUsuario);
        List<String> lineas = new ArrayList<>();
        boolean existe = false;

        // 1) Leer archivo existente y detectar usuario por ID
        if (Files.exists(path)) {
            try (BufferedReader br = Files.newBufferedReader(path)) {
                String linea;
                while ((linea = br.readLine()) != null) {
                    lineas.add(linea);
                    String[] partes = linea.split(";");
                    // indice 5 = id en: nombre;email;contraseña;rol;saldo;id;pin
                    if (partes.length >= 6 && partes[5].equals(String.valueOf(usuario.getId()))) {
                        existe = true;
                    }
                }
            } catch (IOException e) {
                System.err.println("Error al leer archivo de usuarios: " + e.getMessage());
                return;
            }
        }

        // 2) Si no existe, añadirlo
        if (!existe) {
            String nuevaLinea = String.format("%s;%s;%s;%s;%.2f;%d;%d",
                    usuario.getNombre(),
                    usuario.getEmail(),
                    usuario.getContraseña(),
                    usuario.getRol(),
                    usuario.getSaldo(),
                    usuario.getId(),
                    usuario.getPin());
            lineas.add(nuevaLinea);

            // 3) Reescribir todas las lineas
            try (BufferedWriter bw = Files.newBufferedWriter(path)) {
                for (String l : lineas) {
                    bw.write(l);
                    bw.newLine();
                }
            } catch (IOException e) {
                System.err.println("Error al guardar usuario: " + e.getMessage());
            }
        } 
    }
}
