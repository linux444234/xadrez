#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BLOCKS 8
#define BLOCK_SIZE (SCREEN_WIDTH / BLOCKS)

const char *init_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

typedef enum PieceType {
    B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING, 
    EMPTY,
    PIECE_COUNT
} PieceType;

typedef struct ChessPieces {
    Texture2D textures[PIECE_COUNT];
} ChessPieces;

PieceType getPiece(char piece) {
    switch (piece) {
    case 'p':
        return B_PAWN;
    case 'n':
        return B_KNIGHT;
    case 'b':
        return B_BISHOP;
    case 'r':
        return B_ROOK;
    case 'q':
        return B_QUEEN;
    case 'k':
        return B_KING;
    case 'P':
        return W_PAWN;
    case 'N':
        return W_KNIGHT;
    case 'B':
        return W_BISHOP;
    case 'R':
        return W_ROOK;
    case 'Q':
        return W_QUEEN;
    case 'K':
        return W_KING;
    default:
        return EMPTY;
    }
}

void drawPiece(Texture2D texture, int file, int rank) {
    DrawTexturePro(
        texture,
        (Rectangle){0, 0, (float)texture.width, (float)texture.height}, // source rectangle (full image)
        (Rectangle){
            file * BLOCK_SIZE, // X position on screen
            rank * BLOCK_SIZE, // Y position on screen
            BLOCK_SIZE,        // width to draw (scaled)
            BLOCK_SIZE         // height to draw (scaled)
        },
        (Vector2){0, 0}, // origin offset (not needed here)
        0.0f,            // rotation
        WHITE            // tint (WHITE = no tint)
    );
}

void LoadChessPieces(ChessPieces *pieces) {
    pieces->textures[W_PAWN] = LoadTexture("img/wp.png");
    pieces->textures[W_KNIGHT] = LoadTexture("img/wn.png");
    pieces->textures[W_BISHOP] = LoadTexture("img/wb.png");
    pieces->textures[W_ROOK] = LoadTexture("img/wr.png");
    pieces->textures[W_QUEEN] = LoadTexture("img/wq.png");
    pieces->textures[W_KING] = LoadTexture("img/wk.png");

    pieces->textures[B_PAWN] = LoadTexture("img/bp.png");
    pieces->textures[B_KNIGHT] = LoadTexture("img/bn.png");
    pieces->textures[B_BISHOP] = LoadTexture("img/bb.png");
    pieces->textures[B_ROOK] = LoadTexture("img/br.png");
    pieces->textures[B_QUEEN] = LoadTexture("img/bq.png");
    pieces->textures[B_KING] = LoadTexture("img/bk.png");
}

void UnloadChessPieces(ChessPieces *pieces) {
    for (int i = 0; i < PIECE_COUNT; i++)
        UnloadTexture(pieces->textures[i]);
}

void parseBoardString(const char *board, ChessPieces *pieces) {
    int rank = 0, file = 0;

    for (int i = 0; board[i] != '\0'; i++) {
        char c = board[i];

        if (c == '/') {
            rank++;
            file = 0;
        }
        else if (c >= '1' && c <= '8') {
            file += (c - '0');
        }
        else {
            PieceType p = getPiece(c);
            if (p != EMPTY)
                drawPiece(pieces->textures[p], file, rank);
            file++;
        }
    }
}

void drawBoard() {
    for (int rank = 0; rank < BLOCKS; rank++) {
        for (int file = 0; file < BLOCKS; file++) {
            Color color = ((rank + file) % 2 == 0)
                              ? (Color){122, 153, 90, 255}   // Dark square
                              : (Color){240, 240, 211, 255}; // Light square

            DrawRectangle(file * BLOCK_SIZE,
                          rank * BLOCK_SIZE,
                          BLOCK_SIZE,
                          BLOCK_SIZE,
                          color);
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Chess");
    SetTargetFPS(60);
    ChessPieces chessPieces;
    LoadChessPieces(&chessPieces);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);

        drawBoard();
        parseBoardString(init_board, &chessPieces);

        EndDrawing();
    }

    UnloadChessPieces(&chessPieces);

    CloseWindow();
    return 0;
}