package _01_ASSIGNMENTS.ex11_chatAvrg;



import java.io.DataInputStream;
import java.net.Socket;



/**
 * The server must calculate:
 * - The average of the even values received by all clients
 * - The average of the odd values received by each client
 */

public class ServerThread extends Thread
{
  Socket socket = null;

  public ServerThread(Socket socket) {
    this.socket = socket;
  }



  @Override
  public void run()
  {
    int sum = 0, count = 0, read;
    Avrg avrg = Server.getAvrg();

    try (DataInputStream in = new DataInputStream(socket.getInputStream())) {
      while ((read = in.readInt()) >= 0) {
        if ((read & 1) == 1) {
          sum += read;
          count++;
        }
        else {
          avrg.update(read);
        }
      }
    }
    catch (Exception e) {
      System.out.println(e.getMessage());
    }

    System.out.printf("Global even numbers' average is: %.2f\n", avrg.avrg());
    System.out.printf("The average of the client's odd numbers is: %.2f\n",
      count != 0
        ? (double) sum / count
        : 0d
    );
  }
}
