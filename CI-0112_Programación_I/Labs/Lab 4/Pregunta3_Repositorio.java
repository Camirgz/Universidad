import java.util.HashMap;
import java.util.Map;

class Pregunta3_Repositorio {
    private String nombreRepositorio;
    private Map<String, Pregunta3_Pelicula> peliculas;

    // Constructor de Repositorio
    public Pregunta3_Repositorio(String nombreRepo, String[] datosPeliculas) {
        this.nombreRepositorio = nombreRepo;
        this.peliculas = new HashMap<>();

        // Inicializa el repositorio a partir de los datos del archivo
        for (String datoPelicula : datosPeliculas) {
            String[] partes = datoPelicula.split("#");
            if (partes.length == 3) {
                int id = Integer.parseInt(partes[0]);
                String[] nombreAno = partes[1].split("\\(");
                String nombrePelicula = nombreAno[0].trim();
                int anoPelicula = Integer.parseInt(nombreAno[1].split("\\)")[0]);
                String calificaciones = partes[2];

                Pregunta3_Pelicula pelicula = new Pregunta3_Pelicula(nombrePelicula, anoPelicula, calificaciones);
                peliculas.put(nombrePelicula, pelicula);
            }
        }
    }

    // Método para registrar una calificación
    public void registrarCalificacion(String nombrePelicula, double calificacion) {
        Pregunta3_Pelicula pelicula = peliculas.get(nombrePelicula);
        if (pelicula != null) {
            pelicula.registrarCalificacion(calificacion);
        } else {
            System.out.println("La película no existe en el repositorio.");
        }
    }

    // Método para imprimir información de una película
    public void imprimirInformacion(String nombrePelicula) {
        Pregunta3_Pelicula pelicula = peliculas.get(nombrePelicula);
        if (pelicula != null) {
            System.out.println(pelicula.imprimirPelicula());
        } else {
            System.out.println("La película no existe en el repositorio.");
        }
    }

    // Método para obtener el promedio general de todas las películas en el repositorio
    public double obtenerPromedioGeneral() {
        double sumaPromedios = 0.0;
        int cantidadPeliculas = peliculas.size();
        for (Pregunta3_Pelicula pelicula : peliculas.values()) {
            sumaPromedios += pelicula.obtenerPromedio();
        }
        return sumaPromedios / cantidadPeliculas;
    }
}