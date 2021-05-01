# typos
Typing speed test in terminal written in C++ using ncurses.
> made by tmaluh a.k.a _ipal a.k.a MrChebys a.k.a ...

## Features:

 - You can move across already typped characters with Arrow Keys.
 - Deleting input of current word by pressing <kbd>Ctrl</kbd>+<kbd>Backspace</kbd>, or if you at the start of the word - this shortcut will move the cursor to begin of the previous word.
 - When words are ended, but time still ticking - you will start typing the same words from the beginning again. (Statistic will not be reset until the time is over)
 - Under all the words displaying also prints previous, current, and next word to type with the current character always at the center of the screen.
 - Displaying the timer.
 - Detailed statistics.
 - Ability to restart the test.

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
 - `-t <seconds>`: Number of maximum time to type in seconds. Accepts only positive integer in range: 10 - 240; Default: 60.
 - `-w <number>`: Number of maximum words to type. Accepts only positive integer in range: 10 - 150; Default: 42;
 - `-a`: Words sorted in alphabetical order. Default: false;
 - `-m`: Monochrome mode. Default: false;

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

## Using the typos:
After successful installation you can run it like this:
```bash
./typos
```

To see the help info about some options:
```bash
./typos -h
```
