import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Principal {

    private final Scanner scanner = new Scanner(System.in);
    private final ControlDestinos controlDestinos = new ControlDestinos();
    private final ControlPaquetes controlPaquetes = new ControlPaquetes();
    private final ControlReseñas controlReseñas = new ControlReseñas();
    private final ControlReservas controlReservas = new ControlReservas();
    private final ControlUsuarios controlUsuarios = new ControlUsuarios();
    private final ControlServicios controlServicios = new ControlServicios();
    private final Sesion sesion = Sesion.getInstancia();
    private final Historial historial = Historial.getInstancia();
    private final List<Usuario> usuariosRegistrados = new ArrayList<>();
    private final List<Administrador> administradores = new ArrayList<>();

    // Constructor para inicializar datos
    public Principal() {
        usuariosRegistrados.addAll(controlUsuarios.cargarUsuarios());
        usuariosRegistrados.add(new Usuario("Juan", "juan@mail.com", "pass123", "usuario", 500.0, 1, 1234));
        usuariosRegistrados.add(new Usuario("Maria", "maria@mail.com", "pass456", "usuario", 1200.0, 2, 5678));
        administradores.add(new Administrador("Admin", "admin@system.com", "adminpass", 1, "Administrador"));
        usuariosRegistrados.add(new Usuario("a", "a", "a", "a", 20000, 3, 123));
        administradores.add(new Administrador("b", "b", "b", 3, "b"));
        controlDestinos.inicializarDestinosDisponibles();
        controlPaquetes.inicializarPaquetesPredeterminados(); // Inicializar paquetes
    }

    public void iniciar() {
        while (true) {
            try {
                System.out.println("\n=== Agencia de Viajes ===");
                System.out.println("1. Administrador");
                System.out.println("2. Usuario");
                System.out.println("3. Salir");
                System.out.print("Seleccione tipo de usuario: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 1:
                        menuAdministrador();
                        break;
                    case 2:
                        menuUsuario();
                        break;
                    case 3:
                        System.out.println("¡Gracias por usar nuestros servicios!");
                        return;
                    default:
                        System.out.println("Opcion invalida");
                }
            } catch (InputMismatchException e) {
                System.out.println("Entrada invalida. Intente de nuevo.");
                scanner.nextLine();
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void menuAdministrador() {
        try {
            System.out.print("\nEmail: ");
            String email = scanner.nextLine();
            System.out.print("Contraseña: ");
            String password = scanner.nextLine();

            Administrador admin = autenticarAdmin(email, password);
            if (admin == null) {
                System.out.println("Credenciales invalidas");
                return;
            }

            sesion.setSesionAdministrador(admin);
            // Registrar login de administrador
            historial.registrarAccion(new Usuario(admin.getNombre(), admin.getEmail(), "", "admin", 0.0, 0, 0),
                    "Login como administrador");

            while (true) {
                try {
                    System.out.println("\n=== PANEL ADMINISTRADOR ===");
                    System.out.println("1. Ver todos los paquetes");
                    System.out.println("2. Ver todas las reservas");
                    System.out.println("3. Ver todas las reseñas");
                    System.out.println("4. Ver historial de usuarios");
                    System.out.println("5. Gestionar historial");
                    System.out.println("6. Salir");
                    System.out.print("Seleccione: ");

                    int opcion = scanner.nextInt();
                    scanner.nextLine();

                    switch (opcion) {
                        case 1:
                            verPaquetes();
                            historial.registrarAccion(
                                    new Usuario(admin.getNombre(), admin.getEmail(), "", "admin", 0.0, 0, 0),
                                    "Consulto todos los paquetes");
                            break;
                        case 2:
                            verReservas();
                            historial.registrarAccion(
                                    new Usuario(admin.getNombre(), admin.getEmail(), "", "admin", 0.0, 0, 0),
                                    "Consulto todas las reservas");
                            break;
                        case 3:
                            verReseñas();
                            historial.registrarAccion(
                                    new Usuario(admin.getNombre(), admin.getEmail(), "", "admin", 0.0, 0, 0),
                                    "Consulto todas las reseñas");
                            break;
                        case 4:
                            menuHistorialAdmin();
                            break;
                        case 5:
                            menuGestionHistorial();
                            break;
                        case 6:
                            historial.registrarAccion(
                                    new Usuario(admin.getNombre(), admin.getEmail(), "", "admin", 0.0, 0, 0),
                                    "Cerro sesion de administrador");
                            sesion.cerrarSesion();
                            return;
                        default:
                            System.out.println("Opcion invalida");
                    }
                } catch (InputMismatchException e) {
                    System.out.println("Entrada invalida.");
                    scanner.nextLine();
                } catch (Exception e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
        } catch (Exception e) {
            System.out.println("Error en el login de administrador: " + e.getMessage());
        }
    }

    private void menuHistorialAdmin() {
        while (true) {
            try {
                System.out.println("\n=== HISTORIAL DE USUARIOS ===");
                System.out.println("1. Ver todos los usuarios con historial");
                System.out.println("2. Ver historial completo de un usuario");
                System.out.println("3. Buscar historial por fecha");
                System.out.println("4. Volver");
                System.out.print("Seleccione: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 1:
                        mostrarUsuariosConHistorial();
                        break;
                    case 2:
                        mostrarHistorialUsuario();
                        break;
                    case 3:
                        buscarHistorialPorFecha();
                        break;
                    case 4:
                        return;
                    default:
                        System.out.println("Opcion invalida");
                }
            } catch (InputMismatchException e) {
                System.out.println("Entrada invalida.");
                scanner.nextLine();
            }
        }
    }

    private void menuGestionHistorial() {
        while (true) {
            try {
                System.out.println("\n=== GESTION DE HISTORIAL ===");
                System.out.println("1. Limpiar historial de un usuario");
                System.out.println("2. Volver");
                System.out.print("Seleccione: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 1:
                        limpiarHistorialUsuario();
                        break;
                    case 2:
                        return;
                    default:
                        System.out.println("Opcion invalida");
                }
            } catch (InputMismatchException e) {
                System.out.println("Entrada invalida.");
                scanner.nextLine();
            }
        }
    }

    private void mostrarUsuariosConHistorial() {
        try {
            List<String> usuarios = historial.obtenerListaUsuarios();
            if (usuarios.isEmpty()) {
                System.out.println("No hay usuarios con historial registrado.");
            } else {
                System.out.println("\n=== USUARIOS CON HISTORIAL ===");
                for (int i = 0; i < usuarios.size(); i++) {
                    System.out.println((i + 1) + ". " + usuarios.get(i));
                }
            }
        } catch (Exception e) {
            System.out.println("Error al mostrar usuarios: " + e.getMessage());
        }
    }

    private void mostrarHistorialUsuario() {
        try {
            System.out.print("Nombre del usuario: ");
            String nombreUsuario = scanner.nextLine();

            Usuario usuario = buscarUsuarioPorNombre(nombreUsuario);
            if (usuario != null) {
                String historialCompleto = historial.obtenerHistorialCompleto(usuario);
                System.out.println("\n" + historialCompleto);
            } else {
                System.out.println("Usuario no encontrado.");
            }
        } catch (Exception e) {
            System.out.println("Error al mostrar historial del usuario: " + e.getMessage());
        }
    }

    private void buscarHistorialPorFecha() {
        try {
            System.out.print("Nombre del usuario: ");
            String nombreUsuario = scanner.nextLine();

            Usuario usuario = buscarUsuarioPorNombre(nombreUsuario);
            if (usuario != null) {
                System.out.print("Ingrese la fecha (dd-MM-yyyy): ");
                String fechaBusqueda = scanner.nextLine();

                // Validacion simple de formato
                if (!fechaBusqueda.matches("\\d{2}-\\d{2}-\\d{4}")) {
                    System.out.println("Formato de fecha invalido. Use dd-MM-yyyy (ejemplo: 09-06-2025)");
                    return;
                }

                String resultado = historial.buscarHistorialPorFecha(usuario, fechaBusqueda);
                System.out.println("\n" + resultado);
            } else {
                System.out.println("Usuario no encontrado.");
            }
        } catch (Exception e) {
            System.out.println("Error al buscar historial por fecha: " + e.getMessage());
        }
    }

    private void limpiarHistorialUsuario() {
        try {
            System.out.print("Nombre del usuario: ");
            String nombreUsuario = scanner.nextLine();

            Usuario usuario = buscarUsuarioPorNombre(nombreUsuario);
            if (usuario != null) {
                System.out.print("¿Esta seguro de limpiar el historial de " + nombreUsuario + "? (s/n): ");
                String confirmacion = scanner.nextLine();

                if (confirmacion.toLowerCase().equals("s") || confirmacion.toLowerCase().equals("si")) {
                    if (historial.limpiarHistorial(usuario)) {
                        System.out.println("Historial de " + nombreUsuario + " limpiado exitosamente.");

                        // FIX: Obtener el administrador actual correctamente
                        Object usuarioActual = sesion.getUsuarioActual();
                        if (usuarioActual != null) {
                            String nombreAdmin = "";
                            String emailAdmin = "";

                            // Verificar si es Usuario o Administrador
                            if (usuarioActual instanceof Usuario) {
                                Usuario admin = (Usuario) usuarioActual;
                                nombreAdmin = admin.getNombre();
                                emailAdmin = admin.getEmail();
                            } else if (usuarioActual instanceof Administrador) {
                                Administrador admin = (Administrador) usuarioActual;
                                nombreAdmin = admin.getNombre();
                                emailAdmin = admin.getEmail();
                            }

                            // Registrar la accion del administrador
                            Usuario adminComoUsuario = new Usuario(nombreAdmin, emailAdmin, "", "admin", 0.0, 0, 0);
                            historial.registrarAccion(adminComoUsuario,
                                    "Limpio historial del usuario: " + nombreUsuario);
                        }
                    } else {
                        System.out.println("Error al limpiar el historial.");
                    }
                } else {
                    System.out.println("Operacion cancelada.");
                }
            } else {
                System.out.println("Usuario no encontrado.");
            }
        } catch (Exception e) {
            System.out.println("Error al limpiar historial: " + e.getMessage());
        }
    }

    // Menu de usuario (faltante)
    private void menuUsuario() {
        try {
            System.out.println("\n1. Iniciar sesion");
            System.out.println("2. Registrarse");
            System.out.println("3. Volver");
            System.out.print("Seleccione: ");

            int opcion = scanner.nextInt();
            scanner.nextLine();

            switch (opcion) {
                case 1:
                    iniciarSesionUsuario();
                    break;
                case 2:
                    registrarUsuario();
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Opcion invalida");
            }
        } catch (InputMismatchException e) {
            System.out.println("Entrada invalida.");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void iniciarSesionUsuario() {
        try {
            System.out.print("\nEmail: ");
            String email = scanner.nextLine();
            System.out.print("Contraseña: ");
            String password = scanner.nextLine();

            Usuario usuario = autenticarUsuario(email, password);
            if (usuario == null) {
                System.out.println("Credenciales invalidas");
                return;
            }

            sesion.setSesionUsuario(usuario);
            historial.registrarAccion(usuario, "Login exitoso");
            menuUsuarioAutenticado();
        } catch (Exception e) {
            System.out.println("Error al iniciar sesion: " + e.getMessage());
        }
    }

    private void menuUsuarioAutenticado() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();

        while (true) {
            try {
                System.out.println("\n=== BIENVENIDO " + usuario.getNombre().toUpperCase() + " ===");
                System.out.println("0. Realizar reserva");
                System.out.println("1. Ver destinos");
                System.out.println("2. Mis paquetes");
                System.out.println("3. Mis reservas");
                System.out.println("4. Gestionar reseñas");
                System.out.println("5. Ver mi perfil");
                System.out.println("6. Ver mi historial");
                System.out.println("7. Gestionar reservas"); // Nueva opción
                System.out.println("8. Cerrar sesion");
                System.out.print("Seleccione: ");
                System.out.print("Seleccione: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 0:
                        menuTipoReserva(); // Nueva funcion para elegir tipo de reserva
                        break;
                    case 1:
                        buscarDestinos();
                        historial.registrarAccion(usuario, "Consulto destinos disponibles");
                        break;
                    case 2:
                        verPaquetesUsuario();
                        historial.registrarAccion(usuario, "Consulto sus paquetes");
                        break;
                    case 3:
                        verReservasUsuario();
                        historial.registrarAccion(usuario, "Consulto sus reservas");
                        break;
                    case 4:
                        menuReseñas();
                        break;
                    case 5:
                        usuario.mostrarDatos();
                        historial.registrarAccion(usuario, "Consulto su perfil");
                        break;
                    case 6:
                        mostrarHistorialPersonal(usuario);
                        break;
                    case 7: // Nueva opción de gestión
                        gestionarReservasUsuario();
                        break;
                    case 8:
                        historial.registrarAccion(usuario, "Cerro sesion");
                        sesion.cerrarSesion();
                        return;
                    default:
                        System.out.println("Opcion invalida");
                }
            } catch (InputMismatchException e) {
                System.out.println("Entrada invalida.");
                scanner.nextLine();
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    // Nueva funcion para elegir tipo de reserva
    private void menuTipoReserva() {
        try {
            System.out.println("\n=== TIPO DE RESERVA ===");
            System.out.println("1. Paquete completo (destino + hotel + servicios)");
            System.out.println("2. Reserva por separado (personalizada)");
            System.out.println("3. Volver");
            System.out.print("Seleccione: ");

            int opcion = scanner.nextInt();
            scanner.nextLine();

            switch (opcion) {
                case 1:
                    reservarPaquete();
                    break;
                case 2:
                    realizarReserva();
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Opcion invalida");
            }
        } catch (InputMismatchException e) {
            System.out.println("Entrada invalida.");
            scanner.nextLine();
        }
    }

    // Nueva funcion para reservar paquetes
    private void reservarPaquete() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();

        System.out.println("\n=== PAQUETES DISPONIBLES ===");
        List<String> paquetes = controlPaquetes.listarTodosPaquetes();

        if (paquetes.isEmpty()) {
            System.out.println("No hay paquetes disponibles.");
            return;
        }

        // Mostrar paquetes disponibles
        for (int i = 0; i < paquetes.size(); i++) {
            System.out.println((i + 1) + ". " + paquetes.get(i));
        }

        System.out.print("Seleccione el numero del paquete (0 para volver): ");
        int seleccion = scanner.nextInt();
        scanner.nextLine();

        if (seleccion == 0) {
            return;
        }

        if (seleccion < 1 || seleccion > paquetes.size()) {
            System.out.println("Seleccion invalida.");
            return;
        }

        String paqueteSeleccionado = paquetes.get(seleccion - 1);

        // Extraer informacion del paquete para crear la reserva
        String nombrePaquete = extraerCampo(paqueteSeleccionado, "Destino: ");
        String fechaInicio = extraerFechaInicio(paqueteSeleccionado);
        String fechaFin = extraerFechaFin(paqueteSeleccionado);
        double precioTotal = extraerPrecioTotal(paqueteSeleccionado);

        // Crear reserva basada en el paquete
        Reservas reserva = new Reservas();
        reserva.setNombreHotel(nombrePaquete);
        reserva.setTipoReserva("Paquete Completo");
        reserva.setFechaInicio(fechaInicio);
        reserva.setFechaFin(fechaFin);
        reserva.setDescripcion("Reserva de paquete completo: " + nombrePaquete);
        reserva.setPrecioTotal(precioTotal);
        reserva.setUsuario(usuario);

        System.out.println("\n=== CONFIRMACION DE RESERVA ===");
        System.out.println("Paquete: " + nombrePaquete);
        System.out.println("Fechas: " + fechaInicio + " al " + fechaFin);
        System.out.println("Precio Total: $" + precioTotal);
        System.out.print("¿Confirmar reserva? (s/n): ");

        String confirmacion = scanner.nextLine();

        if (confirmacion.toLowerCase().equals("s")) {
            if (controlReservas.agregarReserva(reserva)) {
                System.out.println("¡Reserva de paquete realizada con exito!");
                historial.registrarAccion(usuario, "Reservo paquete: " + nombrePaquete +
                        " del " + fechaInicio + " al " + fechaFin + " por $" + precioTotal);
            } else {
                System.out.println("Error al realizar la reserva del paquete");
            }
        } else {
            System.out.println("Reserva cancelada.");
        }
    }

    // Metodos auxiliares para extraer informacion del paquete
    private String extraerCampo(String paquete, String campo) {
        int inicio = paquete.indexOf(campo);
        if (inicio == -1)
            return "N/A";
        inicio += campo.length();
        int fin = paquete.indexOf(" |", inicio);
        if (fin == -1)
            fin = paquete.indexOf(",", inicio);
        if (fin == -1)
            return "N/A";
        return paquete.substring(inicio, fin).trim();
    }

    private String extraerFechaInicio(String paquete) {
        String fechas = extraerCampo(paquete, "Fechas: ");
        if (fechas.contains(" a ")) {
            return fechas.split(" a ")[0].trim();
        }
        return "N/A";
    }

    private String extraerFechaFin(String paquete) {
        String fechas = extraerCampo(paquete, "Fechas: ");
        if (fechas.contains(" a ")) {
            return fechas.split(" a ")[1].trim();
        }
        return "N/A";
    }

    private double extraerPrecioTotal(String paquete) {
        String precio = extraerCampo(paquete, "Precio Total: ");
        try {
            return Double.parseDouble(precio);
        } catch (NumberFormatException e) {
            return 0.0;
        }
    }

    private void mostrarHistorialPersonal(Usuario usuario) {
        while (true) {
            try {
                System.out.println("\n=== MI HISTORIAL ===");
                System.out.println("1. Ver historial completo");
                System.out.println("2. Buscar por fecha");
                System.out.println("3. Volver");
                System.out.print("Seleccione: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 1:
                        String historialCompleto = historial.obtenerHistorialCompleto(usuario);
                        System.out.println("\n" + historialCompleto);
                        historial.registrarAccion(usuario, "Consulto su historial completo");
                        break;
                    case 2:
                        buscarHistorialPersonalPorFecha(usuario);
                        break;
                    case 3:
                        return;
                    default:
                        System.out.println("Opcion invalida");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
                scanner.nextLine();
            }
        }
    }

    private void buscarHistorialPersonalPorFecha(Usuario usuario) {
        try {
            System.out.print("Ingrese la fecha (dd-MM-yyyy): ");
            String fechaBusqueda = scanner.nextLine();

            // Validacion simple de formato
            if (!fechaBusqueda.matches("\\d{2}-\\d{2}-\\d{4}")) {
                System.out.println("Formato de fecha invalido. Use dd-MM-yyyy (ejemplo: 09-06-2025)");
                return;
            }

            String resultado = historial.buscarHistorialPorFecha(usuario, fechaBusqueda);
            System.out.println("\n" + resultado);

            historial.registrarAccion(usuario, "Consulto su historial del " + fechaBusqueda);

        } catch (Exception e) {
            System.out.println("Error al buscar historial por fecha: " + e.getMessage());
        }
    }

    private void menuReseñas() {
        try {
            System.out.println("\n=== GESTION DE RESEÑAS ===");
            System.out.println("1. Crear reseña");
            System.out.println("2. Ver mis reseñas");
            System.out.println("3. Volver");
            System.out.print("Seleccione: ");

            int opcion = scanner.nextInt();
            scanner.nextLine();

            switch (opcion) {
                case 1:
                    crearReseña();
                    break;
                case 2:
                    verReseñasUsuario();
                    historial.registrarAccion((Usuario) sesion.getUsuarioActual(), "Consulto sus reseñas");
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Opcion invalida");
            }
        } catch (InputMismatchException e) {
            System.out.println("Entrada invalida.");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void crearReseña() {
        try {
            System.out.print("\nTipo de servicio (Hotel/Paquete): ");
            String tipo = scanner.nextLine();
            System.out.print("Nombre del servicio: ");
            String nombre = scanner.nextLine();
            System.out.print("Reseña: ");
            String texto = scanner.nextLine();
            System.out.print("Puntuacion (1-5): ");
            int puntuacion = scanner.nextInt();
            scanner.nextLine();

            Usuario usuario = (Usuario) sesion.getUsuarioActual();
            Reseña reseña = new Reseña(texto, tipo, nombre, usuario.getNombre(), puntuacion);

            if (controlReseñas.guardarReseña(reseña)) {
                System.out.println("¡Reseña publicada!");
                historial.registrarAccion(usuario,
                        "Creo reseña para " + tipo + ": " + nombre + " (Puntuacion: " + puntuacion + ")");
            } else {
                System.out.println("Error al publicar reseña");
            }
        } catch (InputMismatchException e) {
            System.out.println("Entrada invalida.");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error al crear reseña: " + e.getMessage());
        }
    }

    // Metodos de apoyo
    private Administrador autenticarAdmin(String email, String password) {
        return administradores.stream()
                .filter(a -> a.getEmail().equals(email) && a.verificarContraseña(password))
                .findFirst()
                .orElse(null);
    }

    private Usuario autenticarUsuario(String email, String password) {
        return usuariosRegistrados.stream()
                .filter(u -> u.getEmail().equals(email) && u.verificarContraseña(password))
                .findFirst()
                .orElse(null);
    }

    private void registrarUsuario() {
        try {
            System.out.print("\nNombre: ");
            String nombre = scanner.nextLine();
            System.out.print("Email: ");
            String email = scanner.nextLine();
            System.out.print("Contraseña: ");
            String password = scanner.nextLine();
            System.out.print("PIN (4 digitos): ");
            int pin = scanner.nextInt();
            scanner.nextLine();

            // Generar ID unico
            int nuevoId = usuariosRegistrados.size() + 1;
            Usuario nuevoUsuario = new Usuario(nombre, email, password, "usuario", 0.0, nuevoId, pin);
            usuariosRegistrados.add(nuevoUsuario);

            // Registrar la accion de registro
            historial.registrarAccion(nuevoUsuario, "Usuario registrado en el sistema");
            System.out.println("¡Registro exitoso! Ahora puede iniciar sesion");
        } catch (InputMismatchException e) {
            System.out.println("Entrada invalida.");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error al registrar usuario: " + e.getMessage());
        }
    }

    // Metodos de visualizacion
    private void verPaquetes() {
        System.out.println("\n=== TODOS LOS PAQUETES ===");
        controlPaquetes.listarTodosPaquetes().forEach(System.out::println);
    }

    private void verReservas() {
        System.out.println("\n=== TODAS LAS RESERVAS ===");
        controlReservas.listarTodasReservas().forEach(System.out::println);
    }

    private void verReseñas() {
        System.out.println("\n=== TODAS LAS RESEÑAS ===");
        controlReseñas.obtenerTodasLasReseñas().forEach(System.out::println);
    }

    private void verPaquetesUsuario() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();
        System.out.println("\n=== MIS PAQUETES ===");
        List<String> todasReservas = controlReservas.listarReservasUsuario(usuario.getNombre());

        // Filtrar SOLO paquetes
        List<String> paquetes = todasReservas.stream()
                .filter(reserva -> reserva.contains("Descripcion: Reserva de paquete completo:"))
                .collect(Collectors.toList());

        if (paquetes.isEmpty()) {
            System.out.println("No tienes paquetes reservados.");
        } else {
            paquetes.forEach(System.out::println);
        }
    }

    private void verReservasUsuario() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();
        System.out.println("\n=== MIS RESERVAS ===");
        List<String> todasReservas = controlReservas.listarReservasUsuario(usuario.getNombre());

        // Filtrar reservas que NO son paquetes
        List<String> reservas = todasReservas.stream()
                .filter(reserva -> !reserva.contains("Descripcion: Reserva de paquete completo:"))
                .collect(Collectors.toList());

        if (reservas.isEmpty()) {
            System.out.println("No tienes reservas activas.");
        } else {
            reservas.forEach(System.out::println);
        }
    }

    private void realizarReserva() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();

        // 1. Seleccionar destino
        System.out.println("\n=== SELECCIONAR DESTINO ===");
        controlDestinos.listarDestinosDisponibles().forEach(System.out::println);
        System.out.print("ID del destino: ");
        int idDestino = scanner.nextInt();
        scanner.nextLine();

        // 2. Seleccionar servicios extra
        System.out.println("\n=== SERVICIOS DISPONIBLES ===");
        List<ServicioExtra> servicios = controlServicios.obtenerServicios();
        for (int i = 0; i < servicios.size(); i++) {
            System.out.printf("%d. %s - $%.2f%n", i + 1, servicios.get(i).getDescripcion(),
                    servicios.get(i).getPrecio());
        }
        System.out.print("Seleccione servicios (separados por coma): ");
        String[] seleccion = scanner.nextLine().split(",");
        List<ServicioExtra> serviciosSeleccionados = new ArrayList<>();
        for (String s : seleccion) {
            int idx = Integer.parseInt(s.trim()) - 1;
            if (idx >= 0 && idx < servicios.size()) {
                serviciosSeleccionados.add(servicios.get(idx));
            }
        }

        // 3. Fechas
        System.out.print("Fecha de inicio (dd/MM/yyyy): ");
        String fechaInicio = scanner.nextLine();
        System.out.print("Fecha de fin (dd/MM/yyyy): ");
        String fechaFin = scanner.nextLine();

        // 4. Crear reserva
        Reservas reserva = new Reservas();
        reserva.setNombreHotel(controlDestinos.obtenerNombreDestino(idDestino));
        reserva.setTipoReserva("Paquete Completo");
        reserva.setFechaInicio(fechaInicio);
        reserva.setFechaFin(fechaFin);
        reserva.setDescripcion("Servicios: " + serviciosSeleccionados.stream()
                .map(ServicioExtra::getDescripcion)
                .collect(Collectors.joining(", ")));
        reserva.setPrecioTotal(calcularPrecioTotal(idDestino, serviciosSeleccionados));
        reserva.setUsuario(usuario);

        if (controlReservas.agregarReserva(reserva)) {
            System.out.println("¡Reserva realizada con exito!");
            historial.registrarAccion(usuario, "Realizo reserva: " + reserva.getNombreHotel() +
                    " del " + fechaInicio + " al " + fechaFin +
                    " por $" + reserva.getPrecioTotal());
        } else {
            System.out.println("Error al realizar reserva");
        }
    }

    private double calcularPrecioTotal(int idDestino, List<ServicioExtra> servicios) {
        double precioDestino = controlDestinos.obtenerPrecioDestino(idDestino);
        double precioServicios = servicios.stream().mapToDouble(ServicioExtra::getPrecio).sum();
        return precioDestino + precioServicios;
    }

    private Usuario buscarUsuarioPorNombre(String nombre) {
        if (nombre == null || nombre.trim().isEmpty()) {
            return null;
        }

        return usuariosRegistrados.stream()
                .filter(u -> u.getNombre() != null && u.getNombre().equalsIgnoreCase(nombre.trim()))
                .findFirst()
                .orElse(null);
    }

    // Método para ver las reseñas del usuario actual
    private void verReseñasUsuario() {
        try {
            Usuario usuario = (Usuario) sesion.getUsuarioActual();
            System.out.println("\n=== MIS RESEÑAS ===");

            List<String> reseñasUsuario = controlReseñas.obtenerReseñasUsuario(usuario.getNombre());

            if (reseñasUsuario.isEmpty()) {
                System.out.println("No tienes reseñas publicadas.");
            } else {
                for (int i = 0; i < reseñasUsuario.size(); i++) {
                    System.out.println((i + 1) + ". " + reseñasUsuario.get(i));
                    System.out.println("----------------------------------------");
                }
            }
        } catch (Exception e) {
            System.out.println("Error al mostrar reseñas: " + e.getMessage());
        }
    }

    // Método para buscar destinos disponibles
    private void buscarDestinos() {
        try {
            while (true) {
                System.out.println("\n=== BUSCAR DESTINOS ===");
                System.out.println("1. Ver todos los destinos disponibles");
                System.out.println("2. Volver");
                System.out.print("Seleccione: ");

                int opcion = scanner.nextInt();
                scanner.nextLine();

                switch (opcion) {
                    case 1:
                        verTodosLosDestinos();
                        break;
                    case 2:
                        return;
                    default:
                        System.out.println("Opción inválida");
                }
            }
        } catch (InputMismatchException e) {
            System.out.println("Entrada inválida.");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error en búsqueda de destinos: " + e.getMessage());
        }
    }

    // Método auxiliar para mostrar todos los destinos
    private void verTodosLosDestinos() {
        try {
            System.out.println("\n=== DESTINOS DISPONIBLES ===");
            List<String> destinos = controlDestinos.listarDestinosDisponibles();

            if (destinos.isEmpty()) {
                System.out.println("No hay destinos disponibles en este momento.");
            } else {
                for (int i = 0; i < destinos.size(); i++) {
                    System.out.println((i + 1) + ". " + destinos.get(i));
                }
            }

            System.out.println("\nPresione Enter para continuar...");
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Error al mostrar destinos: " + e.getMessage());
        }
    }

    private void gestionarReservasUsuario() {
        Usuario usuario = (Usuario) sesion.getUsuarioActual();
        System.out.println("\n=== GESTIONAR RESERVAS ===");

        // Obtener todas las reservas del usuario (tanto reservas como paquetes)
        List<String> todasReservas = controlReservas.listarReservasUsuario(usuario.getNombre());

        if (todasReservas.isEmpty()) {
            System.out.println("No tienes reservas para gestionar.");
            return;
        }

        // Mostrar todas las reservas numeradas
        System.out.println("Tus reservas:");
        for (int i = 0; i < todasReservas.size(); i++) {
            System.out.println((i + 1) + ". " + todasReservas.get(i));
        }

        System.out.print("\nSeleccione el número de reserva a eliminar (0 para cancelar): ");
        int seleccion = scanner.nextInt();
        scanner.nextLine();

        if (seleccion == 0) {
            return;
        }

        if (seleccion < 1 || seleccion > todasReservas.size()) {
            System.out.println("Selección inválida.");
            return;
        }

        // Extraer ID de la reserva seleccionada
        String reservaSeleccionada = todasReservas.get(seleccion - 1);
        String idReserva = extraerIdReserva(reservaSeleccionada);

        if (idReserva == null) {
            System.out.println("Error: No se pudo obtener el ID de la reserva.");
            return;
        }

        // Confirmar eliminación
        System.out.print("¿Está seguro que desea eliminar esta reserva? (s/n): ");
        String confirmacion = scanner.nextLine();

        if (confirmacion.equalsIgnoreCase("s")) {
            if (controlReservas.eliminarReserva(idReserva)) {
                System.out.println("Reserva eliminada con éxito.");
                historial.registrarAccion(usuario, "Eliminó reserva con ID: " + idReserva);
            } else {
                System.out.println("Error al eliminar la reserva.");
            }
        } else {
            System.out.println("Operación cancelada.");
        }
    }

    // Método auxiliar para extraer ID de reserva
    private String extraerIdReserva(String lineaReserva) {
        try {
            // Formato: "ID: 1 | Hotel: ..."
            int inicio = lineaReserva.indexOf("ID: ") + 4;
            int fin = lineaReserva.indexOf(" |", inicio);
            return lineaReserva.substring(inicio, fin).trim();
        } catch (Exception e) {
            return null;
        }
    }

}