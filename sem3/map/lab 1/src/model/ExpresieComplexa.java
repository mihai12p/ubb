package model;

import model.domain.NumarComplex;

import java.util.Arrays;
import java.util.Vector;

public abstract class ExpresieComplexa
{
    private Vector<NumarComplex> args;

    public ExpresieComplexa(NumarComplex[] nrCs)
    {
        this.args = new Vector<NumarComplex>(Arrays.asList(nrCs));
    }

    public abstract NumarComplex executaOperatie(NumarComplex nrC1, NumarComplex nrC2);

    public NumarComplex executa()
    {
        NumarComplex rez = args.elementAt(0);
        for (int i = 1; i < args.size(); ++i)
        {
            rez = executaOperatie(rez, args.elementAt(i));
        }
        return rez;
    }
}
