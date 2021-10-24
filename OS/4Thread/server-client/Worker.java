import java.util.*;
import java.io.*;
import java.net.*;


public class Worker implements Runnable {
    protected Socket socket;

    public Worker(Socket socket) {
        this.socket = socket;
    }

    private int[] parseCountsContext(String ctx) {
        int[] counts = {0, 0};
    
        for (int i = 0; i < ctx.length(); i++) {
            if (Character.isDigit(ctx.charAt(i)))
                counts[0]++;
            else
                counts[1]++;
        }
    
        return counts;
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
            String context = br.readLine();
            String response;

            int[] counts = this.parseCountsContext(context);
            response = "Context: " + context + "\tDigits: " + counts[0] + "\tCharacters: " + counts[1];

            System.out.println(response);

            this.socket.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
