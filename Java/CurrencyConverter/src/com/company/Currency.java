package com.company;

public class Currency {
    String CharCode;
    int Nominal;
    String Name;
    double Value;

    public Currency(String OuterCharCode, int OuterNominal,
                    String OuterName, double OuterValue) {

        this.CharCode = OuterCharCode;
        this.Nominal = OuterNominal;
        this.Name     = OuterName;
        this.Value    = OuterValue;
    }

    public int getNominal() {
        return this.Nominal;
    }

    public String getName() {
        return this.Name;
    }

    public double getValue() {
        return this.Value;
    }
}

