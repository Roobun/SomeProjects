package com.company;

import java.net.*;
import java.io.*;
import java.util.*;
import org.dom4j.*;
import org.dom4j.io.SAXReader;

public class Server {

    Map CurrencyTableCB;
    Map CurrencyTableECB;

    public Server() {
        CurrencyTableCB = new HashMap<String, com.company.Currency>();
        AddingRUR(CurrencyTableCB); // RUR is not included in xml file from CB :c

        ParsingCurrencyFromCB(CurrencyTableCB);

        CurrencyTableECB = new HashMap<String, com.company.Currency>();
        new com.company.ParserECB(CurrencyTableECB);
    }

    public Map getTable(boolean isCB) {
        if (isCB == true) {
            return CurrencyTableCB;
        } else {
            return CurrencyTableECB;
        }
    }

    private void AddingRUR(Map CurrencyTable) {
        com.company.Currency RUR = new com.company.Currency("RUR", 1,
                "Russian Ruble", 1);
        CurrencyTable.put("RUR", RUR);
    }

    private void ParsingCurrencyFromCB(Map CurrencyTable) {
        makeFileFromString("https://www.cbr.ru/scripts/XML_daily_eng.asp");

        try {
            File Rates = new File("Rates.txt");
            SAXReader reader = new SAXReader();
            Document document = reader.read(Rates);

            document.getRootElement().getName();

            List<Node> nodes = document.selectNodes("/ValCurs/Valute");

            for (Node node : nodes) {
                String ServerCharCode = node.selectSingleNode("CharCode").getText();

                String ServerNominalString = node.selectSingleNode("Nominal").getText();
                int ServerNominal = Integer.parseInt(ServerNominalString);

                String ServerName = node.selectSingleNode("Name").getText();

                String ServerValueString = node.selectSingleNode("Value").getText();

                ServerValueString = ConvertComma(ServerValueString);
                double ServerValue = Double.valueOf(ServerValueString);


                com.company.Currency Valute = new com.company.Currency(ServerCharCode, ServerNominal, ServerName, ServerValue);
                CurrencyTable.put(node.selectSingleNode("CharCode").getText(), Valute);
            }
        } catch (DocumentException e) {
            e.printStackTrace();
        }
    }

    private String ConvertComma(String WrongSequence) {
        int commaNumber = WrongSequence.indexOf(',');
        char[] temporary = WrongSequence.toCharArray();
        temporary[commaNumber] = '.';
        return String.valueOf(temporary);
    }

    private String getExchangeRates(String Url) {
        HttpURLConnection connection = null;

        try {
            // Create connection
            URL url = new URL(Url);

            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Content-Type",
                    "application/x-www-from-urlencoded");

            connection.setRequestProperty("Content-Language", "en-US");

            connection.setUseCaches(false);
            connection.setDoOutput(true);

            // Send request
            DataOutputStream wr = new DataOutputStream(connection.getOutputStream());
            wr.close();

            // Get response
            InputStream is = connection.getInputStream();
            BufferedReader rd = new BufferedReader(new InputStreamReader(is));
            StringBuilder response = new StringBuilder();
            String line;
            while ((line = rd.readLine()) != null) {
                response.append(line);
                response.append('\r');
            }
            rd.close();

            return  response.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        } finally {
            if (connection != null) {
                connection.disconnect();
            }
        }
    }

    private void makeFileFromString(String Url) {
        try (PrintWriter Rates = new PrintWriter("Rates.txt")) {
            Rates.println(getExchangeRates(Url));
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
