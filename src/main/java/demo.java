import LightHouse.*;
import LeapMotion.*;
import OSC.*;
import com.illposed.osc.OSCSerializeException;
import com.leapmotion.leap.Gesture;
import org.json.JSONObject;
import java.io.IOException;
import java.time.Duration;
import java.time.Instant;
import java.util.*;

public class demo {

    public static void main(String[] args) throws IOException,
            OSCSerializeException, InterruptedException {
        LightHouse.Reset("127.0.0.1", 9001, "/lighthouse/light");
        //MainFrame mainFrame = new MainFrame(255);
        JSONObject data = new JSONObject();
        LeapMotion leapMotion = new LeapMotion();
        Duration dt;
        Instant t0 = Instant.now();
        Integer counter = 0;
        Map<Integer, List<Integer>> coords = new HashMap<>();
        JSONObject color = new JSONObject();
        color.put("red", 255);
        color.put("green", 0);
        color.put("blue", 0);
        boolean leftHand = false;
        do {

            while (data.isEmpty()) {

                data = leapMotion.getData();
                leftHand = data.has("Linke Hand") &&
                        data.getJSONObject("Linke Hand").has("Finger");
                dt = Duration.between(t0, Instant.now());

                if (dt.getSeconds() > 5 && leftHand) {
                    LightHouse.resetLED(coords, "127.0.0.1", 9001,
                            "/lighthouse/light");
                    t0 = Instant.now();
                    coords = new HashMap<>();
                }
            }
            String path = "/lighthouse/light";

            //if gesture is detected
            if(leapMotion.getCon().frame().gestures().count() > 0){

                //get the first gesture
                Gesture gesture = leapMotion.getCon().frame().gestures().get(0);
                int brightness = data
                        .getJSONObject(leftHand? "Linke Hand" : "Rechte Hand")
                        .getJSONObject("Finger")
                        .getJSONObject("Mittelfinger")
                        .getJSONObject("Position").getInt("z");

                //if the gesture is a circle
                if(gesture.type() == Gesture.Type.TYPE_CIRCLE){
                    color = leapMotion.colorPicker(brightness, gesture);
                }
            }

            JSONObject param = LeapMotion.getParams(data, color);
            //mainFrame.setBrightness(param.getInt("z"));
            List<Integer> tc = new ArrayList<>();
            tc.add(param.getJSONObject("param").getInt("x"));
            tc.add(param.getJSONObject("param").getInt("y"));
            coords.put(counter, tc);
            counter++;

            //System.out.println(param);

            OSC osc = new OSC();
            osc.setPort(9001);
            osc.setIP("127.0.0.1");
            osc.Sender(path, param.getJSONObject("param"));
            dt = Duration.between(t0, Instant.now());

            if (dt.getSeconds() > 0 && data.has("Linke Hand") &&
                    data.getJSONObject("Linke Hand").has("Finger")) {

                LightHouse.resetLED(coords, "127.0.0.1", 9001,
                        "/lighthouse/light");
                t0 = Instant.now();
                coords = new HashMap<>();
            }
            data = new JSONObject();
        } while (true);
    }
}