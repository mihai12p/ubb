package exercises;

public class FindLargestSmallestNumber
{
    public static void main(String[] args)
    {
        int numbers[] = new int[]{ 32, 43, 53, 54, 32, 65, 63, 98, 43, 23 };

        int smallest = numbers[0];
        int largest = numbers[0];

        for (int i = 1; i < numbers.length; ++i)
        {
            if (numbers[i] > largest)
            {
                largest = numbers[i];
            }
            else if (numbers[i] < smallest)
            {
                smallest = numbers[i];
            }
        }
        System.out.println("Largest number is: " + largest);
        System.out.println("Smallest numbers is: " + smallest);
    }
}
