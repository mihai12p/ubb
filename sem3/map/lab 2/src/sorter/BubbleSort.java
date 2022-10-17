package sorter;

import java.util.Collections;
import java.util.Vector;

public class BubbleSort extends AbstractSorter
{
    @Override
    public void sort(Vector<Integer> array)
    {
        for (int i = 0; i < array.size() - 1; ++i)
        {
            for (int j = 0; j < array.size() - i - 1; ++j)
            {
                if (array.elementAt(j) > array.elementAt(j + 1))
                {
                    Collections.swap(array, j, j + 1);
                }
            }
        }
    }
}
