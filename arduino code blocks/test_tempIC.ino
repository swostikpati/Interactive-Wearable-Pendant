// TMP36 Pin Variables
int tempPin = A0;  // the output pin of the TMP36

void setup() {
  // Start the Serial communication to send data to the computer
  Serial.begin(9600);  
}

void loop() {
  int reading = analogRead(tempPin);  
  float voltage = reading * 3.3;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;  // converting from 10 mv per degree with 500 mV offset
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; // Convert Celsius to Fahrenheit

  // Print the temperature in Celsius and Fahrenheit
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C, ");
  Serial.print(temperatureF);
  Serial.println(" F");

  // Delay between readings
  delay(1000);
}
