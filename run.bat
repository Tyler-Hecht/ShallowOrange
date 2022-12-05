@echo off
cd src
g++ -o ../main.exe main.cpp readconfig.cpp Game.cpp MoveTree.cpp Evaluate.cpp Board.cpp Eval.cpp Piece.cpp Move.cpp
cd ..
.\main
