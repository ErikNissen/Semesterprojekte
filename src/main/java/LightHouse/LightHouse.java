package LightHouse;

import OSC.OSC;
import org.json.JSONObject;

import java.util.List;
import java.util.Map;

public class LightHouse {
    public static void Reset(String ip, Integer port, String path){
        OSC osc = new OSC();
        osc.setIP(ip);
        osc.setPort(port);
        for (byte x = 0; x <= 34; x++){
            for (byte y = 0; y <= 7; y++){
                JSONObject param = new JSONObject();
                param.put("x", x);
                param.put("y", y);
                param.put("r", 0);
                param.put("g", 0);
                param.put("b", 0);
                osc.Sender(path, param);
            }
        }
    }

    public static void resetLED(Map<Integer, List<Integer>> coords, String ip, Integer port, String path) {
        OSC osc = new OSC();
        osc.setIP(ip);
        osc.setPort(port);
        for(Integer index : coords.keySet()){
            JSONObject param = new JSONObject();
            param.put("x", coords.get(index).get(0));
            param.put("y", coords.get(index).get(1));
            param.put("r", 0);
            param.put("g", 0);
            param.put("b", 0);
            osc.Sender(path, param);
        }
    }
}
