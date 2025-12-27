package Pregunta1;

class Interaccion{
    Scanner in = new Scanner (System.in);
    Lista nombresDesordenados = new Lista();

    public void cargarInformacion(){
        while (in.hasNext()){

            String linea = in.nextLine();
            nombresDesordenados.AgregarNodoArriba(linea);

        }
    }

    public void imprimirInformacion(){
        Lista ordenada = new Lista();

        if (nombresDesordenados.getCabeza() == null){
            System.out.println("La lista está vacía");
        }

        else{

            Nodo auxiliar = nombresDesordenados.getCabeza();

            while (auxiliar!=null){
                if (!ordenada.repetido(auxiliar.getNombre())){
                    ordenada.AgregarNodoFinal(auxiliar.getNombre());
                }

                auxiliar = auxiliar.getSiguiente();
            }
        }

        ordenada.imprimirListaOrdenado();

    }
}
