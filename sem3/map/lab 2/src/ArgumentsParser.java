import container.Strategy;

public class ArgumentsParser
{
    private Strategy strategy;

    public ArgumentsParser(String[] args)
    {
        if (args.length < 1)
        {
            return;
        }

        if (args[0].compareTo("FIFO") == 0)
        {
            this.strategy = Strategy.FIFO;
        }
        else if (args[0].compareTo("LIFO") == 0)
        {
            this.strategy = Strategy.LIFO;
        }
        else
        {
            this.strategy = Strategy.UNKNOWN;
        }
    }

    public Strategy getStrategy()
    {
        return this.strategy;
    }
}
