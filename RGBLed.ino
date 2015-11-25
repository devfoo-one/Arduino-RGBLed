class rgbLed {
  private:
    const int m_redPin, m_greenPin, m_bluePin;
    float m_red, m_green, m_blue, m_redFactor = 1.0f, m_greenFactor = 1.0f, m_blueFactor = 1.0f, m_brightness = 1.0f;
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
      setColor(m_red, m_green, m_blue); //reset color after changing color correction
    }
    void setBrightness(float brightness) {
      m_brightness = brightness;
      setColor(m_red, m_green, m_blue);
    }
    void setColor(float red, float green, float blue) {
      m_red = red;
      m_green = green;
      m_blue = blue;
      analogWrite(m_redPin, int(m_red * 255.0f * m_redFactor * m_brightness));
      analogWrite(m_greenPin, int(m_green * 255.0f * m_greenFactor * m_brightness));
      analogWrite(m_bluePin, int(m_blue * 255.0f * m_blueFactor * m_brightness));
    }
    void fadeToColor(float red, float green, float blue, int duration) {
        float oldRed = m_red;
        float oldGreen = m_green;
        float oldBlue = m_blue;
      for(int i=0; i<= 100; i++) {
        float t = float(i) / 100.f;
        float newRed = (1.0f - t) * oldRed + t * red;
        float newGreen = (1.0f - t) * oldGreen + t * green;
        float newBlue = (1.0f - t) * oldBlue + t * blue;
        setColor(newRed, newGreen, newBlue);
        delay(duration / 100);
      }
    }
};

rgbLed led1 = rgbLed(11, 10, 9, 1.0f, 0.2f, 1.0f);
rgbLed led2 = rgbLed(6, 5, 3, 1.0f, 0.2f, 1.0f);


void setup() { }

void loop() {  
  for(int i = 0; i <= 200; i++) {
    float a = float(i) / 100.f;
    float red = constrain(cos(PI * a) + 0.5f, 0, 1);
    float green = constrain(cos(PI * a - 2.1f) + 0.5f, 0, 1);
    float blue = constrain(cos(PI * a - 4.2f) + 0.5f, 0, 1);
    led1.setColor(red, green, blue);
    delay(10);
  }
}

