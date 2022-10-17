package container;

import model.Task;

import static utils.Constants.INITIAL_CONTAINER_SIZE;

public abstract class AbstractContainer implements Container
{
    protected Task[] tasks;
    protected int size;

    public AbstractContainer()
    {
        this.size = 0;
        this.tasks = new Task[INITIAL_CONTAINER_SIZE];
    }

    @Override
    public void add(Task task)
    {
        if (tasks.length == size)
        {
            Task[] _task = new Task[tasks.length * 2];
            System.arraycopy(this.tasks, 0, _task, 0, tasks.length);
            this.tasks = _task;
        }
        this.tasks[this.size++] = task;
    }

    @Override
    public int size()
    {
        return this.size;
    }

    @Override
    public boolean isEmpty()
    {
        return this.size == 0;
    }
}
