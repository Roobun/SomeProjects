package app;

import app.core.Window;
import app.sandbox.Example;

import java.awt.*;

public class Main {

    public static void main(String[] args) {
        Window window = new Window("Window", 960, 640);
        window.addLayer(new Example("Layer-1", Color.BLUE));
        window.addLayer(new Example("Layer-2", Color.RED));
    }
}
