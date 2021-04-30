# typos
Typing speed test in terminal written in C using ncurses.

Just begun.


# Installation the deps.:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

Most of the other tools is already pre-installed in most of Linux distros. but if u still have troubles when building the app:
```bash
sudo apt-get install build-essential gcc
```
Or even try different compiler:
```bash
sudo apt-get install clang
```

# Building:
Just make it working:
```bash
make
```

# Using the typos:
After successful installation you can run it like this:
```bash
./typos
```

To see the help info about some options:
```bash
./typos -h
```

# Stats:
 - WPM: a.k.a Net WPM; the correct way of calculating WPM including corrected typos.
 - RAW WPM: a.k.a Gross WPM; WPM without any typos calculations.
 - REAL WPM: a.k.a Net WPM v2; calculating Net WPM, but with all typos what you ever made in your life ...
 - TYPED: count of all typed characters.
 - CPS: Characters Per Second.
 - TYPOS: Corrected typos.
 - REAL TYPOS: All typos that you made.
 - ACC: Accuracy with corrected typos.
 - REAL ACC: Accuracy with all typos.
