

void setup() 
{
  Serial.begin(9600);
  
}

void loop()
{
  setPrescaler(7000);
  delay(2000);
}

void setPrescaler(uint16_t timeMs)
{
  uint16_t n = nextPowerOf2(timeMs);
  uint8_t  reg = (uint8_t)(log (n) / log (2) + 0.5) - 4; //logxn = logy n / logy x
  
  Serial.println (reg);
}
uint16_t nextPowerOf2(uint16_t n)   
{ 
    n--; 
    n |= n >> 1; 
    n |= n >> 2; 
    n |= n >> 4; 
    n |= n >> 8; 
    n |= n >> 16; 
    n++;
    Serial.println(n);
    return n; 
}  
  
