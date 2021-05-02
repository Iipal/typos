# typos

Typing speed test in terminal written in C++ using ncurses.

> made by tmaluh a.k.a \_ipal a.k.a MrChebys a.k.a ...

## Features:

- You can move across already typped characters with Arrow Keys.
- Deleting input of current word by pressing <kbd>Ctrl</kbd>+<kbd>Backspace</kbd>, or if you at the start of the word - this shortcut will move the cursor to begin of the previous word.
- When words are ended, but time still ticking - you will start typing the same words from the beginning again. (Statistic will not be reset until the time is over)
- You can reset the current test with <kbd>Tab</kbd>, or on the Stats Screen with <kbd>Enter</kbd>.
- Under all the words displaying also prints previous, current, and next word to type with the current character always at the center of the screen.
- Displaying the timer.
- Detailed statistics.

***

#### Statistics:

- **WPM**: The correct way of calculating WPM including corrected typos. <sub>Net WPM</sub>
- **RAW WPM**: WPM without any typos calculations. <sub>Gross WPM</sub>
- **REAL WPM**: Calculating Net WPM, but with all typos what you ever made in your life ... <sub>Net WPM v2</sub>
- **TYPED**: Count of all typed characters.
- **CPS**: Characters Per Second.
- **TYPOS**: Corrected typos.
- **REAL TYPOS**: All typos that you made.
- **ACC**: Accuracy with corrected typos.
- **REAL ACC**: Accuracy with all typos.

***

#### Flags:
- `-h`: Prints this help message.
- `-t <seconds>`: Number of maximum time to type in seconds. <sub>Accepts only positive integer in range: 10 - 240; Default: 60.</sub>
- `-w <number>`: Number of maximum words to type. <sub>Accepts only positive integer in range: 10 - 150; Default: 42;</sub>
- `-S <path>`: Full path to file where your stats will be saved. <sub>Default: `./typos.log`;</sub>
- `-o <fmt_str>`: Stats format string. <sub>Valid format options: `|wrRtcTCaA`; Default: `wrR|tc|TC|aA`;</sub>
  - `|`: Delimiter.
  - `w`: Net WPM.
  - `r`: Gross WPM.
  - `R`: Net WPM v2.
  - `t`: Total typed characters.
  - `c`: Characters Per Second.
  - `T`: Corrected typos.
  - `C`: All typos.
  - `a`: Accuracy with corrected typos.
  - `A`: Accuracy with all typos.
- `-s`: Auto-save your stats at the end. <sub>Default: false;</sub>
- `-a`: Words sorted in alphabetical order. <sub>Default: false;</sub>
- `-m`: Monochrome mode. <sub>Default: false;</sub>
- `-f`: Free typing mode. The timer will not start. <sub>Default: false;</sub>
***

#### Keybindigs:

- Welcome Screen:
  - <kbd>Ctrl</kbd>+<kbd>C</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd>, and <kbd>Esc</kbd>: Now closing the `typos`.
  - Any other key will start the `typos`.

- While typing:
  - <kbd>←</kbd>: Moves to the previously typed character.
  - <kbd>→</kbd>: Moves to the next character. Works only for already typed characters.
  - <kbd>Backspace</kbd>: Removing current character.
  - <kbd>Ctrl</kbd>+<kbd>Backspace</kbd>: Removing current word, or goes to start of the previous.
  - <kbd>Tab</kbd>: Fully resetting current typing test(Already typed stats, words, and even timer will be reset). And you will start the test from the beginning.
  - <kbd>Ctrl</kbd>+<kbd>R</kbd>: Reset everything just like <kbd>Tab</kbd> do, but also re-roll words.
  - <kbd>Ctrl</kbd>+<kbd>C</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd>, and <kbd>Esc</kbd>: Now closing the `typos`.
  - Only printable characters will be prompt to the test (see `man 3 isprint`).
  - Any other input will be ignored.

- Stats Screen:
  - <kbd>Ctrl</kbd>+<kbd>C</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd>, and <kbd>Esc</kbd>: Now closing the `typos`.
  - <kbd>Ctrl</kbd>+<kbd>S</kbd>: Saves your typing test result to `./typos.log` file. By appending new test data to the end of the file and with the current local date at the top of each result.
  - <kbd>Tab</kbd>: Restart the test.
  - <kbd>Ctrl</kbd>+<kbd>R</kbd>: Restart the test and re-roll the words.

> !! IMPORTANT !!; My advice is to use <kbd>Ctrl</kbd>+<kbd>C</kbd>, and <kbd>Ctrl</kbd>+<kbd>D</kbd> keybindings instead of <kbd>Esc</kbd> whatever it's possible. Because of reasons of handling the "Escape Sequences" the <kbd>Esc</kbd>-key by itself has a delay in 1 sec.
>> The <kbd>Esc</kbd> is not removed because for some peoples the <kbd>Esc</kbd>-key may be a more comfortable way to close the program.

***

#### Debug mode

Will show you some additional information about current input with some stats if you need it.

To active this you must rebuild `typos` with:

```bash
make debug_all
```

## Installation the deps.:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev clang
```

Most of the other tools is already pre-installed in most of Linux distros. but if u still have troubles when building the app:

```bash
sudo apt-get install build-essential
```

## Building:

Just make it working:

```bash
make
```

More options for Makefile are described [here](https://github.com/Iipal/MakeMeBetter).

## Using the typos:

After successful installation you can run it like this:

```bash
./typos
```

To see the help info about some options:

```bash
./typos -h
```

If you wanted globally access to the `typos`:

```bash
mkdir -p ~/.bin;
git clone https://github.com/Iipal/typos/ ~/.bin/typos;
cd ~/.bin/typos && make re;
sudo ln -P ~/.bin/typos/typos /usr/bin/typos;

```

> Be careful with saving stat log, it always will be stored in the directory where you call the `typos`.
