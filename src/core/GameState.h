#pragma once

// Represents the current match state.
enum GameState
{
    Playing,         // Match is running
    Player1Victory,  // Player 1 wins
    Player2Victory,  // Player 2 wins
    Draw             // Draw
};