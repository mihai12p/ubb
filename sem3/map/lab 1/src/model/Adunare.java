package model;

import model.domain.NumarComplex;

public class Adunare extends ExpresieComplexa
{
    public Adunare(NumarComplex[] nrCs)
    {
        super(nrCs);
    }

    @Override
    public NumarComplex executaOperatie(NumarComplex nrC1, NumarComplex nrC2)
    {
        NumarComplex rez = nrC1.adunare(nrC2);
        return rez;
    }
}
