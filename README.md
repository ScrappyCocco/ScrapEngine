![Engine Logo](readme_images/logo.png)

## An engine made of scrap code [/s](https://www.urbandictionary.com/define.php?term=%2Fs)

| Build command  | Status |
| :---: | :---: |
| cppcheck | [![cppcheck](https://github.com/ScrappyCocco/ScrapEngine/actions/workflows/cppcheck.yml/badge.svg)](https://github.com/ScrappyCocco/ScrapEngine/actions/workflows/cppcheck.yml) |

# Description

I have always been passionate about game development and rendering, and I wanted to go deeper into it. With the arrival of Vulkan, I thought it was a good time to start learning how a game engine works. The development of his game engine started on July 2018, and at the beginning of August 2018 it was able to render the basic triangle. Since then I had to slow down for a few months because of University and its projects, but on August 2019 this repository has been made public with the release of the first working small game tagged as [demo 1](https://github.com/ScrappyCocco/ScrapEngine/releases/tag/demo_1).

I followed mostly [Alexander Vulkan tutorial](https://vulkan-tutorial.com/) and [SaschaWillems Vulkan examples](https://github.com/SaschaWillems/Vulkan) to understand the basics and to develop it.

It is a very simple game engine, made mostly to understand the basics of rendering and how to connect multiple parts between them (input-render-audio-physics).

It is not perfect and is not intended to be used in production, is a personal project made to study Vulkan, feel free to modify it if you want. If you have any question feel free to open an Issue.

# How to build the engine
To see how to build the engine from the source code, please read the [wiki page](https://github.com/ScrappyCocco/ScrapEngine/wiki/How-to-build-the-engine).

# Known problems
Since it's a engine made from zero, the GameObject-Component structure is not perfect and may lead to bugs or errors involving transformations or rotation. Specially when moving the GameObject with multiple components or a GameObject and its children.
This is known when the user try to rotate a RigidbodyComponent.

There may be other parts of the engine that do not work perfectly or as expected.

I will try to make it better and to fix all the issues about it.

# What's next
I currently do not plan to keep working/updating this repository. I will not archive it and will leave it open to receive questions, pull requests or similar if anyone is interested in it.

Previous TODO list:
- [x] Directional light and Shadow-Mapping;
- [ ] (Should improve Forward Rendering structure or move to Deferred Rendering before adding more lights);
- [ ] Omnidirectional light and Shadow-Mapping;
- [ ] [...?]

# Special thanks
* [SaschaWillems](https://github.com/SaschaWillems/) for all his Vulkan examples and for his suggestions on Discord;
* [Charles](https://github.com/WubiCookie) for all his support during the whole development, helping me understanding where and what the problem was, and for all his help and suggestions;
* My friends [frncscdf](https://github.com/frncscdf) and [davidepi](https://github.com/davidepi) for their suggestions and support;
* All the people in the [Vulkan Discord server](https://discordapp.com/invite/tFdvbEj).

# Vulkan FAQ
* How do you render multiple objects? How do you render the UI?
  * See the discussion on [Issue#38](https://github.com/ScrappyCocco/ScrapEngine/issues/38).
* Resources to understand the basics of lights/shadows
  * See the discussion on [Issue#40](https://github.com/ScrappyCocco/ScrapEngine/issues/40).

# Download / Example gameplay gif

You can download this example game [here](https://github.com/ScrappyCocco/ScrapEngine/releases).

Version #1 of the game: [GIF](readme_images/game_animation_aug_2019.gif).

Version #2 of the game:
![Example game Gif gameplay](readme_images/game_animation.gif)
