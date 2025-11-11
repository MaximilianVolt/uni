package _01_ASSIGNMENTS.ex10_chatLength;



import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;



public class Server
{
  private static int random;
  private static final int port = 9000;



  public static int getRandom() {
    return Server.random;
  }



  public static int getPort() {
    return Server.port;
  }


  public static void main(String[] args) {
    try (ServerSocket ss = new ServerSocket(Server.port)) {
      random = (int) (Math.random() * 4950 + 50);

      System.out.printf("RANDOM property now equals %d\n", random);

      while (true) {
        Socket clientSocket = ss.accept();
        ServerThread serverThread = new ServerThread(clientSocket);
        serverThread.start();
      }
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }  
}
