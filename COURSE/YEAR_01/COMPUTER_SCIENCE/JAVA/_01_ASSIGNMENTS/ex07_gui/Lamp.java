package _01_ASSIGNMENTS.ex07_gui;



import java.awt.*;
import javax.swing.*;



public class Lamp extends javax.swing.JFrame
{
  public Lamp(String title)
  {
    super(title);
    add(new LampPanel());
  }

  public static void main(String[] args)
  {
    Lamp window = new Lamp("App");

    Dimension screenDimension = Toolkit.getDefaultToolkit().getScreenSize();
    int w = 400
      , h = 400
      , x = (screenDimension.width >> 1) - w / 2
      , y = (screenDimension.height >> 1) - h / 2
    ;

    Math.pow(x, y);

    window.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    window.setBounds(x, y, w, h);
    window.setVisible(true);
  }
}



class LampPanel extends JPanel
{
  public void paintComponent(Graphics g)
  {
    setBackground(Color.WHITE);
    super.paintComponent(g);
    g.setColor(Color.BLACK);

    Dimension windowSize = getSize();

    int w = windowSize.width
      , h = windowSize.height
    ;

    /// Lamp shape

    // Lamp base
    int lampBaseHeight = 42
      , lampBaseYoffset = h - lampBaseHeight
    ;

    g.fillRect(0, lampBaseYoffset, w, lampBaseHeight);

    // Lamp stem
    int lampStemWidth = 50
      , lampWidth = 100
      , lampHeight = 120
      , lampTop = lampBaseYoffset - lampHeight
      , lampStemHeight = 80
      , lampXcenter = w / 2
      , lampXoffset = lampXcenter - lampStemWidth / 2
      , lampShadeWidth = 110
      , lampShadeHeight = 50
      , lampShadeYoffset = lampBaseHeight / 2 
      , lampShadesYdiff = 75
      , lampShadeYbase = lampBaseYoffset - lampBaseHeight - lampShadeYoffset - lampShadeHeight / 2
      , lampDotRadius = 40
      // , lampYoffset = 0
    ;

    g.drawLine(lampXoffset            , lampBaseYoffset, lampXoffset            , lampBaseYoffset - lampStemHeight);
    g.drawLine(lampXoffset + lampStemWidth, lampBaseYoffset, lampXoffset + lampStemWidth, lampBaseYoffset - lampStemHeight);

    // Lamp shade
    g.drawArc(lampXcenter - lampShadeWidth / 2, lampShadeYbase                  , lampShadeWidth, lampShadeHeight, -65, 312);
    g.drawArc(lampXcenter - lampShadeWidth / 2, lampShadeYbase - lampShadesYdiff, lampShadeWidth, lampShadeHeight, 62, 58);

    // Lamp shade
    g.drawLine(lampXcenter - lampWidth / 2, lampShadeYbase, lampXcenter - (lampWidth + lampShadeWidth) / 8, lampTop);
    g.drawLine(lampXcenter + lampWidth / 2, lampShadeYbase, lampXcenter + (lampWidth + lampShadeWidth) / 8, lampTop);
    // g.fillOval(lampXcenter - lampWidth / 2, lampTop, lampXcenter + lampWidth / 2, 3);

    // Dots
    g.fillArc(78, lampTop,  lampDotRadius, lampDotRadius, 63, -174);
    g.fillOval(120, 96, lampDotRadius, lampDotRadius);
    g.fillArc(173, 100, lampDotRadius, lampDotRadius, 110, 180);
  }
}