#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <ds3231.h>

//---------------------------------------------------------------------------------------------------------------------
const char* ssid1 = "PCSHSCR-DOM"; //--> Nama Wifi / SSID.
const char* ssid2 = "PCSHSCR"; //--> Nama Wifi / SSID.
String ssid="";
bool wifi_status=false;

const char* password = ""; //-->  Password wifi .
#define LINE_TOKEN_1  "VGHMHuyPQuXH066Y92ZcAEv6rFN0IaLG22oMboHibZN"
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
const char* host = "script.google.com";
const int httpsPort = 443;
String GAS_ID_user = "https://script.google.com/macros/s/AKfycbwKuSZ1P4-UaGcVUKHoR2pU1m708U3lbbr2w9imyZeAOelCphS7w_xfoAQmQ2sgw-a4SQ"; 
//---------------------------------------------------------------------------------------------------------------------

int num=0; 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WiFiClientSecure client;
//---------------------------------------------------------------------------------------------------------------------
struct ts t;
SoftwareSerial NodeSerial(D3, D4); // RX | TX
float dht22_temperature, dht22_humidity,  ds18b20_temperature, analog_ph, dissolved_oxygen;
float mq135_co,mq135_al,mq135_co2,mq135_to,mq135_nh4,mq135_ace;
float mq5_h2,mq5_lpg,mq5_ch4,mq5_co,mq5_al;
int i,j,k;

class data_analysis{
    private:
    bool st_data = true;
    bool st_detail_error = true;
    bool st_detail_equation=true;
    bool st_equation = true;
    bool st_select = true;
    bool st_other_data = true;

    String name="nan";
    double data[40][2]={};
    double new_x=0 ,new_y=0;
    double all_equation[3][10]={};
    double all_error[10]={};
    double equation_sum_linear[2]={};
    double equation_sum_parabola[3]={};
    double storage_error[3]={};

    bool type=false;
    bool chek_error=true;
    int status=-1;
    int r=0;
    int train=0;
    int turn=0;
    int wrong=0;
    int best_equation=0;
    int available=0;
    int real_r=0;
    int status_error=0;
    double avg_error=0;
    double rate=3;
    double detect=50;
    double critical=0;
    int time_critical=0;
    int round_critical=0;
    double time_limit[3]={-1,-1,-1};
    double time_notify=120;


    public:
    bool notify_status=false;
    String data_equation="nan";
    String data_status="nan";
    String data_detail="nan";
    String data_all_detail="nan";
    String line_notify;
    
    data_analysis(char new_name[20] ,double new_criticl ,double new_time_notify ,double new_rate ,double new_detect ,bool collect_error);
    void status_printf(bool data ,bool train_error ,bool equation ,bool detail_equation ,bool select ,bool other_data);

    void cal_linear(void);
    void cal_parabora(int type,int store_position,int n1,int n2,int n3 ,double equation_parabola1[2][3] ,double equation_parabola2[4][3]);
    void calculation_equation(void);

    double equation(double x,double a,double b,double c);
    double rsquared(double a, double b, double c, int n);
    double rmse(double a, double b, double c, int n);
    double mae(double a, double b, double c, int n);

    bool select_equation(double parabola[3] ,double linear[2] ,int n);
    void cal_error(int n ,bool type);

    void swap_data(double new_x ,double new_y);
    void swap_equation(void);
    void swap_status(void);

    void printf_equation(void);
    void printf_data(void);
    void printf_detail_equation(void);
    void print_otherdata(void);
    void printf_error(void);

    void update(void);
    void main_input(void);
    void main_output(void);

    void train_equation(void);
    void train_distance_error(void);
    void train_data(void);
    void find_accuracy(void);
    void check_error(double error);

    void reset(void);
    void reset_data(void);
    void reset_equation(void);
    void reset_variable(void);

    void run(double x ,double y);

    void find_time_limit(void);
    void notify_linear(double slope);
    void notify_parabola_increase(double slope ,double h ,double k);
    void notify_parabola_decrease(double slope ,double h ,double k);
    void main_notify(void);

    double a(void);
    double b(void);
    double c(void);
    double error(void);
};

data_analysis Do("Do" ,2 ,120 ,3 ,50 ,true);
data_analysis ph("pH" ,4 ,120 ,3 ,50 ,true);



void setup() {
  if(wifi_status==false) ssid=ssid1;
  else ssid=ssid2;
  
  pinMode(D3, INPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);
  NodeSerial.begin(4800);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  int respon=0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
    respon++;

    if(respon==480){
      if(wifi_status==false) wifi_status=true;
      else wifi_status=false;
      setup();
    }
  }
  
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(LINE.getVersion());
  Serial.println();
  LINE.setToken(LINE_TOKEN_1);
  
  j = -1;
  
  Serial.begin(9600);
  Do.status_printf(0,0,0,0,0,0);
  ph.status_printf(0,0,0,0,0,0);
  LINE.notify("JAPS is working");
  client.setInsecure();

}



