import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class ControlUsuarios {
    private static final String ARCHIVO_USUARIOS = "data\\Usuarios.txt";

    public void guardarUsuario(Usuario usuario) {
        Path path = Paths.get(ARCHIVO_USUARIOS);
        try {
            List<String> lineas = new ArrayList<>();
            if (Files.exists(path)) {
                lineas = Files.readAllLines(path);
            }
            String linea = String.format("%s;%s;%s;%s;%.2f;%d;%d",
                    usuario.getNombre(),
                    usuario.getEmail(),
                    usuario.getContraseña(),
                    usuario.getRol(),
                    usuario.getSaldo(),
                    usuario.getId(),
                    usuario.getPin());
            lineas.add(linea);
            Files.write(path, lineas);
        } catch (IOException e) {
            System.err.println("Error al guardar usuario: " + e.getMessage());
        }
    }

    public List<Usuario> cargarUsuarios() {
        List<Usuario> usuarios = new ArrayList<>();
        Path path = Paths.get(ARCHIVO_USUARIOS);
        if (!Files.exists(path)) {
            return usuarios;
        }
        try {
            List<String> lineas = Files.readAllLines(path);
            for (String linea : lineas) {
                String[] partes = linea.split(";");
                if (partes.length == 7) {
                    String nombre = partes[0];
                    String email = partes[1];
                    String password = partes[2];
                    String rol = partes[3];
                    double saldo = Double.parseDouble(partes[4]);
                    int id = Integer.parseInt(partes[5]);
                    int pin = Integer.parseInt(partes[6]);
                    usuarios.add(new Usuario(nombre, email, password, rol, saldo, id, pin));
                }
            }
        } catch (IOException e) {
            System.err.println("Error al cargar usuarios: " + e.getMessage());
        }
        return usuarios;
    }
}