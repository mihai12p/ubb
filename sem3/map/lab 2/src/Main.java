public class Main
{
    public static void main(String[] args)
    {
        ArgumentsParser argsParser = new ArgumentsParser(args);
        TestRunner.Run(argsParser.getStrategy());
        TestRunner.Sort();
    }
}