package _01_ASSIGNMENTS.ex11_chatAvrg;



import java.net.*;
import java.io.*;



public class Server
{
  private static int port = 9000;
  private static Avrg avrg = new Avrg();



  public static int getPort() {
    return Server.port;
  }



  public static Avrg getAvrg() {
    return Server.avrg;
  }



  public static void main(String[] args) {
    try (ServerSocket ss = new ServerSocket(Server.port)) {
      while (true) {
        new ServerThread(ss.accept()).start();
      }
    }
    catch (IOException e) {
      System.out.println(e.getMessage());
    }
  }
}



class Avrg
{
  private int sum = 0;
  private int count = 0;

  public synchronized void update(int n) {
    sum += n;
    ++count;
  }

  public synchronized double avrg() {
    return count != 0
      ? (double) sum / count
      : 0d
    ;
  }
}
