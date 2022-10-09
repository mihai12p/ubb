public class Square
{
    private int length, breadth;
    public void get(int x, int y)
    {
        length = x;
        breadth = y;
    }
    public int area()
    {
        return length * breadth;
    }
}
