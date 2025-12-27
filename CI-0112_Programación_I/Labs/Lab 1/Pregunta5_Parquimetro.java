import java.util.Scanner;
public class Pregunta5_Parquimetro{
    public static void main (String[]args) {
        Scanner in = new Scanner(System.in);
        //Inicialización de Variables
        int hora_entrada = in.nextInt();
        int mins_entrada = in.nextInt();
        int hora_salida = in.nextInt();
        int mins_salida = in.nextInt();
        in.nextLine(); //Corrector de Problema de Scanner
        String cine = in.nextLine();
        //Inicialización de Contadores
        int salida_correcta = 0;
        int precio = 0;
        int hora_parqueo = 0;
        int hora_cobro =0;
        int día_salida = 1;

        int día_entrada = 1;
        boolean dias_diferentes = false;
        //Validaciones de la entrada
        if (hora_entrada == 2 || hora_entrada == 3 || hora_entrada == 4 ||
                hora_entrada == 5){
            salida_correcta += 1;
        }
        if ((hora_salida == 3 || hora_salida == 4 || hora_salida == 5) ) {
            salida_correcta += 1;
        }
        if (hora_salida == 2 && mins_salida != 0){
            salida_correcta += 1;
        }
        if (mins_entrada < 0 || mins_entrada > 59 || mins_salida < 0 ||
                mins_entrada > 59){
            salida_correcta += 1;
        }
        if (hora_entrada < 0 || hora_entrada > 24 || hora_salida < 0 ||
                hora_entrada > 24){
            salida_correcta += 1;
        }
        if (!cine.equals("SI") && !cine.equals("NO")){
            salida_correcta += 1;
        }
        //Calcular Horas de Parqueo
        //Horas Iguales
        if (hora_entrada == hora_salida && mins_salida > mins_entrada &&
                mins_salida - mins_entrada > 30){
            hora_parqueo = 1;
        }
        if (hora_entrada == hora_salida && mins_salida == mins_entrada){
            hora_cobro = 0;
        }
        if (hora_entrada == hora_salida && mins_salida<mins_entrada){
            salida_correcta += 1;
        }
        //Hora Salida Mayor a Hora Entrada
        if (hora_salida > hora_entrada && mins_salida > mins_entrada){
            hora_parqueo = hora_salida - hora_entrada +1;
        }
        if (hora_salida > hora_entrada && mins_salida == mins_entrada){
            hora_parqueo = hora_salida-hora_entrada;
        }
        if (hora_salida > hora_entrada && mins_salida < mins_entrada){
            hora_parqueo = hora_salida - hora_entrada;
        }
        //Divisor de Días
        if (hora_salida == 0 || hora_salida == 1 || hora_salida == 2){
            día_salida = 2;
        }
        if (hora_entrada == 0 || hora_entrada == 1 || hora_entrada == 2){
            día_entrada = 2;
        }
        if (día_salida != día_entrada){
            dias_diferentes = true;
        }

        //Hora Salida Menor a Hora Entrada
        if (hora_salida < hora_entrada && mins_salida > mins_entrada &&
                dias_diferentes == true){
            hora_parqueo = 24 - hora_entrada + hora_salida + 1;
        }
        if (hora_salida < hora_entrada && mins_salida == mins_entrada &&
                dias_diferentes == true){
            hora_parqueo = 24 - hora_entrada + hora_salida;
        }
        if (hora_salida < hora_entrada && mins_salida < mins_entrada &&
                dias_diferentes == true){
            hora_parqueo = 24 - hora_entrada + hora_salida;
        }
        if (hora_salida < hora_entrada && dias_diferentes == false) {
            salida_correcta += 1;
        }
        //Horas a Cobrar
        if ((hora_parqueo == 3 || hora_parqueo < 3) && cine.equals("SI")){
            hora_cobro = 0;
        }
        if (hora_parqueo > 3 && cine.equals("SI")){
            hora_cobro = hora_parqueo - 3;
        }
        if (hora_parqueo > 3 && cine.equals("NO")){
            hora_cobro = hora_parqueo;
        }
        if (hora_parqueo == 1 && mins_salida > mins_entrada && mins_salida - mins_entrada < 30){
            hora_cobro = 0;
        }
        if (hora_parqueo == 1 && mins_salida < mins_entrada && (60 -
                mins_entrada + mins_salida < 30)){
            hora_cobro = 0;
        }
        if (hora_parqueo < 3 && hora_parqueo > 1 && cine.equals("NO")) {
            hora_cobro = hora_parqueo;
        }

        //Cobro Final si no va al cine
        if (hora_cobro < 4 && cine.equals("NO")){
            precio = 600;
        }
        if (hora_cobro == 0 && cine.equals("NO")){
            precio = 0;
        }
        if (hora_cobro == 4 && cine.equals("NO")){
            precio = 1350;
        }
        if (hora_cobro > 4 && cine.equals("NO")){
            precio = 1350 + (1000 *(hora_cobro-4));
        }
        //Cobro final si va al cine
        if (hora_parqueo < 4 && cine.equals("SI")){
            precio = 0;
        }
        if (hora_parqueo == 4 && cine.equals("SI")){
            precio = 750;
        }
        if (hora_parqueo > 4 && cine.equals("SI")){
            precio = 750 + 1000*(hora_parqueo-4);
        }

        //Salida Final
        if (salida_correcta != 0){
            System.out.println("Entrada invalida");
        }
        else {
            System.out.println(precio);
        }
    }
}