package _01_ASSIGNMENTS.ex13_chat;

/* ChatClient */
import java.net.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ChatClientFrame extends JFrame implements Runnable, ActionListener {
  protected DataInputStream i = null;
  protected DataOutputStream o = null;
  protected Socket s = null;
  protected String nome = "";
  protected JLabel l;
  protected JTextArea output;
  protected JTextField input;
  DefaultListModel<String> listModel = new DefaultListModel<>();
  protected JList<String> scelta;
  protected Thread ascolta = null;
  protected char separatore = '\n';
  static String host = null;
  static String porta = null;
  volatile boolean continua = true;

  public ChatClientFrame(String titolo) {
    super(titolo);

    JPanel pannello = new JPanel();
    pannello.setLayout(new BorderLayout());

    setFont(new Font("Helvetica", Font.PLAIN, 14));
    setLayout(new BorderLayout());
    output = new JTextArea("", 10, 10);
    JScrollPane sp = new JScrollPane(output);
    add(sp, "Center");
    output.setEditable(false);
    listModel.addElement("Tutti");
    scelta = new JList<String>(listModel);
    scelta.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    scelta.setSelectedIndex(0);
    JScrollPane sp2 = new JScrollPane(scelta);
    pannello.add(sp2, "Center");

    add(pannello, "East");

    l = new JLabel("Destinatario:");
    pannello.add(l, "North");

    input = new JTextField();
    input.setEditable(false);
    input.addActionListener(this);
    add(input, "South");
    ascolta = new Thread(this);
    ascolta.start();
  }

  public void termina() {
    if (ascolta != null)
      continua = false;
    ;
    ascolta = null;
    try {
      if (o != null)
        o.close();
    } catch (IOException ecc) {
      ecc.printStackTrace();
    }
    try {
      if (i != null)
        i.close();
    } catch (IOException ecc) {
      ecc.printStackTrace();
    }
    try {
      if (s != null)
        s.close();
    } catch (IOException ecc) {
      ecc.printStackTrace();
    }
  }

  public void run() {
    try {
      output.append(" G/L Chat di Gentile Francesco e Lucarelli Marco\n\n");
      output.append("Puoi inviare messaggi alla chat scrivendo nella riga in basso e poi battendo INVIO. \n");
      output.append("Puoi scegliere dalla lista a destra il destinatario dei messaggi che invii.\n\n");
      output.append("Connessione al server in corso... ");
      s = new Socket(host, Integer.parseInt(porta));
      i = new DataInputStream(new BufferedInputStream(s.getInputStream()));
      o = new DataOutputStream(new BufferedOutputStream(s.getOutputStream()));
      output.append("ok\n\nScrivi il tuo nome:\n");

      input.setEditable(true);
      input.requestFocus();
      String selezionato = "";
      String riga = "";
      // String str;
      // int primo, prossimo;
      int n;
      String parole[];
      int posizione;
      riga = i.readUTF(); // come primo messaggio il server rimanda il nome eventualmente modificato con
                          // gli asterishi
      nome = riga;
      setTitle("Esempio chat: " + nome);

      while (continua) {
        riga = i.readUTF();
        if (riga.indexOf(separatore) == -1) {
          output.append(riga + '\n');
        } // “marco > Ciao!”
        else { // ”marco si è collegato alla chat\nstefano\nanna\nmarco”
          parole = riga.split("\\n");
          output.append(parole[0] + '\n');
          selezionato = scelta.getSelectedValue();
          listModel.removeAllElements();
          listModel.addElement("Tutti");
          scelta.setSelectedIndex(0);
          posizione = 0;

          for (n = 1; n < parole.length; n++) {
            if (!nome.equals(parole[n])) {
              listModel.addElement(parole[n]);
              posizione++;
              if (parole[n].trim().equals(selezionato.trim()))
                scelta.setSelectedIndex(posizione);
            }
          }
        }
      }
    } catch (Exception ecc) {
      output.append("ERRORE!!!");
      output.append(ecc.getMessage());
      termina();
      return;
    }
  }

  public void actionPerformed(ActionEvent e) {
    if ((e.getSource() instanceof JTextField) && ((JTextField) e.getSource() == input) &&
        (!input.getText().equals(""))) {
      String msg;
      String testo = input.getText();
      if (nome.equals("")) { // il primo messaggio: mando il mio nome
        output.setText("");
        msg = testo;
      } else { // normale messaggio della chat
        output.append("> " + testo + '\n');
        msg = scelta.getSelectedValue() + separatore + testo;
      }
      try {
        o.writeUTF(msg);
        o.flush();
      } catch (IOException ecc) {
      }
      input.setText("");
    }
  }

  public void dispose() {
    termina();
    super.dispose();
  }

  public static void main(String args[]) {
    if (args.length >= 1)
      host = args[0];
    else
      host = "192.168.137.1";
    if (args.length >= 2)
      porta = args[1];
    else
      porta = "3000";
    ChatClientFrame finestra = new ChatClientFrame("Esempio chat");
    finestra.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    finestra.setSize(600, 400);
    finestra.setVisible(true);
  }
}
