package model;

import model.domain.NumarComplex;

public class Scadere extends ExpresieComplexa
{
    public Scadere(NumarComplex[] nrCs)
    {
        super(nrCs);
    }

    @Override
    public NumarComplex executaOperatie(NumarComplex nrC1, NumarComplex nrC2)
    {
        NumarComplex rez = nrC1.scadere(nrC2);
        return rez;
    }
}
