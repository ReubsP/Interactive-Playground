class Note {
  AudioSample sample; 
  
  Note(int octave, int note){
    String fileToLoad = "Pentatonic_O" + octave + "N" + note + ".wav";
    sample = minim.loadSample(fileToLoad, 512);
  }
  
  void playNote() {
    sample.trigger();
  }
  
  void closeNote() {
    sample.close();
  }
  
}
