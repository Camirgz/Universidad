import java.util.Scanner;

public class Interaccion {
    Agente[] agentes = new Agente[1000];
    int cantidadAgentes = 0;
    String errores = "";
    int cantidadErrores;

    public Interaccion() {
        CargarInformacion();
        Imprimir();

        if (cantidadErrores > 0) {
            System.out.println("\n--- Errores de formato ---");
            System.out.println("El archivo presenta " + cantidadErrores + " líneas con errores de formato: " + errores + ".");
        }
    }

    public void CargarInformacion() {
        Scanner in = new Scanner(System.in);

        int cantidad_lineas = 0;

        String primera_linea = in.nextLine();
        String entero = primera_linea;

        while (in.hasNext()) {
            String linea = in.nextLine();
            entero = entero + "/" + linea;
        }

        in.close();

        String[] lineas = entero.split("/");

        for (int i = 0; i < lineas.length; i++) {
            String[] partes = lineas[i].split(";");
            int validaciones = 0;
            cantidad_lineas++;

            if (partes.length != 7) {
                validaciones++;
            } else {
                try {
                    Integer.parseInt(partes[3]);
                    Double.parseDouble(partes[4]);
                    Double.parseDouble(partes[6]);
                } catch (NumberFormatException error) {
                    validaciones++;
                }
            }

            if (validaciones != 0) {
                if (errores.equals("")) {
                    errores = errores + cantidad_lineas;
                    cantidadErrores++;
                } else {
                    errores = errores + ", " + cantidad_lineas;
                    cantidadErrores++;
                }
            } else if (validaciones == 0) {
                boolean exito = false;

                for (int j = 0; j < cantidadAgentes; j++) {
                    if (agentes[j] != null && agentes[j].getIdAgente().equals(partes[5])) {
                        agentes[j].AgregarVenta(lineas[i]);
                        exito = true;
                        break;
                    }
                }

                if (!exito) {
                    agentes[cantidadAgentes] = new Agente(partes[5], lineas[i]);
                    cantidadAgentes++;
                }
            }
        }
    }

    public void Imprimir() {
        System.out.println("A CONTINUACION SE MUESTRA LA INFORMACION DE AGENTES:");

        for (int i = 0; i < cantidadAgentes; i++) {
            if (agentes[i] != null) {
                System.out.println("\n--- Agente " + agentes[i].getIdAgente() + " ---");
                System.out.println("Ventas totales: " + agentes[i].ventasTotales() + " USD");
                System.out.println("Monto pagado en comisiones: " + agentes[i].gananciasTotales() + " USD");
                System.out.println("Su top 3 de ventas: " + agentes[i].top3() + " USD");
            }
        }
    }
}
