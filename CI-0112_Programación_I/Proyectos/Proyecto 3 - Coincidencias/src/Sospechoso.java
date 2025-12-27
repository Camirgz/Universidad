public class Sospechoso{
    private String nombre;
    private String provincia;
    private String canton;
    private int edad;
    private String genero;
    private String estadoCivil;
    private String pelo;
    private int altura;
    
    public Sospechoso (String [] informacion){
        this.nombre = informacion[0];
        this.provincia = informacion[1];
        this.canton = informacion[2];
        int edad = Integer.parseInt(informacion[3]);
        this.edad = edad;
        this.genero = informacion[4];
        this.estadoCivil = informacion[5];
        this.pelo = informacion[6];
        int altura = Integer.parseInt(informacion[7]);
        this.altura = altura;
    }
    
    public void imprimirSospechoso(){
        System.out.println("Nombre: " + nombre + "\nResidencia: " + provincia + ", " + canton + "\nEdad: " + edad + ", genero: " + genero + "\nEstado Civil: " + estadoCivil + "\nColor de Pelo: " + pelo + ", altura: " + altura);
    }
    
    public String getNombre(){
        return nombre;
    }
    
    public String getProvincia(){
        return provincia;
    }
    
    public String getCanton(){
        return canton;
    }
    
    public int getEdad(){
        return edad;
    }
    
    public String getGenero(){
        return genero;
    }
    
    public String getEstadoCivil(){
        return estadoCivil;
    }
    
    public String getPelo(){
        return pelo;
    }
    
    public int getAltura(){
        return altura;
    }
}
