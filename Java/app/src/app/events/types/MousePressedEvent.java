package app.events.types;

import app.events.Event;

public class MousePressedEvent extends MouseButtonEvent {

    public MousePressedEvent(int keyCode, int x, int y) {
        super(Type.MOUSE_PRESSED, keyCode, x, y);
    }
}

