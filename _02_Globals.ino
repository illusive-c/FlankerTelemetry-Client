//serial
static boolean recvInProgress = false;
boolean newData = false;//Do we have data waiting to be processed
char receivedChars[NUMCHARS];//Buffer for incoming serial
bool cDebug = 1; //Is debugging allowed

//Connection check
boolean cStatus = false;//Are we connected to PC
unsigned long lastStatus = 0;

//CPU Vars
int CPU_Temp, CPU1_Temp, CPU2_Temp, CPU3_Temp, CPU4_Temp;

//TIME
String DataType;
int integerFromPC = 0;
float floatFromPC = 0.0;

//NET
int maxUpSpeed = 300;
int maxDownSpeed = 3500;

//Benchmark
unsigned long previousMicros = 0;        // store last time LED was updated
