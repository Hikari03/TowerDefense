# Tower Defense

## Instalation
 - Simply git clone and run `make compile` and then `./td` in this directory

## Description

### Introduction

This is a simple tower defense game written in C++.
Tower Defense is a game where you have to defend your base from enemies
by building towers to defeat them before they reach your base.

### Enemies

Enemies are spawned in waves. Each wave is stronger than the previous one.
There are 4 types of enemies: `Minion`, `Orc`, `Dragon` and `Boss` and on map are shown
as `M`, `O`, `D` and `B` respectively.
- `Minion` is basic enemy with no special abilities.
- `Orc` has armor, so it takes less damage from towers.
- `Dragon` is invisible for specified amount of time after first hit.
- `Boss` has healing ability and heals itself all the time.

### Towers

There are 4 types of towers: `Tower`, `Fire Tower`, `Ice Tower` and `Sniper Tower` and on map are shown
as `T`, `F`, `I` and `S` respectively.

- `Tower` is basic tower with no special abilities.
- `Fire Tower` sets enemies on fire, so they take damage over time.
- `Ice Tower` stuns enemies.
- `Sniper Tower` has long range and deals high damage but reloads slowly.

Tower can be upgraded to these types, aka **specialized**.

### UI

User interface is realized without any graphics library.

![](https://houdeda2.cz/hosting/tower_defense/tower_defense_UI.png)

## Key bindings

- `n` - next frame (next point in time)
- `t` - tower menu (select, build, upgrade, sell)
- `v` - start wave
- `s` - save game
- `e` - exit game

#### Tower menu

- `1-9` to input tower spot
- `e` to erase number
- `c` to confirm

When tower menu is active, UI is interactively updated with colors to show
which spot is <span style="color: #FFC3FF">free</span>, which is <span style="color: #5F87FF">occupied</span> and
whenever are you **selecting** <span style="color: #FF40FF">free</span> or <span style="color: #660BFF">occupied</span> spot
as shown in screenshots below.

![](https://houdeda2.cz/hosting/tower_defense/tower_defense_tower_menu_.png)
![](https://houdeda2.cz/hosting/tower_defense/tower_defense_tower_menu_2.png)

## Other Features

- **Save/Load** - game can be saved and loaded at any time
- **Settings** - game settings can be changed in `config.txt` file in `assets` folder
- **Map Creation** - new maps can be created in `assets` folder and loaded in game using `config.txt` file
- **Input** - input is processed without having to press enter

### Map Creation

As mentioned above, new maps can be created in `assets` folder and loaded in game using `config.txt` file.
Map has to be .txt file and has to contain only these characters:

- `(space)` - empty space
- `-` - horizontal wall
- `|` - vertical wall
- `1` - top left corner
- `2` - top right corner
- `3` - bottom right corner
- `4` - bottom left corner
- `5` - double lower corner
- `6` - double left corner
- `7` - double upper corner
- `8` - double right corner
- `+` - cross wall
- `!` - spawn point
- `?` - base point
- `9` - tower spot

Using these characters, you can create any map you want. Here is example of map from
screenshots:

![](https://houdeda2.cz/hosting/tower_defense/tower_defense_map_example.png)

### Other Visual Features

#### You can see name with health of spawned enemies in lower left corner

![](https://houdeda2.cz/hosting/tower_defense/tower_defense_enemies_display.png)

#### Enemy coloring

- `Default` - <span style="color: #AF1C27">red</span>
- `Attacked` - <span style="background-color: #B51C27">red background</span>
- `Invisible` - <span style="color: #04E0E0">blue</span>

![](https://houdeda2.cz/hosting/tower_defense/tower_defense_screen.png)


# TODO
 - [ ] Rewrite rendering to use librender from personal projects to get rid of awful things like `system(clear)`
