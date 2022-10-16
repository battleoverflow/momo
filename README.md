# Momo's Quest
Momo's Quest is a C++ game using raylib (inspired by Nene's Quest from New Game!)

Momo's Quest is a short story about an adventurer who wanders into the woods and encounters a horrifying BOSS battle! She'll have to battle this boss with all her might, but in the end, it's up to the player if she wins or loses. Good luck!

<img src=".github/assets/banner.png" alt="Banner of Momo's Quest" />

If you would like to build the code from source, you can download the Makefile by running the bash script:
```bash
./download.sh
```

You will also need to setup your `.vscode` tasks to build the project. This can be done multiple ways, but I just created some quick tasks to generate an executable while testing. This was more a personal project, so no real documentation will be created, but if you would like to play the finished game, feel free to check out the releases on GitHub.

Example (Windows - Debug):

`tasks.json`
```json
{
    "tasks": [
        {
            "label": "build debug",
            "type": "process",
            "command": "make",
            "args": [
                "PLATFORM=PLATFORM_DESKTOP",
                "BUILD_MODE=DEBUG"
            ],
            "windows": {
                "command": "C:/raylib/w64devkit/bin/mingw32-make.exe",
                "args": [
                    "RAYLIB_PATH=C:/raylib/raylib",
                    "PROJECT_NAME=${fileBasenameNoExtension}",
                    "OBJS=src/*.cpp",
                    "BUILD_MODE=DEBUG"
                ]
            }
        }
    ]
}
```

NOTES
- The map does not currently have boundaries, so feel free to run off the map if you feel like it

## Resources
All sprites and art were provided by the following:
- [LuizMelo](https://luizmelo.itch.io/) - Charcter Sprites
- [Elthen](https://elthen.itch.io/) - Map Tileset
- [Hifumi1337](https://github.com/Hifumi1337) - Background/Code