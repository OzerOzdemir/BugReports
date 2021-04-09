# BugReports

## SimpleFlicker
**Bug:** Adding a large number of items (100 /sec) to QListView via a QAbstractItemModel
causes the list to flicker.

**Project Folder:** [SimpleFlicker](SimpleFlicker)

**Repro Video:** [Flicker.mov](SimpleFlicker/Flicker.mov)
**Repro Video2:** [Flicker2.mov](SimpleFlicker/Flicker2.mov)


**BUG REPRO:** 

Change the following line for flicker.
The first argument tells how many items to create.
The second argument is the time to Sleep in ms bewteen each item creation

When the Sleep argument is 10 ms, it creates 100 items per second. This
causes a clear flicker on a Release build (as well as Debug build)

The flicker mostly goes away when the Sleep argument is set to 100 (i.e.
10 insertions /sec)

Note: the cell size, number of items, and item insertion frequency have been
set to these values only to make it easier to show the flickering. If you
set them to lesser values, it still happens. For example the [Flicker2.mov](SimpleFlicker/Flicker2.mov)
file shows with cell size 200, number of insertion 1000, and it still flickers
when resizing the window.

This has been verified on a Macbook Pro macOS Big Sur 11.2.3
QT Version 6.0.1

* Qt 5.15.2 (x86_64-little_endian-lp64 shared (dynamic) release build;
by Clang 10.0.0 (clang-1000.11.45.5) (Apple)) on "cocoa"
* OS: macOS 10.16 [darwin version 20.3.0]
* Architecture: x86_64; features: SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX AVX2

Also verified on Ubuntu QT 6.0.3

* Qt 5.15.2 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 5.3.1 20160406 (Red Hat 5.3.1-6)) on "xcb" 
* OS: Ubuntu 20.04.2 LTS [linux version 5.8.0-48-generic]
* Architecture: x86_64; features: SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX AVX2
