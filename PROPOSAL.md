# The Island

Author: Kanav Bhatnagar

This project would involve developing a role playing two dimensional [top-down](https://en.wikipedia.org/wiki/Video_game_graphics#Top-down_perspective) video game. The goal of the game is not to beat an evil boss character, rather to explore the world of the island. The player will control the main character with just the keyboard; moving around in this world, interacting with NPCs, and battling them if need be.

The player would be dropped in to the world of the island, and be able to set out on their journey to do whatever they want in this open world game. The game will have a linear progression, with a focus on the player improving their stats throughout the playthrough. The combat system may be a bit limited, with calculations based on the player's stats determining the outcome *most* of the time.

### **Motivation to do this project**
I spent most of the free time in my childhood (and a considerable amount of time in my teen years) playing retro style top-down games. While it is challenging to play this sort of a game, I feel it would be even more fun to develop it. While I do realize that making a game on such a large scale is nigh impossible, it should be relatively easy to make a smaller, less complicated version of it. 

As a side note, the calculations involved behind the flashy animations and graphics in, say pokemon, ranges from [fun math](https://gamefaqs1.cbsistatic.com/faqs/11/75211-2.png) to [even more fun math](https://www.smogon.com/media/smog/eq08.png). These were highly influential in my inclination towards math when I was a kid, and being able to incorporate such calculations into a fully fledged game of my own excites me, even though it is not related to programming the aspects of the game itself.

### **External libraries**
At the beginning, I was planning on using the [Godot engine](https://github.com/godotengine/godot) and the [Allegro library](https://liballeg.org/) in conjunction with Cinder. With Godot's built-in dedicated 2D engine that works with pixel coordinates, and its compatability with CLion, it will make my job in creating the world easier. Allegro provides some useful features that can be incorporated into any 2D RPG, like separate audio files and displaying text to the user in an 8-bit style.

This did not work out in the end, since throughout the course of the project, I found that most of Allegro's and Godot's in built functions were harder to integrate into Cinder than writing the functions myself. So, in the end, I decided to use [nlohmann/json](https://github.com/nlohmann/json) in conjunction with [gflags](https://github.com/gflags/gflags) to implement a save state so that the user can save their progress and load it up later whenever they want.

### **Rough Timeline**
* Week 1: Graphics
  * Set up Allegro and Godot with CLion
  * Make sprites for the characters 
  * Develop a map area based on tiles, zones, areas etc.
  
* Week 2: Characters and Combat
  * Make a user controlled player character, test whether the movements work properly
  * Make NPCs with assigned dialogue
  * Incorporate the graphics from week 1 with the characters
  * Add an entirely separate combat window, make interactions between the player and opponent possible
  
* Week 3: Statistics and Story
  * Make an inventory menu for the player's item storage
  * Add calculations for combat using the players statistics, formulate experience-based growth
  * Add currency based system for item purchase
  * Add a reasonably paced story with specific dialogue

### **Stretch Goals**
If I am able to finish the project in time, I would like to:
  * improve the story, possibly adding an ending where the player could escape the island
  * add side quests specific to NPCs, which would result in the player getting specific boosts to their abilities.
  * make a sandbox combat mode where the user could practice battling

---

