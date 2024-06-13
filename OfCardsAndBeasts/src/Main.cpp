#include "raylib.h"
#include "Player.h"

const int gameWidth = 640;   // Original resolution width
const int gameHeight = 360;  // Original resolution height
const int scaleFactor = 4;   // Scaling factor (2, 3, or 4 depending on your preference)

const int screenWidth = gameWidth * scaleFactor;   // Scaled-up width
const int screenHeight = gameHeight * scaleFactor; // Scaled-up height

const int cellSize = 32;
const int dungeonWidth = gameWidth / cellSize;
const int dungeonHeight = gameHeight / cellSize;
int dungeon[dungeonWidth][dungeonHeight];

void InitializeDungeon()
{
    for (int y = 0; y < dungeonHeight; y++)
    {
        for (int x = 0; x < dungeonWidth; x++)
        {
            dungeon[x][y] = 1; // Initialize all cells as walls
        }
    }
}

void GenerateDungeon(int startX, int startY)
{
    int x = startX;
    int y = startY;

    dungeon[x][y] = 0;  // Start point

    for (int i = 0; i < 100; i++)
    {
        int direction = GetRandomValue(0, 3);

        switch (direction)
        {
        case 0: // Move up
            if (y > 1) y--;
            break;
        case 1: // Move down
            if (y < dungeonHeight - 2) y++;
            break;
        case 2: // Move left
            if (x > 1) x--;
            break;
        case 3: // Move right
            if (x < dungeonWidth - 2) x++;
            break;
        }

        dungeon[x][y] = 0;
    }
}

void DrawDungeon()
{
    for (int y = 0; y < dungeonHeight; y++)
    {
        for (int x = 0; x < dungeonWidth; x++)
        {
            if (dungeon[x][y] == 1) DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, DARKGRAY); // Wall
            else DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, LIGHTGRAY); // Floor
        }
    }
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "OfCardsAndBeasts");
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    InitializeDungeon();
    GenerateDungeon(dungeonWidth / 2, dungeonHeight / 2);   // Start in the center

    Player player({ 400.0f, 300.0f });
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        player.Update(deltaTime);

        BeginDrawing();

        ClearBackground(BLACK);
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        DrawDungeon();
        EndTextureMode();

        player.Draw();

        Rectangle sourceRect = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
        Rectangle destRect = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(
            target.texture,
            sourceRect,
            destRect,
            origin,
            0.0f,
            WHITE
        );

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}