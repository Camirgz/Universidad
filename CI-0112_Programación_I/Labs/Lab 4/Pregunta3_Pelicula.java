class Pregunta3_Pelicula {
    private String nombre;
    private int ano;
    private double promedioCalificaciones;
    private int cantidadCalificaciones;

    // Constructor de Pelicula
    public Pregunta3_Pelicula(String nombre, int ano, String calificaciones) {
        this.nombre = nombre;
        this.ano = ano;
        this.promedioCalificaciones = calcularPromedio(calificaciones);
        this.cantidadCalificaciones = contarCalificaciones(calificaciones);
    }

    // Método privado para calcular el promedio de calificaciones
    private double calcularPromedio(String calificaciones) {
        String[] calificacionArray = calificaciones.split("-");
        double suma = 0;
        for (String calificacion : calificacionArray) {
            suma += Double.parseDouble(calificacion);
        }
        return suma / calificacionArray.length;
    }

    // Método privado para contar la cantidad de calificaciones
    private int contarCalificaciones(String calificaciones) {
        String[] calificacionArray = calificaciones.split("-");
        return calificacionArray.length;
    }

    // Método para registrar una nueva calificación
    public void registrarCalificacion(double calificacion) {
        promedioCalificaciones = (promedioCalificaciones * cantidadCalificaciones + calificacion) / (cantidadCalificaciones + 1);
        cantidadCalificaciones++;
    }

    // Método para obtener el promedio de calificaciones
    public double obtenerPromedio() {
        return promedioCalificaciones;
    }

    // Método para imprimir los detalles de la película
    public String imprimirPelicula() {
        return nombre + " (" + ano + ") : calificacion " + String.format("%.2f", promedioCalificaciones);
    }
}




