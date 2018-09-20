//Morse code program

// Change the "SOS" to any message you like...

const char message[ ] = "SOS";

// create constant array of the messages you want Morse'd out

// In ASCII code, 'space' is 32, '0'-'9' is 48-57, and 'A'-'Z' is 65-90

//The first 10 codes are 0 to 9, and A is “.-” and so on

const String morse[] = { ".----", "..---", "...--", "....-", ".....",

                         "-....", "--...", "---..", "----.", "-----", ".-", "-...", "-.-.", "-..",

                         ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",

                         ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",

                         "--.."
                       };

const byte led = 11; // LED

const int dotLen = 200; //delay in milliseconds

const int dashLen = 3 * dotLen; // 3X longer than the dot

const int wordLen = 7 * dotLen; // space between words.

void setup() {

  pinMode(led, OUTPUT);

}


void signalMorse(String c) { // blink out one morse code character.

  int i = 0;

  while (c[i]) { // for each dot or dash in the letter...

    digitalWrite(led, HIGH); // light on

    if (c[i] == '.') {

      delay(dotLen); // if dot, short delay

    } else if (c[i] == '-') {

      delay(dashLen); // if dash, longer delay

    }

    digitalWrite(led, LOW); // and light off again

    delay(dotLen); // off blink.

    i++; //bring in the next dot or dash from the morse letter!]'

  };

  //One dot length delay happened in the loop. A Word break is a dashLen...

  delay(dashLen - dotLen);
}

void loop() {

  int i = 0; //counter variable to move through the array

  char C; //holds each letter as it gets converted to blinks

  while (message[i]) { //fails when reaches the null term (0) of the string

    C = toupper(message[i]);

    if (C == ' ') {

      delay(wordLen); // space between words

    }

    else if (C > 47 && C < 58) { // 0-9. ASCII 48-57

      signalMorse(morse[C - 48]);

    }

    else if (C > 64 && C < 91) { // A-Z, ASCII 65-90, 10-34 in morse[]

      signalMorse(morse[C - 55]);

    }

    else {

      delay(wordLen);

    }

    i++; // move to the next character in your message

  }

  delay(2 * wordLen);

}
