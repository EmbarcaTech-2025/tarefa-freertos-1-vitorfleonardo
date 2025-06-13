# Tarefa: Sistema Multitarefa com FreeRTOS - EmbarcaTech 2025

**Autor:** Vitor Feijó  
**Curso:** Residência Tecnológica em Sistemas Embarcados  
**Instituição:** EmbarcaTech - HBr  
📍 Brasília, Junho de 2025

---

## 🎯 Objetivo da tarefa

Implementar um sistema embarcado multitarefa utilizando o sistema operacional de tempo real **FreeRTOS** na plataforma **BitDogLab**, baseada na **Raspberry Pi Pico W**.

O projeto tem como objetivo demonstrar o controle concorrente de periféricos através de tarefas independentes criadas com o FreeRTOS. O sistema é capaz de controlar um LED RGB e um buzzer de forma periódica, além de utilizar dois botões físicos para suspender e retomar essas tarefas dinamicamente.

---

## 🛠️ Componentes Utilizados

| Componente           | Descrição                                              |
|----------------------|--------------------------------------------------------|
| **BitDogLab**        | Plataforma embarcada baseada na Raspberry Pi Pico W    |
| **Raspberry Pi Pico W** | Microcontrolador dual-core com suporte a C/C++ e FreeRTOS |
| **LED RGB (GPIO11/12/13)** | Controlado ciclicamente por tarefa independente      |
| **Buzzer (GPIO21)**  | Emite bipes curtos periodicamente via tarefa própria   |
| **Botão A (GPIO5)**  | Controla suspensão/retomada da tarefa do LED           |
| **Botão B (GPIO6)**  | Controla suspensão/retomada da tarefa do buzzer        |

---

## 🧠 Funcionalidades do Projeto

- LED RGB alterna entre vermelho, verde e azul a cada 500ms.
- Buzzer emite um bipe de 100ms a cada 1 segundo.
- Botão A suspende/retoma o LED.
- Botão B suspende/retoma o buzzer.
- Polling dos botões a cada 100ms com controle por prioridade de tarefas.

---

## 📁 Estrutura do Projeto

```
.
├── CMakeLists.txt # Script de build principal do projeto
├── pico_sdk_import.cmake # Importa o SDK do Raspberry Pi Pico
├── include/
│ └── FreeRTOSConfig.h # Configuração do FreeRTOS para o RP2040
├── main.c # Código principal da aplicação multitarefa
├── FreeRTOS/ # Kernel do FreeRTOS clonado
│ ├── include/ # Headers padrão do FreeRTOS
│ ├── portable/ # Implementações específicas de arquitetura
│ └── *.c # Fontes do kernel RTOS
```

---

## 🚀 Como Executar o Projeto

### 1. Clone o projeto e entre na pasta:

```bash
git clone https://github.com/EmbarcaTech-2025/tarefa-freertos-1-vitorfleonardo
cd tarefa-freertos-1-vitorfleonardo
```

### 2. Clone o kernel do FreeRTOS (se ainda não feito):

```bash
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git FreeRTOS
```

### 3. Compile o projeto:

```bash
rm -rf build
mkdir build
cd build
cmake ..
make -j4
```

### 4. Embarque o .uf2 na BitDogLab:

```bash
cp tarefa-freertos-1-vitorfleonardo.uf2 /media/$USER/RPI-RP2/
```

---

## 🔍 Observações Técnicas

- Utiliza vTaskCreate(), vTaskDelay(), vTaskSuspend() e vTaskResume().
- O polling de botões é feito com gpio_get() e controle de estados internos (ledSuspenso, buzzerSuspenso).
- Configuração mínima de pilha por tarefa (256).
- FreeRTOSConfig.h adequado ao RP2040, com suporte a heap_4, contadores, semáforos e timers.
- Modularização de código e boas práticas de legibilidade.

---

## 📸 Resultado Esperado

- O LED RGB pisca em sequência (vermelho, verde, azul).
- O buzzer emite um “bip” curto de forma periódica.
- Botão A pausa e retoma o LED.
- Botão B pausa e retoma o buzzer.

<p align="center">
  <img src="./assets/demo.gif" alt="Demonstração do sistema em funcionamento" width="500"/>
</p>