void loop() {
  Serial.println("OK");
  data_systems();
  analog_ph-=0;
  dissolved_oxygen+=2.5;
  display_data();
  
  
  ph.run(num,analog_ph);
  Do.run(num,dissolved_oxygen);
  ph.main_notify();
  Do.main_notify();
  
  Serial.println(num);

  double data_tem = ds18b20_temperature;
  double data_ph = analog_ph;
  double data_do = dissolved_oxygen;
  String pdata_equation = ph.data_equation;
  String pdata_status = ph.data_status;
  String pdata_detail = ph.data_detail;
  String pdata_more_detail = ph.data_all_detail;
  double pa = ph.a();
  double pb = ph.b();
  double pc = ph.c();
  double pperror = ph.error();
  
  String ddata_equation = Do.data_equation;
  String ddata_status = Do.data_status;
  String ddata_detail = Do.data_detail;
  String ddata_more_detail = Do.data_all_detail;
  double da = Do.a();
  double db = Do.b();
  double dc = Do.c();
  double derror = Do.error();
  
  sendData(data_tem ,data_ph ,data_do ,pdata_equation ,pdata_status ,pdata_detail ,pdata_more_detail ,pa ,pb ,pc ,pperror ,ddata_equation ,ddata_status ,ddata_detail ,ddata_more_detail ,da ,db ,dc ,derror);
  delay(1000);
  
  if(ph.notify_status==true&&Do.notify_status==true){
    reset_client();
    LINE.notify(ph.line_notify +"\n\n" + Do.line_notify);
    }
  else if(ph.notify_status==true) {
    reset_client();
    LINE.notify(ph.line_notify);
  }

  else if(Do.notify_status==true) {
    reset_client();
    LINE.notify(Do.line_notify);
  }

  else{
    reset_client();
    Serial.println();
  }

  num+=3;
  if(num==1440) num=0;
  
  delay(165960);
}

void reset_client(void){
    WiFi.begin("1","1");
    int time_out=0;
    
    while (WiFi.status() != WL_CONNECTED) {
    time_out++;
    Serial.print(".");
    delay(250);
    if(time_out==4) break;
    }
    
    WiFi.begin(ssid, password);
    
    int respon=0;
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
    respon++;

    if(respon==480){
      if(wifi_status==false) wifi_status=true;
      else wifi_status=false;
      setup();
    }
  }
}

void data_systems(){  
  j = 1;  
//----------------------------------------- send command it Arduino which collect information from all sensors    
  NodeSerial.print(j);
  NodeSerial.print("\n");
  delay(1000);
  
  int respon=0;
  Serial.println("not ok");
   while(1){
    if(NodeSerial.read() == '\n'){
      break;
    }
    delay(1);
    respon++;
    if(respon==30000) loop();
  }


//----------------------------------------- Input temperature data from Arduino by DHT22
//----------------------------------------- Input temperature water data from Arduino by DS18B20
  respon=0;
  while(1){
    Serial.println("not ok 14");
    ds18b20_temperature = NodeSerial.parseFloat();
    if(NodeSerial.read() == '\n'){
      break;
    }
    delay(1);
    respon++;
    if(respon==30000) loop();
  }

//----------------------------------------- Input pH data from Arduino by ph sensor arduino analog ph meter
  respon=0;
  while(1){
    Serial.println("not ok 15");
   analog_ph = NodeSerial.parseFloat();
    if(NodeSerial.read() == '\n'){
      break;
    }
    delay(1);
    respon++;
    if(respon==30000) loop();
  }

//----------------------------------------- Input dissolved oxygen data from Arduino by analog dissolved oxygen sensor
  respon=0;                                                                      
  while(1){
    Serial.println("not ok 16");
    dissolved_oxygen = NodeSerial.parseFloat();
    if(NodeSerial.read() == '\n'){
      break;
    }
    delay(1);
    respon++;
    if(respon==30000) loop();
  }
  j = 0 ;
}

void timef() {
  DS3231_get(&t);
  Serial.print("Date : ");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);
}

