package OSC;

import com.illposed.osc.OSCMessage;
import com.illposed.osc.OSCSerializeException;
import com.illposed.osc.transport.OSCPortOut;
import org.json.JSONObject;

import java.io.IOException;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.List;

public class OSC {
    private static String ip;
    private static Integer port;
    public void Sender(String path, JSONObject param){
        assert param.has("xCoord") && param.has("yCoord") && param.has("red")
                && param.has("green") && param.has("blue");


        try {
            OSCPortOut sender = null;
            while (sender == null){
                try {
                    sender = new OSCPortOut(InetAddress.getByName(this.getIP()), this.getPort());
                } catch (SocketException ignored) {
                }
            }

            List<Object> data = new ArrayList<>();
            data.add(param.getInt("r"));
            data.add(param.getInt("g"));
            data.add(param.getInt("b"));

            path = path + "x" + param.getInt("x") + "y" + param.getInt("y");

            OSCMessage msg = new OSCMessage(path, data);

            sender.send(msg);

        }catch (IOException | OSCSerializeException e){
            e.printStackTrace();
        }
    }

    public String getIP() {
        return ip;
    }

    public void setIP(String ip) {
        OSC.ip = ip;
    }

    public Integer getPort() {
        return port;
    }

    public void setPort(Integer port) {
        OSC.port = port;
    }
}
