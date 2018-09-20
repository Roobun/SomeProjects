package com.company;

//

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.math.BigDecimal;
import java.math.RoundingMode;

import java.util.*;
import java.util.List;

import javax.imageio.ImageIO;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JSpinner;
import javax.swing.SpinnerListModel;

//

public class Interface extends JFrame {
    private JButton Equality;
    private JComboBox StartingCurrency, ResultCurrency;
    private JTextField StartingValue, ResultValue;
    private JLabel StartingName, ResultName;
    private JSpinner BankName;

    private Map Table;
    private Server DataCB;

    private double StartingMoney = 1.0;
    private double ResultMoney = 1.0;

    private boolean isR;

    public Interface(Server server) {
        super("Currency");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(420, 360);
        this.setResizable(false);
        this.setLocationRelativeTo(null);

        DataCB = server;
        Table = server.getTable(true);

        Container Content = this.getContentPane();

        AddingComponents(Content);
    }

    private void AddingComponents(Container Content) {
        ComboBox(Content);
        Content.add(StartingCurrency);
        Content.add(ResultCurrency);

        TextField();
        Content.add(StartingValue);
        Content.add(ResultValue);

        Button();
        Content.add(Equality);

        Label();
        Content.add(StartingName);
        Content.add(ResultName);

        Spinner(Content);
        Content.add(BankName);


        Content.add(new JLabel());
        this.setVisible(true);
    }

    private void Refresh(Container Content) {
        Content.removeAll();
        AddingComponents(Content);
    }

    private void ComboBox(Container Content) {
        Set<String> CharCodes = Table.keySet();

        JComboBox[] forSimplification = {StartingCurrency, ResultCurrency};
        for (JComboBox Currency: forSimplification) {
            boolean isStarting = Currency == StartingCurrency;

            Currency = new JComboBox(CharCodes.toArray());
            Currency.setEditable(false);
            Currency.setFont(new Font("Arial", Font.PLAIN, 14));
            Currency.setForeground(Color.BLUE);
            Currency.setMaximumRowCount(4);
            Currency.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    Content.remove(StartingName);
                    Content.remove(ResultName);
                    Label();
                    Content.add(StartingName);
                    Content.add(ResultName);
                }
            });

            if (isStarting == true) {
                Currency.setBounds(40, 40, 100, 40);
                StartingCurrency = Currency;
            } else {
                Currency.setBounds(260, 40, 100, 40);
                ResultCurrency = Currency;
            }
        }
    }

    private void TextField() {
        JTextField[] forSimplification = {StartingValue, ResultValue};
        for (JTextField Value: forSimplification) {
            boolean isStarting = Value == StartingValue;

            Value = new JTextField(Double.toString(StartingMoney));
            Value.setFont(new Font("Arial", Font.PLAIN, 14));
            Value.setForeground(Color.BLUE);
            Value.setVisible(true);

            if (isStarting == true) {
                Value.setText(Double.toString(StartingMoney));
                Value.setBounds(40, 140, 100, 40);
                StartingValue = Value;
            } else {
                Value.setText(Double.toString(ResultMoney));
                Value.setBounds(260, 140, 100, 40);
                ResultValue = Value;
            }

        }

    }

    private void Button() {
        Equality = new JButton();
        try {
            Image img = ImageIO.read(getClass().getResource("equality.png"));
            Equality.setIcon(new ImageIcon(img));
        } catch (Exception ex) {
            System.out.println(ex);
        }

        Equality.setBounds(180, 140, 40, 40);
        Equality.setVisible(true);
        Equality.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String Starting = (String)StartingCurrency.getSelectedItem();
                String Result = (String)ResultCurrency.getSelectedItem();
                if (!isR) {
                    String temp = Starting;
                    Starting = Result;
                    Result = temp;
                }
                StartingMoney = Double.valueOf(StartingValue.getText());

                com.company.Converter Calculate = new com.company.Converter(Starting, Result, StartingMoney, Table);
                ResultMoney = Calculate.CalculationOfMoney();
                // round to *.2
                BigDecimal bd = new BigDecimal(Double.toString(ResultMoney));
                bd = bd.setScale(2, RoundingMode.HALF_UP);

                ResultMoney = bd.doubleValue();
                ResultValue.setText(Double.toString(ResultMoney));
            }
        });
    }

    private void Label() {
        JLabel[] forSimplification = {StartingName, ResultName};
        for (JLabel Name: forSimplification) {
            boolean isStarting = Name == StartingName;

            Name = new JLabel();
            Name.setFont(new Font("Folks", Font.PLAIN, 10));
            Name.setForeground(Color.BLUE);
            Name.setVisible(true);

            if (isStarting == true) {
                Name.setBounds(40, 70, 160, 40);
                String name = (String)StartingCurrency.getSelectedItem();
                com.company.Currency curr = (com.company.Currency)Table.get(name);
                Name.setText(curr.Name);
                StartingName = Name;
            } else {
                Name.setBounds(260, 70, 160, 40);
                String name = (String)ResultCurrency.getSelectedItem();
                com.company.Currency curr = (com.company.Currency)Table.get(name);
                Name.setText(curr.Name);
                ResultName = Name;
            }
        }
    }

    private void Spinner(Container Content) {
        class SpinnerCircularListModel extends SpinnerListModel {
            public SpinnerCircularListModel(Object[] items) {
                super(items);
            }

            public Object getNextValue() {
                List list = getList();
                int index = list.indexOf(getValue());

                index = (index >= list.size() - 1) ? 0 : index + 1;
                return list.get(index);
            }

            public Object getPreviousValue() {
                List list = getList();
                int index = list.indexOf(getValue());

                index = (index <= 0) ? list.size() - 1 : index - 1;
                return list.get(index);
            }
        }

        SpinnerCircularListModel listModelR = new SpinnerCircularListModel(
                new String[] {"Russian Central Bank", "European Central Bank"});
        SpinnerCircularListModel listModelE = new SpinnerCircularListModel(
                new String[] {"European Central Bank", "Russian Central Bank"});

        isR = DataCB.CurrencyTableCB == Table;

        BankName = new JSpinner(isR? listModelR: listModelE);

        BankName.setBounds(130, 220, 150, 40);
        BankName.setVisible(true);
        BankName.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                Table = DataCB.getTable(isR? false: true);
                Refresh(Content);
            }
        });
    }
}
