# Breakout

A nostalgic remake of the classic Atari Breakout game, designed specifically for PC DOS.
You can download the `EXE` file from [itch.io](https://ms0g.itch.io/breakout).

<img src="IMG/1.png" alt="image" width="402" height="auto"> <img src="IMG/2.png" alt="image" width="402" height="auto">
<img src="IMG/3.png" alt="image" width="402" height="auto"> <img src="IMG/4.png" alt="image" width="402" height="auto">

## Prerequisites
- **Turbo C++** (`TCC.EXE`) version 3.0 or later  
- **Turbo Assembler** (`TASM.EXE`) version 4.1 or later  
- **Turbo Linker** (`TLINK.EXE`) version 5.0 or later  
- **DOSBox** emulator or a real MS-DOS-compatible computer

## Building
To install the required build tools and compile the source files, follow these steps:

1. Download and install DOSBox from [DOSBox website](https://www.dosbox.com/).

2. Open DOSBox and mount the directory containing the project files.

```bash
mount C /path/to/PROJECT
```

3. Change to the mounted directory.
```bash
C:
```

4. Navigate to the `TOOLS/tcpp` directory within the project directory.
```bash
C:\>cd TOOLS\tcpp
```


5. Run `INSTALL.EXE`.
```bash
C:\>INSTALL.EXE
```

6. Follow the on-screen prompts to complete the installation.

7. Move the `MAKEFILE`, `COPTS.TXT`, `TOOLS/TASM.EXE`, and the source files into the `/TC/BIN/` directory.

8. After moving the files, return to DOSBox and cd `/TC/BIN/`.
```bash
C:\>cd /TC/BIN
```
and start the build process:
```bash
C:\>MAKE.EXE
```
## Run
```bash
C:\>BREAKOUT.EXE
```
## How to play
- Use the arrow keys on your keyboard to move the paddle left and right.
- Hit the ball with the paddle to break the bricks at the top of the screen.
- Prevent the ball from falling off the bottom of the screen by keeping it in play with the paddle.
- Try to break as many bricks as possible to score points and advance through levels.

## Contributing

Contributions to improve the game are welcome! If you have ideas for enhancements or bug fixes, feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MPL-2.0 License. See the LICENSE file for details.



