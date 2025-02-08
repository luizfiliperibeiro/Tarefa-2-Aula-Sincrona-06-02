# Controle de Servomotor com PWM no Raspberry Pi Pico

## Descrição
Este projeto implementa o controle de um **servomotor** utilizando o **Raspberry Pi Pico** e a modulação por largura de pulso (**PWM**). O servomotor é movimentado entre **0°, 90° e 180°** inicialmente, e depois entra em um modo de movimentação contínua entre 0° e 180° de forma suave.

Adicionalmente, um **LED Verde (GPIO 12)** é utilizado para indicar visualmente a posição do servomotor. O brilho do LED aumenta conforme o servo se aproxima de 180° e diminui quando retorna a 0°.

## Requisitos

- **Raspberry Pi Pico**
- **Micro Servo Motor**
- **LED Verde**
- **Ambiente VS Code configurado para Pico SDK**
- **CMake e Make para compilação**
- **Git para versionamento**

## Configuração do Ambiente
1. Instale o **Pico SDK**:
   ```bash
   git clone -b master https://github.com/raspberrypi/pico-sdk.git
   cd pico-sdk
   git submodule update --init
   export PICO_SDK_PATH=$(pwd)
   ```

2. Instale dependências no **Linux (Ubuntu/Debian)**:
   ```bash
   sudo apt update && sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
   ```

3. Instale o **VS Code** e a extensão **C/C++**.

## Como Compilar e Rodar
1. Clone o repositório e entre na pasta do projeto:
   ```bash
   git clone https://github.com/luizfiliperibeiro/Tarefa-2-Aula-Sincrona-06-02.git
   cd Tarefa-2-Aula-Sincrona-06-02
   ```

2. Crie a pasta **build** e execute o **CMake**:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j4
   ```

3. Conecte o Raspberry Pi Pico ao PC segurando o botão **BOOTSEL** e copie o arquivo gerado (`servo_pwm.uf2`) para o dispositivo:
   ```bash
   cp servo_pwm.uf2 /media/$USER/RPI-RP2/
   ```
   O Pico reiniciará automaticamente e executará o código.

## Funcionamento do Programa
- O servomotor irá inicialmente para **180°, depois 90° e 0°**.
- Após essa sequência, ele iniciará um movimento suave e contínuo de **0° para 180° e vice-versa**.
- O **LED Verde (GPIO 12)** aumenta de brilho conforme o servo se aproxima de **180°** e diminui quando retorna a **0°**.

🔹 O que o discente observará no LED Verde?

✅ O brilho do LED Verde (GPIO 12) acompanhará a movimentação do servo:

🟢 Servo em 0° → LED Verde bem fraco.

🟢 Servo em 90° → LED Verde com brilho médio.

🟢 Servo em 180° → LED Verde bem brilhante.

💡 Durante a movimentação contínua, a intensidade do LED aumentará e diminuirá suavemente.

## Vídeo Ensaio

https://drive.google.com/file/d/1R4Ehd4NT3iIH5XwuAlY90NQZaUM3FraZ/view?usp=sharing