package LeapMotion;

import com.leapmotion.leap.Controller;
import com.leapmotion.leap.Listener;

public class LeapListner extends Listener {
    @Override
    public void onInit(Controller controller) {
        super.onInit(controller);
        System.out.println("Init");
    }

    @Override
    public void onConnect(Controller controller) {
        super.onConnect(controller);
        System.out.println("Connected");
    }

    @Override
    public void onDisconnect(Controller controller) {
        super.onDisconnect(controller);
        System.out.println("Disconnected");
    }

    @Override
    public void onExit(Controller controller) {
        super.onExit(controller);
        System.out.println("Exited");
    }

    @Override
    public void onFrame(Controller controller) {
    }
}
