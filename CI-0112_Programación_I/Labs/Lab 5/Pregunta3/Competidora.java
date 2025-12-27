package Pregunta3;

class Competidora{
    private String cedula;
    private String nombre;
    private String edad;
    private String id;

    Competidora(String cedula, String nombre, String edad){
        this.cedula = cedula;
        this.nombre = nombre;
        this.edad = edad;
    }

    public String getCedula(){
        return this.cedula;
    }

    public void imprimirCompetidora(){
        System.out.println(nombre + "(ced. " + cedula + ", edad " + edad + ")");
    }
}