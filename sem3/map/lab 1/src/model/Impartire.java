package model;

import model.domain.NumarComplex;

public class Impartire extends ExpresieComplexa
{
    public Impartire(NumarComplex[] nrCs)
    {
        super(nrCs);
    }

    @Override
    public NumarComplex executaOperatie(NumarComplex nrC1, NumarComplex nrC2)
    {
        NumarComplex rez = nrC1.impartire(nrC2);
        return rez;
    }
}
