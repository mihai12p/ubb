import container.Strategy;
import model.MessageTask;
import runner.DelayTaskRunner;
import sorter.Sorter;
import sorter.SortingTask;
import runner.PrinterTaskRunner;
import runner.StrategyTaskRunner;

import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.Vector;

public class TestRunner
{
    private static MessageTask[] getMessages()
    {
        MessageTask messageTask1 = new MessageTask("1", "Seminar","Tema laborator", "Florentin", "Razvan", LocalDateTime.now());
        MessageTask messageTask2 = new MessageTask("2", "Laborator","Solutie", "Razvan", "Florentin", LocalDateTime.now());
        MessageTask messageTask3 = new MessageTask("3", "Nota laborator","10", "Florentin", "Razvan", LocalDateTime.now());

        return new MessageTask[] { messageTask1, messageTask2, messageTask3 };
    }

    public static void Sort()
    {
        Vector<Integer> v = new Vector<Integer>();
        v.add(1); v.add(3); v.add(2); v.add(4);
        SortingTask sorter = new SortingTask("1", "Sortare folosind QuickSort", v, Sorter.QuickSort);
        sorter.execute();
    }

    public static void Run(Strategy strategy)
    {
        StrategyTaskRunner runner = new StrategyTaskRunner(strategy);
        PrinterTaskRunner printer = new PrinterTaskRunner(runner);
        DelayTaskRunner delayedPrinter = new DelayTaskRunner(runner);

        MessageTask[] messages = getMessages();
        for (int i = 0; i < getMessages().length; ++i)
        {
            runner.addTask(messages[i]);
        }
        runner.executeAll();

        for (int i = 0; i < getMessages().length; ++i)
        {
            printer.addTask(messages[i]);
        }
        printer.executeAll();

        for (int i = 0; i < getMessages().length; ++i)
        {
            delayedPrinter.addTask(messages[i]);
        }
        delayedPrinter.executeAll();
    }
}

