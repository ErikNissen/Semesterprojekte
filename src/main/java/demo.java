import GUI.MainFrame;
import LightHouse.*;
import LeapMotion.*;
import OSC.*;
import com.illposed.osc.OSCSerializeException;
import org.json.JSONObject;

import java.io.IOException;
import java.time.Duration;
import java.time.Instant;
import java.util.*;

public class demo {

    public static void main(String[] args) throws IOException, OSCSerializeException, InterruptedException {
        LightHouse.Reset("127.0.0.1", 9001, "/lighthouse/light");
        //MainFrame mainFrame = new MainFrame(255);
        JSONObject data = new JSONObject();
        LeapMotion leapMotion = new LeapMotion();
        Duration dt;
        Instant t0 = Instant.now();
        Integer counter = 0;
        Map<Integer, List<Integer>> coords = new HashMap<>();
        JSONObject color = new JSONObject();
        boolean leftHand = false;
        do {
            while (data.isEmpty()) {

                data = leapMotion.getData();
                leftHand = data.has("Linke Hand") && data.getJSONObject("Linke Hand").has("Finger");
                dt = Duration.between(t0, Instant.now());
                if (dt.getSeconds() > 5 && leftHand) {
                    LightHouse.resetLED(coords, "127.0.0.1", 9001, "/lighthouse/light");
                    t0 = Instant.now();
                    coords = new HashMap<>();
                }
            }
            String path = "/lighthouse/light";
            while (color.isEmpty()){
                JSONObject tmp = leapMotion.colorPicker(data.getJSONObject(leftHand ? "Linke Hand" : "Rechte Hand").getJSONObject("Finger").getJSONObject("Zeigefinger").getJSONObject("Position").getInt("z"));
                if(tmp.getInt("red") == tmp.getInt("green") && tmp.getInt("red") == tmp.getInt("blue") && tmp.getInt("red") == 0 && color.isEmpty()){
                    color.put("red", 0);
                    color.put("green", 0);
                    color.put("blue", 0);
                }else {
                    color = tmp;
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
            if (dt.getSeconds() > 0 && data.has("Linke Hand") &&  data.getJSONObject("Linke Hand").has("Finger")) {
                LightHouse.resetLED(coords, "127.0.0.1", 9001, "/lighthouse/light");
                t0 = Instant.now();
                coords = new HashMap<>();
            }
            data = new JSONObject();
        } while (true);
    }
}