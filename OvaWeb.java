import java.io.*;

public class OvaWeb {
    public static void main(String[] args) throws IOException, InterruptedException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Ingresa el comando permitido (git, touch, nano, mkdir): ");
        String comando = br.readLine();

        // Ejecutar el programa en C pasándole el comando
        ProcessBuilder pb = new ProcessBuilder("./ejecutable", comando);
        pb.inheritIO(); // Esto ya mostrará la salida del proceso C
        Process p = pb.start();
        p.waitFor(); // Esperar a que termine el proceso

        // Leer el archivo de salida creado por el programa en C
        File archivo = new File("resultado_comando.txt");
        if (!archivo.exists()) {
            System.out.println("No se encontró el archivo con la salida del comando.");
            return;
        }

        System.out.println("=== Salida del comando en AWS ===");
        try (BufferedReader reader = new BufferedReader(new FileReader(archivo))) {
            String linea;
            while ((linea = reader.readLine()) != null) {
                System.out.println(linea);
            }
        }
    }
}

