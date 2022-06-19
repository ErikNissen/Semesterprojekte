package LeapMotion;

import com.leapmotion.leap.Finger;
import com.leapmotion.leap.Hand;
import org.json.JSONObject;
import org.json.JSONTokener;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import static org.junit.jupiter.api.Assertions.*;

import java.awt.Color;

class LeapMotionTest {

    @AfterEach
    void tearDown() {
        System.out.println("Test passed");
    }

    //@Mock
    //private LeapMotion lm;

    @InjectMocks
    private LeapMotion lm = new LeapMotion();

    @Test
    public void testhsb2rgb() throws NoSuchMethodException,
            InvocationTargetException, IllegalAccessException {
        Method m = LeapMotion.class.getDeclaredMethod("hsb2rgb",
                int.class, int.class, int.class);

        m.setAccessible(true);

        for (int hue = 0; hue < 360; hue+=25) {
            for (int saturation = 0; saturation < 100; saturation+=25) {
                for (int brightness = 0; brightness < 100; brightness+=25) {
                    int rgb = Color.HSBtoRGB(hue / 360.0f,
                            saturation / 100.0f,
                            brightness / 100.0f);
                    Color soll = new Color(rgb);
                    int[] ist = (int[]) m.invoke(lm, hue, saturation,
                            brightness);
                    Color ist1 = new Color(ist[0], ist[1], ist[2]);
                    assertEquals(soll, ist1);
                }
            }
        }
        int rgb = Color.HSBtoRGB(-1 / 360.0f, 0 / 100.0f,
                0 / 100.0f);
        Color soll = new Color(rgb);
        int[] ist = (int[]) m.invoke(lm, -1, 0, 0);
        assertNull(ist);

        rgb = Color.HSBtoRGB(0 / 360.0f, -1 / 100.0f,
                0 / 100.0f);
        soll = new Color(rgb);
        ist = (int[]) m.invoke(lm, 0, -1, 0);
        assertNull(ist);

        rgb = Color.HSBtoRGB(0 / 360.0f, 0 / 100.0f,
                -1 / 100.0f);
        soll = new Color(rgb);
        ist = (int[]) m.invoke(lm, 0, 0, -1);
        assertNull(ist);

        ist = (int[]) m.invoke(lm, 361, 0, 0);
        assertNull(ist);

        ist = (int[]) m.invoke(lm, 0, 101, 0);
        assertNull(ist);

        ist = (int[]) m.invoke(lm, 0, 0, 101);
        assertNull(ist);
    }

    @Mock
    Hand h = new Hand();
    @Test
    public void testgetFingers() throws NoSuchMethodException {
        Method m = LeapMotion.class.getDeclaredMethod("getFingers", Hand.class);
        m.setAccessible(true);
        JSONObject data = new JSONObject();

    }

    @Test
    public void testgetCoord() throws NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        Method m = LeapMotion.class.getDeclaredMethod("getCoord", boolean.class, String.class, JSONObject.class, String.class);
        m.setAccessible(true);

        for(int x = 0; x < 100; x+=10) {
            for(int y = 0; y < 100; y+=10) {
                for(int z = 0; z < 100; z+=10) {
                    int x2 = 0, y2 = 0, z2 = 0;
                    for(int i = 0; i < 100; i++){
                        //generate coordinates with range of 2 percent deviation
                        int x1 = (int) (x + (Math.random() * 2 - 1) * x / 100);
                        int y1 = (int) (y + (Math.random() * 2 - 1) * y / 100);
                        int z1 = (int) (z + (Math.random() * 2 - 1) * z / 100);
                        x2 += x1;
                        y2 += y1;
                        z2 += z1;
                    }
                    x2 /= 100;
                    y2 /= 100;
                    z2 /= 100;
                    JSONObject data = new JSONObject(new JSONTokener("""
                            {
                                'Linke Hand': {
                                    'Finger': {
                                        'Daumen': {
                                            'Position': {
                                                'x':""" + x2 + """
                                                ,
                                                'y':""" + y2 + """
                                                ,
                                                'z':""" + z2 + """
                                            }
                                        },
                                        'Zeigefinger': {
                                            'Position': {
                                                'x':""" + x2 + """
                                                ,
                                                'y':""" + y2 + """
                                                ,
                                                'z':""" + z2 + """
                                            }
                                        },    
                                        'Mittelfinger': {
                                            'Position': {
                                                'x':""" + x2 + """
                                                ,
                                                'y':""" + y2 + """
                                                ,
                                                'z':""" + z2 + """
                                            }
                                        },
                                        'Ringfinger': {
                                            'Position': {
                                                'x':""" + x2 + """
                                                ,
                                                'y':""" + y2 + """
                                                ,
                                                'z':""" + z2 + """
                                            }
                                        },
                                        'kleiner Finger': {
                                            'Position': {
                                                'x':""" + x2 + """
                                                ,
                                                'y':""" + y2 + """
                                                ,
                                                'z':""" + z2 + """
                                            }
                                        }
                                    }
                                }
                            }
                            """));
                    int avg = (int) m.invoke(lm, true, "Daumen", data, "x");
                    assertEquals(avg, x2);

                    avg = (int) m.invoke(lm, true, "Daumen", data, "y");
                    assertEquals(avg, y2);

                    avg = (int) m.invoke(lm, true, "Daumen", data, "z");
                    assertEquals(avg, z2);

                    avg = (int) m.invoke(lm, true, "Zeigefinger", data, "x");
                    assertEquals(avg, x2);

                    avg = (int) m.invoke(lm, true, "Zeigefinger", data, "y");
                    assertEquals(avg, y2);

                    avg = (int) m.invoke(lm, true, "Zeigefinger", data, "z");
                    assertEquals(avg, z2);

                    avg = (int) m.invoke(lm, true, "Mittelfinger", data, "x");
                    assertEquals(avg, x2);

                    avg = (int) m.invoke(lm, true, "Mittelfinger", data, "y");
                    assertEquals(avg, y2);

                    avg = (int) m.invoke(lm, true, "Mittelfinger", data, "z");
                    assertEquals(avg, z2);

                    avg = (int) m.invoke(lm, true, "Ringfinger", data, "x");
                    assertEquals(avg, x2);

                    avg = (int) m.invoke(lm, true, "Ringfinger", data, "y");
                    assertEquals(avg, y2);

                    avg = (int) m.invoke(lm, true, "Ringfinger", data, "z");
                    assertEquals(avg, z2);

                    avg = (int) m.invoke(lm, true, "kleiner Finger", data, "x");
                    assertEquals(avg, x2);

                    avg = (int) m.invoke(lm, true, "kleiner Finger", data, "y");
                    assertEquals(avg, y2);

                    avg = (int) m.invoke(lm, true, "kleiner Finger", data, "z");
                    assertEquals(avg, z2);
                }
            }
        }
    }
}