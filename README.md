# Tower Defense

[![](https://tokei.rs/b1/github/Hikari03/TowerDefense?category=lines)](https://github.com/Hikari03/TowerDefense)
[![](https://tokei.rs/b1/github/Hikari03/TowerDefense?category=code)](https://github.com/Hikari03/TowerDefense)


## Installation
 - Simply git clone and run `make` and then `./td` in this directory

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

![tower_defense_UI](https://github.com/Hikari03/TowerDefense/assets/39591367/3ec32f9b-12e8-4673-9c51-49e8ee3566e5)

## Key bindings

- `n` - next frame (next point in time)
- `t` - tower menu (select, build, upgrade, sell)
- `v` - start wave
- `s` - save game
- `e` - exit game

#### Tower menu

- `1-9` to input tower spot
- `backspace` to erase number
- `enter` to confirm

When tower menu is active, UI is interactively updated with colors to show
which spot is <span style="color: #FFC3FF">free</span>, which is <span style="color: #5F87FF">occupied</span> and
whenever are you **selecting** <span style="color: #FF40FF">free</span> or <span style="color: #660BFF">occupied</span> spot
as shown in screenshots below.

![tower_defense_tower_menu_](https://github.com/Hikari03/TowerDefense/assets/39591367/e3a5f85f-8186-4cae-8ef0-47360c4a1430)
![tower_defense_tower_menu_2](https://github.com/Hikari03/TowerDefense/assets/39591367/14e24578-c3e8-4092-bf64-592479dec413)

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

![tower_defense_map_example](https://github.com/Hikari03/TowerDefense/assets/39591367/48d6d285-9071-4e81-994e-237a2b3add0a)

### Other Visual Features

#### You can see name with health of spawned enemies in lower left corner

![tower_defense_enemies_display](https://github.com/Hikari03/TowerDefense/assets/39591367/d528a2e4-006c-4cd3-96b6-e5b1fc96fbac)

#### Enemy coloring

- `Default` - <span style="color: #AF1C27">red</span>
- `Attacked` - <span style="background-color: #B51C27">red background</span>
- `Invisible` - <span style="color: #04E0E0">blue</span>

![tower_defense_screen](https://github.com/Hikari03/TowerDefense/assets/39591367/39d4b6d8-0516-4d51-b0fb-580bf1756700)
