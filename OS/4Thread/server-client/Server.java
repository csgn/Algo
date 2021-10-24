import java.io.*;
import java.net.*;
import java.util.*;



public class Server implements Runnable {
    private ServerSocket serverSocket;
    private int port;
    private boolean isRunning;

    public Server(int port) {
        this.port = port;
    }

    public void run() {
        this.startServerSocket();
        this.isRunning = true;

        Socket socket;
        while (this.isRunning) {
		    try {
                socket = this.serverSocket.accept();
	        } catch (Exception e) {System.out.println("Server Error: " + e); break;}

            new Thread(new Worker(socket)).start();
        }

        System.out.println("Server stopped");
    }

    private void startServerSocket() {
        try {
            this.serverSocket = new ServerSocket(this.port);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) throws IOException {
        try {
            new Thread(new Server(6100)).start();
        } catch (Exception e) {
            e.printStackTrace();
        }
	}
}
