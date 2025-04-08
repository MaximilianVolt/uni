package _01_ASSIGNMENTS.ex04_inheritance;



public class Main
{
  public static void main(String[] args)
  {
    int years = (int) (Math.round(Math.random() * 15));
    TennisSociety ts = new TennisSociety(100, 50);

    System.out.printf(
      "The average cost of players playing for more than %d years is $%.2f",
      years,
      ts.avgSubCostAfterYearsPlaying(years)
    );
  }
}



abstract class TennisPlayer
{
  private String name;
  private int yearsPlaying = 0;



  abstract protected double getSubscriptionCost();



  public TennisPlayer(String name, int yearsPlaying)
  {
    setYearsPlaying(yearsPlaying);
    this.name = name;
  }



  public String getName()
  {
    return this.name;
  }



  public int getYearsPlaying()
  {
    return this.yearsPlaying;
  }



  private void setYearsPlaying(int yearsPlaying)
  {
    // Years must be >= 0
    if (yearsPlaying < 0)
      return;

    this.yearsPlaying = yearsPlaying;
  }



  public void renewSubscription()
  {
    ++this.yearsPlaying;
  }
}



class ProfessionalTennisPlayer extends TennisPlayer
{
  private int score = 0;



  public ProfessionalTennisPlayer(String name, int yearsPlaying, int score)
  {
    super(name, yearsPlaying);
    this.score = score;
  }



  public double getSubscriptionCost()
  {
    return score < 2000
      ? 500d
      : 600d
    ;
  }
}



class NewbieTennisPlayer extends TennisPlayer
{
  private int playedTournamentCount = 0;



  public NewbieTennisPlayer(String name, int yearsPlaying, int playedTournamentCount)
  {
    super(name, yearsPlaying);
    this.playedTournamentCount = playedTournamentCount;
  }



  public double getSubscriptionCost()
  {
    return playedTournamentCount < 20
      ? 300d
      : 450d
    ;
  }
}



class TennisSociety
{
  TennisPlayer players[];



  public TennisSociety(int newbieCount, int professionalCount)
  {
    int count = newbieCount + professionalCount;

    this.players = new TennisPlayer[count];

    for (int i = 0; i < newbieCount; ++i)
      this.players[i] = new NewbieTennisPlayer(
        "Newbie Player" + (i + 1),
        (int) (Math.random() * 15),
        (int) (Math.random() * 40)
      );

    for (int i = newbieCount; i < count; ++i)
      this.players[i] = new ProfessionalTennisPlayer(
        "Professional Player" + (i + 1),
        (int) (Math.random() * 15),
        (int) (Math.random() * 4000)
      );
  }



  public double avgSubCostAfterYearsPlaying(int years)
  {
    int count = 0;
    double sum = 0;

    for (TennisPlayer player : this.players)
    {
      if (player.getYearsPlaying() > years)
      {
        sum += player.getSubscriptionCost();
        ++count;
      }
    }

    return count > 0
      ? sum / count
      : 0d
    ;
  }
}
