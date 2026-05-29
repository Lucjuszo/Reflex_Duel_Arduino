# ⚡ Reflex Duel (Arduino Uno)

An engaging, fast-paced two-player arcade game built on the Arduino Uno. This project tests players' reaction speeds in milliseconds and uses an 8-digit 7-segment display (split into two 4-digit sections) to show exact reaction times.

## 🎮 How to Play
1. **Start the Game:** Press the Start button. The display will show `StArt` and count down from 3.
2. **Wait for the Signal:** The system will wait for a random duration (between 2 and 5 seconds). 
3. **React!** As soon as the center Start LED lights up, press your button as fast as you can.
4. **False Starts:** If you press your button *before* the LED lights up, it's a false start, and your opponent automatically gets a point!
5. **Winning:** The first player to reach 2 points wins the game. The display will show the winner (e.g., `P 1` or `P 2`).

## 🛠️ Hardware Requirements
* 1x Arduino Uno
* 1x 8-Digit 7-Segment Display Module (MAX7219)
* 3x Push Buttons (Player 1, Player 2, Start/Reset)
* 5x LEDs (1x Start signal, 4x Score indicators)
* Resistors (for LEDs)
* Breadboard and jumper wires

## 🔌 Pin Configuration (Wiring)

### Buttons (Wired to GND, using internal pull-ups)
| Component | Arduino Pin |
| :--- | :--- |
| Player 1 Button | `Pin 2` |
| Player 2 Button | `Pin 3` |
| Start/Reset Button | `Pin 9` |

### LEDs
| Component | Arduino Pin |
| :--- | :--- |
| Start Signal LED (Center) | `Pin 4` |
| Player 1 Score LED 1 | `Pin 5` |
| Player 1 Score LED 2 | `Pin 6` |
| Player 2 Score LED 1 | `Pin 7` |
| Player 2 Score LED 2 | `Pin 8` |

### 7-Segment Display (MAX7219)
| Display Pin | Arduino Pin |
| :--- | :--- |
| DIN (Data) | `Pin 12` |
| CS (Load) | `Pin 11` |
| CLK (Clock) | `Pin 10` |
| VCC | `5V` |
| GND | `GND` |

## ⚙️ Software Dependencies
This project requires the **LedControl** library to drive the MAX7219 display. 
You can install it directly via the Arduino IDE Library Manager:
1. Open Arduino IDE.
2. Go to `Sketch` -> `Include Library` -> `Manage Libraries...`
3. Search for **LedControl** and install it.

## 🚀 How to run
1. Clone this repository or download the `.ino` file.
2. Open the file in the Arduino IDE.
3. Wire the components according to the Pin Configuration table.
4. Connect your Arduino Uno to your computer.
5. Compile and upload the code!