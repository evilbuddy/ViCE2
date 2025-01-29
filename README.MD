# Usage
`ViCE.exe <video> (length) (height)`

the 1st argument is the video.

The 2nd and 3rd arguments are the size of the output (cols, rows). If only one is set then it will be ignored.

Performance highly depend on the terminal emulator (e.g. runs better in Kitty than GNOME Terminal on the same environment)
If you're using Windows, enjoy the 5 FPS.

# Build
## Dependencies
- CMake (3.30+)
- OpenCV2 (tested with 4.11)

## Linux
```
git clone https://github.com/evilbuddy/ViCE2.git
mkdir build
cd build
cmake ..
make
```

## Windows
Coming someday (maybe (maybe not))

## MacOS
I'm not sure it'd run anyways
