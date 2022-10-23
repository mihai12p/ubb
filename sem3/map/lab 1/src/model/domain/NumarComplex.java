package model.domain;

public class NumarComplex
{
    private float re;
    private float im;

    public NumarComplex()
    {
        this.re = 0;
        this.im = 0;
    }

    public NumarComplex(float re, float im)
    {
        this.re = re;
        this.im = im;
    }

    public void setRe(float re)
    {
        this.re = re;
    }

    public void setIm(float im)
    {
        this.im = im;
    }

    public float getRe()
    {
        return this.re;
    }

    public float getIm()
    {
        return this.im;
    }

    public String toString()
    {
        if (this.im < 0)
        {
            return String.valueOf(this.re) + String.valueOf(this.im) + "*i";
        }
        else
        {
            return String.valueOf(this.re) + '+' + String.valueOf(this.im) + "*i";
        }
    }

    public NumarComplex conjugat()
    {
        NumarComplex rezultat = new NumarComplex();
        rezultat.re = this.re;
        rezultat.im = -this.im;

        return rezultat;
    }

    public NumarComplex adunare(NumarComplex nr)
    {
        NumarComplex rezultat = new NumarComplex();
        rezultat.re = this.re + nr.re;
        rezultat.im = this.im + nr.im;

        return rezultat;
    }

    public NumarComplex scadere(NumarComplex nr)
    {
        NumarComplex rezultat = new NumarComplex();
        rezultat.re = this.re - nr.re;
        rezultat.im = this.im - nr.im;

        return rezultat;
    }

    public NumarComplex inmultire(NumarComplex nr)
    {
        NumarComplex rezultat = new NumarComplex();
        rezultat.re = this.re * nr.re - this.im * nr.im;
        rezultat.im = this.re * nr.im + this.im * nr.re;

        return rezultat;
    }

    public NumarComplex impartire(NumarComplex nr)
    {
        NumarComplex rezultat = this.inmultire(nr.conjugat());
        rezultat.re /= (nr.re)*(nr.re) + (nr.im)*(nr.im);
        rezultat.im /= (nr.re)*(nr.re) + (nr.im)*(nr.im);

        return rezultat;
    }
}
