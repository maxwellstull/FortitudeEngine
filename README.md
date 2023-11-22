# Fortitude Engine
Fortitude Engine is an engine I am making to be used in the creation of tower defense games. 
### Inspiration
I've wanted to create games for a while as a hobby, and have tried using engines like Unreal. However, I was not a fan of all of the bulky overhead, and the node connecting. I wanted a game engine that was as heavy-duty as I needed, and mainly, *that used actually programming.*
### Motivation
The motivation behind creating this game engine and game is to eventually create a tower defense game and publish it on Steam. I also wanted to learn more about game development, such as how input is handled, and the overall functionality of a "game loop". 
### Engine Goals
The goal of the engine is to provide an easy-to-use and uncumbersome library to interact with to make tower defense games. The thought behind it is that whoever uses it would slightly edit the library to adjust it to the needs. The code is meant to be easily interpretable, and not full of what we see so often in C++ libraries where you need Bjarne Stroustrup to help you read it.

## Todo
### Tasks
- [ ] Create classes for each tower
  - [ ] Prospector needs damage falloff for range of explosion
- [ ] Implement reload mechanics
  - [ ] Remove targeting timer
  - [ ] Add reload progress bar near health bar
- [ ] Create classes for each enemy
  - [ ] Draw skin for enemies (bandana and eyecovers)
- [ ] Create wall (just make it placable, don't worry about blocking bullets)
- [ ] Create damage type for melee (derive from projectile since this is anarchy)
- [ ] Create "waves" and gameplay
  - [ ] Create 'start wave' button
  - [ ] Create way to auto-generate enemies
- [ ] Make bullets use less cheese on hit detection (???)
- [ ] Create pause menu with save & exit, options, etc
- [ ] Implement save game
- [ ] Implement "bank"


### Features

#### Towers
- Lawman
  - Basic unit with a 6-shooter
  - Ammo: 6
  - Special: Roulette
    - One round in the clip deals more damage.
    - Upgrading increases damage
- Marshall
  - Long-range tower with high damage but slower fire rate
  - Ammo: 8
  - Special: Armor Piercing
- Repeater
  - Fast-firing tower with an automatic pistol
  - Ammo: 16
  - Special: Pocket Sand!
    - Throws pocket sand at enemy when reloading
    - Blinds enemy from shooting for an upgradable time
- Prospector
  - Dynamite-throwing tower that deals splash damage to enemies
  - Special: Bigger Booms
    - Increased radius, less damage dropoff
- Blaster
  - Shotgun-wielding tower that shoots multiple projectiles
  - Special: More Pellets
- Brawler
  - Throws broken bottles at enemies with a chance to stun, and shanks enemies with a broken bottle if they're close enough
  - Special: Sharper bottles
    - Increases bleed time
- Doc
  - Movable tower that heals nearby units
  - Special: Wall repair
- Sheriff
  - Player-controllable tower with 2 revolvers
    - Can be set to auto or manual
  - Special: How!?!
    - Increases ammo capacity
#### Enemies
- Robber
  - 6-shooter wielding enemy
- Train Robber
  - Robber on a horse! Moves faster
- Corrupt Politician
  - Slow-moving tank unit that does no damage
- Gold Rusher
  - Fast-moving unit that swings his pickaxe at anything he can reach
- Modifiers
  - Armored: Reduces damage taken
  - Hidden: Increases tower miss chance
  - Trigger Happy: Increases fire rate

#### Skin Customization
- Sheriff has steam-tradable skins that are gotten from cases
  - Cases are given after reaching certain progressions
  - Attributes
    - Bandanas (color, pattern)
    - Hat bands (color, pattern)
    - Hat colors
    - Hat pins
    - Projectile skins
  - Rare: 
    - Cowboy boots (colors, patterns)
    - Weapon skins
  - Special: 
    - Football helmet
      - With the caption of "wrong kind of cowboy", inspired by when I looked up "cowboy hat" and got pictures of hats for the Dallas Cowboys
    - Ram horns
      - With the caption "18 more wild cowboys out in the yard"
- Tower skins are unlocked by progression and non-tradable, same as sheriff but to a lesser extent

#### Bank
- 
#### Achievements
- Create basic implementation of first achievement.

#### Leaderboards
- Each map will have a leaderboard based on settings
- Speedrun & max waves
  - Open (any bank level)
  - Presets for bank 0, 10, 30, 50, with everyone having the same bank

#### Procedural/random map generation
- Create random map and place random houses, blocks, etc

#### Map of the Day
- Using procedural maps, have map of the day with leaderboard that tracks highest wave


