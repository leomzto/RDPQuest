# 🎮 Design Document - Prompt Rogue

## 📝 Overview
**Prompt Rogue** is a text-based rogue-like RPG featuring:
- Character creation
- Class system
- Battles
- Dungeons
- Game progress saving

## 🧩 Game Structure

### 📦 Main Modules
- **player.c/h** – Defines the player, their classes, and functions for creation and stat display.
- **enemy.c/h** – Manages enemy generation and battle logic.
- **dungeon.c/h** – Handles dungeon mechanics and progression.
- **funcs.c/h** – Utility functions (health bar, save folder creation, save listing).
- **game.c/h** – Main menu logic, game loop, player decisions, and flow control.
- **utils.c/h** – Helper functions (buffer clearing, screen clearing, loading screen).

## 🧍 Core Data

### 👤 Player
- Name
- Class (with attributes: life, attack, defense)
- Current and max life
- Current and max attack and defense

### 🧙‍♂️ Classes
- **Warrior**, **Wizard**, **Archer**, **Paladin**, **Barbarian**, **Rogue**, **supreme_adm**
- Each class has:
  - Base life
  - Base attack
  - Base defense

### 💾 Save System
- Saves to files in a default directory
- Up to **5 save slots**
- Save files include character and progress data
- Save folder is created in the **user directory**

## ⚔️ Gameplay

- Character and class selection
- Exploration: searching for enemies and dungeons
- Turn-based battles with random enemies
- View player stats
- Save and load game progress

## 💻 Interface

- Simple **text-based terminal** interface
- Includes:
  - Health bars
  - Loading screens
  - Interactive menus