void display_data(){
  Serial.println("------------------------------------------------------------------------------");
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

void sendData(double data_tem ,double data_ph ,double data_do ,String pdata_equation ,String pdata_status ,String pdata_detail ,String pdata_more_detail ,double pa ,double pb ,double pc ,double pperror ,String ddata_equation ,String ddata_status ,String ddata_detail ,String ddata_more_detail ,double da ,double db ,double dc ,double derror) {
  Serial.println("==========");
  Serial.print("connecting to ");
  Serial.println(host);
  
  //----------------------------------------Connect to Google host
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //----------------------------------------

  //----------------------------------------Proses dan kirim data  


 
  String url = GAS_ID_user + "/exec?wtemp=" + data_tem + "&wph=" + data_ph + "&wdo=" + data_do + "&pa=" + pa + "&pb=" + pb + "&pc=" + pc + "&perror=" + pperror;
  url = url + "&da=" + da + "&db=" + db + "&dc=" + dc + "&derror=" + derror;
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  //----------------------------------------
  
  //---------------------------------------
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } 
  else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.print("reply was : ");
  Serial.println(line);
  Serial.println("closing connection");
  Serial.println("==========");
  Serial.println();
  //----------------------------------------
  
} 
//===============================================


data_analysis::data_analysis(char new_name[20] ,double new_critical ,double new_time_notify ,double new_rate ,double new_detect ,bool collect_error){
    if(new_rate<0) new_rate *= -1;
    if(new_detect<0) new_detect *= -1;
    critical=new_critical;
    time_notify=new_time_notify;
    name=new_name;
    rate=new_rate;
    detect=new_detect;
    chek_error=collect_error;
}

void data_analysis::status_printf(bool data ,bool detail_error ,bool equation ,bool detail_equation ,bool select ,bool other_data){
    st_data = data;
    st_detail_error = detail_error;
    st_equation = equation;
    st_detail_equation = detail_equation;
    st_select = select;
    st_other_data = other_data;
}

void data_analysis::reset_data(void){
    for(int i=0;i<40;i++){
        data[i][0]=0;
        data[i][1]=0;
    }
    printf("---------->> Reset Data \n",name);
}

void data_analysis::reset_equation(void){
    for(int i=0;i<10;i++){
        all_equation[0][i]=0;
        all_equation[1][i]=0;
        all_equation[2][i]=0;
        all_error[i]=0;
    }
    printf("---------->> Reset Equation and Error \n",name);
}

void data_analysis::reset_variable(void){
    type=false;

    status=-1;
    r=0;
    train=0;
    turn=0;
    wrong=0;
    best_equation=0;
    available=0;

    printf("---------->> Reset Variable \n",name);
}

void data_analysis::reset(void){
    reset_data();
    reset_equation();
    reset_variable();

    printf("---------->> Reset %s \n",name);
}

void data_analysis::cal_linear(void) {
    // Sum of x and y coordinates
    int n=6;
    double sumX = 0, sumY = 0;
    for (int i = 0; i < n; i++) {
        sumX += data[i][0];
        sumY += data[i][1];
    }

    // Mean of x and y coordinates
    double meanX = sumX / n;
    double meanY = sumY / n;

    // Calculate slope (m) and y-intercept (b)
    double numer = 0, denom = 0;
    for (int i = 0; i < n; i++) {
        numer += (data[i][0] - meanX) * (data[i][1] - meanY);
        denom += (data[i][0] - meanX) * (data[i][0] - meanX);
    }
    double m = numer / denom;
    double b = meanY - m * meanX;

    equation_sum_linear[0]=m;
    equation_sum_linear[1]=b;
}

void data_analysis::cal_parabora(int type,int store_position,int n1,int n2,int n3 ,double equation_parabola1[2][3] ,double equation_parabola2[4][3]){
    /*
    find variable of parabola by using 3 points
    name is name of the array to collect data
      --> 1 is equation_p1
      --> 2 is equation_p2

    position is position of the data in the array
      -->[position][a,b,c]

    n1 is first data
    n2 is second data
    n3 is third data
      -->(x,y)
    */

    double x1 = data[n1][1];
    double y1 = data[n1][0];
    double x2 = data[n2][1];
    double y2 = data[n2][0];
    double x3 = data[n3][1];
    double y3 = data[n3][0];

    double m31,m32,h,k,a,b,c;

    if((y3-y1)==0) m31=0;
    else m31=(x3-x1)/(y3-y1);
    if((y3-y2)==0) m32=0;
    else m32=(x3-x2)/(y3-y2);
    if((2*(m31-m32))==0) h=0;
    else h=(m31*(y3+y2)-m32*(y3+y1))/(2*(m31-m32));
    if((y1-y2)==0) a=0;
    else a=(m31-m32)/(y1-y2);

    k=x1-a*(y1-h)*(y1-h);
    b=-2*a*h;
    c=a*h*h+k;

    if(type==1){
        equation_parabola1[store_position][0] = a;
        equation_parabola1[store_position][1] = b;
        equation_parabola1[store_position][2] = c;
    }
    else{
        equation_parabola2[store_position][0] = a;
        equation_parabola2[store_position][1] = b;
        equation_parabola2[store_position][2] = c;
    }
}

