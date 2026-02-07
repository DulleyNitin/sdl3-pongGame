#!/bin/sh
set -e

g++ main.cpp app.cpp paddle.cpp ball.cpp UImanager.cpp -o pong $(pkg-config --cflags --libs sdl3 sdl3-ttf)

