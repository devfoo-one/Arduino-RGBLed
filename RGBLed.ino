class rgbLed {
  private:
    const int m_redPin, m_greenPin, m_bluePin;
    float m_red, m_green, m_blue, m_redFactor = 1.0f, m_greenFactor = 1.0f, m_blueFactor = 1.0f;
  public:
    rgbLed(int redPin, int greenPin, int bluePin):
      m_redPin(redPin),
      m_greenPin(greenPin),
      m_bluePin(bluePin)
    { }
    rgbLed(int redPin, int greenPin, int bluePin, float redFactor, float greenFactor, float blueFactor):
      m_redPin(redPin),
      m_greenPin(greenPin),
      m_bluePin(bluePin),
      m_redFactor(redFactor),
      m_greenFactor(greenFactor),
      m_blueFactor(blueFactor)
    { }
    void setColorCorrection(float redFactor, float greenFactor, float blueFactor) {
      m_redFactor = redFactor;
      m_greenFactor = greenFactor;
      m_blueFactor = blueFactor;
    }
    void setColor(float red, float green, float blue) {
      m_red = red;
      m_green = green;
      m_blue = blue;
      analogWrite(m_redPin, int(m_red * 255.0f * m_redFactor));
      analogWrite(m_greenPin, int(m_green * 255.0f * m_greenFactor));
      analogWrite(m_bluePin, int(m_blue * 255.0f * m_blueFactor));
    }
    void fadeToColor(float red, float green, float blue, int duration) {
        float oldRed = m_red;
        float oldGreen = m_green;
        float oldBlue = m_blue;
      for(float t = 0.0f; t<= 1.0f; t = t + 0.01f) {
        float newRed = (1.0f - t) * oldRed + t * red;
        float newGreen = (1.0f - t) * oldGreen + t * green;
        float newBlue = (1.0f - t) * oldBlue + t * blue;
        setColor(newRed, newGreen, newBlue);
        delay(duration / 100);
      }
    }
};

rgbLed led1 = rgbLed(11, 10, 9, 1.0f, 0.2f, 1.0f);

void setup() {
  Serial.begin(9600);
}

void loop() {  
  led1.setColor(1,0,0);
  delay(2000);
  led1.setColor(1,1,0);
  delay(2000);
  led1.setColor(0,1,0);
  delay(2000);
  led1.fadeToColor(0,0,0,500);
  led1.fadeToColor(1,1,1,2000);
  
}
