package _01_ASSIGNMENTS.ex12_trivia;

import java.io.*;
import java.net.*;

public class Trivia {
  public static void main(String[] args) {
    final int PORTNUM = 1234;
    Socket socket = null;
    DataInputStream in = null;
    DataOutputStream out = null;
    String address = "192.168.137.1";
    // Check the command-line args for the host address
    if (args.length != 1) {
      System.out.println("Usage: java Trivia <address>");
    } else
      address = args[0];
    // Initialize the socket and streams
    try {
      socket = new Socket(address, PORTNUM);
      in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
      out = new DataOutputStream(new BufferedOutputStream(socket.getOutputStream()));
    } catch (IOException e) {
      System.err.println("Exception: couldn't create stream socket");
      System.exit(1);
    }
    // Process user input and server responses
    try {
      StringBuffer str = new StringBuffer(128);
      String inStr;
      int c;
      while ((inStr = in.readUTF()) != null) { // usa caratteri UNICODE
        System.out.println("Server: " + inStr);
        if (inStr.equals("Bye."))
          break;
        while ((c = System.in.read()) != '\n')
          str.append((char) c);
        System.out.println("Client: " + str);
        out.writeUTF(str.toString()); // usa caratteri UNICODE
        out.flush();
        str.setLength(0);
      }
      // Cleanup
      out.close();
      in.close();
      socket.close();
    } catch (IOException e) {
      System.err.println("Exception: I/O error trying to talk to server");
    }
  }
}
