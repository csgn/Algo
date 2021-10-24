import java.nio.charset.Charset;
import java.io.*;
import java.util.*;
import java.net.*;

public class Client {
    private Socket socket;
    private String context;

    public Client() {
        this.context = this._generateString();
    }

    public void createSocket() {
        try {
            this.socket = new Socket("localhost", 6100);
        } catch (Exception e) { System.out.println(e);}
    }

    public String getContext() {
        return this.context;
    }

    private String _generateString() {
        return UUID.randomUUID().toString().replace("-", "");
    }

    public void start() {
        this.createSocket();

        try {
            PrintStream ps = new PrintStream(this.socket.getOutputStream());
            //BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            //ps.print(br.readLine());
            ps.print(this.context);
            
        } catch (Exception e) {System.out.println(e);}
    }

    public void close() throws IOException {
        this.socket.close();
    }
}
