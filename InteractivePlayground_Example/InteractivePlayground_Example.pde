import ddf.minim.*;
import ddf.minim.ugens.*;

Minim minim;
Note[] scale;

color[] colourScale;

boolean[][] sequence;

int timer;
int delay = 1000;
int column;

int res = 4;
int boxes = 8;
int boxSize = 75;

int gridSize;

ControlBox[] testBoxes;

void setup(){
  size(min(displayWidth,displayHeight), min(displayWidth,displayHeight));
  
  gridSize = min(width,height) - (2 * boxSize);
  
  minim = new Minim(this);
  // load the notes needed for this resolution
  scale = new Note[res + 1];
  for (int i=0; i<scale.length; i++) {
    int octave = i / 5;
    int note = i % 5;
    scale[i] = new Note(octave, note);
  }
  
  colourScale = new color[res + 1];
  colorMode(HSB, 360, 100, 100);
  for (int i=0; i<colourScale.length; i++){
    float hue = map(boxSize + ((gridSize/res) * i), boxSize, gridSize, 300, 0);
    colourScale[i] = color(hue, 100, 80);
  }
  // initialise sequence to blank
  sequence = new boolean[res+1][res+1];
  for (int i=0; i<res+1; i++){
    for (int j=0; j<res+1; j++){
      sequence[i][j] = false;
    }
  }
  
  testBoxes = new ControlBox[boxes];
  
  for (int i=0; i<testBoxes.length; i++){
    testBoxes[i] = new ControlBox(i / res, i % res, res, gridSize, boxSize);
    sequence[i/res][i%res] = true; // set sequence note true for the box position
  }
  
  column = 0;
  timer = millis();
}

void draw(){
  colorMode(RGB, 255, 255,255);
  background(255);
  drawGrid(res);
  updateCubes();  
  if (millis() - timer > delay){
    column++;
    if (column > res){
      column = 0;
    }
    playSamples(column);
    
    timer = millis();
  }
  drawCubes(column);
}

void drawGrid(int res){
  pushMatrix();
  translate(boxSize, boxSize);
  
  stroke(0);
   for (int i = 1; i < res; i++){
     line(0, (gridSize/res) * i, gridSize, (gridSize/res) * i);
     line((gridSize/res) * i, 0, (gridSize/res) * i, gridSize);
   }
   
   noFill();
   rectMode(CORNERS);
   rect(0,0,gridSize,gridSize);
   
   popMatrix();
//   noStroke();
//   for (int i=0; i<colourScale.length; i++){
//     fill(colourScale[i]);
//     rect(20, 20 + (20 * i), 20, 20);
//   }
}

void updateCubes() {
  for (int i=0; i<testBoxes.length; i++) {
   if (testBoxes[i].moving) {
    testBoxes[i].update(mouseX, mouseY, sequence);
    for (int j = 0; j<testBoxes.length; j++){
      if (j != i) {
        testBoxes[i].checkCollision(testBoxes[j], sequence);
      }
    }
   }
  }
}

void playSamples(int col){
  for (int i=0; i<res+1; i++){
    if (sequence[col][i]){
      scale[i].playNote();
    }
  }
}

void drawCubes() {
 for(ControlBox thisBox : testBoxes){
   thisBox.render();
 }
}

void drawCubes(int col){
  colorMode(RGB, 255);
  color tempCol = color(0, 0, 0);
  for (int i=0; i<res+1; i++){
    if (sequence[col][i]){
      tempCol = blendColor(tempCol,colourScale[i], ADD);
    }
  }
  
 for(ControlBox thisBox : testBoxes){
   if (thisBox.locationState == thisBox.INTERSECTION && thisBox.gridPosX == col){
     thisBox.render(tempCol);
   } else {
     thisBox.render();
   }
 }
}

void mousePressed(){
  for (ControlBox testBox : testBoxes){
    if (testBox.checkMouse(mouseX, mouseY)){
      testBox.moving = true;
    }
  }
}

void mouseReleased(){
  for (ControlBox testBox : testBoxes) {
     if (testBox.moving){
      testBox.moving = false;
     } 
  }
}
