import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        ArrayList<Client> clients = new ArrayList<Client>();

        for (int i = 0; i < 1000; i++) {
            Client client = new Client();
            clients.add(client);
        }
    }
}
