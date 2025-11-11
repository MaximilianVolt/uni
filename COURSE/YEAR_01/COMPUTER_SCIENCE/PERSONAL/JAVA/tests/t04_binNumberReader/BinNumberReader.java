package tests.t04_binNumberReader;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class BinNumberReader
{
  public static final int IEEE754_SIGN_INDEX = 0;
  public static final int IEEE754_EXPONENT_START_INDEX = 1;
  public static final int IEEE754_EXPONENT_END_INDEX = 6;
  public static final int IEEE754_MANTISSA_START_INDEX = 6;
  public static final int IEEE754_MANTISSA_END_INDEX = 16;

  public static final int IEEE754_EXPONENT_BIAS = 15;
  public static final int IEEE754_MANTISSA_DIVIDER = 1024;

  public static final int IEEE754_EXPONENT_MAX = 16;
  public static final int IEEE754_EXPONENT_MIN = -15;
  public static final int IEEE754_EXPONENT_MIN_TO_NORMALIZED = -14;



  private ArrayList<String> data = null;



  public BinNumberReader(String filename) {
    this.data = new ArrayList<>();

    try (BufferedReader in = new BufferedReader(new FileReader(filename))) {
      String line;

      while ((line = in.readLine()) != null) {
        data.add(line);
      }
    }
    catch (IOException e) {
      System.err.println("Error while reading file.");
    }
  }



  public String get(int index) {
    return data.get(index);
  }



  public double getNumber(int index) {
    return getNumber(get(index));
  }



  public double getNumber(String number) {
    String expStr = number.substring(IEEE754_EXPONENT_START_INDEX, IEEE754_EXPONENT_END_INDEX)
      , mantissaStr = number.substring(IEEE754_MANTISSA_START_INDEX, IEEE754_MANTISSA_END_INDEX)
      , signStr = String.valueOf(number.charAt(IEEE754_SIGN_INDEX))
    ;

    int exp = binStrToInt(expStr) - IEEE754_EXPONENT_BIAS
      , sign = signStr.charAt(0) == '0' ? 1 : -1
      , mantissa = binStrToInt(mantissaStr)
      , unit = 1
    ;

    if (mantissa == 0 && exp < IEEE754_EXPONENT_MAX) {
      return 0;
    }

    if (exp == IEEE754_EXPONENT_MAX) {
      return mantissa != 0
        ? Double.NaN
        : sign > 0
          ? Double.POSITIVE_INFINITY
          : Double.NEGATIVE_INFINITY
      ;
    }
    else if (exp == IEEE754_EXPONENT_MIN) {
      exp = IEEE754_EXPONENT_MIN_TO_NORMALIZED;
      unit = 0;
    }

    return sign * Math.pow(2, exp) * (unit + (double) mantissa / IEEE754_MANTISSA_DIVIDER);
  }



  public int binStrToInt(String str) {
    int len = str.length(), x = 0;

    for (int i = 0; i < len; ++i) {
      x += (str.charAt(len - i - 1) - '0') << i;
    }

    return x;
  }
}
