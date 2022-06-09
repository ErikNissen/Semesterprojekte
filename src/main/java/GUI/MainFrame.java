package GUI;

import LeapMotion.LeapMotion;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class MainFrame {

    private int hue;
    private int saturation;
    private static int brightness;

    private Color rgb = new Color(Color.HSBtoRGB(hue, saturation, brightness));

    //constructor
    public MainFrame(int brightness){
        JFrame frame = new JFrame("LightHouse");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 500);

        JSlider slider_hue = createSlider("Hue", 0, 360, 0);
        JSlider slider_saturation = createSlider("Saturation", 0, 100, 100);

        JLabel label_hue = new JLabel("Hue: " + slider_hue.getValue());
        JLabel label_saturation = new JLabel("Saturation: " + slider_saturation.getValue());

        JPanel sliders = createPanel("");
        //add grid layout
        sliders.setLayout(new GridLayout(2, 2));
        sliders.add(label_hue);
        sliders.add(slider_hue);
        sliders.add(label_saturation);
        sliders.add(slider_saturation);

        JPanel color = createPanel("Color");
        color.setBackground(new Color(hue, saturation, brightness));
        color.setPreferredSize(new Dimension(100, 100));

        slider_hue.addChangeListener(e -> {
            color.setBackground(new Color(Color.HSBtoRGB(slider_hue.getValue() / 360f, slider_saturation.getValue() / 100f, brightness / 100f)));
            label_hue.setText("Hue: " + slider_hue.getValue());
            hue = slider_hue.getValue();
            rgb = new Color(Color.HSBtoRGB(hue, saturation, MainFrame.brightness));
        });
        slider_saturation.addChangeListener(e -> {
            color.setBackground(new Color(Color.HSBtoRGB(hue, slider_saturation.getValue() / 100f, brightness / 100f)));
            label_saturation.setText("Saturation: " + slider_saturation.getValue());
            saturation = slider_saturation.getValue();
            rgb = new Color(Color.HSBtoRGB(hue, saturation, brightness));
        });

        frame.add(sliders, BorderLayout.NORTH);
        frame.add(color, BorderLayout.CENTER);
        frame.setVisible(true);

    }
    private JSlider createSlider(String name, int min, int max, int value){
        JSlider slider = new JSlider(min, max, value);
        slider.setMajorTickSpacing(max/2);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);
        slider.setName(name);
        return slider;
    }

    private JPanel createPanel(String name){
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBorder(BorderFactory.createTitledBorder(name));
        return panel;
    }

    public int getRed(){
        return rgb.getRed();
    }

    public int getGreen(){
        return rgb.getGreen();
    }

    public int getBlue(){
        return rgb.getBlue();
    }

    public void setBrightness(int brightness){
        MainFrame.brightness = brightness;
    }
}
