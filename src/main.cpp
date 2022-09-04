#include <M5Stack.h>
#include <SparkFun_SCD30_Arduino_Library.h>
#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>
static LGFX lcd;
// spriteを生成
static LGFX_Sprite canvas(&lcd);
static LGFX_Sprite sprite(&canvas);
static LGFX_Sprite sprite2(&canvas);
static LGFX_Sprite sprite3(&canvas);
static LGFX_Sprite sprite4(&canvas);
static LGFX_Sprite sprite5(&canvas);
static LGFX_Sprite sprite6(&canvas);
static LGFX_Sprite sprite7(&canvas);
static LGFX_Sprite sprite8(&canvas);
static LGFX_Sprite sprite9(&canvas);

SCD30 airSensor;

uint16_t co2;
float temprature;
float humidity;

void setup()
{
  M5.begin();
  M5.Power.begin();

  lcd.init();
  lcd.setTextColor(TFT_WHITE);
  lcd.clear(TFT_BLACK);
  lcd.setColorDepth(16);
  lcd.setTextSize(1);
  lcd.setCursor(0, 0);

  // spriteの設定
  sprite.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite.createSprite(160, 48);
  sprite2.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite2.createSprite(160, 48);
  sprite3.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite3.createSprite(160, 48);
  sprite4.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite4.createSprite(72, 48);
  sprite5.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite5.createSprite(72, 48);
  sprite6.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite6.createSprite(72, 48);
  sprite7.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite7.createSprite(72+4, 48);
  sprite8.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite8.createSprite(72+4, 48);
  sprite9.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  sprite9.createSprite(72+4, 48);

  canvas.setColorDepth(4); // 4ビット(16色)パレットモードに設定
  canvas.createSprite(320, 240);
  //固定表示
  sprite7.setFont(&fonts::lgfxJapanGothic_24);
  sprite7.drawString("CO2", 4, 0);
  sprite8.setFont(&fonts::lgfxJapanGothic_24);
  sprite8.drawString("温度", 4, 0);
  sprite9.setFont(&fonts::lgfxJapanGothic_24);
  sprite9.drawString("湿度", 4, 0);
  sprite4.setFont(&fonts::lgfxJapanGothic_24);
  sprite4.drawString("ppm", 4, 0);
  sprite5.setFont(&fonts::lgfxJapanGothic_24);
  sprite5.drawString("℃", 4, 0);
  sprite6.setFont(&fonts::lgfxJapanGothic_24);
  sprite6.drawString("%", 4, 0);

  sprite7.pushSprite(0, 0);
  sprite8.pushSprite(0, sprite.height());
  sprite9.pushSprite(0, sprite.height() + sprite2.height());
  sprite4.pushSprite(sprite7.width()+sprite.width(), 0);
  sprite5.pushSprite(sprite8.width()+sprite2.width(), sprite.height());
  sprite6.pushSprite(sprite9.width()+sprite3.width(), sprite.height() + sprite2.height());

  Wire.begin();
  if (airSensor.begin() == false)
  {
    // M5.Lcd.print("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  airSensor.setAutoSelfCalibration(true);
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    co2 = airSensor.getCO2();
    temprature = airSensor.getTemperature();
    humidity = airSensor.getHumidity();

    sprite.clear();
    sprite.setFont(&fonts::Font7);
    sprite.setTextDatum(bottom_right);
    sprite.drawString((String)co2, 160, 48);

    sprite2.clear();
    sprite2.setFont(&fonts::Font7);
    sprite2.setTextDatum(bottom_right);
    sprite2.drawString((String)temprature, sprite2.width(), sprite2.height());

    sprite3.clear();
    sprite3.setFont(&fonts::Font7);
    sprite3.setTextDatum(bottom_right);
    sprite3.drawString((String)humidity, sprite3.width(), sprite.height());

    sprite.pushSprite(sprite7.width(), 0);
    sprite2.pushSprite(sprite8.width(), sprite.height());
    sprite3.pushSprite(sprite9.width(), sprite.height() + sprite2.height());
    canvas.pushSprite(0, 0);
  }
  else
  {
    // M5.Lcd.setCursor(0, 0);
    // M5.Lcd.print("data unavailable.");
  }

  // 2000ミリ秒待機
  delay(2000);
}