void data_analysis::calculation_equation(void){
    /*
    parabola y=ax^2+bx+c
    a=equation_sum_parabola[0]
    b=equation_sum_parabola[1]
    c=equation_sum_parabola[2]

    linear y=mx+c;
    m=equation_sum_linear[0]
    c=equation_sum_linear[1]

    in function you can change the data which is used to calculate variables by changing the number
    */
    double equation_parabola1[2][3];
    double equation_parabola2[4][3];

    cal_linear();

    cal_parabora(1,0,0,2,4,equation_parabola1,equation_parabola2);
    cal_parabora(1,1,1,3,5,equation_parabola1,equation_parabola2);

    cal_parabora(0,0,0,1,2,equation_parabola1,equation_parabola2);
    cal_parabora(0,1,1,2,3,equation_parabola1,equation_parabola2);
    cal_parabora(0,2,2,3,4,equation_parabola1,equation_parabola2);
    cal_parabora(0,3,3,4,5,equation_parabola1,equation_parabola2);

    equation_sum_parabola[0] = 0;
    equation_sum_parabola[1] = 0;
    equation_sum_parabola[2] = 0;


    equation_sum_parabola[0] += ((equation_parabola1[0][0]+equation_parabola1[1][0])/2+(equation_parabola2[0][0]+equation_parabola2[1][0]+equation_parabola2[2][0]+equation_parabola2[3][0])/4)/2;
    equation_sum_parabola[1] += ((equation_parabola1[0][1]+equation_parabola1[1][1])/2+(equation_parabola2[0][1]+equation_parabola2[1][1]+equation_parabola2[2][1]+equation_parabola2[3][1])/4)/2;
    equation_sum_parabola[2] += ((equation_parabola1[0][2]+equation_parabola1[1][2])/2+(equation_parabola2[0][2]+equation_parabola2[1][2]+equation_parabola2[2][2]+equation_parabola2[3][2])/4)/2;

    equation_sum_parabola[0] += ((equation_parabola1[0][0]+equation_parabola1[1][0])+(equation_parabola2[0][0]+equation_parabola2[1][0]+equation_parabola2[2][0]+equation_parabola2[3][0])/4)/3;
    equation_sum_parabola[1] += ((equation_parabola1[0][1]+equation_parabola1[1][1])+(equation_parabola2[0][1]+equation_parabola2[1][1]+equation_parabola2[2][1]+equation_parabola2[3][1])/4)/3;
    equation_sum_parabola[2] += ((equation_parabola1[0][2]+equation_parabola1[1][2])+(equation_parabola2[0][2]+equation_parabola2[1][2]+equation_parabola2[2][2]+equation_parabola2[3][2])/4)/3;

    equation_sum_parabola[0] /= 2;
    equation_sum_parabola[1] /= 2;
    equation_sum_parabola[2] /= 2;
}

double data_analysis::equation(double x,double a,double b,double c){
    return a*x*x+b*x+c;
}

double data_analysis::rsquared(double a, double b, double c, int n) {
    double y_mean = 0;
    double ss_tot = 0;
    double ss_res = 0;
    double y_pred;
    for (int i=0; i<n; i++) {
        y_mean += data[i][1];
    }
    y_mean /= n;

    for (int i = 0; i < n; i++) {
        y_pred = equation(data[i][0], a, b, c);
        ss_tot += pow(data[i][1] - y_mean, 2);
        ss_res += pow(data[i][1] - y_pred, 2);
    }

    return 1 - (ss_res/ss_tot);
}

double data_analysis::rmse(double a, double b, double c, int n) {
    double rmse_value = 0;
    double y_pred;
    for (int i = 0; i < n; i++) {
        y_pred = equation(data[i][0], a, b, c);
        rmse_value += pow(data[i][1] - y_pred, 2);
    }
    return sqrt(rmse_value/n);
}

double data_analysis::mae(double a, double b, double c, int n) {
    double mae_value = 0;
    double y_pred;
    for (int i = 0; i < n; i++) {
        y_pred = equation(data[i][0], a, b, c);
        mae_value += abs(data[i][1] - y_pred);
    }
    return mae_value/n;
}

