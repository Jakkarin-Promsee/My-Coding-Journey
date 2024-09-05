// A0 --> Do
// A1 --> pH
// A2 --> MQ-5
// A3 --> MQ-135

// MQ-135 AIR QUALITY :: http://fitrox.lnwshop.com
// MQ-135 Vcc -> 5v
// MQ-135 Gnd -> Gnd
// MQ-135 A0 -> A3
// resistor 22k between Gnd and A0

// DHT22 VCC -> 5V
// DHT22 GND -> Gnd
// DHT22 Data -> 13(Arduino)

// DS18B20 Vcc -> 5v
// DS18B20 Gnd -> Gnd
// DS18B20 Data -> pin12
// resistor 4.7k between Vcc and Data

// PH VCC -> 5V
// PH Gnd -> Gnd
// PH PO -> A1


#include <OneWire.h> 
#include <DallasTemperature.h>
#include "DHT.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MQUnifiedsensor.h>
 
#define DO_PIN A0
int ph_sensor = A1;
#define ONE_WIRE_BUS 12 //DS18B20 pin12

#define VREF 5000    //VREF (mv)
#define ADC_RES 1024 //ADC Resolution
#define TWO_POINT_CALIBRATION 1
#define READ_TEMP (25) //Current water temperature ℃, Or temperature sensor function

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin1 A3 //Analog input 0 of your arduino
#define type1 "MQ-135" //MQ135
#define pin2 A2 //Analog input 0 of your arduino
#define type2 "MQ-5" //MQ135
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
#define RatioMQ5CleanAir 6.5//RS / R0 = 3.6 ppm  

//**********************************************  calibrate **********************************************
#define CAL1_V (1674) //mv
#define CAL1_T (30)   //℃
#define CAL2_V (1373) //mv
#define CAL2_T (19)   //℃
//********************************************************************************************************

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin1, type1);
MQUnifiedsensor MQ5(placa, Voltage_Resolution, ADC_Bit_Resolution, pin2, type2);

DHT dht;
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
SoftwareSerial UnoSerial(2, 3); // RX | TX

int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;


//**********************************************  calibrate **********************************************
float calibration_value = 21.34+10.59;
//********************************************************************************************************

float dht22_temperature, dht22_humidity,  ds18b20_temperature, analog_ph, dissolved_oxygen;
float mq135_co,mq135_al,mq135_co2,mq135_to,mq135_nh4,mq135_ace;
float mq5_h2,mq5_lpg,mq5_ch4,mq5_co,mq5_al;
int i = 0,j;

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};
 
uint8_t Temperaturet;
uint16_t ADC_Raw;
uint16_t ADC_Voltage;
uint16_t DO;
 
int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 00
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}



void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  UnoSerial.begin(4800);
  int j=1;
  Serial.begin(9600);
  dht.setup(13); // DHT22 pin13
  sensors.begin(); 
  Serial.println(F("OK"));

}

void loop() {
 
      while(1){
       int k = UnoSerial.parseFloat();
       if(UnoSerial.read() == '\n'){
        break;
       }
       delay(1);
      }
      
      collect_data();
      delay(100);
      UnoSerial.print("\n");
      delay(100);
     
      UnoSerial.print("\n");
      delay(100);
      UnoSerial.print(ds18b20_temperature);
      delay(100);
      UnoSerial.print("\n");
      delay(100);
      UnoSerial.print(analog_ph);
      delay(100);
      UnoSerial.print("\n");
      delay(100);
      UnoSerial.print(dissolved_oxygen);
      delay(100);
      UnoSerial.print("\n");
      j=1;
      Serial.print("8");
      delay(100);

  

  

}

