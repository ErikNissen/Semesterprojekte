//// SETUP LOGIC

// Die Funktion "initVariablen()" gibt allen Variablen Werte. Zur Veränderung des Visuals Variablen hier anpassen
// FuntionsInput: NULL => Es wird nichts übergeben, die Funktion ist lediglich zur Verbesserung der Lesbarkeit. 
// FunktionsOutput: NULL => Es wird kein Rückgabewert erwartet. 
void initVariablen()
{
  // Layout des Hochhaus
  spaceBetweenWindowsY = 50;
  windowSize =  27;
  xWindowLeft = 16;
  xWindowRight = 19;
  yWindow = 8;

  // Abstände in Pixel für x-Richtung
  xBraunerRand = 50;
  xAbstandWeissRechteckFenster = 5;
  xAbstandFensterWeissRechteck = 10;
  xAbstandSchwarzeLinie = 5;
  xBacksteinTreppenhaus = 90;

  // Abstände in Pixel für y-Richtung
  yBraunerRandOben = 50;
  yBraunerRandUnten = 30;
  yWeisserRand = 10;
}


// Die Funktion "fillArray()" füllt den Array mit Nullen = "Lichter aus".
// FuntionsInput: NULL => Es wird nichts übergeben, die Funktion ist lediglich zur Verbesserung der Lesbarkeit. 
// FunktionsOutput: NULL => Es wird kein Rückgabewert erwartet.
void fillArray()
{
  // 3D Array 1.[] = x-Koordinate = "Fensterposistion"; 2.[] = y-Koordinate = "Stockwerk"; 3.[] = RGB Farbwerte LED
  colorArray  = new int[35][8][3];

  for (int i=0; i<colorArray.length; i++)
  { 
    for (int j=0; j < colorArray[0].length; j++)
    {
      for (int k=0; k< colorArray[0][0].length; k++)
      {
        colorArray[i][j][k] = 0;
      }
    }
  }
}

// Die Funktion "calculateWidth()" dient zur dynamischen Berechnung von "width" des Bildschirms
// FunktionsInput: Keine Parameterübergabe nötig, nur Berechnung.
// FunktionsOutput: Das Ergebniss muss in size() hard codiert werden, weil size() Integer erwartet.
int calculateWidth()
{
  return 2 * xBraunerRand+ 2 * xAbstandWeissRechteckFenster + 2 * xAbstandFensterWeissRechteck + xBacksteinTreppenhaus + (xWindowLeft+xWindowRight) * windowSize;
}

// Die Funktion "calculateHeight()" dient zur dynamischen Berechnung von "height" des Bildschirms
// FunktionsInput: Keine Parameterübergabe nötig, nur Berechnung.
// FunktionsOutput: Das Ergebniss muss in size() hard codiert werden, weil size() Integer erwartet.
int calculateHeight()
{
  return yBraunerRandOben + yBraunerRandUnten + yWindow * spaceBetweenWindowsY;
}



//// DRAW LOGIC

// Die Funktion "drawWand()" zeichnet das Hochhaus ohne Fenster.
// Die Farblayer werden von außen nach innen aufgebaut und abgebildet
void drawWand()
{
  // Außenwand - Backsteinfarbe
  background(#904104);

  // Fensterfront - weißes Rechteck
  noStroke();
  fill(233);
  rect(xBraunerRand, 
    yBraunerRandOben, 
    width - (2*xBraunerRand), 
    height - (yBraunerRandOben+yBraunerRandUnten));

  // Treppenhaus in der Mitte - Backsteinfarbe
  fill(#904104);
  rect(xWindowLeft * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + xAbstandFensterWeissRechteck, 
    0, 
    xBacksteinTreppenhaus, 
    height);

  // Schwarze Linien für die Begrenzungen zum Treppenhaus
  stroke(0x00);
  strokeWeight(2);

  // Linke Linie
  line(xWindowLeft * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + xAbstandFensterWeissRechteck + xAbstandSchwarzeLinie, 
    0, 
    xWindowLeft * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + xAbstandFensterWeissRechteck + xAbstandSchwarzeLinie, 
    height);
  
  // Rechte Linie    
  line((xWindowLeft * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + xAbstandFensterWeissRechteck) + xBacksteinTreppenhaus - xAbstandSchwarzeLinie, 
    0, 
    (xWindowLeft * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + xAbstandFensterWeissRechteck) + xBacksteinTreppenhaus - xAbstandSchwarzeLinie, 
    height);
}

// Die Funktion "drawFenster()" zeichnet die Fenster mit LED Farbwerten
void drawFenster()
{
  // strokeWeight zurück auf "1" setzten für weiteres arbeiten
  strokeWeight(1);

  //// Linke Fenster Front
  for (int i = 0; i < xWindowLeft; i++)
  {
    for (int j = 0; j < yWindow; j++) 
    { 
      // Übergabe Farbwerte für das Fenster
      fill(colorArray[i][j][0], colorArray[i][j][1], colorArray[i][j][2]);
      // weißer Rahmen um die Fenster
      stroke(0xff);
      // das Fenster
      rect(i * windowSize + xBraunerRand + xAbstandWeissRechteckFenster, 
        j * spaceBetweenWindowsY + yBraunerRandOben + yWeisserRand, 
        windowSize, 
        windowSize);
    }
  }

  //// Rechte Fenster Front
  for (int i = 0; i < xWindowRight; i++)
  {
    for (int j = 0; j < yWindow; j++) 
    {
      // Übergabe Farbwerte für das Fenster
      fill(colorArray[i + xWindowLeft][j][0], colorArray[i + xWindowLeft][j][1], colorArray[i + xWindowLeft][j][2]);
      // weißer Rahmen um die Fenster
      stroke(0xff);
      // das Fenster
      rect((i + xWindowLeft) * windowSize + xBraunerRand + xAbstandWeissRechteckFenster + 2 * xAbstandFensterWeissRechteck + xBacksteinTreppenhaus, 
        j * spaceBetweenWindowsY + yBraunerRandOben + yWeisserRand, 
        windowSize, 
        windowSize);
    }
  }
}
