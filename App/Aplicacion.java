package App;

import javax.swing.*;

public class Aplicacion {

    static {
        System.load("/home/andres/Descargas/programming/Ova-Web-bueno-telojuro/App/libovaweb.so");
    }

    public native String ejecutarComandosGit(String IP, String rutaKey, String comando);

    public static void main(String[] args) {
        Aplicacion e = new Aplicacion();
        String pepe = JOptionPane.showInputDialog("digite comando:\n");
        String resultado = e.ejecutarComandosGit("3.138.123.82", "/home/andres/Descargas/keys/id_rsa.pem", pepe);
        System.out.println(resultado);
    }
}

