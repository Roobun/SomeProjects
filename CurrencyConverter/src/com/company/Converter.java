package com.company;

import java.util.*;

public class Converter {

    private double StartingCurrencyValue;
    private int    StartingCurrencyNominal;

    private double ResultCurrencyValue;
    private int    ResultCurrencyNominal;

    private double AmountOfMoney;

    public Converter(String StartingCurrencyName, String ResultCurrencyName, double StartingMoney, Map Table) {
        Currency StartingCurrency    = (Currency)Table.get(StartingCurrencyName);
        this.StartingCurrencyValue   = StartingCurrency.getValue();
        this.StartingCurrencyNominal = StartingCurrency.getNominal();

        Currency ResultCurrency      = (Currency)Table.get(ResultCurrencyName);
        this.ResultCurrencyValue     = ResultCurrency.getValue();
        this.ResultCurrencyNominal   = ResultCurrency.getNominal();

        this.AmountOfMoney           = StartingMoney;
    }

    private double CurrencyRatio() {
        double StartingValue = StartingCurrencyValue / StartingCurrencyNominal;
        double ResultValue   = ResultCurrencyValue / ResultCurrencyNominal;

        return StartingValue / ResultValue;
    }

    private double ResultAmountOfMoney(double Ratio) {
        return AmountOfMoney * Ratio;
    }

    public double CalculationOfMoney() {
        double Result = ResultAmountOfMoney(this.CurrencyRatio());

        return Result;
    }


}
