public class Arbol{
    Nodo raiz;
    
    public Nodo getRaiz(){
        return this.raiz;
    }
    
    public class Nodo{
        private Sospechoso sospechoso;
        private int indice_coincidencia;
        private Nodo hijo_izquierda;
        private Nodo hijo_derecha;
        private int lugar;
        
        public int getLugar(){
            return this.lugar;
        }
        
        public void setLugar(int lugar){
            this.lugar = lugar;
        }
        
        public Nodo (String [] informacion){
            this.sospechoso = new Sospechoso (informacion);
        }
        
        public Nodo (Sospechoso sospechoso){
            this.sospechoso = sospechoso;
        }
        
        public Nodo (Sospechoso sospechoso, int indice_coincidencia){
            this.sospechoso = sospechoso;
            this.indice_coincidencia = indice_coincidencia;
        }
        
        public void setHijo_izquierda (Nodo a){
            this.hijo_izquierda = a;
        }
        
        public void setHijo_derecha (Nodo a){
            this.hijo_derecha = a;
        }
        
        public void setIndice_coincidencia (int a){
            this.indice_coincidencia = a;
        }
        
        public Nodo getHijo_izquierda (){
            return this.hijo_izquierda;
        }
        
        public Nodo getHijo_derecha(){
            return this.hijo_derecha;
        }
        
        public Sospechoso getSospechoso (){
            return this.sospechoso;
        }
        
        public void setSospechoso(Sospechoso nuevo){
            this.sospechoso = nuevo;
        }
        
        public int getIndice_Coincidencia(){
            return this.indice_coincidencia;
        }
    }
    
    public void insertar(Sospechoso sospechoso, int indice_coincidencia) {
        
        if (this.raiz == null) {
            this.raiz = new Nodo (sospechoso, indice_coincidencia);
        } else {
            Nodo auxiliar = this.raiz;
            while ((indice_coincidencia <= auxiliar.getIndice_Coincidencia() && auxiliar.getHijo_izquierda() != null) ||
                (indice_coincidencia > auxiliar.getIndice_Coincidencia() && auxiliar.getHijo_derecha() != null)) {
                if (auxiliar.getHijo_izquierda() != null && indice_coincidencia <= auxiliar.getIndice_Coincidencia() ) {
                    auxiliar = auxiliar.getHijo_izquierda();
                } else if (auxiliar.getHijo_derecha() != null && indice_coincidencia > auxiliar.getIndice_Coincidencia()) {
                    auxiliar = auxiliar.getHijo_derecha();
                }
            }
            if ( indice_coincidencia <= auxiliar.getIndice_Coincidencia() ) {
                auxiliar.setHijo_izquierda( new Nodo(sospechoso, indice_coincidencia));
            }
            else if ( indice_coincidencia > auxiliar.getIndice_Coincidencia() ) {
                auxiliar.setHijo_derecha( new Nodo(sospechoso, indice_coincidencia) );
            }
        }
    }

    public void eliminar(int contadorTemporal) {
        this.raiz = eliminarInterno(raiz, contadorTemporal);
        actualizarContadores();
    }
    
    private Nodo eliminarInterno(Nodo nodo, int contadorTemporal) {
        if (nodo == null) {
            return nodo;
        }
    
        if (contadorTemporal > nodo.getLugar()) {
            nodo.setHijo_izquierda(eliminarInterno(nodo.getHijo_izquierda(), contadorTemporal));
        } else if (contadorTemporal < nodo.getLugar()) {
            nodo.setHijo_derecha(eliminarInterno(nodo.getHijo_derecha(), contadorTemporal));
        } else {
            if (nodo.getHijo_izquierda() == null) {
                return nodo.getHijo_derecha(); // Caso sin hijo izquierdo
            } else if (nodo.getHijo_derecha() == null) {
                return nodo.getHijo_izquierda(); // Caso sin hijo derecho
            }
    
            Nodo sucesor = buscarHijoExtremoIzquierda(nodo.getHijo_derecha());
            nodo.setSospechoso(sucesor.getSospechoso());
            nodo.setIndice_coincidencia(sucesor.getIndice_Coincidencia());
    
            nodo.setHijo_derecha(eliminarInterno(nodo.getHijo_derecha(), sucesor.getLugar()));
        }
        return nodo;
    }
    
    public Nodo buscarHijoExtremoIzquierda(Nodo inicio){
        
        if (inicio.getHijo_izquierda() != null){
            inicio = buscarHijoExtremoIzquierda (inicio);
        }
        
        return inicio;
    }
    
    public Nodo buscarHijoExtremoDerecha(Nodo inicio){
        if (inicio.getHijo_izquierda() != null){
            inicio = buscarHijoExtremoDerecha (inicio);
        }
        
        return inicio;
    }
    
    public void actualizarContadores() {
        contadorTemporal = 0; // Reiniciar el contador temporal a cero
        actualizarContadoresInterno(raiz); // Llama al método interno para actualizar los contadores
    }
    
    private int contadorTemporal;
    
    private void actualizarContadoresInterno(Nodo nodo) {
        if (nodo != null) {
            actualizarContadoresInterno(nodo.getHijo_derecha());
            nodo.setLugar(++contadorTemporal);
            actualizarContadoresInterno(nodo.getHijo_izquierda());
        }
    }
    
    private void imprimirInterno (Nodo inicio) {
            
        if (inicio.getHijo_derecha() != null) {
            imprimirInterno (inicio.getHijo_derecha());
        }
        
        System.out.println("-" + inicio.getLugar() + "-------------------------------------------");
        inicio.getSospechoso().imprimirSospechoso();
        
        if (inicio.getHijo_izquierda() != null) {
            imprimirInterno (inicio.getHijo_izquierda());
        }
    }
    
    private Nodo buscarNodoInterno (Nodo inicio, int lugar){
        if (inicio.getHijo_derecha() != null) {
            if (inicio.getLugar() == lugar){
                return inicio;
            }
        }
        else if (inicio.getHijo_izquierda() != null) {
            if (inicio.getLugar() == lugar){
                return inicio;
            }
        }
        else{
            return inicio;
        }
        return null;
    }
    
    public Nodo buscarNodo (int lugar){
        return buscarNodoInterno(this.raiz, lugar);
    }
    
    public int getContadorTemporal(){
        return this.contadorTemporal;
    }
    
        public void asignarLugar (Nodo inicio) {
            
        if (inicio.getHijo_derecha() != null) {
            asignarLugar (inicio.getHijo_derecha());
        }
        
        contadorTemporal++;
        inicio.setLugar(contadorTemporal);
        
        if (inicio.getHijo_izquierda() != null) {
            asignarLugar (inicio.getHijo_izquierda());
        }
    }
    
    public void imprimir () {
        if (this.raiz != null) {
            this.imprimirInterno(this.raiz);
        } else {
            System.out.println("No hay ningún sospechoso");
        }
    }
    
    public boolean compararArray(String [] array1, String [] array2){
        boolean igual = true;
        
        if (array1.length!=array2.length){
            igual = false;
        } else{
            for (int i = 0; i<array1.length; i++){
                if (!array1[i].equals(array2[i])){
                    igual = false;
                }
            }
        }
        return igual;
    }
}
