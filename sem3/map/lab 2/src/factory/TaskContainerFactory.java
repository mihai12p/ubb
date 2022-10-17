package factory;

import container.Container;
import container.QueueContainer;
import container.StackContainer;
import container.Strategy;

public final class TaskContainerFactory implements Factory
{
    private static final TaskContainerFactory instance;
    private TaskContainerFactory() { }

    static
    {
        instance = new TaskContainerFactory();
    }

    public static TaskContainerFactory getInstance()
    {
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy)
    {
        if (strategy == Strategy.LIFO)
        {
            return new StackContainer();
        }
        else if (strategy == Strategy.FIFO)
        {
            return new QueueContainer();
        }
        return null;
    }
}