void collect_data() {
  set_data();
  ds18b20_temperature = ds18b20_temperaturef();
  analog_ph = analog_phf();
  dissolved_oxygen = dissolved_oxygenf();

 //float mq135_co,mq135_al,mq135_co2,mq135_to,mq135_nh4,mq135_ace;
//float mq5_h2,mq5_lpg,mq5_ch4,mq5_c0,mq5_al;

  Serial.println("------------------------------------------------------------------------------");
  Serial.print(F("Air Temperature : "));
  Serial.print(dht22_temperature);
  Serial.println(" *C");
  Serial.print(F("Air humidity : "));
  Serial.print(dht22_humidity);
  Serial.println(" %");
  Serial.print(F("Air MQ5 H2 : "));
  Serial.print(mq5_h2);
  Serial.println(" ppm");
  Serial.print(F("Air MQ5 LPG : "));
  Serial.print(mq5_lpg);
  Serial.println(" ppm");
  Serial.print(F("Air MQ5 CH4 : "));
  Serial.print(mq5_ch4);
  Serial.println(" ppm");
  Serial.print(F("Air MQ5 CO : "));
  Serial.print(mq5_co);
  Serial.println(" ppm");
  Serial.print(F("Air MQ5 Alcohol : "));
  Serial.print(mq5_al);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 CO : "));
  Serial.print(mq135_co);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 Alcohol : "));
  Serial.print(mq135_al);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 CO2 : "));
  Serial.print(mq135_co2);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 Toluen : "));
  Serial.print(mq135_to);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 NH4 : "));
  Serial.print(mq135_nh4);
  Serial.println(" ppm");
  Serial.print(F("Air MQ135 Aceton : "));
  Serial.print(mq135_ace);
  Serial.println(" ppm");
  Serial.print(F("Water temperature : "));
  Serial.print(ds18b20_temperature);
  Serial.println(" *C");
  Serial.print(F("Water PH : "));
  Serial.print(analog_ph);
  Serial.println("");
  Serial.print(F("Water Do : "));
  Serial.print(dissolved_oxygen);
  Serial.println("\n");
}

float dissolved_oxygenf(){
  Temperaturet = (uint8_t)READ_TEMP;
  ADC_Raw = analogRead(DO_PIN);
  ADC_Voltage = uint32_t(VREF) * ADC_Raw / ADC_RES;
  float DO = (readDO(ADC_Voltage, Temperaturet));
  return DO/1000;

}

float analog_phf(){
  for(int i=0;i<10;i++) { 
    buffer_arr[i]=analogRead(ph_sensor);
    delay(30);
  }
  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buffer_arr[i]>buffer_arr[j]){
        temp=buffer_arr[i];
        buffer_arr[i]=buffer_arr[j];
        buffer_arr[j]=temp;
      }
    }
  }
 
  avgval=0;
  for(int i=2;i<8;i++)
  avgval+=buffer_arr[i];
  float volt=(float)avgval*5.0/1024/6;
  float ph_act = -5.70 * volt + calibration_value;
  return ph_act;
}

float dht22_temperaturef() {
  delay(dht.getMinimumSamplingPeriod());
  float temperature = dht.getTemperature();
  return temperature;
}

float dht22_humidityf() {
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  return humidity;
}

float ds18b20_temperaturef() {
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}

//float mq135_co,mq135_al,mq135_co2,mq135_to,mq135_nh4,mq135_ace;
//float mq5_h2,mq5_lpg,mq5_ch4,mq5_c0,mq5_al;
void set_data() {
  dht22_temperature = 0;
  dht22_humidity = 0;
  ds18b20_temperature = 0;
  analog_ph = 0;
  mq135_co = 0;
  mq135_al = 0;
  mq135_co2 = 0;
  mq135_to = 0;
  mq135_nh4 = 0;
  mq135_ace = 0;
  mq5_h2 = 0;
  mq5_lpg = 0;
  mq5_ch4 = 0;
  mq5_co = 0;
  mq5_al = 0;
  dissolved_oxygen = 0;
}

float result_mq5(float a,float b){
  set_ab_5(a,b);
  return ppm_5();
}

float result_mq135(float a,float b){
  set_ab_135(a,b);
  return ppm_135();
}

void set_ab_5(float a,float b){
  MQ5.setRegressionMethod(1); 
  MQ5.setA(a);
  MQ5.setB(b); 
  
  MQ5.init();   
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ5.calibrate(RatioMQ5CleanAir);
    Serial.print(F("."));
  }
  MQ5.setR0(calcR0/10);
  Serial.println(F("  done!."));
  
  if(isinf(calcR0)) {Serial.println(F("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply")); while(1);}
  if(calcR0 == 0){Serial.println(F("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply")); while(1);}
  MQ5.serialDebug(true);
}

float ppm_5(void){
  MQ5.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ5.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ5.serialDebug(); // Will print the table on the serial port
  float x=MQ5.interceptinformation();
  return x;
}

void set_ab_135(float a,float b){
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(a); 
  MQ135.setB(b); 

  MQ135.init(); 
  Serial.print(F("Calibrating please wait."));
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ135.update();
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(F("."));
  }
  MQ135.setR0(calcR0/10);
  Serial.println(F("  done!."));
  
  if(isinf(calcR0)) {Serial.println(F("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply")); while(1);}
  if(calcR0 == 0){Serial.println(F("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply")); while(1);}
  MQ135.serialDebug(true);
}

float ppm_135(void){
  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ135.serialDebug(); // Will print the table on the serial port
  float x=MQ135.interceptinformation();
  return x;
}
