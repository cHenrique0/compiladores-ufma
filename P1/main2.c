char fita[100] = "/*";
int index = 0;

char getNextCharacter()
{
    char character = fita[index];

    return character;
}

int main(int argc, char **argv)
{
  int state = 0;
  char actual_character;
  char TOKEN[100];

  while((actual_character = getNextCharacter())){
    index++;
    switch(state) {
      case 0:
        switch(actual_character) {
          case '/': 
            state = 1; 
            TOKEN[index-1] = actual_character;
            continue;
          default:
            state = 0;
            break;
        }
      case 1:
        switch(actual_character) {
          case '*': 
            state = 2;
            TOKEN[index-1] = actual_character;
            continue;
        default:
            state = 0;
            break;
        } 
      case 2:
        switch(actual_character) {
          case '*': 
            state = 3; 
            TOKEN[index-1] = actual_character;
            continue;
          default: 
            state = 2;
            TOKEN[index-1] = actual_character;
            continue;
        }
      case 3:
        switch(actual_character) {
          case '*': 
            state = 3;
            TOKEN[index-1] = actual_character;
            continue;
          case '/': 
            state = 4;
            TOKEN[index-1] = actual_character;
            continue;
          default: continue;
        }
      case 4:
        switch(actual_character) {
          default: continue;
        }
    }
  }

  if(state != 4){
    printf('Não aceito');
    return 0;
  }
  
  printf(TOKEN);
  return 0;
}
