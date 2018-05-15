# The Royal Game of Ur

[![Build Status](https://travis-ci.org/kirklange/royal-game-of-ur.svg?branch=master)](https://travis-ci.org/kirklange/royal-game-of-ur)
[![Code Documented](https://img.shields.io/badge/docs-passing-brightgreen.svg)](http://kirklange.com/royal-game-of-ur)
[![Contributors](https://img.shields.io/github/contributors/kirklange/royal-game-of-ur.svg)](https://github.com/kirklange/royal-game-of-ur/graphs/contributors)
[![License: zlib](https://img.shields.io/badge/license-zlib-blue.svg)](https://zlib.net/zlib_license.html)
<!--[![GitHub Issues](https://img.shields.io/github/issues/kirklange/royal-game-of-ur.svg)](https://github.com/kirklange/royal-game-of-ur/issues)-->

The Royal Game of Ur with expectiminimax AI.



## Quick Start Guide

Get the prerequisites, if you don't have them already.

```bash
sudo apt-get update
sudo apt-get install -y gcc git make
```

Download, build, and run the repo code.

```bash
git clone https://github.com/kirklange/royal-game-of-ur.git
cd royal-game-of-ur
make init
make build
make run
```

`test_ai` is the default project. To change which project gets built and run,
see the [Make It!](#make-it) section.



## Game Rules Description

This game has four tetrahedral dice. Two of the four corners are marked with a
white dot. The amount of moves a player gets is equivalent to the amount of
dots pointing up after a roll. Rolling a 0 means you lose that turn. The
probability of recieving `n` amount of moves is as follows:

0 | 1 | 2 | 3 | 4
--- | --- | --- | --- | ---
1/16 | 1/4 | 3/8 | 1/4 | 1/16

There are two players. Each starts in the notch on their own side of the
board. Each piece must go up their row (starting on the four-tile segment),
down the middle row, then back around to the notch in order to complete its
tour around the board. In order to move off the board you must have the exact
number of required moves in order to do so. For example, if a piece is on the
very last tile, you must roll exactly a 1 in order to move that tile off the
board. The first player to have all seven of their pieces go around the board
wins.

![The Game Board](https://raw.githubusercontent.com/kirklange/royal-game-of-ur/master/docs/rgu_video_snapshot.png)

**Snapshot taken from [this video](https://youtu.be/WZskjLq040I) at `3m49s`.**

On the shared center row, players can land on each other and reset the victim
tile back to its starting position. Landing on a flower tile grants an extra
turn and dice roll. Being on a flower tile protects you from enemy tiles (i.e.
they can't land on you).



## AI Implementation

TODO: explain



## Proof of Competence

Below is an example output of `test_ai`, formatted into a pretty spreadsheet.

![AI Benchmark](https://raw.githubusercontent.com/kirklange/royal-game-of-ur/master/docs/test_ai_spreadsheet.png)



## Make It!

The following are various unit tests for this project, including the main 
game executable itself.

* `test_dice` The most basic test, it prints out a 10x10 table of dice rolls.
* `test_board` This verifies whether the board initializes correctly or not.
* `test_ai` This benchmarks the AI, comparing it against random agents and 
agents with less lookahead than itself.
* `main_rgu` The main game itself. The program will ask you an initial set of 
questions like whether you want each player to be a human or an AI. This 
program will print out the board and its utility value after each turn.

To change which project gets built and run, modify the `MAIN_SUBDIR` variable 
in `Makefile`.



## Copyright

Copyright (c) 2018 Kirk Lange <https://github.com/kirklange/royal-game-of-ur>

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

