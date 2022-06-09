package LeapMotion;

import com.leapmotion.leap.*;

import java.awt.*;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.leapmotion.leap.Frame;
import org.json.JSONObject;


public class LeapMotion {
    private final LeapListner lis;
    private final Controller con;

    //Constructor
    public LeapMotion() {
        lis = new LeapListner();
        con = new Controller(lis);
        con.enableGesture(Gesture.Type.TYPE_CIRCLE);
    }

    /**
     * @return hue value of the HSB color space
     * */
    public JSONObject colorPicker(int brightness){
        JSONObject color = new JSONObject();
        color.put("red", 0);
        color.put("green", 0);
        color.put("blue", 0);
        //if gesture is detected
        if (con.frame().gestures().count() > 0) {
            //get the first gesture
            Gesture gesture = con.frame().gestures().get(0);
            //if the gesture is a circle
            if (gesture.type() == Gesture.Type.TYPE_CIRCLE) {
                //get the circle gesture
                CircleGesture circle = new CircleGesture(gesture);
                //get the pointable
                Pointable pointable = circle.pointable();
                //get the direction of the pointable
                Vector direction = pointable.direction();
                //get the angle of the direction
                float angle = direction.angleTo(circle.normal());
                //get the angle in degrees
                angle = (float) Math.toDegrees(angle);
                //convert hsb to rgb
                int rgb = Color.HSBtoRGB((int) (angle / 360), 100, brightness);
                //get the rgb values
                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = rgb & 0xFF;
                //set the values in the json object
                color.put("red", r);
                color.put("green", g);
                color.put("blue", b);
            }
        }
        return color;
    }

    /**
     * @return Handdaten
     * */
    public JSONObject getData() {
        JSONObject data = new JSONObject();
        JSONObject leftHand = new JSONObject();
        JSONObject rightHand = new JSONObject();
        /*
         * INDEX = Zeigefinger
         * THUMB = Daumen
         * MIDDLE = Mittelfinger
         * PINKY = kleiner Finger
         * RING = Ringfinger
         * */
        Frame frame = this.con.frame();
        for (Hand h : frame.hands()) {
            if (h.isLeft()) {
                leftHand.put("Handflächenposition", h.palmPosition());
                leftHand.put("Finger", getFingers(h));
            } else {
                rightHand.put("Handflächenposition", h.palmPosition());
                rightHand.put("Finger", getFingers(h));
            }
            data.put("Linke Hand", leftHand);
            data.put("Rechte Hand", rightHand);
        }
        return data;
    }

    /**
     * @param data  Handdaten
     * @param color RGB im Format 0 >= {r, g, b} <= 255 mit den keys "red", "green", "blue"
     * @return      JSONObject mit Koordinaten & RGB Wert
     */
    public static JSONObject getParams(JSONObject data, JSONObject color) {
        assert color.has("red") && color.has("green") && color.has("blue");
        assert 0 >= color.getInt("red") && color.getInt("red") <= 255;
        assert 0 >= color.getInt("green") && color.getInt("green") <= 255;
        assert 0 >= color.getInt("blue") && color.getInt("blue") <= 255;

        boolean leftHand = data.getJSONObject("Linke Hand").has("Finger");
        List<Byte> coords = getCoords(leftHand, data, "Zeigefinger");
        JSONObject o = new JSONObject();
        JSONObject map = new JSONObject();

        o.put("x", coords.get(0));
        o.put("y", coords.get(1));
        o.put("r", color.getInt("red") / 100 * coords.get(2));
        o.put("g", color.getInt("green") / 100 * coords.get(2));
        o.put("b", color.getInt("blue") / 100 * coords.get(2));

        map.put("param", o);
        map.put("z", coords.get(2));

        return map;
    }

    /**
     * @param f Finger
     * @return  Fingerdaten
     * */
    private static Map<String, Object> parseData(Finger f) {
        Map<String, Object> data = new HashMap<>();
        data.put("Position", f.tipPosition());
        data.put("Raised", f.isExtended());
        return data;
    }

    /**
     * @param h Hand
     * @return  Liste mit den Fingerdaten
     * */
    private static JSONObject getFingers(Hand h){
        JSONObject data = new JSONObject();
        for (Finger f : h.fingers()){
            switch (f.type()) {
                case TYPE_THUMB -> data.put("Daumen", parseData(f));
                case TYPE_INDEX -> data.put("Zeigefinger", parseData(f));
                case TYPE_MIDDLE -> data.put("Mittelfinger", parseData(f));
                case TYPE_RING -> data.put("Ringfinger", parseData(f));
                case TYPE_PINKY -> data.put("kleiner Finger", parseData(f));
            }
        }
        return data;
    }

    /**
     * @param left      true = linke Hand, false = rechte Hand
     * @param finger    Fingerdaten
     * @param data      Handdaten
     * @param axis      x, y, z
     * @return          Coordinate like x, y or z
     * */
    private static int getCoord(boolean left, String finger, JSONObject data, String axis){
        byte iterations = 100;
        int avg = 0;
        for(byte i = 0; i < iterations; i++){
            avg += data.getJSONObject(left ? "Linke Hand" : "Rechte Hand").getJSONObject("Finger")
                    .getJSONObject(finger).getJSONObject("Position").getInt(axis);
        }
        return avg / iterations;
    }

    /**
     * @param left      true = linke Hand, false = rechte Hand
     * @param data      Handdaten
     * @param finger    Finger
     * @return          List of coords
     * */
    private static List<Byte> getCoords(boolean left, JSONObject data, String finger){
        byte xCoord, yCoord, zCoord;
        xCoord = (byte) (getCoord(left, finger, data, "x") % 35);
        if (xCoord < 0) xCoord *= -1;
        yCoord = (byte) (getCoord(left, finger, data, "y") % 8);
        if (yCoord < 0) yCoord *= -1;
        zCoord = (byte) (getCoord(left, finger, data, "z") % 100);
        if (zCoord < 0) zCoord *= -1;
        return List.of(xCoord, yCoord, zCoord);
    }

    /**
     * Main Methode
     * */
    public void main(String[] args) {
        LeapMotion lm = new LeapMotion();
        con.addListener(lis);

        JSONObject data = new JSONObject();
        JSONObject color = new JSONObject();
        color.put("red", 100);
        color.put("green", 60);
        color.put("blue", 25);

        while (data.isEmpty()){
            data = lm.getData();
        }
        System.out.println(data.toString(4));
        System.out.println(getParams(data, color));
    }
}