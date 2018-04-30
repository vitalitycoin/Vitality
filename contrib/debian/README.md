
Debian
====================
This directory contains files used to package Vitalityd/Vitality-qt
for Debian-based Linux systems. If you compile Vitalityd/Vitality-qt yourself, there are some useful files here.

## Vitality: URI support ##


Vitality-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Vitality-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Vitalityqt binary to `/usr/bin`
and the `../../share/pixmaps/Vitality128.png` to `/usr/share/pixmaps`

Vitality-qt.protocol (KDE)

