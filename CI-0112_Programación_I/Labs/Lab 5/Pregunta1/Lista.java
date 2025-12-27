package Pregunta1;

class Lista{
    private Nodo cabeza;

    public Nodo getCabeza(){
        return this.cabeza;
    }

    public void AgregarNodoArriba(String nombre){
        if (this.cabeza == null){
            this.cabeza = new Nodo (nombre);
        }

        else{
            Nodo auxiliar = cabeza;
            if (!repetido(nombre)){
                cabeza = new Nodo (nombre);
                cabeza.setSiguiente(auxiliar);
            }

        }
    }

    public void AgregarNodoFinal(String nombre){
        if (this.cabeza == null){
            this.cabeza = new Nodo(nombre);
        }

        else{
            Nodo anterior = cabeza;
            while (anterior.getSiguiente()!= null){
                anterior = anterior.getSiguiente();
            }

            anterior.setSiguiente(new Nodo (nombre));
        }
    }

    public boolean repetido(String nombre){
        boolean repetido = false;

        Nodo auxiliar = cabeza;
        while (auxiliar!=null){
            if (auxiliar.getNombre().equals(nombre)){
                repetido = true;
                break;
            } else{
                auxiliar = auxiliar.getSiguiente();
            }
        }

        return repetido;
    }

    public void imprimirListaOrdenado(){
        Nodo auxiliar = cabeza;
        if (auxiliar == null){
            System.out.println("Lista vacía");
        }

        else{
            while(auxiliar.getSiguiente()!=null){
                System.out.println(auxiliar.getNombre());
                auxiliar = auxiliar.getSiguiente();
            }

            System.out.println(auxiliar.getNombre());
        }
    }
}

