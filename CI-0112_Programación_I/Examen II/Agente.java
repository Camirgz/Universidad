public class Agente {
    String IdAgente;
    String todas_sus_ventas = "";

    public Agente(String IdAgente, String venta) {
        this.IdAgente = IdAgente;
        this.todas_sus_ventas = venta;
    }

    public void AgregarVenta(String venta) {
        this.todas_sus_ventas = this.todas_sus_ventas + "/" + venta;
    }

    public String[] getVentas() {
        return todas_sus_ventas.split("/");
    }

    public String getIdAgente() {
        return this.IdAgente;
    }

    public String top3() {
        String[] ventas = todas_sus_ventas.split("/");
        double[] top3 = new double[]{0.0, 0.0, 0.0};

        for (int i = 0; i < ventas.length; i++) {
            String[] partes = ventas[i].split(";");
            double precio = Double.parseDouble(partes[4]);
            formarTop(precio, top3);
        }

        String resultado = "";
        for (int i = 0; i < top3.length; i++) {
            if (top3[i] != 0.0) {
                if (!resultado.isEmpty()) {
                    resultado += ", ";
                }
                resultado += redondeo(top3[i]);
            }
        }

        return resultado;
    }

    public String gananciasTotales() {
        double gananciasTotales = 0.0;
        String[] ventas = todas_sus_ventas.split("/");
        for (int i = 0; i < ventas.length; i++) {
            String[] partes = ventas[i].split(";");
            double porcentaje = Double.parseDouble(partes[6]);
            double precio = Double.parseDouble(partes[4]);
            gananciasTotales = gananciasTotales + (porcentaje * precio / 100.00);
        }

        return redondeo(gananciasTotales);
    }

    public String ventasTotales() {
        double ventasTotales = 0.0;
        String[] ventas = todas_sus_ventas.split("/");
        for (int i = 0; i < ventas.length; i++) {
            String[] partes = ventas[i].split(";");
            double ventaActual = Double.parseDouble(partes[4]);
            ventasTotales = ventasTotales + ventaActual;
        }

        return redondeo(ventasTotales);
    }

    public String redondeo(double numero) {
        return String.format("%.2f", numero);
    }

    public void formarTop(double precio, double[] top3) {
        // Tercer Lugar
        if (precio >= top3[2] || top3[2] == 0) {
            top3[0] = top3[1];
            top3[1] = top3[2];
            top3[2] = precio;
        }
        // Segundo Lugar
        else if (precio >= top3[1] || top3[1] == 0) {
            top3[0] = top3[1];
            top3[1] = precio;
        }
        // Primer Lugar
        else if (precio >= top3[0] || top3[0] == 0) {
            top3[0] = precio;
        }
    }
}
