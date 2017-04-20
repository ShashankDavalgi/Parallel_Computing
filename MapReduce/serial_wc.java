import java.util.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class serial_wc
{
	public static void main(String ar[]) throws Exception
	{
		System.out.println("Serial Java Word Count");
		int wordCount = 1,count=1;
	
		//Reading a file from the system.
		BufferedReader br = new BufferedReader(new FileReader("file.txt"));
        
		String str2 = "", str1 = "";
	//Reading a word one by one throughout the file.
        while ((str1 = br.readLine()) != null) 
		{
			str2 += str1;

        }

		//checking the frequencyof a single word.
		for (int i = 0; i < str2.length(); i++) 
		{
			if (str2.charAt(i) == ' ' && str2.charAt(i+1)!=' ') 
			{
				wordCount++;
			} 
		}
	
    System.out.println("Frequency of each word is = " +(wordCount));
	}
}
