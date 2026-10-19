#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Configurações do Display OLED (128x64 I2C)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuração do DHT22
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Definições de pinos
#define PINO_SOLO A0
#define RELE_VALVULA 7 // Pino conectado ao IN1 do módulo relé

// Limiar base para solo seco definido em 440
const int LIMIAR_BASE_SECO = 440;

void setup() {
  Serial.begin(9600);

  // Inicializa o pino do relé
  pinMode(RELE_VALVULA, OUTPUT);
  // O módulo relé trabalha em nível lógico baixo (LOW = Ativa, HIGH = Desliga)
  digitalWrite(RELE_VALVULA, HIGH); // Inicia desligado/fechado

  // Inicializa o sensor DHT
  dht.begin();

  // Inicializa o display OLED no endereço 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao inicializar o display OLED!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  Serial.println(F("Sistema AgroPulse Inicializado (Limiar Base: 440)!"));
}

void loop() {
  // Leitura dos sensores
  float temp = dht.readTemperature();
  float umidAr = dht.readHumidity();
  int leituraSolo = analogRead(PINO_SOLO);

  // Lógica Dinâmica de Limiar do Solo
  float fatorReducao = 0.0;

  // Se a temperatura for maior que 28°C, perde 10% do limiar
  if (!isnan(temp) && temp > 28.0) {
    fatorReducao += 0.10;
  }

  // Se a umidade do ar for menor que 60%, perde mais 10%
  if (!isnan(umidAr) && umidAr < 60.0) {
    fatorReducao += 0.10;
  }

  // Calcula o limiar efetivo após as penalidades climáticas
  // Ex: Base 440 -> -10% vira 396 -> -20% vira 352
  int limiarEfetivo = LIMIAR_BASE_SECO * (1.0 - fatorReducao);

  // Acionamento da Válvula Solenoide pelo Relé
  bool irrigando = false;
  if (leituraSolo > limiarEfetivo) {
    digitalWrite(RELE_VALVULA, LOW);  // Dispara o relé (conduz os 12V e abre a solenoide)
    irrigando = true;
  } else {
    digitalWrite(RELE_VALVULA, HIGH); // Desliga o relé (corta os 12V e fecha a solenoide)
    irrigando = false;
  }

  // --- SAÍDA COMPLETA PARA O MONITOR SERIAL ---
  Serial.print(F("Temp: "));
  if (isnan(temp)) Serial.print(F("Erro"));
  else { Serial.print(temp, 1); Serial.print(F(" C")); }

  Serial.print(F(" | Umid Ar: "));
  if (isnan(umidAr)) Serial.print(F("Erro"));
  else { Serial.print(umidAr, 1); Serial.print(F(" %")); }

  Serial.print(F(" | Solo: "));
  Serial.print(leituraSolo);
  Serial.print(F(" | Limiar Atual: "));
  Serial.print(limiarEfetivo);
  Serial.print(F(" (Red: -"));
  Serial.print((int)(fatorReducao * 100));
  Serial.print(F("%) | Status: "));
  Serial.println(irrigando ? F("VALVULA ABERTA") : F("VALVULA FECHADA"));

  // --- DISPLAY OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(18, 2);
  display.println(F("AGROPULSE v1.0"));
  display.drawLine(0, 11, 128, 11, SSD1306_WHITE);

  // Linha 1: Temperatura
  display.setCursor(0, 16);
  display.print(F("Temp: "));
  if (isnan(temp)) display.println(F("Erro"));
  else { display.print(temp, 1); display.println(F(" C")); }

  // Linha 2: Umidade do Ar
  display.setCursor(0, 26);
  display.print(F("Umid: "));
  if (isnan(umidAr)) display.println(F("Erro"));
  else { display.print(umidAr, 1); display.println(F(" %")); }

  // Linha 3: Solo com Limiar Dinâmico
  display.setCursor(0, 36);
  display.print(F("Solo: "));
  display.print(leituraSolo);
  display.print(F(" (L:"));
  display.print(limiarEfetivo);
  display.println(F(")"));

  // Linha 4: Compensação Ativa
  display.setCursor(0, 46);
  display.print(F("Ajuste Clima: -"));
  display.print((int)(fatorReducao * 100));
  display.println(F("%"));

  // Linha 5: Válvula
  display.setCursor(0, 56);
  display.print(F("Valvula: "));
  display.println(irrigando ? F("ABERTA (ON)") : F("FECHADA"));

  display.display();

  delay(2000);
}