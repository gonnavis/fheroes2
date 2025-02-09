# [**fheroes2**](README.md) installation guide

## Requirements

You will need to have a demo version or the full version of **Heroes of Might and Magic II** game to be able to play. We strongly advise to purchase the original game on [**GOG**](https://www.gog.com) or [**Ubisoft Store**](https://store.ubi.com) platforms. Alternatively, you can **download a free demo version of the game using the bundled script**. See detailed instructions below.

## Installation

Precompiled binaries of the release version are currently available for the following platforms and operating systems:

* [**Windows**](#windows)
  * [**Windows installer**](#windows-installer)
  * [**Windows ZIP archive**](#windows-zip-archive)
* [**macOS**](#macos)
  * [**MacPorts**](#macports)
  * [**macOS ZIP archive**](#macos-zip-archive)
* [**Linux**](#linux)
  * [**AUR package**](#aur-package)
  * [**Linux ZIP archive**](#linux-zip-archive)

Alternatively, you can download the precompiled binaries of the latest commit (snapshot) [**here**](#snapshots).

<a name="windows"></a>
## Windows

<a name="windows-installer"></a>
### Windows installer

* Download one of the following Windows installer packages:

  * **Windows x64 (64-bit)**:<br>
  [**SDL2 (recommended)**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x64_SDL2_installer.exe) or<br>
  [**SDL1**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x64_SDL1_installer.exe)

  * **Windows x86 (32-bit)**:<br>
  [**SDL2 (recommended)**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x86_SDL2_installer.exe) or<br>
  [**SDL1**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x86_SDL1_installer.exe)

* After downloading the installer, launch it and follow the instructions.

* During the installation process, you will be prompted to download and install the demo version of the original game (you can also do this later by clicking the appropriate shortcut in the Windows Start menu).

* If you have a legally purchased copy of the original game, you can choose not to install the demo version, but to copy all files belonging to the original game to the fheroes2 installation directory.

<a name="windows-zip-archive"></a>
### Windows ZIP archive

* Download one of the following Windows ZIP archives:

  * **Windows x64 (64-bit)**:<br>
  [**SDL2 (recommended)**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x64_SDL2.zip) or<br>
  [**SDL1**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x64_SDL1.zip)

  * **Windows x86 (32-bit)**:<br>
  [**SDL2 (recommended)**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x86_SDL2.zip) or<br>
  [**SDL1**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_windows_x86_SDL1.zip)

* After downloading the ZIP archive, extract it to a suitable directory of your choice.

* If you have a legally purchased copy of the original game, copy all files belonging to the original game to the fheroes2 installation directory. Otherwise, you can download and install the demo version of the original game by running the `demo_windows.bat` script supplied in the ZIP archive.

<a name="macos"></a>
## macOS

<a name="macports"></a>
### MacPorts

If you are using [**MacPorts**](https://www.macports.org/), you can install the game by running the following command:

```sh
port install fheroes2
```

Then follow the instructions on the screen.

<a name="macos-zip-archive"></a>
### macOS ZIP archive

* Download the [**macOS ZIP archive**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_macos10_15_sdl2.zip).

* After downloading the ZIP archive, extract it to a suitable directory of your choice and then run the script `install_sdl_1.sh` or `install_sdl_2.sh` (depending on the downloaded build) from the `script/macos` subdirectory. This will install the SDL libraries required to run the game.

* If you have a legally purchased copy of the original game, copy all files belonging to the original game to the fheroes2 installation directory. Otherwise, you can download and install the demo version of the original game by running the `demo_unix.sh` script supplied in the ZIP archive.

<a name="linux"></a>
## Linux

<a name="aur-package"></a>
### AUR package

If you are using Arch Linux or compatible distribution, you can install [fheroes2 package](https://aur.archlinux.org/packages/fheroes2) from AUR (Arch User Repository).

#### Install using AUR helper

If you use one of AUR helpers, e.g. `yay`, you can install the game by running the following command:

```sh
yay -S aur/fheroes2
```

#### Install using official guide

Follow [official guide](https://wiki.archlinux.org/title/Arch_User_Repository#Installing_and_upgrading_packages). One of possible command sets:

```sh
git clone https://aur.archlinux.org/fheroes2.git
cd fheroes2
makepkg -si
```

If you have a legally purchased copy of the original game, copy all files belonging to the original game to the `$XDG_DATA_HOME/fheroes2` (usually `~/.local/share/fheroes2`) directory. Otherwise, you can download and install the demo version of the original game by running the `/usr/share/fheroes2/demo_unix.sh` script.

<a name="linux-zip-archive"></a>
### Linux ZIP archive

* Download one of the following Linux ZIP archives:<br>
[**SDL2 (recommended)**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_ubuntu_sdl2.zip) or<br>
[**SDL1**](https://github.com/ihhub/fheroes2/releases/latest/download/fheroes2_ubuntu_sdl1.zip).

* After downloading the ZIP archive, extract it to a suitable directory of your choice. Then you will need to install the SDL libraries required to run the game. The installation procedure depends on the Linux distribution you are using:

  * **Debian-based**: run the script `install_sdl_1.sh` or `install_sdl_2.sh` (depending on the downloaded build) from the `script/linux` subdirectory.

  * **Pacman-based (e.g. Arch Linux)**: run the following command: `sudo pacman -S sdl sdl_mixer`.

  * **RedHat-based**: for RPM-based distributions (such as Fedora or RedHat) use the commands `sudo yum install SDL*` or `sudo dnf install SDL*`.

  * **openSUSE**: openSUSE supports the One-Click-Install using the `SDL_mixer.ymp` file from the `script/linux` subdirectory.

  * **Gentoo**: run the following command: `emerge --ask media-libs/sdl2-mixer`.

* After all dependencies are installed, copy all files belonging to the original game to the fheroes2 installation directory if you have a legally purchased copy of the original game. Otherwise, you can download and install the demo version of the original game by running the `demo_unix.sh` script supplied in the ZIP archive.

<a name="snapshots"></a>
## Snapshots

You can download the precompiled binaries of the latest commit (snapshot) for
**Windows** (
[**x64 SDL2**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-windows-x64-SDL2),
[**x64 SDL1**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-windows-x64-SDL1),
[**x86 SDL2**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-windows-x86-SDL2) and
[**x86 SDL1**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-windows-x86-SDL1)
),
**macOS** (
[**SDL2**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-osx-sdl2_dev) and
[**SDL1**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-osx-sdl1_dev)
),
**Ubuntu** (
[**SDL2**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-linux-sdl2_dev) and
[**SDL1**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-linux-sdl1_dev)
) and
[**PS Vita**](https://github.com/ihhub/fheroes2/releases/tag/fheroes2-psv-sdl2_dev).
**These binaries incorporate all the latest changes, but also all the latest bugs, and are mainly intended for developers. DON'T EXPECT THEM TO WORK PROPERLY.**
