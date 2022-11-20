DarkOrbit (2009)
================

This is a pet project of mine so that I can play with a few tools mixed altogether (namely: cross-platform and cross-compiler [C++20][1], [CMake presets][2], [CLion][3] integration, [Conan][4] migration, [SFML][5], ...).

DarkOrbit (now named [DarkOrbit: Reloaded][6]) is a old Flash & web-based MMO game I used to play a lot when I was younger. The old client was a fixed-size window and UI, so recreating it makes for a great small learning project, not having to support thousands of modern features and configurations.

## How to build

You need to install and configure Conan, CMake 3.17+ and Ninja.

### Conan

```shell
[sudo] pip install -U conan # Not using sudo means having to manually add to PATH on Linux
conan profile new --detect default
# Using GCC or Clang with libstdc++? Execute this line too:
conan profile set settings.compiler.libcxx=libstdc++11
conan config set general.revisions_enabled=1
# Windows (cmd or Powershell)
cmd /C "echo tools.cmake.cmaketoolchain:generator=Ninja Multi-Config >> %USERPROFILE%/.conan/global.conf"
# Others
echo "tools.cmake.cmaketoolchain:generator=Ninja Multi-Config" >> ~/.conan/global.conf
```

### Build

Then (don't forget to run this from your VS command prompt if building with MSVC):
```shell
conan install -if build/generators/Release .
cmake --preset default
cmake --build --preset release
```

### Run

```shell
# Windows (CMD or Powershell)
.\build\Release\DarkOrbit.exe
# Others
./build/Release/DarkOrbit
```

[1]: https://github.com/AnthonyCalandra/modern-cpp-features#c20171411
[2]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[3]: https://www.jetbrains.com/clion/features/
[4]: https://docs.conan.io/en/latest/
[5]: https://www.sfml-dev.org/index.php
[6]: https://www.darkorbit.com/
