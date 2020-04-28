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

### To do:
* Add npc sprites
* Add npcs throughout the map
* Add a save state
* Make a menu of sorts
* Figure out combat system