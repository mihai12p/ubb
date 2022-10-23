package service;

import model.*;
import model.domain.NumarComplex;
import model.domain.Operatie;

public class ExpresieFactory
{
    private static ExpresieFactory instance = null;

    public static ExpresieFactory getInstance()
    {
        if (instance == null)
        {
            instance = new ExpresieFactory();
        }

        return instance;
    }

    public ExpresieComplexa creeazaExpresie(Operatie operatie, NumarComplex[] nrCs)
    {
        switch (operatie)
        {
            case Adunare ->
            {
                return new Adunare(nrCs);
            }
            case Scadere ->
            {
                return new Scadere(nrCs);
            }
            case Inmultire ->
            {
                return new Inmultire(nrCs);
            }
            case Impartire ->
            {
                return new Impartire(nrCs);
            }
        }
        return null;
    }
}
