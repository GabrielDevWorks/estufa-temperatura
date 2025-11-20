// Biblioteca LCD
#include <LiquidCrystal.h>
// Inicializa a biblioteca LCD
LiquidCrystal LCD(12,11,5,4,3,2);

// Define o pino analógico A0 como entrada do Sensor de Temperatura
int SensorTempPino = A0; // usar A0 por clareza

// Define o pino 8 para o alerta de temperatura baixa
int AlertaTempBaixa = 8;
// Define o pino 13 para o alerta de temperatura alta
int AlertaTempAlta = 13;

// Define temperatura baixa como abaixo de zero grau Celsius
int TempBaixa = 0;
// Define temperatura alta como acima de 40 graus Celsius
int TempAlta = 40;

void setup() {
  // Define o pino de alerta de temperatura baixa como saída
  pinMode(AlertaTempBaixa, OUTPUT);
  // Define o pino de alerta de temperatura alta como saída
  pinMode(AlertaTempAlta, OUTPUT);

  // Define a quantidade de colunas e linhas do LCD
  LCD.begin(16, 2);
  // Imprime a mensagem no LCD
  LCD.print("Sensor Temperatura:");
  // Muda o cursor para a primeira coluna e segunda linha do LCD
  LCD.setCursor(0, 1);
  LCD.print("      /     ");
}

void loop() {
  int SensorTempTensao = analogRead(SensorTempPino);

  // Calcula tensão (assumindo Vref = 5.0V). Se seu Arduino usar 4.9V, troque 5.0 por 4.9
  float Tensao = SensorTempTensao * 5.0 / 1024.0;

  // Para sensor TMP36: TemperaturaC = (Vout - 0.5) * 100
  float TemperaturaC = (Tensao - 0.5) * 100.0;
  float TemperaturaF = (TemperaturaC * 9.0 / 5.0) + 32.0;

  // Mostra tensão e temperatura no LCD
  LCD.setCursor(0, 1);
  // sobrescreve com formato fixo (2 casas decimais)
  LCD.print(Tensao, 2);
  // garante que posições vazias sejam limpas (se necessário)
  LCD.print("   "); // ajusta se precisar

  LCD.setCursor(9, 1);
  LCD.print(TemperaturaC, 1); // 1 casa decimal
  LCD.print("C");

  // Lógica de alerta
  if (TemperaturaC >= TempAlta) {
    digitalWrite(AlertaTempBaixa, LOW);
    digitalWrite(AlertaTempAlta, HIGH);
  } else if (TemperaturaC <= TempBaixa) {
    digitalWrite(AlertaTempAlta, LOW);
    digitalWrite(AlertaTempBaixa, HIGH);
  } else {
    // temperatura normal
    digitalWrite(AlertaTempAlta, LOW);
    digitalWrite(AlertaTempBaixa, LOW);
  }

  delay(1000); // atualiza 2x por segundo
}
