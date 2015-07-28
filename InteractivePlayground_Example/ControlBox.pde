class ControlBox{
 int gridPosX;
 int gridPosY;
 
 int x, y;
 int prevX, prevY;
 int boxSize;
 
 boolean moving;
 int locationState;
 int prevLocationState;
 final int INTERSECTION = 0;
 final int VERTICAL = 1;
 final int HORIZONTAL = 2;
 
 int res;
 
 int[] columns;
 int[] rows;
 
 color boxCol;
 
  public ControlBox(int initPosX, int initPosY, int gridRes, int gridSize, int size){
    gridPosX = initPosX;
    gridPosY = initPosY;
    res = gridRes;
    boxSize = size;
    
    columns = new int[res + 1];
    rows = new int[res + 1];
    
    for (int i=0; i<columns.length; i++){
      columns[i] = boxSize + (gridSize/res) * i;
      rows[i] = boxSize + (gridSize/res) * i;
    }
    
    x = columns[gridPosX];
    y = rows[gridPosY];
    
    colorMode(HSB, 360, 100, 100);
    boxCol = color(map(y, boxSize, gridSize, 300, 0), 100, 50); 
    
    
    moving = false;
    locationState = INTERSECTION;
    prevLocationState = HORIZONTAL;
  }
  
  boolean checkMouse(int mousePosX, int mousePosY){
    if (mousePosX > (x - (boxSize/2)) && mousePosX < (x + (boxSize/2))
      && mousePosY > (y - (boxSize/2)) && mousePosY < (y + (boxSize/2))){
        return true;
      } else {
        return false;
      }
  }
  
  void update(int mousePosX, int mousePosY, boolean[][] nodePositions) {
    prevX = x;
    prevY = y;
    
    if (locationState == INTERSECTION){
      // move on to row or column if mouse is outside 'snap' zone
      if (dist(mousePosX, mousePosY, columns[gridPosX], rows[gridPosY]) > boxSize/2){
        // move on to column or row depending on which the mouse is closer to
        if ( abs(mousePosY - rows[gridPosY]) < (abs(mousePosX - columns[gridPosX])) 
            && !( (gridPosX == 0 && mousePosX < columns[0]) || (gridPosX == res && mousePosX > columns[res])  ) ){
          x = mousePosX;
          locationState = HORIZONTAL;
        } else if (!( (gridPosY == 0 && mousePosY < rows[0]) || (gridPosY == res && mousePosY > rows[res])  )){
          y = mousePosY;
          locationState = VERTICAL;
        }
        if (locationState != INTERSECTION){
          nodePositions[gridPosX][gridPosY] = false;
        }
      }
    } else {    
      if (locationState == VERTICAL) {
        // move along columns
        y = mousePosY;
      } else if (locationState == HORIZONTAL) {
        // move along rows
        x = mousePosX;
      }
      
      // check if we have snapped to an intersection only if we haven't jumped really far
      if (abs(x - prevX) < boxSize && abs(y - prevY) < boxSize) {
        for (int i=0; i < columns.length; i++) {
          for (int j=0; j < rows.length; j++) {
            if (dist(x, y, columns[i], rows[j]) < (boxSize/2)){
              gridPosX = i;
              gridPosY = j;
              x = columns[i];
              y = rows[j];
              prevLocationState = locationState;
              locationState = INTERSECTION;
              nodePositions[gridPosX][gridPosY] = true;
            }
          }
        }
      }
    }
    
  }
  
  void checkCollision(ControlBox otherBox, boolean[][] nodePositions){
    if (locationState == HORIZONTAL && y == otherBox.y) {

        if ( (x > (otherBox.x - boxSize) && x < (otherBox.x + boxSize)) ){
          if (x < otherBox.x) {
            x = otherBox.x - boxSize;
          } else {
            x = otherBox.x + boxSize;
          }
        }
          
        // make sure box cannot pass through another box
        if ((x > otherBox.x && prevX < otherBox.x )|| (x < otherBox.x && prevX > otherBox.x)){
          x = prevX;
        }

    } else if (locationState == VERTICAL && x == otherBox.x) {

        if ( (y > (otherBox.y - boxSize) && y < (otherBox.y + boxSize)) ) {
            if (y < otherBox.y){
              y = otherBox.y - boxSize;
            } else {
              y = otherBox.y + boxSize;
            }
        }
        // make sure box cannot pass through another box
        if ( (y > otherBox.y && prevY < otherBox.y) || (y < otherBox.y && prevY > otherBox.y) ){
          y = prevY;
        }

    } else if (x > (otherBox.x - boxSize) && x < (otherBox.x + boxSize) 
       && y > (otherBox.y - boxSize) && y < (otherBox.y + boxSize) ) {
      
    if (locationState == INTERSECTION){
         
          if (prevLocationState == HORIZONTAL) {
            if (x < otherBox.x) {
              x = otherBox.x - boxSize;
            } else {
              x = otherBox.x + boxSize;
            }
            
            locationState = HORIZONTAL;
            
          } else if (prevLocationState == VERTICAL) {
            if (y < otherBox.y){
              y = otherBox.y - boxSize;
            } else {
              y = otherBox.y + boxSize;
            }
            
            locationState = VERTICAL;
          }
          
          if (otherBox.locationState != INTERSECTION){
            nodePositions[gridPosX][gridPosY] = false;
          }
          
       } else if (locationState == HORIZONTAL) {
         x = prevX;
       } else if (locationState == VERTICAL) {
         y = prevY;
       }
       
    }
    
  }
  
  void render(){
    // update box colour based on y position
    colorMode(HSB, 360, 100, 100);
    boxCol = color(map(y, boxSize, boxSize + gridSize, 300, 0), 100, 50); 
    
    render(boxCol);
  }
  
  void render(color boxColour){
    noStroke();
    rectMode(CENTER);
    
    fill(boxColour);
    rect(x,y,boxSize,boxSize);
  }
  
  
  
}
