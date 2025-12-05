package _01_ASSIGNMENTS.ex10_chatLength;

import java.net.Socket;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Client
{
  public static void main(String[] args) {
    String server;

    server = args.length == 1
      ? args[0]
      : "localhost"
    ;

    try (
      Socket clientSocket = new Socket(server, Server.getPort());
      BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))
    ) {
      String line;
      int length = 0;

      while ((line = in.readLine()) != null) {
        if (line.trim().equalsIgnoreCase(ServerThread.TRANSMISSION_CODE_OVER))
          break;

        length += line.length();
      }

      System.out.printf("The length of the messages read is: %d\n", length);
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }
}
