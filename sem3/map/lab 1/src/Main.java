import service.AnalizatorExpresie;
import model.domain.NumarComplex;

public class Main
{
    public static void main(String[] args)
    {
        AnalizatorExpresie analizator = new AnalizatorExpresie();
        analizator.analizeaza(args);

        NumarComplex rez = analizator.creeazaExpresie().executa();
        System.out.println("Rezultat: " + rez);
    }
}

