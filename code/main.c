#include "include/raylib.h"
#include <stdio.h>

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
int indexbg;
int hpbarlen;
typedef enum{
    MENU, PLAY, END
} GameState;

typedef struct {
    Rectangle hitbox;   // Hitbox
    Vector2 speed;      // Speed
    int health;         // Hp
    bool isAttacking;   // Atk status
    Texture2D texture;  // Idle texture
    Texture2D run;      // Running texture
    Texture2D atk;      // Attack texture
    Texture2D hpbar;    // Heatlh bar texture
    int frameIndex;     // Frame position
    float frameCounter; // Animation frame 
} Character;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Fighting Mamat");
    InitAudioDevice();
    SetTargetFPS(30);

    GameState gameState = MENU;

    //Import texture
    Character player1 = {{300, 800, 225, 200}, {0, 0}, 100, false, 
        LoadTexture("D:/coding/game/assets/sprite1/idle.png"), 
        LoadTexture("D:/coding/game/assets/sprite1/Run.png"), 
        LoadTexture("D:/coding/game/assets/sprite1/Attack1.png"),
        LoadTexture("D:/coding/game/assets/hpbar.png")};
    Character player2 = {{1300, 800, 225, 200}, {0, 0}, 100, false, 
        LoadTexture("D:/coding/game/assets/sprite2/idle2.png"), 
        LoadTexture("D:/coding/game/assets/sprite2/Run.png"), 
        LoadTexture("D:/coding/game/assets/sprite2/Attack1.png"),
        LoadTexture("D:/coding/game/assets/hpbar.png"), };
    Vector2 origin = {0.0f, 0.0f};

    Music bgsong = LoadMusicStream("D:/coding/game/assets/menusong.WAV");
    Music battlesg = LoadMusicStream("D:/coding/game/assets/battlesong.WAV");
    PlayMusicStream(bgsong);
    PlayMusicStream(battlesg);
    Texture2D bg1 = LoadTexture("D:/coding/game/assets/bg/bg1/bg1.png");
    Texture2D bg2 = LoadTexture("D:/coding/game/assets/bg/bg2/bg2.png");
    Texture2D bg3 = LoadTexture("D:/coding/game/assets/bg/bg3/bg3.png");
    Texture2D bg4 = LoadTexture("D:/coding/game/assets/bg/bg4/bg4.png");
    if (bg1.id == 0 || player1.texture.id == 0 || player2.texture.id == 0 ) {
        printf("Failed to load one or more textures.\n");
    }

    while (!WindowShouldClose()) {
        if (gameState == MENU) {
            // Menu Page
            BeginDrawing();
            ClearBackground(RAYWHITE);
            UpdateMusicStream(bgsong);
            DrawText("Game Fighting Rahmat", SCREEN_WIDTH / 2 - 400, 250, 80, DARKBLUE);
            DrawText("Tekan [ENTER] untuk Memulai", SCREEN_WIDTH / 2 - 250, 450, 40, BLACK);
            DrawText("Pilih Map: [A] Map 1, [B] Map 2, [C] Map 3, [D] Map 4", SCREEN_WIDTH / 2-540, 600, 40, BLACK);
            // Draw selectbg
            Rectangle selectBg = {670, 640, 120, 120};
            Rectangle selectBg2 = {870, 640, 120, 120};
            Rectangle selectBg3 = {1070, 640, 120, 120};
            Rectangle selectBg4 = {1270, 640, 120, 120};
            // Logic selectbg
            if (IsKeyPressed(KEY_A)){
                indexbg = 1;
            }
            if (IsKeyPressed(KEY_B)){
                indexbg = 2;
            }
            if (IsKeyPressed(KEY_C)){
                indexbg = 3;
            }
            if (IsKeyPressed(KEY_D)){
                indexbg = 4;
            }
            if (indexbg == 1){
                DrawRectangleRec(selectBg, RED);
            }
            if (indexbg == 2){
                DrawRectangleRec(selectBg2, RED);
            }
            if (indexbg == 3){
                DrawRectangleRec(selectBg3, RED);
            }
            if (indexbg == 4){
                DrawRectangleRec(selectBg4, RED);
            }
            Rectangle srcRectBgmn = {0.0f, 0.0f, (float)bg1.width, (float)bg1.height};
            Rectangle destRectBg1mn = {680, 650, 100, 100};
            Rectangle destRectBg2mn = {880, 650, 100, 100};
            Rectangle destRectBg3mn = {1080, 650, 100, 100};
            Rectangle destRectBg4mn = {1280, 650, 100, 100};
            DrawTexturePro(bg1, srcRectBgmn, destRectBg1mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg2, srcRectBgmn, destRectBg2mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg3, srcRectBgmn, destRectBg3mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg4, srcRectBgmn, destRectBg4mn, origin, 0.0f, WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = PLAY; // Masuk ke mode bermain
            }
            EndDrawing();
        } 

        else if (gameState == PLAY){
                // Game Page
            UpdateMusicStream(battlesg);
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

            // Draw bg1
            Rectangle srcRectBg = {0.0f, 0.0f, (float)bg1.width, (float)bg1.height};
            Rectangle destRectBg = {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT};
            if (indexbg == 1){
                DrawTexturePro(bg1, srcRectBg, destRectBg, origin, 0.0f, WHITE);
            }else if (indexbg == 2){
                DrawTexturePro(bg2, srcRectBg, destRectBg, origin, 0.0f, WHITE);
            }else if (indexbg == 3){
                DrawTexturePro(bg3, srcRectBg, destRectBg, origin, 0.0f, WHITE);
            }else{
                DrawTexturePro(bg4, srcRectBg, destRectBg, origin, 0.0f, WHITE);
            }

            // parameters for p1 
            float scale1 = 3.6;
            float frameWidth = player1.texture.width/8; 
            float frameHeight = player1.texture.height;
            Rectangle srcRect = {player1.frameIndex * frameWidth, 0.0f, frameWidth, frameHeight};
            Rectangle srcRectflip = {player1.frameIndex * frameWidth, 0.0f, -frameWidth, frameHeight};
            Rectangle destRect = {player1.hitbox.x-400, player1.hitbox.y-240, player1.hitbox.width *scale1, player1.hitbox.height*scale1};
            Vector2 origin = {0.0f, 0.0f}; 
            // hitbox
            //DrawRectangleRec(player1.hitbox, RED);
            
            // parameters for p2
            float scale2 = 2.5;
            float frameWidth2 = player2.texture.width/10; 
            float frameHeight2 = player2.texture.height;
            Rectangle srcRect2 = {player2.frameIndex * frameWidth2, 0.0f, -frameWidth2, frameHeight2}; 
            Rectangle srcRect2flip = {player2.frameIndex * frameWidth2, 0.0f, frameWidth2, frameHeight2};
            Rectangle destRect2 = {player2.hitbox.x-230, player2.hitbox.y-125, player2.hitbox.width*scale1, player2.hitbox.height*scale2};
            // hitbox
            //DrawRectangleRec(player2.hitbox, BLUE);

            // Input P1
            if (IsKeyDown(KEY_A)){
                player1.hitbox.x -= 8.0f;
                DrawTexturePro(player1.run, srcRectflip , destRect, origin, 0.0f, WHITE);
            }else if (IsKeyDown(KEY_D)){
                player1.hitbox.x += 8.0f;
                DrawTexturePro(player1.run, srcRect, destRect, origin, 0.0f, WHITE);
            }else if (IsKeyPressed(KEY_W)){
                player1.isAttacking = true;
                DrawTexturePro(player1.atk, srcRect, destRect, origin, 0.0f, WHITE);
            }else{DrawTexturePro(player1.texture, srcRect, destRect, origin, 0.0f, WHITE);}

            // Input P2
            if (IsKeyDown(KEY_J)){
                player2.hitbox.x -= 8.0f;
                DrawTexturePro(player2.run, srcRect2, destRect2, origin, 0.0f, WHITE);
            }else if (IsKeyDown(KEY_L)){
                player2.hitbox.x += 8.0f; 
                DrawTexturePro(player2.run, srcRect2flip, destRect2, origin, 0.0f, WHITE);
            }else if (IsKeyPressed(KEY_I)){
                player2.isAttacking = true;
                DrawTexturePro(player2.atk, srcRect2, destRect2, origin, 0.0f, WHITE);
            }else{DrawTexturePro(player2.texture, srcRect2, destRect2, origin, 0.0f, WHITE);}

            // Collision Hitbox
            if (player1.isAttacking && CheckCollisionRecs(player1.hitbox, player2.hitbox)) {
                player2.health -= 18; 
                hpbarlen -= 47;

            } else if (player2.isAttacking && CheckCollisionRecs(player1.hitbox, player2.hitbox)) {
                player1.health -= 18; 
                hpbarlen -= 47;
            }
            player1.isAttacking = false;
            player2.isAttacking = false;
            if (player1.health <= 0){
                player1.health = 0;
                gameState = END;
            }
            if (player2.health <= 0){
                player2.health = 0;
                gameState = END;
            }

            // Draw health bar


            if (indexbg == 3){
                DrawText(TextFormat("Player 1 Health: %d", player1.health), 10, 30, 40, WHITE);
                DrawText(TextFormat("Player 2 Health: %d", player2.health), SCREEN_WIDTH - 400, 30, 40, WHITE);
            } else{DrawText(TextFormat("Player 1 Health: %d", player1.health), 10, 30, 40, BLACK);
            DrawText(TextFormat("Player 2 Health: %d", player2.health), SCREEN_WIDTH - 400, 30, 40, BLACK);}
            EndDrawing();
        }
        else if (gameState == END){
            BeginDrawing();
            ClearBackground(RAYWHITE);
            UpdateMusicStream(bgsong);
            if (player1.health == 0){
               DrawText("Player 2 wins", SCREEN_WIDTH / 2 - 260, 250, 80, DARKBLUE);
            }
            if (player2.health == 0){
                DrawText("Player 1 wins", SCREEN_WIDTH / 2 - 260, 250, 80, DARKBLUE);
                
            }
            DrawText("Pilih Map: [A] Map 1, [B] Map 2, [C] Map 3, [D] Map 4", SCREEN_WIDTH / 2-540, 600, 40, BLACK);
            // Draw selectbg
            Rectangle selectBg = {670, 640, 120, 120};
            Rectangle selectBg2 = {870, 640, 120, 120};
            Rectangle selectBg3 = {1070, 640, 120, 120};
            Rectangle selectBg4 = {1270, 640, 120, 120};
            // Logic selectbg
            if (IsKeyPressed(KEY_A)){
                indexbg = 1;
            }
            if (IsKeyPressed(KEY_B)){
                indexbg = 2;
            }
            if (IsKeyPressed(KEY_C)){
                indexbg = 3;
            }
            if (IsKeyPressed(KEY_D)){
                indexbg = 4;
            }
            if (indexbg == 1){
                DrawRectangleRec(selectBg, RED);
            }
            if (indexbg == 2){
                DrawRectangleRec(selectBg2, RED);
            }
            if (indexbg == 3){
                DrawRectangleRec(selectBg3, RED);
            }
            if (indexbg == 4){
                DrawRectangleRec(selectBg4, RED);
            }
            Rectangle srcRectBgmn = {0.0f, 0.0f, (float)bg1.width, (float)bg1.height};
            Rectangle destRectBg1mn = {680, 650, 100, 100};
            Rectangle destRectBg2mn = {880, 650, 100, 100};
            Rectangle destRectBg3mn = {1080, 650, 100, 100};
            Rectangle destRectBg4mn = {1280, 650, 100, 100};
            DrawTexturePro(bg1, srcRectBgmn, destRectBg1mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg2, srcRectBgmn, destRectBg2mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg3, srcRectBgmn, destRectBg3mn, origin, 0.0f, WHITE);
            DrawTexturePro(bg4, srcRectBgmn, destRectBg4mn, origin, 0.0f, WHITE);
            DrawText("Tekan [ENTER] untuk memulai lagi", SCREEN_WIDTH / 2 - 310, 450, 40, BLACK);
            if (IsKeyPressed(KEY_ENTER)) {
                player1.health = 100;
                player2.health = 100;
                gameState = PLAY; // Masuk ke mode bermain
            }
            EndDrawing();
        }

    }

    // Unload the textures
    UnloadMusicStream(bgsong);
    UnloadTexture(bg1);
    UnloadTexture(player1.texture);
    UnloadTexture(player2.texture);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
