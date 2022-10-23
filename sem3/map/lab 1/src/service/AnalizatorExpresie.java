package service;

import model.ExpresieComplexa;
import model.domain.NumarComplex;
import model.domain.Operatie;

public class AnalizatorExpresie
{
    private Operatie operatie;
    private NumarComplex[] nrCs;

    public void analizeaza(String[] args)
    {
        if (args[1].charAt(0) == '+')
        {
            this.operatie = Operatie.Adunare;
        }
        else if (args[1].charAt(0) == '-')
        {
            this.operatie = Operatie.Scadere;
        }
        else if (args[1].charAt(0) == '*')
        {
            this.operatie = Operatie.Inmultire;
        }
        else
        {
            this.operatie = Operatie.Impartire;
        }

        this.nrCs = new NumarComplex[(args.length + 1) / 2];
        for (int i = 0; i < args.length; i += 2)
        {
            this.nrCs[i / 2] = new Parser(args[i]).getNrC();
        }
    }

    public ExpresieComplexa creeazaExpresie()
    {
        return ExpresieFactory.getInstance().creeazaExpresie(operatie, nrCs);
    }
}

class Parser
{
    private NumarComplex nrC = new NumarComplex();

    public Parser(String nrC)
    {
        final int idx = nrC.lastIndexOf('*');
        if (idx == -1)
        {
            this.nrC.setIm(1);

            final int idxI = nrC.lastIndexOf('i');
            if (nrC.charAt(idxI - 1) == '-')
            {
                this.nrC.setIm(this.nrC.getIm() * -1);
            }

            String realPart = nrC.substring(0, idxI - 1);
            this.nrC.setRe(Float.parseFloat(realPart));
        }
        else
        {
            final int idxPlus = nrC.lastIndexOf('+');
            final int idxMinus = nrC.lastIndexOf('-');

            String imaginaryPart = nrC.substring(Math.max(idxPlus, idxMinus), idx);
            this.nrC.setIm(Float.parseFloat(imaginaryPart));

            String realPart = nrC.substring(0, Math.max(idxPlus, idxMinus));
            this.nrC.setRe(Float.parseFloat(realPart));
        }
    }

    public NumarComplex getNrC()
    {
        return nrC;
    }
}
