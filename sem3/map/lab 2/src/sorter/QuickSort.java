package sorter;

import java.util.Collections;
import java.util.Stack;
import java.util.Vector;

public class QuickSort extends AbstractSorter
{
    private int partition(Vector<Integer> array, int start, int end)
    {
        int pivot = array.elementAt(end);
        int i = start - 1;
        for (int j = start; j <= end - 1; ++j)
        {
            if (array.elementAt(j) <= pivot)
            {
                Collections.swap(array, ++i, j);
            }
        }
        Collections.swap(array, ++i, end);
        return i;
    }

    private void quickSort(Vector<Integer> array, int start, int end)
    {
        if (start < end)
        {
            int pivot = partition(array, start, end);
            quickSort(array, start, pivot - 1);
            quickSort(array, pivot + 1, end);
        }
    }

    @Override
    public void sort(Vector<Integer> array)
    {
        quickSort(array, 0, array.size() - 1);
    }
}
