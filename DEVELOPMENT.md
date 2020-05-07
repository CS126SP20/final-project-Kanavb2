# Development

### 4/18/20
* Added the Allegro library to the CMakeLists.txt file to be able to use the library
* Used snake code structure, modified it according to the needs of the game

### 4/19/20
* Made game structure
    * Created game engine
    * Added location and map handlers
    * Introduced player and npc managers

### 4/20/20
* Added game graphics
    * Added player sprites
    * Added background map

### 4/21/20
* Handled movement in the game
    * Allowed for movement of the player within the map
    * Made sure the player cannot move to certain tiles

* Added a statistics based system for both the player and the NPCs for the combat system

### 4/24/20
* Tried for ~4 hours to figure out a way to make the camera follow the player, failed
* Tried to make a text box system which displays what an npc may say to a character, failed

### 4/25/20
* Finally figured out a way to make the camera follow the player
* Fixed code style using feedback from Week 1's code review
* Refactored statistics to be stored in a struct instead of a class as it stores POD
* Added a placeholder for an inventory and currency
* Moved image files from resources to assets for windows compatibility

### 4/26/20
* Completed tile mapping throughout the map, assigned tiles characteristics using an enum, might change some enum values in the future

### 4/27/20
* Enabled user to interact with map
* Added a text displaying system using basic cinder text boxes
* Added background music and short character text audio

### 4/28/20
* Added an inventory to manage items and money

### 4/30/20
* Refactored long switch cases into HashMaps in islandapp.cc and map.cc
* Made inventory more descriptive, added a money display

### 5/2/20
* Added npc placeholders throughout the map
* Added npc sprites
* Made npc sprites change directions depending on where the user interacted with them from

### 5/3/20
* Added a market where the player can buy items to use in battle
* Added a gflags interface for the user to enter specifics such as their name, whether they want to start a new game etc.

### 5/4/20
* Added a save state, the player can save their current progress
* Added the ability to load from a previously saved file

### 5/5/20
* Added mute button to mute all sounds in the game
* Added framework for the background of the battle system

### 5/6/20
* Finished designing the battle system