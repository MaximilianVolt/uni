package _01_ASSIGNMENTS.ex10_chatLength;



import java.io.IOException;
import java.io.PrintWriter;
import java.net.*;



public class ServerThread extends Thread
{
  Socket socket;
  public static final String TRANSMISSION_CODE_OVER = "OVER";

  public ServerThread(Socket socket) {
    this.socket = socket;
  }


  @Override
  public void run() {
    try (
      PrintWriter out = new PrintWriter(socket.getOutputStream(), true)
    ) {
      for (int i = 0; i < Server.getRandom(); ++i)
        out.printf("Message_%d\n", i);

      out.println(ServerThread.TRANSMISSION_CODE_OVER);
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }
}
