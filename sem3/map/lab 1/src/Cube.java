public class Cube extends Square
{
    int height;
    public void getData(int x, int y, int z)
    {
        get(x, y);
        height = z;
    }
    int volume()
    {
        return (area() * height);
    }
}

class RunInheritance
{
    public static void main(String a[])
    {
        Cube C = new Cube();
        C.getData(10, 20, 30);

        int b1 = C.area();
        System.out.println("Area of square: " + b1);

        int b2 = C.volume();
        System.out.println("Volume of cube: " + b2);
    }
}