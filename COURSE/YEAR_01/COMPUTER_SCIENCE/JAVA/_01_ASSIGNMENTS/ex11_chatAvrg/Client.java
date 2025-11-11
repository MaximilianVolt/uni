package _01_ASSIGNMENTS.ex11_chatAvrg;



import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;



public class Client
{
  public static void main(String[] args) {
    String server = args.length != 1
      ? "localhost"
      : args[0]
    ;

    try (
      Socket s = new Socket(server, Server.getPort());
      DataOutputStream out = new DataOutputStream(s.getOutputStream())
    ) {
      for (int i = 0; i < 100; ++i) {
        out.writeInt((int) (Math.random() * 1e5 + 1));
        out.flush();
      }

      out.writeInt(-1);
      out.flush();
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }

    System.out.println("ciao sono zio bosco");

    System.out.println(
      "ciao".repeat((int) (Math.random() * 10))
    );
  }  
}
