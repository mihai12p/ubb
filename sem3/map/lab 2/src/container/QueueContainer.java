package container;

import model.Task;

public class QueueContainer extends AbstractContainer implements Container
{
    @Override
    public Task remove()
    {
        if (this.isEmpty())
        {
            return null;
        }

        Task toReturn = tasks[0];

        --this.size;
        for (int i = 0; i < this.size; ++i)
        {
            this.tasks[i] = this.tasks[i + 1];
        }

        return toReturn;
    }
}
