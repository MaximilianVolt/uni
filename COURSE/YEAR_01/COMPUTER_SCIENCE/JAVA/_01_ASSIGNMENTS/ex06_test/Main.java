package _01_ASSIGNMENTS.ex06_test;



/**
 * All classes have been defined in the same file for compactness, however they
 * should be put on different files called "<ClassName>.java" with the "public"
 * access modifier
 *
 * @author @MaximilianVolt
 * @since 2025-04-11
 */

public class Main
{
  public static void main(String[] args)
  {
    int woodenBoltCount = (int) (Math.random() * 12 + 4);
    int ironBoltCount = (int) (Math.random() * 12 + 4);

    System.out.printf("Bolts generated:\n- %d for wood\n- %d for iron\n\n", woodenBoltCount, ironBoltCount);

    HardwareStore hs = new HardwareStore(woodenBoltCount, ironBoltCount);

    Bolt[] bolts = hs.getBolts();
    int boltCount = bolts.length;

    for (int i = 0; i < boltCount; ++i)
      System.out.printf("Bolt no.%3d:\t%s\n", i, bolts[i]);
  }
}



/**
 * Class used to represent Bolt objects
 */

abstract class Bolt
{
  /** The diameter of the Bolt */
  private double mmdiameter;

  /** Whether the Bolt is galvanized (true) or not (false) */
  private boolean isGalvanized;



  /**
   * Creates a new Bolt
   * @param mmdiameter The size in millimiters of the diameter of the Bolt
   * @param isGalvanized Whether the Bolt is galvanized (true) or not (false)
   */

  public Bolt(double mmdiameter, boolean isGalvanized)
  {
    this.mmdiameter = mmdiameter;
    this.isGalvanized = isGalvanized;
  }



  /**
   * Creates a new Bolt, non-galvanized
   * @param mmdiameter The size in millimiters of the diameter of the Bolt
   */

  public Bolt(double mmdiameter)
  {
    this(mmdiameter, false);
  }



  /**
   * Returns the diameter of the Bolt
   * @return The diameter of the Bolt
   */

  protected double getDiameter()
  {
    return this.mmdiameter;
  }



  /**
   * Returns whether the Bolt is galvanized (true) or not (false)
   * @return whether the Bolt is galvanized
   */

  protected boolean isGalvanized()
  {
    return this.isGalvanized;
  }



  /**
   * Makes a bolt galvanized
   */

  public void setGalvanized()
  {
    this.isGalvanized = true;
  }



  public String toString()
  {
    return String.format("< Diameter: %5.2fmm | Galvanized: %-5b | Cost: %4.2f", mmdiameter, isGalvanized(), calculatePrice());
  }



  /**
   * Returns the price of the Bolt
   * @return The price of the Bolt
   */

  abstract protected double calculatePrice();
}



/**
 * Class used to represent WoodenBolt objects
 */

class WoodenBolt extends Bolt
{
  /** Whether the Bolt uses phillips-head (true) or not (false) */
  private boolean usesPhillipsHead;



  /**
   * Creates a new WoodenBolt
   * @param mmdiameter The size in millimiters of the diameter of the Bolt
   * @param isGalvanized Whether the Bolt is galvanized (true) or not (false)
   * @param usesPhillipsHead Whether the Bolt uses phillips-head (true) or not (false)
   */

  public WoodenBolt(double mmdiameter, boolean isGalvanized, boolean usesPhillipsHead)
  {
    super(mmdiameter, isGalvanized);
    this.usesPhillipsHead = usesPhillipsHead;
  }



  public String toString()
  {
    return String.format("%s | Uses phillips-head: %-5b >", super.toString(), usesPhillipsHead);
  }



  /**
   * Returns the price of the Bolt
   * @return The price of the Bolt
   */

   @Override
  public double calculatePrice()
  {
    return getDiameter() * .01 + (isGalvanized() ? .1 : .0) + (usesPhillipsHead ? .1 : .0);
  }
}



/**
 * Class used to represent IronBolt objects
 */

class IronBolt extends Bolt
{
  /** Whether the Bolt is of steel (true) or not (false) */
  private boolean isOfSteel;



  /**
   * Creates a new WoodenBolt
   * @param mmdiameter The size in millimiters of the diameter of the Bolt
   * @param isGalvanized Whether the Bolt is galvanized (true) or not (false)
   * @param usesPhillipsHead Whether the Bolt is of steel (true) or not (false)
   */

  public IronBolt(double mmdiameter, boolean isGalvanized, boolean isOfSteel)
  {
    super(mmdiameter, isGalvanized);
    this.isOfSteel = isOfSteel;
  }



  public String toString()
  {
    return String.format("%s | Is of steel: %-12b >", super.toString(), isOfSteel);
  }



  /**
   * Returns the price of the Bolt
   * @return The price of the Bolt
   */

  @Override
  public double calculatePrice()
  {
    return getDiameter() * .02 + (isGalvanized() ? .2 : .0) + (isOfSteel ? .1 : .0);
  }
}



/**
 * Class used to represent HardwareStore objects
 */

class HardwareStore
{
  /** The list of Bolts of the HardwareStore */
  private Bolt bolts[];



  public HardwareStore(int woodenBoltCount, int ironBoltCount)
  {
    int boltCount = woodenBoltCount + ironBoltCount;

    this.bolts = new Bolt[boltCount];

    for (int i = 0; i < woodenBoltCount; ++i)
      this.bolts[i] = new WoodenBolt(
        Math.random() * 10 + 5,
        Math.round(Math.random()) == 1 ? true : false,
        Math.round(Math.random()) == 1 ? true : false
      );

    for (int i = woodenBoltCount; i < boltCount; ++i)
      this.bolts[i] = new IronBolt(
        Math.random() * 10 + 5,
        Math.round(Math.random()) == 1 ? true : false,
        Math.round(Math.random()) == 1 ? true : false
      );
  }



  public Bolt[] getBolts()
  {
    return this.bolts;
  }
}
