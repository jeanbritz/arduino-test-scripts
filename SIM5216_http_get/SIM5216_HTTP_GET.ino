
// Included header files
#include <SoftwareSerial.h>


// AT command related
#define AT_CREG_QUERY ("AT+CREG?")
#define AT_CHTTPACT_COMMAND ("AT+CHTTPACT=\"%s\",%d")
#define AT_CHTTPACT_INIT_RESPONSE ("+CHTTPACT: REQUEST")
#define AT_CHTTPACT_DATA_RESPONSE ("+CHTTPACT: DATA,")
#define AT_CHTTPACT_DONE_RESPONSE ("+CHTTPACT:0")

#define EOS ('\0')
#define ESC (0x1A)
#define OK ("OK")

// GSM definitions
#define unoTXPin (7) // Uno -> GSM
#define unoRXPin (6) // Uno <- GSM
#define powerGSMPin (8)
#define GSMBaudRate (9600)
#define UnoBaudRate (9600)

SoftwareSerial gsmSerial(unoRXPin,unoTXPin);

#define TEST_REQUEST ("GET /test/ HTTP/1.1\r\nHost:ml.sun.ac.za:8000\r\nContent-Length:0\r\n\r\n")
char aux_str [100];

int8_t answer;
int aux = 0;
int data_size = 0;


#define HOST_NAME ("ml.sun.ac.za") 
#define HOST_PORT (8000)

void setup() {

    
  // init sequence
  Serial.begin(UnoBaudRate);
  gsmSerial.begin(UnoBaudRate);
  
  gsm_power_on();
  while( (sendATcommand(AT_CREG_QUERY, "+CREG: 0,1", 500) || 
    sendATcommand(AT_CREG_QUERY, "+CREG: 0,5", 500)) == 0 );
  Serial.println(F("GSM : Registered to network"));
  Serial.println(F("GSM : Ready for AT command"));
}
void loop () {

    sprintf(aux_str, AT_CHTTPACT_COMMAND, HOST_NAME, HOST_PORT);
    Serial.println(F("\n*** Start HTTP Transaction ***\n"));
    Serial.println(AT_CHTTPACT_INIT_RESPONSE);

    answer = sendATcommand(aux_str, AT_CHTTPACT_INIT_RESPONSE, 60000);
    Serial.println(aux_str);
    if (answer == 1)
    {  

      data_size = 0;
      
      Serial.println(F("Sends Request:"));
      Serial.println(TEST_REQUEST);    
      gsmSerial.println(TEST_REQUEST);
      // Sends 
      aux_str[0] = ESC;
      aux_str[1] = 0x00;
      answer = sendATcommand(aux_str, AT_CHTTPACT_DATA_RESPONSE, 100000);

      if(answer == 1)
      {
        Serial.println(AT_CHTTPACT_DATA_RESPONSE);
       
          while(gsmSerial.available() > 0) {
            Serial.print((char)gsmSerial.read());
          }
        
        }
       
      Serial.println(F("\n*** End HTTP Transaction ***\n"));
      Serial.print(F("Memory Free : "));
      Serial.println(memoryFree());
      while(1); // halt
    }



  
}
// variables created by the build process when compiling the sketch
extern int __bss_end;
extern void *__brkval;
// function to return the amount of free RAM
int memoryFree(){
  int freeValue;
  if((int)__brkval == 0) 
    freeValue = ((int)&freeValue) - ((int)&__bss_end);
  else 
    freeValue = ((int)&freeValue) - ((int)__brkval);
  return freeValue;
}

void gsm_power_on(){

  uint8_t answer=0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(powerGSMPin,HIGH);
    delay(200);
    digitalWrite(powerGSMPin,LOW);
    delay(6000);
    // waits for an answer from the module
    while(answer == 0){    
      // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT", OK, 2000);    
    }
  }

}

int8_t sendATcommand(char* ATcommand, char* expected_answer1,
unsigned int timeout)
{

  uint8_t x=0,  answer=0;
  char response[100];
  unsigned long previous;

  memset(response, EOS, 100);    // Initialize the string

  delay(100);

  while( gsmSerial.available() > 0) gsmSerial.read();    // Clean the input buffer

  gsmSerial.println(ATcommand);    // Send the AT command 


    x = 0;
  previous = millis();

  // this loop waits for the answer
  do{

    if(gsmSerial.available() != 0){    
      response[x] = gsmSerial.read();
      x++;
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer1) != NULL)    
      {
        answer = 1;
      }
    }
    // Waits for the asnwer with time out
  }
  while((answer == 0) && ((millis() - previous) < timeout));    

  return answer;
}

int8_t sendATcommand2(char* ATcommand, char* expected_answer1,
char* expected_answer2, unsigned int timeout)
{

  uint8_t x=0,  answer=0;
  char response[100];
  unsigned long previous;

  memset(response, EOS, 100);    // Initialize the string

  delay(100);

  while( gsmSerial.available() > 0) gsmSerial.read();    // Clean the input buffer

  Serial.println(ATcommand);    // Send the AT command 


    x = 0;
  previous = millis();

  // this loop waits for the answer
  do{

    if(gsmSerial.available() != 0){    
      response[x] = gsmSerial.read();
      x++;
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer1) != NULL)    
      {
        answer = 1;
      }
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer2) != NULL)    
      {
        answer = 2;
      }
    }
    // Waits for the asnwer with time out
  }
  while((answer == 0) && ((millis() - previous) < timeout));    

  return answer;
}







