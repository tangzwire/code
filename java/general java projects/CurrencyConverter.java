/*****************************************************************************************
 * 																						 *
 * Author: Tanvir Saif Ahmed															 *
 * Date: 23/1-2017																		 *
 * Program name: CurrencyConverter.java													 *
 * Description: A program that can convert from one currency or between two currencies.  *
 * 																						 *
 *****************************************************************************************/

//Import of java libraries used in this program.
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;
import java.lang.String;
import java.util.regex.Pattern;

//Name of the class.
public class CurrencyConverter 
{
	//Public variables used in the functions of the program.
	//Some are used as flags, some are used to calculate and store the currency value.
	public static String currencyConvert = "";
	public static int counter = 0;
	public static double rateValue = 0.00;
	public static double total = 0.00;
	public static int fromCurrencyFound = 0;
	public static int toCurrencyFound = 0;
	public static int singleCurrency = 0;
	public static int doubleConvert = 0;
	public static int tryAgain = 0;
	
	//If the user enters only one currency, the program will jump to this function.
	//The entered currency will be then converted to the Swedish currency SEK.
	private static void singleCurrConverter(String currencyFrom, double value) throws FileNotFoundException
	{
		currencyConvert = currencyFrom;
		
		//Variables used to read a textfile, where all currencies are labeled.
		Scanner readOneCur = new Scanner(new File("bin\\valutor.txt"), "UTF-8");
		readOneCur.useLocale(Locale.ENGLISH);
		while (readOneCur.hasNextLine()) 
		{
			String currency = readOneCur.next();
			double rate = readOneCur.nextDouble();
			String description = readOneCur.nextLine();
			
			//If the currency is found, the value will be calculated.
			//Some flags will also be set to 1, so a right decision is made later in the program.
			if(currencyConvert.equals(currency) == true)
			{
				total = rate * value;
				toCurrencyFound = 1;
				fromCurrencyFound = 1;
				singleCurrency = 1;
			}
		}
	}
	
	//If the user enters two currencies, the program will jump to this function.
	//The entered currencies will be converted from one currency to the other currency.
	private static void doubleCurrConverter(String currencyFrom, double value, String currencyTo) throws FileNotFoundException
	{
		currencyConvert = currencyFrom;
		
		//A for-loop so that a textfile can be read twice (for the first currency and then the other currency).
		//In order to read the file twice, the scanner also needs to be renewed.
		for(int i=0;i<=1;i++)		
		{	
			if(counter == 1)
			{
				currencyConvert = currencyTo;
			}
			
			//Variables used to read a textfile, where all currencies are labeled.
			Scanner readTwoCur = new Scanner(new File("bin\\valutor.txt"), "UTF-8");
			readTwoCur.useLocale(Locale.ENGLISH);
			counter++;
			while (readTwoCur.hasNextLine()) 
			{
				String currency = readTwoCur.next();
				double rate = readTwoCur.nextDouble();
				String description = readTwoCur.nextLine();
				
				//If the currency is found, the value will be calculated.
				//Some flags will also be set to 1, so a right decision is made later in the program.
				if(currencyConvert.equals(currency) == true && counter == 1)
				{
					rateValue = value * rate;
					fromCurrencyFound = 1;
				}
				//If the currency is found, the value will be calculated.
				//Some flags will also be set to 1, so a right decision is made later in the program.
				else if(currencyConvert.equals(currency) == true && counter != 1)
				{
					total = rateValue * (1/rate);
					toCurrencyFound = 1;
				}
			}
		}
		doubleConvert = 1;
	}
	
	//A function where it checks if the user has entered one currencies or two currencies.
	public static void converter(String currencyFrom, double value, String currencyTo) throws IOException
	{
		if (Pattern.matches("[A-Z]+", currencyTo) == true) 
		{
			doubleCurrConverter(currencyFrom, value, currencyTo);
		}
		else
		{
			singleCurrConverter(currencyFrom,value);
		}
		
		//This part of the function is used to check if the currencies were not found.
		//It is done, using the flags that were activated earlier in the program.
		//If all of the currencies were successfully found, the total amount value will be printed out.
		if(fromCurrencyFound == 0 && toCurrencyFound == 1)
		{
			System.out.println("" + currencyFrom + " is not a recognized currency!");
		}
		else if(toCurrencyFound == 0 && fromCurrencyFound == 1)
		{
			System.out.println("" + currencyTo + " is not a recognized currency!");
		}
		else if(fromCurrencyFound == 0 && toCurrencyFound == 0 && doubleConvert == 1)
		{
			System.out.println("Both " + currencyFrom + " and " + currencyTo + " are not recognized currencies!");
		}
		
		else if(fromCurrencyFound == 0 && toCurrencyFound == 0 && singleCurrency == 0)
		{
			System.out.println("" + currencyFrom + " is not a recognized currency!");
		}
		else if(singleCurrency == 0)
		{
			System.out.println("" + currencyFrom + " " + value + " = " + total + " " + currencyTo);
		}
		else if(singleCurrency == 1)
		{
			System.out.println(currencyFrom + " " + value + " = " + total + " SEK");
		}
	}
	
	//This function will be breaking up the string the user has entered into parts.
	//This will give three pieces of information: first currency, value and the second currency.
	public static void textBreakUp(String convertText) throws IOException
	{
			//If the string contains only one currency and value, these two will be parted.	
			String[] parts = convertText.split(" ");
			String currencyFrom = parts[0];
			String valueChar = parts[1];
			String currencyTo = "";
		
			//If the string contains another currency, this will also be parted (giving three pieces of information).
			if(Character.isLetter(convertText.charAt(convertText.length() - 1)))
			{	
				currencyTo = parts[2];
			}
		
			double value = Double.parseDouble(valueChar);
			currencyFrom = currencyFrom.toUpperCase();
			currencyTo = currencyTo.toUpperCase();
		
			converter(currencyFrom, value, currencyTo);	
	}
	
	//Main function: this is where the program starts and where all the appropriate functions are called.
	//Usage: currency amount [currency], where the currency in brackets is not mandatory.
	public static void main(String[] args) throws IOException
	{
		Scanner convertIns = new Scanner(System.in);
		String convertText = "";
		int newStart = 1;
			
		while(newStart == 1)
		{	
		System.out.println(" - WELCOME TO THE CURRENCY CONVERTING PROGRAM - ");
		System.out.println("Usage: currency amount [currency]");
		System.out.println("1. If one currency is entered, the amount will be converted to the currency SEK.");
		System.out.println("2. If two currencies are entered, the amount will be converted from the first currency to the other currency");
		System.out.printf("Enter the currency and value you want to convert: ");
		convertText = convertIns.nextLine();
		
		if(convertText.isEmpty() == false && Character.isLetter(convertText.charAt(2)) && Character.isDigit(convertText.charAt(4)))
		{
			newStart = 0;
			textBreakUp(convertText);
		}
		else
		{	
			newStart = 1;
		}
		}
	}
}
