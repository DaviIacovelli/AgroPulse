
# 🌾 AgroPulse — Sistema de Irrigação Inteligente & IoT

Protótipo físico de irrigação automatizada de alta precisão desenvolvido em **C/C++** utilizando **PlatformIO / Arduino**, focado na otimização do uso de água na agricultura através de monitoramento ambiental em tempo real e acionamento autônomo de atuadores.

---

## 🛠️ Tecnologias e Stack de Hardware
* **Microcontrolador:** Arduino Uno R3
* **Linguagem:** C / C++
* **Ambiente de Desenvolvimento:** PlatformIO (VS Code)
* **Sensores:** 
  * Sensor de Temperatura e Umidade do Ar: **DHT22**
  * Sensor de Umidade do Solo: **Capacitivo Analógico**
* **Display & Interface:** Display **OLED SSD1306 (I2C)** para telemetria local em tempo real
* **Atuação & Potência:** Módulo Relé de 8 canais, Válvula Solenóide 12V e conversor DC-DC Step-Down **LM2596** para regulação segura de tensão.
* **Documentação:** Especificação técnica estruturada em **LaTeX** (padrão ABNT).

---

## ⚙️ Arquitetura e Funcionamento do Sistema
1. **Coleta de Dados:** O sistema realiza a leitura contínua dos dados ambientais do DHT22 e das taxas de umidade do solo por meio do sensor capacitivo.
2. **Processamento Local & Lógica de Limiares:** A firmware em C/C++ aplica algoritmos de limiares dinâmicos para avaliar a necessidade hídrica da cultura.
3. **Telemetria:** Os dados coletados e o status do sistema são renderizados dinamicamente no display **OLED SSD1306**.
4. **Atuação Automática:** Caso a umidade do solo atinja níveis críticos abaixo do parâmetro estipulado, o microcontrolador aciona o módulo relé, abrindo a válvula solenoide de 12V para irrigação controlada.

---

## 📂 Estrutura do Repositório
```text
AgroPulse/
├── include/       # Cabeçalhos e definições de constantes
├── lib/           # Bibliotecas de terceiros (SSD1306, DHT)
├── src/           # Código-fonte principal em C/C++ (main.cpp)
├── test/          # Testes unitários de bancada
└── platformio.ini # Configuração de ambiente e dependências do PlatformIO

```

---

## 🚀 Como Executar o Projeto

1. Certifique-se de ter o [VS Code](https://code.visualstudio.com/) instalado com a extensão **PlatformIO IDE**.
2. Clone este repositório:
```bash
git clone [https://github.com/Davilacovelli/AgroPulse.git](https://github.com/Davilacovelli/AgroPulse.git)

```


3. Abra a pasta do projeto no PlatformIO.
4. Conecte o Arduino Uno R3 via USB e compile/carregue o código para a placa utilizando o comando de upload do PlatformIO.

---

## 👤 Autor

Desenvolvido por **Davi Iacovelli**

*Estudante de Ciência da Computação — Universidade Veiga de Almeida (UVA)*

