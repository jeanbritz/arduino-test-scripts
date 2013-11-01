
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
#define UnoBaudRate (115200)

SoftwareSerial gsmSerial(unoRXPin,unoTXPin);

#define POST_REQ ("POST /arduino/invoice/add HTTP/1.1\r\nHost:ml.sun.ac.za:8000\r\nContent-Type:application/x-www-form-urlencoded\r\n")
#define POST_REQEUST_CONTENT_LENGTH ("Content-Length:%d\r\n\r\n")
#define PARAMS ("user=%d&amount_payable=%d\r\n\r\n") // parameters sent in Content body e.g. user=<id>&amount_payable=<int> 
char aux_str [32];

/* test params */
int user_id;
int amount_payable;

int8_t content_length = 0;
int8_t answer;
int aux = 0;
int data_size = 0;

#define HOST_NAME ("ml.sun.ac.za") 
#define HOST_PORT (8000)

void setup() {

    
  // init sequence
  Serial.begin(UnoBaudRate);
  gsmSerial.begin(GSMBaudRate);
  
  gsm_power_on();
  while( (sendATcommand(AT_CREG_QUERY, "+CREG: 0,1", 500) || 
    sendATcommand(AT_CREG_QUERY, "+CREG: 0,5", 500)) == 0 );
  Serial.println(F("GSM : Registered to network"));
  Serial.println(F("GSM : Ready for AT command"));
}
void loop () {

  Serial.println (F("==== HTTP POST EXAMPLE ====\n"));
  Serial.println(F("Create an invoice"));
  Serial.print (F("Enter user's id number:"));
  
  while(1) {
      while(!Serial.available());
      user_id = serialReadInt();
      if(user_id > 0) break;
   }
   Serial.println(user_id);
   Serial.print (F("Enter the amount the user have to pay:"));
   
   while(1) {
      while(!Serial.available());
      amount_payable = serialReadInt();
      if(amount_payable > 0) break;
   }
   Serial.println(amount_payable);
    sprintf(aux_str, AT_CHTTPACT_COMMAND, HOST_NAME, HOST_PORT);
    Serial.println(F("\n*** Start HTTP Transaction ***\n"));
    Serial.println(F(AT_CHTTPACT_INIT_RESPONSE));

    answer = sendATcommand(aux_str, AT_CHTTPACT_INIT_RESPONSE, 60000);
    Serial.println(aux_str);
    if (answer)
    {  

      data_size = 0;
      
      Serial.println(F("Sends Request:"));
      Serial.print(POST_REQ);
      gsmSerial.print(POST_REQ);
      sprintf(aux_str, PARAMS, user_id, amount_payable);
      content_length = get_array_length(aux_str);
      sprintf(aux_str, POST_REQEUST_CONTENT_LENGTH, content_length);
      Serial.print(aux_str);
      gsmSerial.print(aux_str);
      sprintf(aux_str, PARAMS, user_id, amount_payable);
      Serial.print(aux_str);
      gsmSerial.print(aux_str);
      //gsmSerial.println(RAW_POST_REQUEST);
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

int8_t get_array_length(char *arr)
{
	int8_t k = 0;
	char *seek = arr;
	while('\0' != *seek++)
	{
		k++;
	}
	return k;
}

int serialReadInt()
{
  int i, serialAvailable;                           // i is a counter, serAva hold number of serial available
  char inputBytes [7];                 // Array hold input bytes
  char * inputBytesPtr = &inputBytes[0];  // Pointer to the first element of the array
      
  if (Serial.available()>0)            // Check to see if there are any serial input
  {
    delay(5);                              // Delay for terminal to finish transmitted
                                               // 5mS work great for 9600 baud (increase this number for slower baud)
    serialAvailable = Serial.available();  // Read number of input bytes
    for ( i= 0; i < serialAvailable; i++)       // Load input bytes into array
      if(i < (serialAvailable - 1)){
        inputBytes[i] = (char)Serial.read();
      }
      else {
        inputBytes[i] =  '\0';             // Put NULL character at the end
      }
    return atoi(inputBytesPtr);    // Call atoi function and return result
  }
  else
    return -1;                           // Return -1 if there is no input
}





