import java.io.*;

public class _3ChildProcess {
    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.err.println("Error");
            System.exit(0);
        }

        ProcessBuilder pb = new ProcessBuilder(args[0]);
        Process process = pb.start();

        InputStream is = process.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        BufferedReader br = new BufferedReader(isr);

        String line;
        while ((line = br.readLine()) != null)
            System.out.println(line);

        br.close();
    }
}