bool data_analysis::select_equation(double parabola[3] ,double linear[2] ,int n){
    double r2_linear = rsquared(0,linear[0],linear[1],n);
    double r2_parabola = rsquared(parabola[0],parabola[1],parabola[2],n);

    if(r2_linear==r2_parabola) return true;
    else if(r2_linear>r2_parabola) return false;
    else return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void data_analysis::swap_data(double new_x ,double new_y){
    for(int i=0; i<40 ;i++){
        if(i==39){
            data[0][0] = new_x;
            data[0][1] = new_y;
        }
        else{
            data[39-i][0] = data[38-i][0];
            data[39-i][1] = data[38-i][1];
        }
    }
}

void data_analysis::swap_status(void){
    if(available==6){
        if(type==false){
            if(equation_sum_linear[0]==0) status=0;
            else if(equation_sum_linear[0]>0) status=1;
            else status=-1;
        }
        else{
            double m=equation_sum_parabola[1]*data[0][0]+equation_sum_parabola[1];
            if(m==0) status=0;
            else if(m>0) status=1;
            else status=-1;
        }
        if(r<40) r++;
        if(available<40) available++;
    }
    else{
        double new_status;
        if(type==false){
            if(equation_sum_linear[0]==0) new_status=0;
            else if(equation_sum_linear[0]>0) new_status=1;
            else new_status=-1;
        }
        else{
            double m=equation_sum_parabola[1]*data[0][0]+equation_sum_parabola[1];
            if(m==0) new_status=0;
            else if(m>0) new_status=1;
            else new_status=-1;
        }
        if(status==new_status) {
            if(r<40) r++;
            if(available<40) available++;
        }
        else {
            if(st_select==true) printf("\nTrend of data change\n\n");
            status=new_status;
            if(r<=6) available = 6;
            else available = 3;
            train=0;
            if(r>6) turn++;
            if(r<40) r++;
        }

    }
}

void data_analysis::swap_equation(void){
    double a,b,c;
    if(type==false){
        a = 0;
        b = equation_sum_linear[0];
        c = equation_sum_linear[1];
    }
    else{
        a = equation_sum_parabola[0];
        b = equation_sum_parabola[1];
        c = equation_sum_parabola[2];
    }

    for(int i=0;i<10;i++){
        if(i==9){
            all_equation[0][9-i] = a;
            all_equation[1][9-i] = b;
            all_equation[2][9-i] = c;
        }
        else{
            all_equation[0][9-i] = all_equation[0][8-i];
            all_equation[1][9-i] = all_equation[1][8-i];
            all_equation[2][9-i] = all_equation[2][8-i];
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void data_analysis::printf_data(void){
    if(st_data==true){
        printf("Name : %s\n\tX\t\tY\n",name);
        for(int i=0;i<40;i++) printf("%d\t%.4lf\t\t%.4lf\n",i+1,data[i][0],data[i][1]);
    }
}

void data_analysis::printf_detail_equation(void){

    if(st_detail_equation==true){
    printf("\n\t\tm\t\tc\n");
    printf("Linear\t\t%.8lf\t%.8lf\n",equation_sum_linear[0],equation_sum_linear[1]);
    printf("\n\t\ta\t\tb\t\tc\n");
    printf("Parabola\t%.8lf\t%.8lf\t%.8lf\n",equation_sum_parabola[0],equation_sum_parabola[1],equation_sum_parabola[2]);
    }

    if(st_select==true){
        double linear_rsquared = rsquared(0 ,equation_sum_linear[0] ,equation_sum_linear[1] ,6);
        double parabola_rsquared = rsquared(equation_sum_parabola[0] ,equation_sum_parabola[1] ,equation_sum_parabola[2] ,6);
        printf("\nLinear : Parabola >> %.4lf  :  %.4lf\n\n",linear_rsquared ,parabola_rsquared);
    }

    if(st_detail_equation==true){
    if(type==false) printf("Equation : linear\n");
    else printf("Equation : parabola\n");
    }
}

void data_analysis::printf_equation(void){
    if(st_equation==true){
    printf("\nn\ta\t\t\tb\t\t\tc\t\t\tr2\n");
    for(int i=0;i<10;i++){
        printf("%d\t%.7lf\t\t%.7lf\t\t%.7lf\t\t%.7lf\n",i+1,all_equation[0][i],all_equation[1][i],all_equation[2][i],rsquared(all_equation[0][i],all_equation[1][i],all_equation[2][i],available));
    }
    printf("equation = %d \n",best_equation+1);
    }
}

void data_analysis::print_otherdata(void){
    if(st_other_data==true){
    printf("\nName = %s \nRound = %d\nAvailable = %d\nStatus = %d\ntype = %d\nn = %d\nTurn : %d\nTrain : %d\nWrong : %d\n\n",name ,r,available,status,type,r-5,turn,train,wrong);
    }
}

void data_analysis::printf_error(void){
    int number=r-5;
    if(number<0) number = 0;
    if(number>10) number = 10;
    printf("\nn\tError(\%)\n");
    double sum_error=0;
    for(int i=0;i<number;i++){
        printf("%d\t%.4lf\n",i+1,all_error[i]);
        if(all_error[i]>=0) sum_error+=all_error[i];
        else sum_error+=all_error[i];
    }
        sum_error/=number;
        printf("Error : %.4lf\n",sum_error);
        printf("AVG Error : %lf\n",avg_error);
        printf("status_error : %d\n",status_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void data_analysis::update(void){
    if(r>=5){
    calculation_equation();
    type = select_equation(equation_sum_parabola,equation_sum_linear,available);

    swap_equation();
    swap_status();
    }
    else{
        r++;
        available++;
    }
}

void data_analysis::main_output(void){
    if(r>=6){
        printf_data();
        printf_detail_equation();
        printf_equation();
        printf_error();
        print_otherdata();
    }
}

void data_analysis::main_input(void){
    swap_data(new_x ,new_y);

    if(time_critical==0){
        if(new_y<=critical){
            time_critical++;
            round_critical++;
        }
    }
    else{
        if(new_y<=critical) time_critical++;
        else time_critical=0;
    }
}

void data_analysis::train_equation(){
    int n=r-5 ,worst_equation;
    if(n>10) n=10;
    double max_rsquared ,min_rsquared;
    for(int i=0;i<n;i++){
        if(i==0){
            worst_equation=i;
            best_equation=i;
            max_rsquared=rsquared(all_equation[0][i] ,all_equation[1][i] ,all_equation[2][i] ,available);
        }
        else{
            double reserve_rsquared=rsquared(all_equation[0][i] ,all_equation[1][i] ,all_equation[2][i] ,available);
            if(reserve_rsquared<min_rsquared){
                min_rsquared = reserve_rsquared;
                worst_equation = i;
            }
            if(reserve_rsquared>max_rsquared){
                max_rsquared = reserve_rsquared;
                best_equation = i ;
            }
        }
    }
    if(n==10){
        double reserve_a ,reserve_b ,reserve_c;
        if(best_equation!=worst_equation && worst_equation!=9){
            if(best_equation==9) best_equation=worst_equation;
            reserve_a = all_equation[0][9];
            reserve_b = all_equation[1][9];
            reserve_c = all_equation[2][9];
            all_equation[0][9] = all_equation[0][worst_equation];
            all_equation[1][9] = all_equation[1][worst_equation];
            all_equation[2][9] = all_equation[2][worst_equation];
            all_equation[0][worst_equation] = reserve_a;
            all_equation[1][worst_equation] = reserve_b;
            all_equation[2][worst_equation] = reserve_c;

        }
    }
}

void data_analysis::train_distance_error(){
    if(r>=6){
        int  n=r-6;
        if(n>10) n=10;

        double error;

        if(chek_error==true){
            error = equation(data[0][0] ,all_equation[0][best_equation] ,all_equation[1][best_equation] ,all_equation[2][best_equation]);
            if(data[0][1]==0) error=0;
            else error = ((data[0][1]-error)/data[0][1])*100;
        }
        else{
            error=0;
            for(int i=0;i<available;i++){
                if(data[i][1]==0) error+=0;
                else error += ((data[i][1]-equation(data[i][0] ,all_equation[0][best_equation] ,all_equation[1][best_equation] ,all_equation[2][best_equation]))/data[i][1])*100;
            }
        error/=available;
        }

        for(int i=0;i<10;i++){
            all_error[9-i] = all_error[8-i];
        }
        all_error[0] = error;

    }
}

void data_analysis::train_data(void){
    if(r>=6) train++;
    double value = equation(data[0][0],all_equation[0][best_equation],all_equation[1][best_equation],all_equation[2][best_equation]);
    double error = ((data[0][1]-value)/data[0][1])*100;
    if(error<0) error*=-1;

    check_error(error);

    if(error>=detect&&r>6){
        data[0][1] = value;
        printf("%d\n",data[0][0]);
    }

    if(train>=6){
        train=0;
        for(int i=0;i<available;i++){
            double values = equation(data[i][0],all_equation[0][best_equation],all_equation[1][best_equation],all_equation[2][best_equation]);
            double errors = ((data[i][1]-value)/data[i][1])*100;
            if(errors>=rate){
                data[i][1] = values;
                printf("%d\n",data[i][0]);
            }

        }
    }
}

void data_analysis::find_accuracy(void){
    if(available>=6){
        double value = equation(data[0][0],all_equation[0][best_equation],all_equation[1][best_equation],all_equation[2][best_equation]);
        double error = ((data[0][1]-value)/data[0][1])*100;
        if(error<0) error*=-1;
        avg_error=(avg_error*real_r+error)/(real_r+1);
        real_r++;
    }
}

void data_analysis::check_error(double error){
    if(available>=6){
        if(error>detect) status_error++;
        else status_error=0;

        if(status_error>=6) reset();
    }
}

void data_analysis::run(double x ,double y){
    new_x=x;
    new_y=y;
    main_input();

    train_data();
    update();
    train_equation();
    train_distance_error();
    find_accuracy();

    main_output();
}

void data_analysis::find_time_limit(void){
    // t = (critical-c)/m
    if(all_equation[0][best_equation]==0){
        if(all_equation[1][best_equation]!=0) time_limit[0]= (critical-all_equation[2][best_equation])/(all_equation[1][best_equation]);
        else time_limit[0]=-1;
    }
    else {
        time_limit[1]=((-all_equation[1][best_equation]-sqrt(all_equation[1][best_equation]*all_equation[1][best_equation]-4*all_equation[0][best_equation]*(all_equation[2][best_equation]-critical))) / (2*all_equation[0][best_equation]));
        time_limit[2]=((-all_equation[1][best_equation]+sqrt(all_equation[1][best_equation]*all_equation[1][best_equation]-4*all_equation[0][best_equation]*(all_equation[2][best_equation]-critical))) / (2*all_equation[0][best_equation]));
    }
}

//------------------------------------------------------------------------------------------------------------------------

void data_analysis::notify_linear(double slope){
    //********************************************************************************************************************
    //m=0 not increase or reduce
    if(slope==0){
        if(data[0][1]==critical){
            data_status = "In danger";
            data_detail =  "the trend of " + name + " is stable";
            data_all_detail = name + " is below the critical point";
            notify_status = true;
        }
        else if(data[0][1]>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is over the critical point";
            notify_status = false;
        }
        else{
            data_status = "In danger";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is below the critical point";
            notify_status = true;
        }
    }
    //********************************************************************************************************************
    //m>0 The trend increase
    else if(slope>0){
        if(data[0][1]==critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is lowering to the critical point";
            notify_status = false;
        }
        else if(data[0][1]>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is over the critical point";
            notify_status = false;
        }
        else{
            data_status = "In danger";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is below the critical point" + " ,In " + (time_limit[0]-data[0][0]) + " minutes " + name + " is going beyond the critical point";
            notify_status = false;
        }
    }
    //********************************************************************************************************************
    //m<0 The trend decrease
    else{
        if(data[0][1]==critical){
            data_status = "Critical";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is lowering to the critical point";
            notify_status = true;
        }
        else if(data[0][1]>critical){
            data_status = "Warning";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is over the critical point" + " ,In "+(time_limit[0]-data[0][0])+" minutes "+ name +" is dropping to the critical point";
            if(time_limit[0]-data[0][0]<time_notify) notify_status=true;
            else notify_status=false;
        }
        else{
            data_status = "In danger";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is lowering to the critical point ," + name +" has entered the critical point for " + (data[0][0]-time_limit[0]) + " minutes";
            notify_status = true;
        }
    //********************************************************************************************************************
    }
}

//------------------------------------------------------------------------------------------------------------------------

void data_analysis::notify_parabola_increase(double slope ,double h ,double k){
    //a+
    //********************************************************************************************************************
    //m=0 trend
    if(slope==0){
        //a+
        if(k==critical){
            data_status = "Critical";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is lowering to the critical point";
            notify_status = true;
        }
        else if(k>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is over the critical point";
            notify_status = false;
        }
        else{
            data_status = "In danger";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is below the critical point ," + name +" has entered the critical point for "+ (time_limit[2]-data[0][0]) + " minutes";
            if(data[0][1]<critical) notify_status=true;
        }
    }
    //********************************************************************************************************************
    //m>0 trend
    else if(slope>0){
        if(k==critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is over the critical point";
            notify_status = false;
        }
        else if(k>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is over the critical point";
            notify_status = false;
        }
        else{
            if(data[0][1]==critical){
                data_status = "Safe";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is lowering to the critical point";
                notify_status = false;
            }
            else if(data[0][1]>critical){
                data_status = "Safe";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is over the critical point";
                notify_status = false;
            }
            else{
                data_status = "In danger";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is below the critical point" + " ,In "+(time_limit[2]-data[0][0]) + " minutes " + name + " is going beyond the critical point";
                notify_status = false;
            }
        }
    }
    //********************************************************************************************************************
    //m<0 trend
    else{
        if(k==critical){
            data_status = "Warning";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is over the critical point"+" ,In "+(time_limit[1]-data[0][0])+" minutes "+ name+" is dropping to the critical point";
            if(time_limit[1]-data[0][0]<time_notify) notify_status=true;
            else notify_status=false;
        }
        
        else if(k>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is over the critical point";
            notify_status=false;
        }
        else{
            if(data[0][1]==critical){
                data_status = "Critical";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is lowering to the critical point";
                notify_status=true;
            }
            else if(data[0][1]>critical){
                data_status = "Warning";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail =name + " is dropping to the critical point" + "in "+(time_limit[1]-data[0][0])+" minutes ";
                if(time_limit[1]-data[0][0]<time_notify) notify_status=true;
                else notify_status=false;
            }
            else{
                data_status = "In danger";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is below the critical point";
                notify_status=true;
            }
        }
    }
    //********************************************************************************************************************
}

//------------------------------------------------------------------------------------------------------------------------

void data_analysis::notify_parabola_decrease(double slope ,double h ,double k){
    //a-
    //********************************************************************************************************************
    //m=0 trend
    if(slope==0){
        //a+
        if(k==critical){
            data_status = "In danger";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is below the critical point";
            notify_status=true;
        }
        else if(k>critical){
            data_status = "Safe";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is over the critical point";
            notify_status=false;
        }
        else{
            data_status = "In danger";
            data_detail = "the trend of " + name + " is stable";
            data_all_detail = name + " is below the critical point";
            notify_status=true;
        }
    }
    //********************************************************************************************************************
    //m>0 trend
    else if(slope>0){
        if(k==critical){
            data_status = "Critical";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is below the critical point"+" ,In "+(time_limit[1]-data[0][0])+" minutes "+name+" is going beyond the critical point";
            notify_status=true;
        }
        else if(k>critical){
            if(data[0][1]==critical){
                data_status = "Safe";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is going beyond the critical point";
                notify_status=false;
            }
            else if(data[0][1]>critical){
                data_status = "Safe";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is over the critical point";
                notify_status=false;
            }
            else{
                data_status = "Critical";
                data_detail = "the trend of " + name + " is increasing";
                data_all_detail = name + " is below the critical point" +" ,In "+(time_limit[1]-data[0][0])+" minutes "+name+" is going beyond the critical point";
                notify_status=true;
            }
        }
        else{
          if(data[0][1]<critical){
            data_status = "In danger";
            data_detail = "the trend of " + name + " is increasing";
            data_all_detail = name + " is below the critical point";
            notify_status=true;
          }
        }
    }
    //********************************************************************************************************************
    //m<0 trend
    else{
        if(k==critical){
            data_status = "In danger";
            data_detail = "the trend of " + name + " is decreasing";
            data_all_detail = name + " is below the critical point ,"+ name +" has entered the critical point for "+(data[0][0]-time_limit[2])+" minutes";
            notify_status=true;
        }
        else if(k>critical){
            if(data[0][1]==critical){
                data_status = "Critical";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is lowering to the critical point";
                notify_status=true;
            }
            else if(data[0][1]>critical){
                data_status = "Warning";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is over the critical point"+" ,In "+(time_limit[2]-data[0][0])+" minutes "+ name+" is dropping to the critical point";
                if(time_limit[2]-data[0][0]<time_notify) notify_status=true;
                else notify_status=false;
            }
            else{
                data_status = "In dander";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is below the critical point"+ name+" has entered the critical point for "+(data[0][0]-time_limit[2])+" minutes\n";
                notify_status=true;
            }
        }
        else{
            if(data[0][1]<critical){
                data_status = "Critical";
                data_detail = "the trend of " + name + " is decreasing";
                data_all_detail = name + " is below the critical point";
                notify_status=true;
           }
        }
    }
}

void data_analysis::main_notify(void){
  if(available>=6){
  find_time_limit();
  double h=(-all_equation[1][best_equation])/(2*all_equation[0][best_equation]);
  double k=(4*all_equation[0][best_equation]*all_equation[2][best_equation]-all_equation[1][best_equation]*all_equation[1][best_equation])/4*all_equation[0][best_equation];
  
  if(all_equation[0][best_equation]==0) notify_linear(all_equation[1][best_equation]);
  else if(all_equation[0][best_equation]>0) notify_parabola_increase(all_equation[0][best_equation] ,h ,k);
  else notify_parabola_decrease(all_equation[0][best_equation] ,h ,k);
  data_equation = name + " : y = " + all_equation[0][best_equation] + " x^2 + " + all_equation[1][best_equation] + " x " + all_equation[2][best_equation];

  Serial.println(name +" : " +data[0][1]);
  Serial.println("Status : "+data_status);
  Serial.println(data_detail);
  Serial.println(data_all_detail);
  Serial.println(data_equation);
  Serial.print("Line : ");
  if(notify_status==true) Serial.println("True");
  else Serial.println("False");
  Serial.println();
  
  line_notify= name + " : " + data[0][1] + "\nStatus : "+data_status +"\n"+data_detail+"\n"+data_all_detail;
  }
}

double data_analysis::a(void){
  return all_equation[0][best_equation];
}

double data_analysis::b(void){
  return all_equation[1][best_equation];
}

double data_analysis::c(void){
  return all_equation[2][best_equation];
}

double data_analysis::error(void){
  int number=r-5;
    if(number<0) number = 0;
    if(number>10) number = 10;
    double sum_error=0;
    for(int i=0;i<number;i++){
        if(all_error[i]>=0) sum_error+=all_error[i];
        else sum_error+=all_error[i];
    }
    sum_error/=number;
  return sum_error;
}
    
