/*
 // Author: Rosa Julia Denich & Michel Siegert
 // Projekt: Lighthouse
 */

import oscP5.*;

//// OSC Objekte
OscP5 myOsc;

//// Varibalen zum zeichnen
int colorArray[][][];
int yWindow, xWindowLeft, xWindowRight, windowSize;
int spaceBetweenWindowsY;
// Varibalen für die Pixelabstände im Visual zwischen den verschiedenen Objekten. 
// Wird für die rechte Seite des Hochhauses an der x-Achse gespiegelt.
int xBraunerRand, 
    xAbstandWeissRechteckFenster, 
    xAbstandFensterWeissRechteck, 
    xAbstandSchwarzeLinie, 
    xBacksteinTreppenhaus, 
    yBraunerRandOben, 
    yBraunerRandUnten, 
    yWeisserRand;

void setup()
{
  // size() hat die Größe des Hochhauses
  // width & height werden in der Funktion calculateWidth, calculateHeight errechnet und müssen in size() hard codiert werden.
  size(1165, 480);

  // OSC läuft auf Port 9001 ggf ändern, wenn anderer Port benutzt werden soll
  myOsc = new OscP5(this, 9001);
  

  fillArray();
  initVariablen();
}


void draw()
{
  drawWand();
  drawFenster();
}


//// Parsen der OSC Message
void oscEvent(OscMessage theOscMessage) 
{
  // Generic Output für OSC
  println("\n\n");
  print("### received an osc message.");
  print(" addrpattern: "+ theOscMessage.addrPattern());
  println(" typetag: "+ theOscMessage.typetag());
  println("R: " + theOscMessage.get(0).intValue() + " G: " + theOscMessage.get(1).intValue() + " B: " + theOscMessage.get(2).intValue());


  // Addresspattern Abfrage  
  if (theOscMessage.addrPattern().contains("lighthouse/light"))
  {
    // AddressPattern in Variable adresse speichern 
    String adresse = theOscMessage.addrPattern();

    // Den gespeicherten String in "adresse" untersuchen und die Anzahl der Charakter zwischen "x" und "y" in "numDigits" speichern.  
    int numDigits = adresse.indexOf("y") - adresse.indexOf("x");

    // Wandelt die gespeicherten Charakter in Interger um und speichert den Intergerwert von "x" in "xc" und "y" in "yc"
    int xc = Integer.parseInt(adresse.substring(adresse.indexOf("x") + 1, adresse.indexOf("x") + numDigits));
    int yc = Integer.parseInt(adresse.substring(adresse.indexOf("y") + 1));

    // Testausgabe der Werte
    //println("xc: " + xc + " yc: " + yc);
    
    // Die IncomingMessage für Fensterposition (x,y) muss "-1" gerechnet werden, damit im Array die richtige Position angesteuert wird. 
    //xc = xc - 1;
    //yc = yc - 1;
    
    // Testausgabe der Werte
    //println("ArrayPos xc: " + xc + " ArrayPos yc: " + yc + "\n");
    

    // Holt sich die 3 Farbwerte 
    colorArray[xc][yc][0] = theOscMessage.get(0).intValue();
    colorArray[xc][yc][1] = theOscMessage.get(1).intValue();
    colorArray[xc][yc][2] = theOscMessage.get(2).intValue();
  }
}
