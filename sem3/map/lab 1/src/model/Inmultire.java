package model;

import model.domain.NumarComplex;

public class Inmultire extends ExpresieComplexa
{
    public Inmultire(NumarComplex[] nrCs)
    {
        super(nrCs);
    }

    @Override
    public NumarComplex executaOperatie(NumarComplex nrC1, NumarComplex nrC2)
    {
        NumarComplex rez = nrC1.inmultire(nrC2);
        return rez;
    }
}
