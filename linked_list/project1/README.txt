Music Playlist Manager

Build (student cluster example):
  g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o playlist

Run:
  ./playlist

How to interact:
  1) Add song: enter title, artist, duration (seconds)
  2) Remove song: enter the song title exactly
  3) Next/Previous: move through the doubly linked list
  4) Jump to position: 1-based index into the playlist
  5) Show playlist: displays all songs and current track
  6) Show current song: prints the active track
