#include "include/raylib.h"
#include <stdio.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450


typedef struct {
    Rectangle hitbox;   // Hitbox
    Vector2 speed;      // Speed
    int health;         // Hp
    bool isAttacking;   // Atk status
    Texture2D texture;  // Idle texture
    Texture2D run;      // Running texture
    Texture2D atk;      // Attack texture
    int frameIndex;     // Frame position
    float frameCounter; // Animation frame 
} Character;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Fighting Mamat");
    SetTargetFPS(30);

    //Import texture
    Character player1 = {{100, 300, 50, 100}, {0, 0}, 100, false, LoadTexture("D:/coding/game/assets/sprite1/idle.png"), LoadTexture("D:/coding/game/assets/sprite1/Run.png"), LoadTexture("D:/coding/game/assets/sprite1/Attack1.png")};
    Character player2 = {{600, 300, 50, 100}, {0, 0}, 100, false, LoadTexture("D:/coding/game/assets/sprite2/idle2.png"), LoadTexture("D:/coding/game/assets/sprite2/Run.png"), LoadTexture("D:/coding/game/assets/sprite2/Attack1.png")};
    Vector2 origin = {0.0f, 0.0f};

    Texture2D background = LoadTexture("D:/coding/game/assets/bg/bg1/bg1.png");
    if (background.id == 0 || player1.texture.id == 0 || player2.texture.id == 0) {
        printf("Failed to load one or more textures.\n");
    }

    while (!WindowShouldClose()) {
        // p1 idle animation
        player1.frameCounter += GetFrameTime() * 10; 
        if (player1.frameCounter>=1){
            player1.frameCounter = 0;
            player1.frameIndex = (player1.frameIndex + 1) % 8;
        }

        // p2 idle animation
        player2.frameCounter += GetFrameTime() * 14; 
        if (player2.frameCounter>=1){
            player2.frameCounter = 0;
            player2.frameIndex = (player2.frameIndex + 1) % 10;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw background
        Rectangle srcRectBg = {0.0f, 0.0f, (float)background.width, (float)background.height};
        Rectangle destRectBg = {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT};
        DrawTexturePro(background, srcRectBg, destRectBg, origin, 0.0f, WHITE);

        // parameters for p1 
        float scale1 = 3.6;
        float frameWidth = player1.texture.width/8; // potong per frame
        float frameHeight = player1.texture.height;
        Rectangle srcRect = {player1.frameIndex * frameWidth, 0.0f, frameWidth, frameHeight};
        Rectangle srcRectflip = {player1.frameIndex * frameWidth, 0.0f, -frameWidth, frameHeight};
        Rectangle destRect = {player1.hitbox.x-65, player1.hitbox.y-120, player1.hitbox.width *scale1, player1.hitbox.height*scale1};
        Vector2 origin = {0.0f, 0.0f}; 
        // hitbox
        DrawRectangleRec(player1.hitbox, RED);
        
        // parameters for p2
        float scale2 = 2.5;
        float frameWidth2 = player2.texture.width/10; // potong per frame
        float frameHeight2 = player2.texture.height;
        Rectangle srcRect2 = {player2.frameIndex * frameWidth2, 0.0f, -frameWidth2, frameHeight2}; 
        Rectangle srcRect2flip = {player2.frameIndex * frameWidth2, 0.0f, frameWidth2, frameHeight2};
        Rectangle destRect2 = {player2.hitbox.x-55, player2.hitbox.y-65, player2.hitbox.width*scale1, player2.hitbox.height*scale2};
        // hitbox
        DrawRectangleRec(player2.hitbox, BLUE);

        // Input P1
        if (IsKeyDown(KEY_A)){
            player1.hitbox.x -= 4.0f;
            DrawTexturePro(player1.run, srcRectflip , destRect, origin, 0.0f, WHITE);
        }else if (IsKeyDown(KEY_D)){
            player1.hitbox.x += 4.0f;
            DrawTexturePro(player1.run, srcRect, destRect, origin, 0.0f, WHITE);
        }else if (IsKeyPressed(KEY_W)){
            player1.isAttacking = true;
            DrawTexturePro(player1.atk, srcRect, destRect, origin, 0.0f, WHITE);
        }else{DrawTexturePro(player1.texture, srcRect, destRect, origin, 0.0f, WHITE);}

        // Input P2
        if (IsKeyDown(KEY_J)){
            player2.hitbox.x -= 4.0f;
            DrawTexturePro(player2.run, srcRect2, destRect2, origin, 0.0f, WHITE);
        }else if (IsKeyDown(KEY_L)){
            player2.hitbox.x += 4.0f; 
            DrawTexturePro(player2.run, srcRect2flip, destRect2, origin, 0.0f, WHITE);
        }else if (IsKeyPressed(KEY_I)){
            player2.isAttacking = true;
            DrawTexturePro(player2.atk, srcRect2, destRect2, origin, 0.0f, WHITE);
        }else{DrawTexturePro(player2.texture, srcRect2, destRect2, origin, 0.0f, WHITE);}

        // Collision Hitbox
        if (player1.isAttacking && CheckCollisionRecs(player1.hitbox, player2.hitbox)) {
            player2.health -= 15; 
        } else if (player2.isAttacking && CheckCollisionRecs(player1.hitbox, player2.hitbox)) {
            player1.health -= 15; 
        }
        player1.isAttacking = false;
        player2.isAttacking = false;
        if (player1.health <= 0 || player2.health <= 0){
            player1.health = 0;
            player2.health = 0;
        }

        // Gambar health bar
        DrawText(TextFormat("Player 1 Health: %d", player1.health), 10, 10, 20, BLACK);
        DrawText(TextFormat("Player 2 Health: %d", player2.health), SCREEN_WIDTH - 200, 10, 20, BLACK);

        EndDrawing();
    }

    // Unload the textures
    UnloadTexture(background);
    UnloadTexture(player1.texture);
    UnloadTexture(player2.texture);

    CloseWindow();
    return 0;
}