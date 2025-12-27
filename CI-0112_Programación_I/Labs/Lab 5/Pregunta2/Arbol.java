package Pregunta2;

class Arbol{
    Nodo raiz;

    class Nodo{
        int etiqueta;
        Nodo derecho;
        Nodo izquierdo;

        public Nodo (int etiqueta){
            this.etiqueta = etiqueta;
        }

        public int getEtiqueta(){
            return this.etiqueta;
        }

        public Nodo getDerecho(){
            return this.derecho;
        }

        public Nodo getIzquierdo(){
            return this.izquierdo;
        }

        public void setDerecho(Nodo derecho){
            this.derecho = derecho;
        }

        public void setIzquierdo (Nodo izquierdo){
            this.izquierdo = izquierdo;
        }

    }

    public void insertar(int etiqueta){
        if (raiz == null){
            raiz = new Nodo (etiqueta);
        } else{
            Nodo auxiliar = raiz;

            while (etiqueta <= auxiliar.getEtiqueta() && auxiliar.getIzquierdo() != null || etiqueta > auxiliar.getEtiqueta() && auxiliar.getDerecho() != null){

                if (etiqueta <= auxiliar.getEtiqueta() && auxiliar.getIzquierdo() != null){
                    auxiliar = auxiliar.getIzquierdo();
                }
                else if (etiqueta > auxiliar.getEtiqueta() && auxiliar.getDerecho() != null){
                    auxiliar = auxiliar.getDerecho();
                }

            }

            if (etiqueta <= auxiliar.getEtiqueta()){
                auxiliar.setIzquierdo(new Nodo (etiqueta));
            }

            else if (etiqueta > auxiliar.getEtiqueta()){
                auxiliar.setDerecho(new Nodo (etiqueta));
            }

        }
    }

    private void imprimirInterno(Nodo raiz){
        if (raiz.derecho!=null){
            imprimirInterno(raiz.getDerecho());
        }
        System.out.println(raiz.getEtiqueta());
        if (raiz.izquierdo!=null){
            imprimirInterno(raiz.getIzquierdo());
        }
    }

    public void imprimir(){
        imprimirInterno(this.raiz);
    }

}
