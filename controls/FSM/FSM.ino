enum State {
  IDLE, 
  TUTORIAL, 
  PLAY, 
  SCORE_AND_RETRIEVAL, 
  ENDGAME, 
  RESET,
  ERROR
};

State state = IDLE;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  bool anybutton_pressed;
  switch (state) {
    case IDLE:
      if (anybutton_pressed) {
        state = TUTORIAL;
      }
      break;

    case TUTORIAL:
      if (anybutton_pressed) {
        state = PLAY;
        break;
      }
      break;

    case PLAY:
      if (first_play) {
        everybody wakes up (mainly environment stuff)
      }
      if (been a while) {
        state = RESET;
      }
      if (somebody scored) {
        state = SCORE_AND_RETRIEVAL;
      }
      break;

    case SCORE_AND_RETRIEVAL:
      wait until retrieved
      if (been a while and still no ball) {
        state = ERROR;
        break
      } 
      if (no one lost yet) {
        state = PLAY;
      } else {
        state = ENDGAME;
      }
      break;

    case ENDGAME:
      display something
      state = RESET;
      break;

    case RESET:
      everyone dies
      clear variables
      return to where you come from
      break;
    
    case ERROR:
      cry
      red color and cry more
      send email
    default:
      exit(1);
      break;
    }

}
