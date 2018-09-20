package com.company;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import org.w3c.dom.Element;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.InputStream;
import java.net.URL;
import java.util.Map;

public class ParserECB {
    ParserECB(Map Table) {
        try {
            InputStream is = new URL("https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml").openStream();

            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document doc = db.parse(is);

            NodeList nodeList = doc.getElementsByTagName("Cube");

            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;

                    String name = element.getAttribute("currency");
                    if (name.isEmpty() == true) {
                        continue;
                    }
                    String rate = element.getAttribute("rate");
                    double value = Double.valueOf(rate);

                    com.company.Currency currency = new com.company.Currency(name, 1, "", value);
                    Table.put(name, currency);
                }
            }
            Table.put("EUR", new com.company.Currency("EUR", 1, "", 1));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}