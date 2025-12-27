public class Aerolinea{
    private String nombre;
    private String [] ciudadesOperando;
    private String [] vuelos;
    private Vuelo [][][] matriz;
    
        public Aerolinea(String nombre, String[] datos) {
        this.nombre = nombre;
        this.vuelos = new String[datos.length];
        String ciudadesOperandoStr = "";

        for (int i = 0; i < datos.length; i++) {
            this.vuelos[i] = datos[i];
            String[] partes = datos[i].split(",");
            ciudadesOperandoStr = agregarCiudad(ciudadesOperandoStr, partes[1]);
            ciudadesOperandoStr = agregarCiudad(ciudadesOperandoStr, partes[2]);
        }
        
        // Convertir ciudadesOperandoStr a un array
        ciudadesOperando = ciudadesOperandoStr.split(",");
        
        CargarMatriz();
    }

    private String agregarCiudad(String ciudadesStr, String ciudad) {
        // Verificar si la ciudad ya está en ciudadesOperando
        if (contieneCiudad(ciudadesStr, ciudad)==false) {
            ciudadesStr += ciudad + ",";
        }
        return ciudadesStr;
    }

    private boolean contieneCiudad(String ciudadesStr, String ciudad) {
        // Verificar si ciudadesStr contiene la ciudad
        String[] ciudades = ciudadesStr.split(",");
        for (String c : ciudades) {
            if (c!=null && c.equals(ciudad)) {
                return true;
            }
        }
        return false;
    }
    
    public void CargarMatriz(){
        matriz = new Vuelo [ciudadesOperando.length][ciudadesOperando.length][150];
        int vuelos_inicializados = 0;
        
        for (int num_vuelo = 0; num_vuelo<vuelos.length; num_vuelo++){
            
            String [] partes = vuelos[num_vuelo].split(",");
            
            for (int i = 0; i<ciudadesOperando.length; i++){
                if (partes [1].equals(ciudadesOperando[i])){
                        for (int j = 0; j<ciudadesOperando.length; j++){
                        if (partes [2].equals(ciudadesOperando[j])){
                            
                            String precio_str = partes[0];
                            double precio = Double.parseDouble(precio_str);
                            
                            String asientos_str = partes[8];
                            int asientos = Integer.parseInt(asientos_str);
                            
                            matriz[i][j][vuelos_inicializados] = new Vuelo (precio, partes [1], partes[2], partes[3], partes[4], partes[5], partes[6], partes[7], asientos);
                            vuelos_inicializados++;
                            
                        }
                    }  
                }
            }
        }
    }
    
    public String VueloDirecto(String ciudadSalida, String ciudadLlegada, String fechaSalida){
        double precio_mas_barato = Double.MAX_VALUE;
        int indice_vuelo_mas_barato = -1;
        int indice_ciudad_salida = -1;
        int indice_ciudad_llegada = -1;
        
        for (int i = 0; i<ciudadesOperando.length; i++){
            if (ciudadSalida.equals(ciudadesOperando[i])){
                indice_ciudad_salida = i;
                for (int j = 0; j<ciudadesOperando.length; j++){
                    if (ciudadLlegada.equals(ciudadesOperando[j])){
                        indice_ciudad_llegada = j;
                        for (int k = 0; k<150; k++){
                            if (matriz[i][j][k] != null && matriz[i][j][k].getFechaSalida().equals(fechaSalida)){
                                if (matriz[i][j][k].getPrecio()<precio_mas_barato){
                                    precio_mas_barato = matriz[i][j][k].getPrecio();
                                    indice_vuelo_mas_barato = k;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        if (indice_vuelo_mas_barato == -1){
            return null;
        }
        else{
            return this.nombre.substring(0,this.nombre.length()-4) + "\n" + matriz[indice_ciudad_salida][indice_ciudad_llegada][indice_vuelo_mas_barato].imprimirVuelo();
        }
    }
    
    public void VueloEscalas(String ciudadSalida, String ciudadLlegada, String fechaSalida){
        
    }
}
