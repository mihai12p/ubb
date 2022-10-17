package sorter;

import model.Task;

import java.util.Vector;

public class SortingTask extends Task
{
    private AbstractSorter sorter;
    private Vector<Integer> vec;

    public SortingTask(String taskID, String description, Vector<Integer> toSort, Sorter strategy)
    {
        super(taskID, description);
        if (strategy == Sorter.BubbleSort)
        {
            this.sorter = new BubbleSort();
        }
        else if (strategy == Sorter.QuickSort)
        {
            this.sorter = new QuickSort();
        }
        this.vec = toSort;
    }

    @Override
    public void execute()
    {
        System.out.println("\nVector nesortat: " + this.vec);
        this.sorter.sort(this.vec);
        System.out.println("Vector sortat: " + this.vec);
    }
}
