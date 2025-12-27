package Pregunta3;

class Lista{
    Nodo cabeza;

    class Nodo{
        private Competidora competidora;
        private Nodo siguiente;

        public Nodo (Competidora competidora){
            this.competidora = competidora;
        }

        public Competidora getCompetidora(){
            return this.competidora;
        }

        public Nodo getSiguiente(){
            return this.siguiente;
        }

        public void setSiguiente(Nodo siguiente){
            this.siguiente = siguiente;
        }
    }

    public void agregar(Competidora competidora){
        if (cabeza==null){
            cabeza = new Nodo(competidora);
        } else{
            Nodo auxiliar = cabeza;
            while(auxiliar.getSiguiente()!=null){
                auxiliar = auxiliar.getSiguiente();
            }

            auxiliar.setSiguiente(new Nodo (competidora));
        }
    }

    public void eliminar(String cedula){
        if (cabeza!=null){
            if (cabeza.getCompetidora().getCedula().equals(cedula)){
                this.cabeza = cabeza.getSiguiente();
            } else{
                Nodo auxiliar = cabeza;
                while(auxiliar!=null && auxiliar.getSiguiente()!=null){
                    if (auxiliar.getSiguiente().getCompetidora().getCedula().equals(cedula)){
                        auxiliar.setSiguiente(auxiliar.getSiguiente().getSiguiente());
                        break;
                    }
                    auxiliar = auxiliar.getSiguiente();
                }
            }
        }
    }

    public void imprimir(){
        Nodo auxiliar = cabeza;
        int contador = 1;
        while(auxiliar!=null){
            System.out.print("#" + contador + " ");
            contador++;
            auxiliar.getCompetidora().imprimirCompetidora();
            auxiliar = auxiliar.getSiguiente();
        }
    }

}
