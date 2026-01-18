# PureStrategy - Console Card Game

## Project Description
PureStrategy is a two-player console card game based on the "Pure Strategy" ruleset. Players compete to win prize cards by bidding with their own hand of cards (ace through king). The game features a persistent user profile system that tracks statistics and match history against specific opponents.

## How to Compile and Run
1. Open the solution in Visual Studio.
2. Ensure all source files (`.cpp`) and header files (`.h`) are included in the project.
3. Build the solution (Ctrl+Shift+B).
4. Run the executable (`Local Windows Debugger`).

## How to Play
1. **Login/Register:**
   * Create a user profile to track your wins and losses.
   * Player 2 can be registered during Player 1's game session.
2. **Gameplay:**
   * A prize card is revealed.
   * Each player chooses a card from their hand to "bid" for the prize.
   * **Input:** Type the card value (e.g., `5`, `10`) or the face name (`A`, `J`, `Q`, `K`).
   * The higher card wins the prize.
   * **Ties:** If both players play the same card, the prize stays in the pot and accumulates for the next round.
3. **Winning:** The game ends when hands are empty. The player with the highest total points in their prize pile wins.

## Features
* **Dynamic Input Parsing:** Accepts both numbers (`11`) and characters (`J`, `j`) for cards.
* **Input Validation:** Prevents invalid moves, duplicate cards, and weak passwords.
* **Game Statistics:** Saves total games, win rates, and history vs specific opponents in `.txt` files.
* **Tie-Breaker Logic:** Fully implements the accumulating "Pot" mechanic.