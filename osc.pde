import processing.serial.*;
import controlP5.*;

ControlP5 cp5;
int slider = 0;
int oldSlider = 0;
boolean mode = false;
int zero;
int[] data;

float zoom = 1;
float xo = 0,yo = 0;

Serial myPort;        // The serial port
float inByte;         // Incoming serial data
boolean newData = false;
int xPos = 1;         // horizontal position of the graph 

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=zero;

void setup()
{
  size(800,400);
  background(0);
  zero = height/2;
  data = new int[width];
  cp5 = new ControlP5(this);
  cp5.addSlider("slider").setPosition(10,10).setRange(-100,100);
  cp5.addButton("Mode").setValue(0).setPosition(width-75,25).setSize(50,50);
  
  drawX();
  
  /*
  myPort = new Serial(this, "com port", 9600);  
  // A serialEvent() is generated when a newline character is received :
  myPort.bufferUntil('\n');
  */
}

void draw()
{
  translate(xo,yo);
  if (mode)
  {//continuous drawing
    drawLines();
    lastxPos = xPos;
    lastheight = int(zero - slider);
    xPos++;
  }
  else
  {//draw buffer at once
  if(xPos < data.length)
    data[xPos] = slider;
    xPos++;
    if(xPos == width - 100)
    {
      drawLines(data);
    }
  }
  if (xPos >=width - 100) 
  {
      xPos = 0;
      lastxPos= 0;
      if(mode)
      background(0);  //Clear the screen.
      drawX();
  } 
  else
  {
    
  }
  drawSideMenu();
  oldSlider = slider;
}

public void Mode()
{
  mode = !mode;
  background(0);
  xPos = 0;
}

void drawX()
{
  stroke(200,0,0,155);
  strokeWeight(2);
  line(0,zero,width - 100,zero);
}
void drawLines()
{
  translate(0,0);
  stroke(255);
  strokeWeight(4);
  line(lastxPos, lastheight, xPos, zero - slider);
}
void drawLines(int[] data)
{
  stroke(255);
  strokeWeight(5);
  background(0);
  for(int i = 1; i < xPos; i++)
      {
        line(i-1,zero - data[i-1],i,zero - data[i]);
      }
}
void drawSideMenu()
{
  stroke(150);
  rect(width-100,0,width,height);
}
void mouseDragged()
{
  xo = xo + (mouseX - pmouseX) ;
  yo = yo + (mouseY - pmouseY);
}
/*
void serialEvent (Serial myPort) 
{
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) 
  {
    inString = trim(inString); // trim off whitespaces.
    inByte = float(inString);  // convert to a number.
    inByte = map(inByte, 0, 1023, 0, height); //map to the screen height.
    newData = true;
  }
}
*/