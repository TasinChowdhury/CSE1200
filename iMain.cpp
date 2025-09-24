#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define MAX_LEVELS 2
#define TILE_SIZE 64
#define LEVEL_WIDTH 67   // in tiles
#define LEVEL_HEIGHT 10  // in tiles

#define MAX_SPEED 8.0f 
#define ACCELERATION 0.5f 
#define FRICTION 0.3f
#define GRAVITY 0.4f
#define JUMP_FORCE 13.0f


// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// GAME STATES using #define
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define STATE_LOADING1       0
#define STATE_LOADING2       1
#define STATE_MAINMENU       2
#define STATE_OPTIONS        3
#define STATE_CONTROLS       4
#define STATE_CREDITS        5
#define STATE_GAME           6
#define STATE_GAME_COMPLETE  7
#define STATE_GAME_OVER      8
#define STATE_WINNER         9
#define STATE_EXIT           10
#define STATE_ENTER_NAME     11
#define STATE_STORYLINE		 12
#define MAX_SMOKES           2
#define SPIKE_TILE           7  // Tile ID for spikes
#define WATER_TILE           6
    

#define ENEMY_SMALL_DURATION 600 
bool enemyHitEffect = false;  
int enemyHitTimer = 0;         
int enemyHitImage;
bool level2MusicPlaying = false;
bool enemySmall = true;
int enemySmallTimer = ENEMY_SMALL_DURATION;
bool level1MusicStarted = false;
bool dragonFireActive = false;
int dragonFireX, dragonFireY;
int dragonFireWidth = 180, dragonFireHeight = 120;
int dragonFireImage;
int dragonFireTimer = 0;        
const int dragonFireDuration = 50; 
int dragonFireSpeed = 8;
int level2EnemySpeed = 2;      
int level2EnemyDir = 1;          
int level2EnemyMinX = 3600;      
int level2EnemyMaxX = 4000;
bool bossHitEffect = false;     
int bossHitTimer = 0;           
int bossHitImage;            
int doraemonHealth = 100;
int damageCooldown = 0;



int gameState = STATE_LOADING1;

int loading1, loading2, mainmenu, startButton, optionButton, control1, control2;
int creditsButton, creditsPage, exitButton;
int loading1Img, loading2Img, mainmenuImg, startBtnImg, optionBtnImg, control1Img, control2Img;
int creditsBtnImg, creditsPageImg, exitBtnImg;

int loadingTimer = 0;
int mouseX = 0, mouseY = 0;
bool bgMusicPlaying = false;
bool enemyMusicPlaying = false;
bool menuMusicPlaying = false;
bool gameOverMusicPlaying = false;
bool level1MusicPlaying = false;

float enemyBulletTimer = 0;      // global
const float BULLET_DELAY = 1.0f;
const float jumpStrength = 0.3f;
bool enemyJumping = false;
bool enemyDirectionUp = true;
float enemyJumpOffsetY = 0;
float enemyJumpVelocity = 50.0f;
const float maxJumpHeight = 100.0f;

int startImage;
float verticalVelocity = 0;
bool isGrounded = false;

const int COYOTE_FRAMES = 8;     //  walking off edge 
const int BUFFER_FRAMES = 8;    

int coyoteTimer = 0;
int jumpBufferTimer = 0;
bool jumpHeld = false;


int frameDelay = 0;
const int maxFrameDelay = 18;

int currentLevel = 1;
char playerName[50] = "";   // typed name
int nameLength = 0;         // current length
bool showNameWarning = false;

int score = 0;
int scoreX = 880;    
int scoreY = 500;

bool isFallingToDeath = false;
float fallDeathTimer = 0.0f;
const float FALL_DEATH_DELAY = 1.3f; //  falling animation
float fallStartPositionX = 0.0f;
float fallStartPositionY = 0.0f;
float respawnPoint[2] = { 100.0f, 118.0f };  // Default respawn position

//BG
int bgImage[2];
float bgScrollX = 0;
const float GROUND_Y = 118.0f;
static const float EPS = 0.1f;

bool screenLocked = false;
int spikeImage[2];
float lockStartX = 0.0f;
float lockEndX = 0.0f;

const float parallaxFactor = 0.3f;

static const int DORA_DRAW_W = 90;
static const int DORA_DRAW_H = 100;
// Collision box 
static const int DORA_W = 60;
static const int DORA_H = 90;

//  World position 
float worldX = 0.0f;
float worldY = 118.0f;   // start height;

int gLevelWidth = LEVEL_WIDTH;
int gLevelHeight = LEVEL_HEIGHT;

//Tile
int level[LEVEL_HEIGHT][LEVEL_WIDTH];
int tileImg[16];

// Camera position
float camX = 0;
float camY = 0;
//float worldX = 0;
float threshold = SCREEN_WIDTH / 3;

int enemy1MaxHealth = 3, enemy1Health = 3;
int enemy4MaxHealth = 3, enemy4Health = 3, enemy4bHealth = 3;
int enemy3MaxHealth = 3, enemy3Health = 3;

float maxHealth = 100.0f;
float currentHealth = 100.0f;
float enemyHealth = 100.0f;


// Invincibility
int invincibleTicks = 0;
const int INVINCIBLE_MAX_TICKS = 60;

bool showStartButtonFullScreen = false;
int buttonDisplayTimer = 0;
const int BUTTON_DISPLAY_TIME = 30;
bool showOptionButtonFullScreen = false;
int optionButtonDisplayTimer = 0;
const int OPTION_BUTTON_DISPLAY_TIME = 30; // Same duration as start button
bool showCreditsButtonFullScreen = false;
int creditsButtonDisplayTimer = 0;
const int CREDITS_BUTTON_DISPLAY_TIME = 30;
bool showExitButtonFullScreen = false;
int exitButtonDisplayTimer = 0;
const int EXIT_BUTTON_DISPLAY_TIME = 30;


bool showingStory = false;
int storyIndex = 0;
int storyTimer = 0;
int storyDelay = 50;  // the speed of image transitions
#define TOTAL_STORY_IMAGES 5
int storyImages[TOTAL_STORY_IMAGES];


// Enemy global position in world space
int enemyWorldX = LEVEL_WIDTH * TILE_SIZE - 300;  // 300px from level end
int enemyWorldY = 118;  // adjust based on tile ground height
int enemyImages[4];
int enemyFrame = 0;
int enemyFrameDelay = 0;
const int maxEnemyFrameDelay = 12;

int bulletImage;
//change
const int MAX_BULLETS = 5;
float bulletX[MAX_BULLETS];
float bulletY[MAX_BULLETS];
bool bulletActive[MAX_BULLETS];
float bulletSpeed = 10.0f;

bool weaponVisible = false;
float weaponX, weaponY;

int weaponImgRight, weaponImgLeft;

bool smokeActive[MAX_SMOKES];
float smokeX[MAX_SMOKES];
float smokeY[MAX_SMOKES];
int smokeDir[MAX_SMOKES];        // Array for each smoke's direction
float smokeScale[MAX_SMOKES];    // Array for each smoke's scale
float smokeStartX[MAX_SMOKES];
int smokeImg;

int activeSmokes = 0; // how many smokes currently exist
float smokeDirection = 1;       
float smokeSpeed = 2.0f;
float smokeBaseScale = 0.3f;    
float smokeMaxDistance = 100;

bool lightWeaponVisible = false;
int lightWeaponImage;
int lightProjectionImage;
bool projectionActive = false;
float projectionX, projectionY;
int projectionTimer = 0;
const int PROJECTION_DURATION = 30; // How long the projection stays visible


int enemy1Hits = 0;
bool enemy1Visible = true;
bool enemy1Flashed = false;
int enemy1FlashTimer = 0;
int enemy1InvisibleImg;

bool enemy1bAlive = true;
int enemy1bHealth = 3;
int enemy1bHits = 0;
bool enemy1bFlashed = false;
int enemy1bFlashTimer = 0;
int enemy1bInvisibleImg;


bool enemy3Alive = true;
bool enemy3BurstActive = false;     // Burst animation active
int enemy3BurstFrame = 0;
int enemy3BurstDelay = 0;           // Delay between frames
const int maxEnemy3BurstDelay = 20;

int enemy3Hits = 0;
bool enemy4Alive = true;
bool enemy4Inverted = false;
int enemy4Frame = 0;
int enemy4FrameDelay = 0;
int enemy4InvertedFrame = 0;
int enemy4Hits = 0;
int enemy4InvertedTimer = 0;           // counts frames after inversion
const int enemy4InvertedDuration = 5;
bool enemy4Spawned = false;


bool enemy4bAlive = false;   // not active until Doraemon passes 3500
bool enemy4bInverted = false;
int enemy4bFrame = 0;
int enemy4bFrameDelay = 0;
int enemy4bInvertedFrame = 0;
int enemy4bHits = 0;
int enemy4bInvertedTimer = 0;           // counts frames after inversion
const int enemy4bInvertedDuration = 5;
bool enemy4bSpawned = false;
float enemy4bMinX = 0.0f;
float enemy4bMaxX = 0.0f;
bool enemy4bMovingRight = true; // Direction flag


int enemy3BurstImages[3];
bool enemy3PendingBurst = false;  // waiting to burst after collision
int enemy3BurstTimer = 0;
const int maxEnemy4FrameDelay = 30;
int leftBound = 0;                               // leftmost position
int rightBound = LEVEL_WIDTH * TILE_SIZE - 100;  // rightmost position minus enemy width


int enemy4Images[4];                   // Walking frames
int enemy4InvertedImages[3];           // Inverted frames

int enemy4bImages[4];                   // Walking frames
int enemy4bInvertedImages[3];           // Inverted frames

int enemy5MaxHealth = 5, enemy5Health = 5;
int enemy5Hits = 0;
bool enemy5Alive = false;
bool enemy5Attacking = false;
int enemy5AttackTimer = 0;
const int ENEMY5_ATTACK_DURATION = 30;
int enemy5WalkImages[4];
int enemy5AttackImages[2];
int enemy5HitImage;
bool enemy5Flashed = false;
int enemy5FlashTimer = 0;

int enemy6MaxHealth = 5, enemy6Health = 5;
int enemy6Hits = 0;
bool enemy6Alive = false;
bool enemy6Attacking = false;
int enemy6AttackTimer = 0;
const int ENEMY6_ATTACK_DURATION = 30;
int enemy6WalkImages[4];       // 4 walking frames
int enemy6AttackImages[4];     // 4 attack frames  
int enemy6HitImage;            // 1 hit image
bool enemy6Flashed = false;
int enemy6FlashTimer = 0;

bool enemy6Spawned = false;

// Enemy7 variables
int enemy7MaxHealth = 3, enemy7Health = 3;
int enemy7Hits = 0;
bool enemy7Alive = false;
bool enemy7Throwing = false;
int enemy7ThrowTimer = 0;
const int ENEMY7_THROW_DURATION = 30;
const int ENEMY7_THROW_COOLDOWN = 80; // Time between throws
int enemy7ThrowCooldown = 0;
int enemy7WalkImages[5];      
int enemy7ThrowImage;         
int enemy7HitImage;           
bool enemy7Flashed = false;
int enemy7FlashTimer = 0;
bool enemy7Spawned = false;

// Ball variables
bool ballActive = false;
float ballX = 0, ballY = 0;
float ballSpeed = 8.0f;
int ballDirection = 1; // 1 for right, -1 for left
int ballImage;
const int BALL_SIZE = 50;

bool showEnemy = false;
bool enemyAlive = false;
double xe, ye;

int level2EnemyImages[6];       // 4 frames
int level2EnemyFrameIndex = 0;
int level2EnemyFrameDelay = 0;
int maxLevel2FrameDelay = 6;
int level2EnemyX = LEVEL_WIDTH * TILE_SIZE - 300;;        // spawn X
int level2EnemyY = 118;         // ground Y
int level2EnemyHealth = 100;
bool level2EnemyAlive = false;
bool level2EnemyVisible = false;

struct Rect {
	int x, y, w, h;
};

// Change: Text coordinates for menu clicks
Rect startTextRect = { 80, 340, 144, 50 };    // Coordinates where "Start" text appears
Rect optionTextRect = { 80, 270, 160, 50 };   // Coordinates where "Option" text appears  
Rect creditsTextRect = { 80, 200, 150, 50 };  // Coordinates where "Credits" text appears
Rect exitTextRect = { 80, 130, 140, 50 };      // Coordinates where "Exit" text appears
Rect backRect = { 30, 40, 50, 80 };           // "Back" area
Rect backRect1 = { 870, 60, 150, 30 };           // "Back" area
Rect control1ClickRect = { 229, 102, 20, 100 };
// check mouse click inside rectangle
bool insideRect(int mx, int my, Rect r) {
	return (mx >= r.x && mx <= r.x + r.w &&
		my >= r.y && my <= r.y + r.h);
}

void drawScoreBar() {
	char scoreText[1000];
	sprintf_s(scoreText, "SCORE: %d", score);

	iSetColor(0, 0, 0); // black
	iText(scoreX, scoreY, scoreText, GLUT_BITMAP_HELVETICA_18);
}

void drawEnemy();
void drawLevel2Enemy();

//change
bool rectOverlap(int ax, int ay, int aw, int ah,
	int bx, int by, int bw, int bh) {
	return (ax < bx + bw) && (ax + aw > bx) &&
		(ay < by + bh) && (ay + ah > by);
}

struct Player {
	char name[50];
	int score;
};

#define MAX_PLAYERS 20
Player players[MAX_PLAYERS];
int playerCount = 0;

void saveCurrentPlayer() {
	FILE* fp;
	fopen_s(&fp, "scores.txt", "a"); // append mode
	if (fp == NULL) return;

	fprintf(fp, "%s %d\n", playerName, score);
	fclose(fp);
}

void saveScoresToFile() {
	FILE* fp;
	fopen_s(&fp, "scores.txt", "w");
	if (fp == NULL) return;

	for (int i = 0; i < playerCount; i++) {
		fprintf_s(fp, "%s %d\n", players[i].name, players[i].score);
	}
	fclose(fp);
}

void loadScoresFromFile() {
	FILE* fp;
	fopen_s(&fp, "scores.txt", "r");
	if (fp == NULL) return;

	while (fscanf_s(fp, "%s %d", players[playerCount].name, &players[playerCount].score) == 2) {
		playerCount++;
		if (playerCount >= MAX_PLAYERS) break;
	}
	fclose(fp);
}

struct Doraemon {
	int x, y;
	int currentFrame;
	int invisibleRight;
	int invisibleLeft;
	int imagesRight[2];
	int imagesLeft[2];
	bool facingRight;
	float velocityX;

	bool isBlinking;
	int blinkTimer;
	int blinkCount;

} doraemon;

struct Enemy {
	int x, y;
	int currentFrame;
	int walkImages[5];
	int frameDelay;
	bool facingRight;
};

Enemy enemy1;
Enemy enemy1b;
Enemy enemy2;
Enemy enemy3;
Enemy enemy4;
Enemy enemy4b;
// New enemy for level 2
Enemy enemy5;
Enemy enemy6;
Enemy enemy7;

#define MAX_DORACAKES 10
struct Doracake {
	float x, y;       // World coordinates
	bool collected;    // Whether it's been collected
	int level;         // Which level it belongs to
	int image;         //  image handle
};

Doracake doracakes[MAX_DORACAKES];
int doracakeCount = 0;

void resetGame() {
	camX = 0;
	camY = 0;
	worldX = 0;
	worldY = GROUND_Y;
	verticalVelocity = 0;
	isGrounded = true;
	gameState = STATE_GAME;

	doraemon.x = 0;
	doraemon.y = GROUND_Y;
	doraemon.velocityX = 0;

	int weaponVisible = 0;
	float weaponX, weaponY;
	int smokeFrame = 0;
	int smokeFrameDelay = 0;

	screenLocked = false;  // Reset screen lock
	lockStartX = 0.0f;
	lockEndX = 0.0f;

	if (currentLevel == 1) {
		enemy1.x = 500;
		enemy1.y = 95;
		enemy1.currentFrame = 0;
		enemy1.frameDelay = 0;
		enemy1.facingRight = false;

		enemy1b.x = 600;
		enemy1b.y = 95;
		enemy1.currentFrame = 0;
		enemy1.frameDelay = 0;
		enemy1.facingRight = false;

		enemy2.x = 2000;
		enemy2.y = 95;
		enemy2.currentFrame = 0;
		enemy2.frameDelay = 0;
		enemy2.facingRight = true;

		enemy3.x = 1600;
		enemy3.y = 98;
		enemy3.currentFrame = 0;
		enemy3.frameDelay = 0;
		enemy3.facingRight = false;
		currentHealth = maxHealth;

		enemy4.x = 5800;
		enemy4.y = 90;
		enemy4.currentFrame = 0;
		enemy4.frameDelay = 0;
		enemy4.facingRight = false;  // set initial direction

		enemy4Alive = true;
		enemy4Health = 3;
		enemy4Inverted = false;
		enemy4Frame = 0;
		enemy4FrameDelay = 0;
		enemy4InvertedFrame = 0;

		// Enemy4b setup
		enemy4bAlive = false;
		enemy4bSpawned = false;
		enemy4b.x = -100;            // start offscreen left
		enemy4bMinX = 0.0f;
		enemy4bMaxX = 0.0f;
		enemy4bMovingRight = true;
		enemy4b.y = 90;
		enemy4b.currentFrame = 0;
		enemy4b.frameDelay = 0;
		enemy4b.facingRight = true; 
	}
	else {
		// For level 2, disable all enemies
		enemy1Visible = false;
		enemy1bAlive = false;
		enemy3Alive = false;
		enemy4Alive = false;
		enemy4bAlive = false;
		showEnemy = false;
		enemyAlive = false;
	}

	
	if (currentLevel == 2) {
		enemy5.x = 550;  // Starting position
		enemy5.y = 118;
		enemy5.currentFrame = 0;
		enemy5.frameDelay = 0;
		enemy5.facingRight = false;
		enemy5Alive = true;
		enemy5Health = enemy5MaxHealth; 
		enemy5Hits = 0;
		enemy5Attacking = false;
		enemy5Flashed = false; // Reset flash state

		enemy6.x = 2500; 
		enemy6.y = 70;
		enemy6.currentFrame = 0;
		enemy6.frameDelay = 0;
		enemy6.facingRight = false;
		
		enemy6Health = enemy6MaxHealth;
		enemy6Hits = 0;
		enemy6Attacking = false;
		enemy6Flashed = false;
		enemy6Alive = false;
		enemy6Spawned = false;
	}
	// enemy7
	if (currentLevel == 2) {
		

		enemy7.x = 6500;  // Different position
		enemy7.y = 90;
		enemy7.currentFrame = 0;
		enemy7.frameDelay = 0;
		enemy7.facingRight = false;
		enemy7Alive = true;
		enemy7Health = enemy7MaxHealth;
		enemy7Hits = 0;
		enemy7ThrowCooldown = 0;
		enemy7Flashed = false;
		enemy7Spawned = false;

		ballActive = false;
		ballX = 0;
		ballY = 0;
	}




	

	showEnemy = false;
	level2EnemyVisible == false;

	//change
	for (int i = 0; i<MAX_BULLETS; i++){
		bulletActive[i] = false;
		bulletX[i] = (enemyWorldX + 50) - (int)camX;
		bulletY[i] = enemyWorldY + 50;
	}

}

struct RaisedTile {
	float x1, x2;  // left and right edges
	float y;       // top surface height
	bool active;
	int level;
};

RaisedTile raisedTiles[] = {
	//Level 1
	{ 1344.0f, 1518.0f, 246.0f, true, 1},
	{ 1650.0f, 1825.0f, 310.0f, true, 1},
	{ 2238.0f, 2420.0f, 246.0f, true, 1},

	// Level 2 
	{ 960.0f, 1020.0f, 250.0f, true, 2},
	{ 1090.0f, 1150.0f, 250.0f, true, 2 },
	{ 1217.0f, 1360.0f, 310.0f, true, 2 },
	{ 1410.0f, 1470.0f, 250.0f, true, 2 },
	{ 1540.0f, 1660.0f, 190.0f, true, 2 }
};
int raisedTileCount = 8;

void respawnDoraemon() {
	// Reset position to respawn point
	worldX = respawnPoint[0];
	worldY = respawnPoint[1];

	// Reset velocity
	doraemon.velocityX = 0;
	verticalVelocity = 0;

	// Reset camera
	camX = 0;

	// Reset health or take damage
	currentHealth -= 15.0f;  // Lose health when respawning

	// Check for game over
	if (currentHealth <= 0) {
		currentHealth = 0;
		gameState = STATE_GAME_OVER;
	}

	
	doraemon.isBlinking = true;
	doraemon.blinkTimer = 0;
	doraemon.blinkCount = 0;

	printf("Respawned! Health: %.1f\n", currentHealth);
}

bool checkCollision(float wx, float wy, float width, float height) {
	//  world coordinates to tile coordinates
	int leftCol = (int)((wx + 64)/ TILE_SIZE);
	int rightCol = (int)((wx + width ) / TILE_SIZE);
	int bottomRow = (int)((wy + 64)/ TILE_SIZE);
	int topRow = (int)((wy + height) / TILE_SIZE);

	// Check all tiles in the bounding box
	for (int row = bottomRow; row <= topRow; row++) {
		for (int col = leftCol; col <= rightCol; col++) {
			if (row < 0 || row >= LEVEL_HEIGHT || col < 0 || col >= LEVEL_WIDTH) {
				continue; // Out of bounds
			}

			// Convert stored row index (top=0) to bottom=0
			int storedRow = LEVEL_HEIGHT - 1 - row;

			if (level[storedRow][col] > 0) { // Solid tile
				return true;
			}
		}
	}
	return false;
}

// Check if standing on a platform
bool isOnPlatform(float wx, float wy, float& platformY) {
	for (int i = 0; i < raisedTileCount; i++) {
		if (!raisedTiles[i].active || raisedTiles[i].level != currentLevel) 
			continue;

		RaisedTile p = raisedTiles[i];

		if (wy <= p.y + 2.0f && wy >= p.y - 2.0f &&  // Within vertical range
			wx + DORA_W > p.x1 && wx < p.x2) {         // Within horizontal bounds
			platformY = p.y;
			return true;
		}
	}
	return false;
}

bool isFallingIntoGapOrSpikes(float wx, float wy) {
	float adjustedWy = wy - GROUND_Y + 64;

	// Check if falling below a certain death height
	if (wy < GROUND_Y - 150.0f && !isFallingToDeath) {  // Fell off the world
		// Start falling death sequence
		isFallingToDeath = true;
		fallDeathTimer = 0.0f;
		fallStartPositionX = worldX;
		fallStartPositionY = worldY;
		return true;
	}

	// Check if landing on spikes (tile ID 7)
	int colLeft = (int)((wx + 53) / TILE_SIZE);  // Check inside feet
	int colRight = (int)((wx + DORA_W - 53) / TILE_SIZE);
	int row = (int)(adjustedWy / TILE_SIZE);

	if (wy < GROUND_Y + 100.0f) {
		for (int col = colLeft; col <= colRight; col++) {
			if (col < 0 || col >= LEVEL_WIDTH || row < 0 || row >= LEVEL_HEIGHT) {
				continue;
			}

			int tileID = level[row][col];
			//int storedRow = LEVEL_HEIGHT - 1 - row;
			//int tileID = level[storedRow][col];
			if (currentLevel == 1){
				if (tileID == SPIKE_TILE && !isFallingToDeath) {  // Landed on spikes
					isFallingToDeath = true;
					fallDeathTimer = 0.0f;
					fallStartPositionX = worldX;
					fallStartPositionY = worldY;
					return true;
				}
			}
			if (currentLevel == 2){
				if (tileID == WATER_TILE && !isFallingToDeath) {  // Landed on spikes
					isFallingToDeath = true;
					fallDeathTimer = 0.0f;
					fallStartPositionX = worldX;
					fallStartPositionY = worldY;
					return true;
				}
			}
		}
	}
	return false;
}

void updateFallingDeath() {
	if (isFallingToDeath) {
		fallDeathTimer += 1.0f / 60.0f; // Assuming 60 FPS

		
		verticalVelocity -= GRAVITY * 2.0f;
		worldY += verticalVelocity;

	
		doraemon.y = (int)(worldY - camY);

		if (fallDeathTimer >= FALL_DEATH_DELAY) {
			//  respawn
			respawnDoraemon();
			isFallingToDeath = false;
		}
	}
}

void drawPlatforms() {
	for (int i = 0; i < raisedTileCount; i++) {
		if (raisedTiles[i].active && raisedTiles[i].level == currentLevel) {
			iSetColor(255, 0, 0);
			iFilledRectangle(raisedTiles[i].x1 - camX, raisedTiles[i].y - 5,
				raisedTiles[i].x2 - raisedTiles[i].x1, 10);
		}
	}
}

void collideHorizontal(float& wx, float wy, float vx) {
	if (vx == 0.0f) return;

	float newWX = wx + vx;

	if (vx > 0.0f) { // Moving right
		if (!checkCollision(newWX + DORA_W - EPS, wy, EPS, DORA_H)) {
			wx = newWX; 
		}
		else {
			// Collision, tile grid
			int tileX = (int)((newWX + DORA_W) / TILE_SIZE) * TILE_SIZE;
			wx = tileX - DORA_W - EPS;
		}
	}
	else { // Moving left
		if (!checkCollision(newWX, wy, EPS, DORA_H)) {
			wx = newWX; // No collision, move freely
		}
		else {
			// Collision, tile grid
			int tileX = (int)(newWX / TILE_SIZE) * TILE_SIZE;
			wx = tileX + TILE_SIZE + EPS;
		}
	}
}

void collideVertical(float wx, float& wy, float& vy, bool& grounded) {
	grounded = false;
	float newWY = wy + vy;

	if (vy > 0.0f) { // Moving up (jumping)
		if (!checkCollision(wx, newWY + DORA_H - EPS, DORA_W, EPS)) {
			wy = newWY; // No ceiling collision
		}
		else {
			// Hit ceiling, stop upward movement
			int tileY = (int)((newWY + DORA_H) / TILE_SIZE) * TILE_SIZE;
			wy = tileY - DORA_H - EPS;
			vy = 0;
		}
	}
	else { // Moving down (falling)
		// First check if falling into gap or spikes
		if (isFallingIntoGapOrSpikes(wx, newWY)) {
			respawnDoraemon();
			return; // Skip rest of collision processing
		}

		//  direct ground check
		if (newWY <= GROUND_Y) {
			wy = GROUND_Y;
			vy = 0;
			grounded = true;
			return;
		}

		float platformY;
		bool onPlatform = isOnPlatform(wx, newWY, platformY);

		if (onPlatform) {
			// Land on platform
			wy = platformY;
			vy = 0;
			grounded = true;
			return;
		}
		// keep falling
		wy = newWY;
	}
}



// Check if walking off edge
bool isWalkingOffEdge(float wx, float wy) {
	float platformY;
	if (!isOnPlatform(wx, wy, platformY)) return false;

	for (int i = 0; i < raisedTileCount; i++) {
		if (!raisedTiles[i].active || raisedTiles[i].level != currentLevel)
			continue;

		RaisedTile p = raisedTiles[i];
		if (fabs(wy - p.y) < 5.0f) {  // Currently on this platform
			// Check if about to move beyond platform edges
			float nextX = wx + doraemon.velocityX;
			if (nextX < p.x1 || nextX + DORA_W > p.x2) {
				return true;
			}
		}
	}
	return false;
}

void updateRespawnPoints() {
	if (currentLevel == 1) {
		respawnPoint[0] = 200.0f;
		respawnPoint[1] = 118.0f;

	}
	else if (currentLevel == 2) {
		respawnPoint[0] = 200.0f;
		respawnPoint[1] = 118.0f;
	}
}

void updateDrawingCoordinates() {
	// world coordinates to screen coordinates for drawing
	doraemon.x = (int)(worldX - camX);
	doraemon.y = (int)(worldY - camY);
}


void initializeDoracakes() {
	// Level 1 Doracakes
	doracakes[0] = { 1450.0f, 252.0f, false, 1, -1 };
	doracakes[1] = { 1730.0f, 317.0f, false, 1, -1 };
	doracakes[2] = { 2330.0f, 252.0f, false, 1, -1 };

	// Level 2 Doracakes  
	doracakes[3] = { 1040.0f, 320.0f, false, 2, -1 };
	doracakes[4] = { 1300.0f, 317.0f, false, 2, -1 };
	doracakes[5] = { 1630.0f, 200.0f, false, 2, -1 };

	doracakeCount = 5;

	// Load images for doracakes
	for (int i = 0; i < doracakeCount; i++) {
		doracakes[i].image = iLoadImage("Images\\doracake.png");
		if (doracakes[i].image == -1) {
			printf("Error loading doracake image!\n");
			
		}
	}
}

void checkDoracakeCollision() {
	for (int i = 0; i < doracakeCount; i++) {
		if (doracakes[i].collected || doracakes[i].level != currentLevel) continue;

		// collision between Doraemon and Doracake
		if (rectOverlap(worldX, worldY, DORA_W, DORA_H, doracakes[i].x, doracakes[i].y, 30, 30)) {
			// Collect the doracake
			doracakes[i].collected = true;

			// Increase health (up to 50% of max)
			currentHealth += maxHealth * 0.50f; // Increase by 25%
			if (currentHealth > maxHealth) {
				currentHealth = maxHealth; // Cap at 50%
			}
			printf("Doracake collected! Health: %.1f/%.1f\n", currentHealth, maxHealth);
		}
	}
}

void resetDoracakesForLevel() {
	for (int i = 0; i < doracakeCount; i++) {
		if (doracakes[i].level == currentLevel) {
			doracakes[i].collected = false; // Reset collection state
		}
	}
}

void updateMovement() {
	// Horizontal friction
	if (doraemon.velocityX > 0) {
		doraemon.velocityX -= FRICTION;
		if (doraemon.velocityX < 0) doraemon.velocityX = 0;
	}
	else if (doraemon.velocityX < 0) {
		doraemon.velocityX += FRICTION;
		if (doraemon.velocityX > 0) doraemon.velocityX = 0;
	}

	// Clamp horizontal velocity
	if (doraemon.velocityX > MAX_SPEED) doraemon.velocityX = MAX_SPEED;
	if (doraemon.velocityX < -MAX_SPEED) doraemon.velocityX = -MAX_SPEED;

	//  horizontal movement with collision
	collideHorizontal(worldX, worldY, doraemon.velocityX);
	// horizontal movement

	// Screen boundary collision
	if (worldX < 0) {
		worldX = 0;
		doraemon.velocityX = 0;
	}

	if (worldX > LEVEL_WIDTH * TILE_SIZE - DORA_W) {
		worldX = LEVEL_WIDTH * TILE_SIZE - DORA_W;
		doraemon.velocityX = 0;
	}


	// SCREEN LOCK LOGIC - Prevent going back if screen is locked
	if (screenLocked && worldX < lockStartX) {
		worldX = lockStartX;  // Block movement to the left
		doraemon.velocityX = 0;  // Stop movement
	}

	// UPDATE SCREEN COORDINATES
	updateDrawingCoordinates();


	// Screen lock logic (illusion)
	float threshold = SCREEN_WIDTH / 3.0f;

	float levelPixelW = (float)(gLevelWidth * TILE_SIZE);

	if (worldX < threshold) {
		doraemon.x = (int)worldX;  // free movement near start
	}
	else if (worldX > levelPixelW - (SCREEN_WIDTH - threshold)) {
		// near end: slide to the right naturally
		float rightScreen = SCREEN_WIDTH - (levelPixelW - worldX);
		doraemon.x = (int)rightScreen;
	}
	else {
		doraemon.x = (int)threshold; // locked in middle
	}

	// Spawn enemy4b after Doraemon passes 1500
	if (!enemy4bSpawned && worldX > 1500) {
		enemy4bAlive = true;
		enemy4bSpawned = true;  // mark as spawned

		// spawn position and movement range
		enemy4b.x = worldX - 200; 
		enemy4b.y = 90;

		// movement range (200px behind to 200px ahead of spawn point)
		enemy4bMinX = enemy4b.x - 200;
		enemy4bMaxX = enemy4b.x + 200;

		enemy4bMovingRight = true; // Start moving right

		
		enemy4bFrame = 0;
		enemy4bFrameDelay = 0;
		enemy4bInverted = false;
		enemy4bInvertedFrame = 0;
		enemy4bInvertedTimer = 0;
		enemy4bHealth = 3;   //  initial health
		enemy4bHits = 0;     // reset hits
	}
	if (!enemy6Spawned && worldX > 2000 && currentLevel ==2) {
		enemy6Alive = true;
		enemy6Spawned = true;

		
	}
	if (!enemy7Spawned && worldX > 2000 && currentLevel == 2) {
		enemy7Alive = true;
		enemy7Spawned = true;


	}
	if (!enemy4Spawned && worldX > 4000 && currentLevel == 1) {
		enemy4Alive = true;
		enemy4Spawned = true;


	}
	
	


	if (currentLevel== 1 && !enemyAlive && (worldX >3300)) {
		enemyAlive = true;
		showEnemy = true;
		enemyHealth = 100;  // reset health
		enemyWorldX = 4000;      // spawn position
		enemyWorldY = 118;       // ground level
	}

	if (currentLevel == 2 && !level2EnemyAlive && (worldX >3300)) {
		level2EnemyAlive = true;
		level2EnemyVisible = true;
		level2EnemyHealth = 100; 
		level2EnemyX = 4000; 
		level2EnemyY = 118;
		printf("Level 2 enemy spawned at worldX=%d\n", level2EnemyX);
	}

}


void updatePhysics() {
	if (isFallingToDeath) {
		// Only update falling death, not regular physics
		updateFallingDeath();
		return;
	}

	// Apply gravity
	verticalVelocity -= GRAVITY;

	// If jump is released while still going up → cut velocity for short hop
	if (!jumpHeld && verticalVelocity > 0) {
		verticalVelocity *= 0.50f;  // damp upward speed
	}

	// Clamp fall speed
	if (verticalVelocity < -MAX_SPEED * 2)
		verticalVelocity = -MAX_SPEED * 2;

	// Check if walking off edge of platform
	if (isGrounded && isWalkingOffEdge(worldX, worldY)) {
		isGrounded = false;
	}

	// Check for hazards
	if (isFallingIntoGapOrSpikes(worldX, worldY)) {
		// This will set isFallingToDeath = true
	}

	// Vertical collision
	collideVertical(worldX, worldY, verticalVelocity, isGrounded);

	checkDoracakeCollision();

	updateRespawnPoints();

	// UPDATE SCREEN COORDINATES
	updateDrawingCoordinates();

	//  COYOTE TIMER
	if (isGrounded) {
		coyoteTimer = COYOTE_FRAMES;  // reset timer on ground
	}
	else if (coyoteTimer > 0) {
		coyoteTimer--;  // count down while in air
	}

	// JUMP BUFFER CHECK 
	if (jumpBufferTimer > 0) {
		jumpBufferTimer--;

		// If buffer is active AND we're grounded/coyote jump
		if (coyoteTimer > 0) {
			verticalVelocity = JUMP_FORCE;
			isGrounded = false;
			coyoteTimer = 0;
			jumpBufferTimer = 0;
		}
	}

	// Smooth animation frame swap when moving
	if (doraemon.velocityX != 0) {
		frameDelay++;
		if (frameDelay >= maxFrameDelay) {
			doraemon.currentFrame = (doraemon.currentFrame + 1) % 2;
			frameDelay = 0;
		}
	}
}

void updateAnimation() {
	if (doraemon.velocityX != 0) {
		frameDelay++;
		if (frameDelay >= maxFrameDelay) {
			doraemon.currentFrame = (doraemon.currentFrame + 1) % 2;
			frameDelay = 0;
		}
	}
}

void loadTiles() {
	char filename[100];
	for (int i = 0; i < 20; i++) {
		sprintf_s(filename, "Images\\tile%d.png", i + 1);
		tileImg[i] = iLoadImage(filename);
		if (tileImg[i] == -1) {
			printf("Error loading image: %s\n", filename);
		}
		else {
			printf("Loaded: %s\n", filename);
		}

	}
}

void loadLevel(int lv) {
	char filename[100];
	sprintf_s(filename, "assets\\level%d.txt", lv);
	printf("Loading level %d...\n", lv);

	FILE *fp = NULL;
	errno_t err = fopen_s(&fp, filename, "r");

	if (fp == NULL) {
		printf("Error: cannot open %s\n", filename);
		exit(1);
	}


	int n;
	for (int y = 0; y < LEVEL_HEIGHT; y++) {
		for (int x = 0; x < LEVEL_WIDTH; x++) {

			if (fscanf_s(fp, "%d", &n) != 1){
				printf("Invalid value at [%d][%d], defaulting to 0\n", y, x);
				n = 0;
			}
			level[y][x] = n;
			printf("%d ", n);

		}
		printf("\n");
	}
	fclose(fp);
	printf("Level %d loaded successfully.\n", lv);
}

void drawTiles() {
	int startCol = camX / TILE_SIZE;
	int endCol = (camX + SCREEN_WIDTH) / TILE_SIZE + 1;
	//printf("camX: %.2f, startCol: %d, endCol: %d\n", camX, startCol, endCol);

	for (int row = 0; row < LEVEL_HEIGHT; row++) {
		for (int col = startCol; col <= endCol; col++) {
			if (col < 0 || col >= LEVEL_WIDTH)
				continue;

			int tileID = level[row][col] - 1; // 0 in file is empty
			if (tileID >= 0 && tileID < 20) { // to load 20 tile images
				float x = col* TILE_SIZE - camX;
				//float y = (LEVEL_HEIGHT - 1 - row) * TILE_SIZE - camY;
				float y = row* TILE_SIZE;
				iShowImage(x, y, TILE_SIZE, TILE_SIZE, tileImg[tileID]);
			}
		}
	}
}

void loadMenu() {
	// MENU IMAGEs
	loading1Img = iLoadImage("Images\\firstpage1.1.png");
	loading2Img = iLoadImage("Images\\firstpage1.2.png");
	mainmenuImg = iLoadImage("Images\\mainmenu.png");

	startBtnImg = iLoadImage("Images\\startbutton.png");
	optionBtnImg = iLoadImage("Images\\optionbutton.png");
	creditsBtnImg = iLoadImage("Images\\creditsbutton.png");
	exitBtnImg = iLoadImage("Images\\exitbutton.png");

	control1Img = iLoadImage("Images\\control1.png");
	control2Img = iLoadImage("Images\\control2.png");

	creditsPageImg = iLoadImage("Images\\credits.png");
}

void updateCamera() {
	float threshold = SCREEN_WIDTH / 3.0f;
	float levelPixelW = (float)(gLevelWidth * TILE_SIZE);

	float targetCamX = worldX - threshold;  // scroll after threshold
	if (targetCamX < 0.0f) targetCamX = 0.0f;
	
	if (targetCamX > levelPixelW - SCREEN_WIDTH)
		targetCamX = levelPixelW - SCREEN_WIDTH;
	camX += (targetCamX - camX) * 0.15f;

	bgScrollX = camX * 0.3f;
}

void syncDoraemonScreenY() {
	doraemon.y = (int)(worldY - camY);
}

void drawDoracakes() {
	for (int i = 0; i < doracakeCount; i++) {
		if (!doracakes[i].collected && doracakes[i].level == currentLevel) {
			//  if doracake is on screen
			float screenX = doracakes[i].x - camX;
			float screenY = doracakes[i].y;

			if (screenX + 30 > 0 && screenX < SCREEN_WIDTH &&
				screenY + 30 > 0 && screenY < SCREEN_HEIGHT) {

				if (doracakes[i].image != -1) {
					iShowImage(screenX, screenY, 40, 25, doracakes[i].image);
				}
				else {
					// yellow rectangle
					iSetColor(255, 255, 0);
					iFilledRectangle(screenX, screenY, 30, 30);
					iSetColor(0, 0, 0);
					iRectangle(screenX, screenY, 30, 30);
				}
			}
		}
	}
}

void drawEnemyHealthBar(Enemy* enemy, int health) {
	if (!enemy || !health) return;

	int x = enemy->x - camX;   // world -> screen
	int y = enemy->y + 100;    // above enemy
	int barWidth = 20;
	int barHeight = 5;
	int gap = 2;

	for (int i = 0; i < 3; i++) {
		if (i < health) iSetColor(0, 255, 0);   // green = remaining
		else iSetColor(255, 0, 0);              // red = lost
		iFilledRectangle(x + i * (barWidth + gap), y, barWidth, barHeight);
	}

}
void drawEnemy5HealthBar(Enemy* enemy, int health) {
	if (!enemy || !health) return;

	int x = enemy->x - camX;   
	int y = enemy->y + 240;    
	int barWidth = 15;         
	int barHeight = 5;
	int gap = 2;

	//  5 health segments 
	for (int i = 0; i < 5; i++) {
		if (i < health) iSetColor(0, 255, 0);   // green = remaining
		else iSetColor(255, 0, 0);              // red = lost
		iFilledRectangle(x + i * (barWidth + gap), y, barWidth, barHeight);
	}
}
void stopAllMusic() {
	mciSendString("stop bg1", NULL, 0, NULL);
	mciSendString("close bg1", NULL, 0, NULL);

	mciSendString("stop menusong", NULL, 0, NULL);
	mciSendString("close menusong", NULL, 0, NULL);

	mciSendString("stop enemyMusic", NULL, 0, NULL);
	mciSendString("close enemyMusic", NULL, 0, NULL);

	mciSendString("stop gameover", NULL, 0, NULL);
	mciSendString("close gameover", NULL, 0, NULL);

	bgMusicPlaying = enemyMusicPlaying = menuMusicPlaying = gameOverMusicPlaying = false;
}

void playEnemyMusic() {
	if (!enemyMusicPlaying) {
		stopAllMusic();
		mciSendString("open \"Music\\enemy1.mp3\" alias enemyMusic", NULL, 0, NULL);
		mciSendString("play enemyMusic repeat", NULL, 0, NULL);
		enemyMusicPlaying = true;
	}
}


void playMenuMusic() {
	if (!menuMusicPlaying) {

		mciSendString("open \"Music\\menu.mp3\" alias menusong", NULL, 0, NULL);
		mciSendString("play menusong repeat", NULL, 0, NULL);
		menuMusicPlaying = true;
	}
}

void playBGMusic() {
	if (!bgMusicPlaying) {
		stopAllMusic();
		mciSendString("open \"Music\\bg1.mp3\" alias bg1", NULL, 0, NULL);
		mciSendString("play bg1 repeat", NULL, 0, NULL);
		bgMusicPlaying = true;
	}
}

void playGameOverMusic() {
	if (!gameOverMusicPlaying) {
		stopAllMusic();
		mciSendString("open \"Music\\gameover.mp3\" alias gameover", NULL, 0, NULL);
		mciSendString("play gameover", NULL, 0, NULL);
		gameOverMusicPlaying = true;
	}
}
void playLevel1Music() {
	if (!level1MusicPlaying) {
		stopAllMusic();
		mciSendString("open \"Music\\win.mp3\" alias level", NULL, 0, NULL);
		mciSendString("play level", NULL, 0, NULL);
		level1MusicPlaying = true;
	}
}

void checkSmokeEnemyCollision(int idx) {
	
	if (!smokeActive[idx]) return;
 
	int sw = (int)(50 * smokeScale[idx]);
	int sh = (int)(50 * smokeScale[idx]);
	int sx = (int)smokeX[idx];
	int sy = (int)smokeY[idx];

	// ---- Enemy (main) ----
	if (enemyAlive) {
		int ex = enemyWorldX - camX;
		int ey = enemyWorldY;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;
			enemyHealth -= 5;                   // health decrease
			enemyHitEffect = true;              // boss hit effect strt
			enemyHitTimer = 60;                 // effect for 1 sec

	
			if (enemyHealth <= 0) {
				enemyHealth = 0;
				enemyAlive = false;
				showEnemy = false;
				score += 500;
				gameState = STATE_GAME_COMPLETE;
				playLevel1Music();
			}
			return;
		}
	}
	if (currentLevel == 2 && level2EnemyAlive && level2EnemyVisible) {
		int bossX = level2EnemyX - (int)camX; // boss screen X
		int bossY = level2EnemyY;
		int bossW = 200;  // boss width
		int bossH = 500;  // boss height

		if (rectOverlap(sx, sy, sw, sh, bossX, bossY, bossW, bossH)) {
			smokeActive[idx] = false;
			

			level2EnemyHealth -= 10;   
			bossHitEffect = true;
			bossHitTimer = 70;
			if (level2EnemyHealth <= 0) {
				level2EnemyHealth = 0;
				level2EnemyAlive = false;
				level2EnemyVisible = false;
				score += 500;

				gameState = STATE_GAME_COMPLETE;
				stopAllMusic();
			}
		}
	}

	// Enemy1
	if (enemy1Visible) {
		int ex = enemy1.x - camX;
		int ey = enemy1.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy1Health--;
			enemy1Hits++;
			score += 10;
			if (enemy1Health <= 0 || enemy1Hits >= 3) {
				enemy1Visible = false;
			}

			enemy1Flashed = true;
			enemy1FlashTimer = 30;
			return;
		}
	}

	// Enemy1b 
	if (enemy1bAlive) {
		int ex = enemy1b.x - camX;
		int ey = enemy1b.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy1bHealth--;
			enemy1bHits++;
			score += 10;
			if (enemy1bHealth <= 0 || enemy1bHits >= 3) {
				enemy1bAlive = false;
				
			}

			enemy1bFlashed = true;
			enemy1bFlashTimer = 30;
			return;
		}
	}

	// Enemy3 
	if (enemy3Alive) {
		int ex = enemy3.x - camX;
		int ey = enemy3.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy3Health--;
			enemy3Hits++;
			score += 10;
			if (enemy3Health <= 0 || enemy3Hits >= 3) {
				enemy3Alive = false;
				enemy3BurstActive = true;
				enemy3BurstFrame = 0;
				enemy3BurstDelay = 0;
				//score += 10;
			}
			return;
		}
	}

	//  Enemy4
	if (enemy4Alive) {
		int ex = enemy4.x - camX;
		int ey = enemy4.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy4Health--;
			enemy4Hits++;
			score += 10;
			if (enemy4Health <= 0 || enemy4Hits >= 3) {
				enemy4Inverted = true;        // trigger dying animation
				enemy4InvertedFrame = 0;
				enemy4InvertedTimer = 0;
				
			}
			return;
		}
	}

	//  Enemy4b
	if (enemy4bAlive) {
		int ex = enemy4b.x - camX;
		int ey = enemy4b.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy4bHealth--;
			enemy4bHits++;
			score += 10;
			if (enemy4bHits >= 3) {
				enemy4bInverted = true;       // trigger dying animation
				enemy4bInvertedFrame = 0;
				enemy4bInvertedTimer = 0;
				//score += 10;
			}
			return;
		}
	}
	

	// Enemy5 
	if (enemy5Alive && currentLevel == 2) {
		int ex = enemy5.x - camX;
		int ey = enemy5.y;
		int ew = 200, eh = 220;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy5Health--;
			enemy5Hits++;
			score += 10;
			//  hit image
			enemy5Flashed = true;
			enemy5FlashTimer = 15;

			if (enemy5Health <= 0 || enemy5Hits >= 5) { //  5 hits for 5 health
				enemy5Alive = false;
				
			}
			return;
		}
	}
	//  Enemy6 
	if (enemy6Alive) {
		int ex = enemy6.x - camX;
		int ey = enemy6.y;
		int ew = 200, eh = 220;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy6Health--;
			enemy6Hits++;
			score += 10;
			//  hit image
			enemy6Flashed = true;
			enemy6FlashTimer = 15;

			if (enemy6Health <= 0 || enemy6Hits >= 5) {
				enemy6Alive = false;
				
			}
			return;
		}
	}
	//  Enemy7 
	if (enemy7Alive) {
		int ex = enemy7.x - camX;
		int ey = enemy7.y;
		int ew = 100, eh = 120;

		if (rectOverlap(sx, sy, sw, sh, ex, ey, ew, eh)) {
			smokeActive[idx] = false;

			enemy7Health--;
			enemy7Hits++;
			score += 10;
			//  hit image
			enemy7Flashed = true;
			enemy7FlashTimer = 15;

			if (enemy7Health <= 0 || enemy7Hits >= 3) {
				enemy7Alive = false;
			
			}
			return;
		}
	}
}

void playSmokeSound() {
	mciSendString("stop smoke", NULL, 0, NULL);
	mciSendString("close smoke", NULL, 0, NULL);

	mciSendString("open \"Music\\smoke.mp3\" alias smoke", NULL, 0, NULL);
	mciSendString("play smoke", NULL, 0, NULL);
}

void updateWeaponSmoke() {
	// if  smokes are active
	bool anySmokeActive = false;
	for (int i = 0; i < MAX_SMOKES; i++) {
		if (smokeActive[i]) {
			anySmokeActive = true;
			break;
		}
	}

	// hide weapon based on smoke activity
	weaponVisible = anySmokeActive;


}
void updateSmoke() {
	int highestActive = -1;

	for (int i = 0; i < MAX_SMOKES; i++) {
		if (!smokeActive[i]) continue;

		smokeX[i] += smokeDir[i] * smokeSpeed;

		float distance = fabs(smokeX[i] - smokeStartX[i]);
		smokeScale[i] = 0.5f + (distance / SCREEN_WIDTH);
		if (smokeScale[i] > 2.0f) smokeScale[i] = 2.0f;

		checkSmokeEnemyCollision(i);  // Pass the index as argument

		if (smokeX[i] < 0 || smokeX[i] > SCREEN_WIDTH) {
			smokeActive[i] = false;
		}
		else {
			highestActive = i; //  highest active index
		}
	}

	//  activeSmokes to the highest active index + 1
	if (highestActive != -1) {
		activeSmokes = highestActive + 1;
	}
	else {
		activeSmokes = 0;
	}
}

int victoryPg;
int gameOverPg;
int endPg;

void initializeDoraemon() {
	void loadMenu();

	// bg images
	for (int i = 0; i < 2; i++) {
		char bgName[100];
		sprintf_s(bgName, "Images\\bg%d.jpeg", i + 1);
		bgImage[i] = iLoadImage(bgName);
	}

	
	storyImages[0] = iLoadImage("Images\\story1.png");
	storyImages[1] = iLoadImage("Images\\story2.png");
	storyImages[2] = iLoadImage("Images\\story3.png");
	storyImages[3] = iLoadImage("Images\\story4.png");
	storyImages[4] = iLoadImage("Images\\story5.png");

	// doraemon image
	for (int i = 0; i < 2; i++) {
		char filenameRight[100], filenameLeft[100];
		sprintf_s(filenameRight, "Images\\d%d.png", i + 1);
		sprintf_s(filenameLeft, "Images\\dl%d.png", i + 1);
		doraemon.imagesRight[i] = iLoadImage(filenameRight);
		doraemon.imagesLeft[i] = iLoadImage(filenameLeft);
	}

	char invisibleFile[100];

	// Right invisible
	sprintf_s(invisibleFile, "Images\\i1.png");
	doraemon.invisibleRight = iLoadImage(invisibleFile);

	// Left invisible
	sprintf_s(invisibleFile, "Images\\i2.png");
	doraemon.invisibleLeft = iLoadImage(invisibleFile);

	weaponImgRight = iLoadImage("Images\\Air Cannon.png");         // original
	weaponImgLeft = iLoadImage("Images\\Air Cannon.png");
	smokeImg = iLoadImage("Images\\ball.png");


	//Level 1 small enemy
	for (int i = 0; i < 5; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\s%d.png", i + 1);
		enemy1.walkImages[i] = iLoadImage(filename);
	}
	enemy1InvisibleImg = iLoadImage("Images\\sInvi.png");

	for (int i = 0; i < 5; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\s%d.png", i + 1);
		enemy1b.walkImages[i] = iLoadImage(filename);
	}
	enemy1bInvisibleImg = iLoadImage("Images\\sInvi.png");

	for (int i = 0; i < 4; i++) {
		char path[100];
		sprintf_s(path, "images\\f%d.png", i + 1);
		enemy2.walkImages[i] = iLoadImage(path);
	}
	char filename1[100];
	for (int i = 0; i < 4; i++) {
		sprintf_s(filename1, "images\\b%d.png", i + 1);
		enemy3.walkImages[i] = iLoadImage(filename1);
	}

	for (int i = 0; i < 3; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\bomb%d.png", i + 1);
		enemy3BurstImages[i] = iLoadImage(filename);
	}


	// Enemy4 walking images
	for (int i = 0; i < 4; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\f%d.png", i + 1);
		enemy4Images[i] = iLoadImage(filename);
		if (enemy4Images[i] == -1) {
			printf("Could not load Enemy4 walk image: %f\n", filename);
		}
	}


	// Enemy4 inverted images
	for (int i = 0; i < 3; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\inv%d.png", i + 1);
		enemy4InvertedImages[i] = iLoadImage(filename);
		if (enemy4InvertedImages[i] == -1) {
			printf("Could not load Enemy4 inverted image: %s\n", filename);
		}
	}
	// Enemy4 walking images
	for (int i = 0; i < 4; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\n%d.png", i + 1);
		enemy4bImages[i] = iLoadImage(filename);
		if (enemy4bImages[i] == -1) {
			printf("Could not load Enemy4 walk image: %n\n", filename);
		}
	}


	// Enemy4 inverted images
	for (int i = 0; i < 3; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\in%d.png", i + 1);
		enemy4bInvertedImages[i] = iLoadImage(filename);
		if (enemy4bInvertedImages[i] == -1) {
			printf("Could not load Enemy4 inverted image: %in\n", filename);
		}
	}

	// enemy5 images (walking)
	for (int i = 0; i < 4; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\en%d.png", i + 1);
		enemy5WalkImages[i] = iLoadImage(filename);
		if (enemy5WalkImages[i] == -1) {
			printf("Could not load Enemy5 walk image: %s\n", filename);
		}
	}

	//  enemy5 attack images
	for (int i = 0; i < 2; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\enA%d.png", i + 1);
		enemy5AttackImages[i] = iLoadImage(filename);
		if (enemy5AttackImages[i] == -1) {
			printf("Could not load Enemy5 attack image: %s\n", filename);
		}
	}

	//  enemy5 hit image
	enemy5HitImage = iLoadImage("Images\\enH1.png");
	if (enemy5HitImage == -1) {
		printf("Could not load Enemy5 hit image\n");
	}

	//  enemy6 walking images (4 frames)
	for (int i = 0; i < 4; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\fo%d.png", i + 1);
		enemy6WalkImages[i] = iLoadImage(filename);
		if (enemy6WalkImages[i] == -1) {
			printf("Could not load Enemy6 walk image: %s\n", filename);
		}
	}

	//  enemy6 attack images (4 frames)
	for (int i = 0; i < 4; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\foA%d.png", i + 1);
		enemy6AttackImages[i] = iLoadImage(filename);
		if (enemy6AttackImages[i] == -1) {
			printf("Could not load Enemy6 attack image: %s\n", filename);
		}
	}

	//  enemy6 hit image
	enemy6HitImage = iLoadImage("Images\\fH1.png");
	if (enemy6HitImage == -1) {
		printf("Could not load Enemy6 hit image\n");
	} 

	//  enemy7 walking images (5 frames)
	for (int i = 0; i < 5; i++) {
		char filename[100];
		sprintf_s(filename, "Images\\enem%d.png", i + 1);
		enemy7WalkImages[i] = iLoadImage(filename);
		if (enemy7WalkImages[i] == -1) {
			printf("Could not load Enemy7 walk image: %s\n", filename);
		}
	}



	//  enemy7 hit image
	enemy7HitImage = iLoadImage("Images\\enemH1.png");
	if (enemy7HitImage == -1) {
		printf("Could not load Enemy7 hit image\n");
	}

	// ball image
	ballImage = iLoadImage("Images\\enemW2.png");
	if (ballImage == -1) {
		printf("Could not load ball image\n");
	}

	lightWeaponImage = iLoadImage("Images\\sm.png");
	lightProjectionImage = iLoadImage("Images\\smL.png");


	// spike images
	for (int i = 0; i < 2; i++) {
		char spikeName[100];
		sprintf_s(spikeName, "Images\\spike%d.png", i + 1);
		spikeImage[i] = iLoadImage(spikeName);
	}

    //Boss enemy - Level 1
	char enemyFiles[4][50] = {
		"Images\\e.1.png",
		"Images\\e.2.png",
		"Images\\e.3.png",
		"Images\\e.4.png"
	};

	for (int i = 0; i < 4; i++) {
		enemyImages[i] = iLoadImage(enemyFiles[i]);
		if (enemyImages[i] == -1) {
			printf("Could not load image: %s\n", enemyFiles[i]);
		}
	}

	//Boss enemy - Level 2
	char level2EnemyFiles[6][50] = {
		"Images\\L1.png",
		"Images\\L2.png",
		"Images\\L3.png",
		"Images\\L4.png",
		"Images\\L5.png",
		"Images\\L6.png",

	};

	for (int i = 0; i < 6; i++) {
		level2EnemyImages[i] = iLoadImage(level2EnemyFiles[i]);
		if (level2EnemyImages[i] == -1) {
			printf("Could not load Level 2 enemy image: %s\n", level2EnemyFiles[i]);
		}
		else {
			printf("Loaded Level 2 enemy image: %s\n", level2EnemyFiles[i]);
		}
	}

	bossHitImage = iLoadImage("Images\\bullethit.png");//ccccccc
	dragonFireImage = iLoadImage("Images\\fire4.png");  //
	if (dragonFireImage == -1) {
		printf("Could not load dragon fire image!\n");
	}
	else {
		printf(" Dragon fire image loaded!\n");
	}
	enemyHitImage = iLoadImage("Images\\bullethit4.png");  
	if (enemyHitImage == -1) {
		printf("Could not load Level1 Boss Hit image!\n");
	}
	else {
		printf(" Level1 Boss Hit image loaded!\n");
	}
	

	bulletImage = iLoadImage("Images\\bt.1.png");
	//change
	for (int i = 0; i<MAX_BULLETS; i++){
		bulletActive[i] = false;
		bulletX[i] = (enemyWorldX + 50) - (int)camX;
		bulletY[i] = enemyWorldY + 50;
	}

	initializeDoracakes();

	victoryPg = iLoadImage("Images\\victorypg.png");
	gameOverPg = iLoadImage("Images\\gameover.png");
	endPg = iLoadImage("Images\\end.png");

	doraemon.velocityX = 0;
	doraemon.x = 0;
	doraemon.y = GROUND_Y;
	doraemon.currentFrame = 0;
	doraemon.facingRight = true;


}

void drawHealthBar() {
	int barWidth = 300, barHeight = 20;
	int x = 0, y = SCREEN_HEIGHT - barHeight;
	iSetColor(150, 150, 150);
	iFilledRectangle(x, y, barWidth, barHeight);
	float p = currentHealth / maxHealth;
	if (p < 0) p = 0;
	iSetColor(255, 0, 0);
	iFilledRectangle(x, y, (int)(barWidth * p), barHeight);
	iSetColor(0, 0, 0);
	iRectangle(x, y, barWidth, barHeight);
}
void drawLevel2EnemyHealthBar() {
	if (!level2EnemyAlive || !level2EnemyVisible) return;

	int barWidth = 300;    
	int barHeight = 20;    
	int margin = 20;               

	
	int x = SCREEN_WIDTH - barWidth ; 
	int y = SCREEN_HEIGHT - barHeight ;

	iSetColor(150, 150, 150);
	iFilledRectangle(x, y, barWidth, barHeight);

	// health (red)
	float p = level2EnemyHealth / 100.0f;
	if (p < 0) p = 0;

	iSetColor(255, 0, 0);
	iFilledRectangle(x, y, (int)(barWidth * p), barHeight);

	// border
	iSetColor(0, 0, 0);
	iRectangle(x, y, barWidth, barHeight);
}



void drawEnemyHealthBar(int enemyHealth) {
	if (showEnemy == false) return;
	if (enemyHealth <= 0) return;  // enemy dies
	if (currentHealth <= 0) return;

	int barWidth = 300;     // health bar width
	int barHeight = 20;     // height
	int margin = 20;        // screen edge to gap

	int x = SCREEN_WIDTH - barWidth ; // right edge to gap
	int y = SCREEN_HEIGHT - barHeight ; // top edge to gap

	// background (gray)
	iSetColor(150, 150, 150);
	iFilledRectangle(x, y, barWidth, barHeight);

	// health (red)
	float p = enemyHealth / 100.0f;
	if (p < 0) p = 0;

	iSetColor(255, 0, 0);
	iFilledRectangle(x, y, (int)(barWidth * p), barHeight);

	// border
	iSetColor(0, 0, 0);
	iRectangle(x, y, barWidth, barHeight);
}


void drawMenu() {
	switch (gameState) {
	case STATE_LOADING1:
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loading1Img);
		break;

	case STATE_LOADING2:
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loading2Img);
		break;
	case STATE_MAINMENU:
		if (showStartButtonFullScreen) {
			// start button on FULL SCREEN
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, startBtnImg);
		}
		else if (showOptionButtonFullScreen) {
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, optionBtnImg);
		}
		else if (showCreditsButtonFullScreen) {
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, creditsBtnImg);
		}
		else if (showExitButtonFullScreen) {
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, exitBtnImg);
		}
		else {
			//  normal menu
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mainmenuImg);
		}
		break;

	case STATE_OPTIONS:
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, control1Img);
		break;

	case STATE_CONTROLS:
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, control2Img);
		break;

	case STATE_CREDITS:
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, creditsPageImg);
		break;

	case STATE_EXIT:
		exit(0);
		break;

	default:
		break;
	}
}

void drawGame() {
	
	if (showingStory) {
		//  the current story image
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, storyImages[storyIndex]);
		return; 
	}

	float bgX = -camX * parallaxFactor;

	iShowImage(bgX, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT, bgImage[currentLevel - 1]);

	drawTiles();
	
	drawDoracakes();

	// Doraemon drawing
	if (doraemon.isBlinking && (doraemon.blinkCount % 2 == 0)) {
		// invisible depending on direction
		if (doraemon.facingRight) {
			iShowImage(doraemon.x, doraemon.y, 90, 100, doraemon.invisibleRight);
		}
		else {
			iShowImage(doraemon.x, doraemon.y, 90, 100, doraemon.invisibleLeft);
		}
	}
	else {
		// Normal drawing
		if (doraemon.facingRight) {
			iShowImage(doraemon.x, doraemon.y, 90, 100, doraemon.imagesRight[doraemon.currentFrame]);
		}
		else {
			iShowImage(doraemon.x, doraemon.y, 90, 100, doraemon.imagesLeft[doraemon.currentFrame]);
		}
	}
	if (weaponVisible) {
		if (doraemon.facingRight) {
			iShowImage(doraemon.x + 50, doraemon.y + 2, 64, 64, weaponImgRight);
		}
		else {
			// Flip horizontally by using negative width
			iShowImage(doraemon.x - 30 + 64, doraemon.y + 2, -64, 64, weaponImgLeft);
		}
	}
	// Smoke
	if (smokeActive) {
		int w = 50;
		int h = 50;
		for (int i = 0; i < activeSmokes; i++) {
			if (smokeActive[i]) {
				iShowImage(smokeX[i], smokeY[i], 50, 50, smokeImg);
			}
		}

	}


	//Enemy
	if (currentLevel == 1 && enemy1Visible) {
		int drawImg;
		if (enemy1Flashed) {
			drawImg = enemy1InvisibleImg;
		}
		else {
			drawImg = enemy1.walkImages[enemy1.currentFrame];
		}
		iShowImage(enemy1.x - camX, enemy1.y, 100, 120, drawImg);
	}
	if (currentLevel == 1 && enemy1bAlive) {
		int drawImg;
		if (enemy1bFlashed) {
			drawImg = enemy1bInvisibleImg;
		}
		else {
			drawImg = enemy1b.walkImages[enemy1b.currentFrame];
		}
		iShowImage(enemy1b.x - camX, enemy1b.y, 100, 120, drawImg);
		drawEnemyHealthBar(&enemy1b, enemy1bHealth);
	}



	if (enemy3Alive) {
		iShowImage(enemy3.x - camX, enemy3.y, 100, 120, enemy3.walkImages[enemy3.currentFrame]);
	}
	else if (enemy3BurstActive) {
		iShowImage(enemy3.x - camX, enemy3.y, 100, 120, enemy3BurstImages[enemy3BurstFrame]);

		enemy3BurstDelay++;
		if (enemy3BurstDelay >= 15) {
			enemy3BurstFrame++;
			enemy3BurstDelay = 0;
		}

		if (enemy3BurstFrame >= 3) {
			enemy3BurstActive = false; // animation finished
		}
	}
	if (enemy4Alive) {
		if (!enemy4Inverted)
			iShowImage(enemy4.x - camX, enemy4.y, 100, 120, enemy4Images[enemy4Frame]);
		else
			iShowImage(enemy4.x - camX, enemy4.y, 100, 120, enemy4InvertedImages[enemy4InvertedFrame]);
	}
	if (enemy4bAlive && !screenLocked) {
		if (!enemy4bInverted)
			iShowImage(enemy4b.x - camX, enemy4b.y, 100, 120, enemy4bImages[enemy4bFrame]);
		else
			iShowImage(enemy4b.x - camX, enemy4b.y, 100, 120, enemy4bInvertedImages[enemy4bInvertedFrame]);
	}

	
	
	// Enemy5
	if (currentLevel == 2 && enemy5Alive) {
		int drawImg;

		if (enemy5Flashed) {
			drawImg = enemy5HitImage; // hit image when flashed
		}
		else if (enemy5Attacking) {
			drawImg = enemy5AttackImages[enemy5.currentFrame];
		}
		else {
			drawImg = enemy5WalkImages[enemy5.currentFrame];
		}
		if (enemy5.facingRight) {
			iShowImage(enemy5.x - camX + 250, enemy5.y, -250, 250, drawImg); // Negative width flips image
		}
		else{
			iShowImage(enemy5.x - camX, enemy5.y, 200, 220, drawImg);
		}
		
		if (enemy5Alive) drawEnemy5HealthBar(&enemy5, enemy5Health);
	}

	if (enemy6Alive) {
		int drawImg;

		if (enemy6Flashed) {
			drawImg = enemy6HitImage;
		}
		else if (enemy6Attacking) {
			drawImg = enemy6AttackImages[enemy6.currentFrame % 4]; // 4 attack frames
		}
		else {
			drawImg = enemy6WalkImages[enemy6.currentFrame % 4]; // 4 walk frames
		}
		if (enemy6.facingRight) {
			iShowImage(enemy6.x - camX + 250, enemy6.y, -250, 250, drawImg); // Negative width flips image
		}
		else{
			iShowImage(enemy6.x - camX, enemy6.y, 250, 250, drawImg);
		}

		
		drawEnemy5HealthBar(&enemy6, enemy6Health); //  same health bar as enemy5
	}

	if (enemy7Alive) {
		int drawImg;

		if (enemy7Flashed) {
			drawImg = enemy7HitImage;
		}
		else {
			drawImg = enemy7WalkImages[enemy7.currentFrame % 5]; //  walking frames
		}

		iShowImage(enemy7.x - camX, enemy7.y, 220, 200, drawImg);
		drawEnemy5HealthBar(&enemy7, enemy7Health);
	}
	
	if (ballActive) {
		int ballScreenX = ballX - camX;
		int ballScreenY = ballY - camY;
		iShowImage(ballScreenX, ballScreenY, BALL_SIZE, BALL_SIZE, ballImage);
	}
	if (screenLocked) {
		// light weapon if visible
		if (lightWeaponVisible) {
			if (doraemon.facingRight) {
				iShowImage(doraemon.x + 55, doraemon.y + 24, 50, 40, lightWeaponImage);
			}
			else {
				iShowImage(doraemon.x + 34, doraemon.y + 28, -40, 40, lightWeaponImage);
			}
		}

		//  projection if active
		if (projectionActive) {
			if (doraemon.facingRight) {
				iShowImage(projectionX - 4, projectionY - 24, 100, 100, lightProjectionImage);
			}
			else {
				iShowImage(projectionX + 115, projectionY - 24, -100, 100, lightProjectionImage);
			}
		}
	}
	

	if (enemy1Visible) drawEnemyHealthBar(&enemy1, enemy1Health);
	if (enemy4Alive)   drawEnemyHealthBar(&enemy4, enemy4Health);
	if (enemy4bAlive)  drawEnemyHealthBar(&enemy4b, enemy4bHealth);
	if (enemy3Alive)   drawEnemyHealthBar(&enemy3, enemy3Health);



	drawEnemy();
	drawLevel2Enemy();

	if (screenLocked) {
		iShowImage(0, 0, 80, 600, spikeImage[0]);
		//iShowImage(1000, 0, 80, 600, spikeImage[1]);
	}
}

// Level complete button area
Rect nextLevelButton = { SCREEN_WIDTH / 2 -160, SCREEN_HEIGHT / 2 - 200, 405, 45 };
Rect mainMenuButton = { SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 125, 400, 50 };
Rect playAgainButton = { SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 50, 400, 60 };
Rect exitGameButton = { SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 120, 200, 60 };

void drawLevelComplete() {
	if (currentLevel == 1){
		char buf[100];
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, victoryPg);
		iSetColor(0, 0, 0);
		sprintf_s(buf, "Score: %d", score);
		iText(450, 300, buf, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (currentLevel == 2){
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, endPg);
		char buf[100];
		iSetColor(0, 0, 0);
		
		sprintf_s(buf, "Score: %d", score);
		iText(620, 150, buf, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	

}

void drawGameOver() {
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameOverPg);
	char buf[100];
	iSetColor(0, 0, 0);

	sprintf_s(buf, "Score: %d", score);
	iText(450, 360, buf,  GLUT_BITMAP_TIMES_ROMAN_24);
}


void updateEnemyCollision() {
	if (invincibleTicks > 0) invincibleTicks--;

	// Doraemon hitbox (world coordinates)
	int doraX = doraemon.x + 20;
	int doraY = doraemon.y + 20;
	int doraW = 20;
	int doraH = 20;
	

	Enemy* enemies[8] = { &enemy1, &enemy1b, &enemy4, &enemy4b, &enemy3, &enemy5, &enemy6, &enemy7 };
	bool aliveFlags[8] = { enemy1Visible, enemy1bAlive, enemy4Alive, enemy4bAlive, enemy3Alive, enemy5Alive, enemy6Alive, enemy7Alive };

	// array sizes
	int enemyW[8] = { 70, 70, 100, 100, 90, 200, 200, 100 };
	int enemyH[8] = { 100, 100, 120, 120, 120, 220, 220, 120 };

	for (int i = 0; i < 8; i++) {
		if (!aliveFlags[i]) continue;

		int ex = enemies[i]->x - camX;
		int ey = enemies[i]->y;
		int ew = enemyW[i];
		int eh = enemyH[i];

		if (ex + ew < 0 || ex > SCREEN_WIDTH) continue;

		//  overlap for regular collision
		bool x_overlap = (doraX < ex + ew) && (doraX + doraW > ex);
		bool y_overlap = (doraY < ey + eh) && (doraY + doraH > ey);

		if (x_overlap && y_overlap) {
			printf("COLLISION DETECTED with enemy %d!\n", i);
		}

		if (!x_overlap || !y_overlap) continue;

		int doraBottom = doraY + doraH;
		if (doraBottom <= ey + 10) continue;

		// BLINK EFFECT
		if (!doraemon.isBlinking) {
			doraemon.isBlinking = true;
			doraemon.blinkTimer = 0;
			doraemon.blinkCount = 0;
			printf("Doraemon BLINKING from enemy %d collision!\n", i);
		}

		// DAMAGE
		if (invincibleTicks == 0) {
			
			if (i == 5) { // enemy5
				if (enemy5Attacking) { // Only damage during attack
					currentHealth -= 0.5f;
					if (currentHealth < 0) currentHealth = 0;
					invincibleTicks = INVINCIBLE_MAX_TICKS;
					printf("Doraemon took DAMAGE from enemy5 attack! Health: %.1f\n", currentHealth);

					if (currentHealth <= 0) {
						enemyAlive = false;
						showEnemy = false;
						gameState = STATE_GAME_OVER;
					}
				}
				else {
					printf("Doraemon collided with enemy5 walking (BLINK but no damage)\n");
				}
			}
			else { 
				currentHealth -= 0.5f;
				if (currentHealth < 0) currentHealth = 0;
				invincibleTicks = INVINCIBLE_MAX_TICKS;
				printf("Doraemon took DAMAGE from enemy %d! Health: %.1f\n", i, currentHealth);

				if (currentHealth <= 0) {
					enemyAlive = false;
					showEnemy = false;
					gameState = STATE_GAME_OVER;
				}
			}
		}
		else {
			printf("Doraemon is INVINCIBLE, no damage taken from enemy %d\n", i);
		}
		//  enemy6 specific handling 
		if (i == 6) { // enemy6 (index 6)
			if (enemy6Attacking) { // Only damage during attack
				currentHealth -= 0.5f;
				if (currentHealth < 0) currentHealth = 0;
				invincibleTicks = INVINCIBLE_MAX_TICKS;

				if (currentHealth <= 0) {
					enemyAlive = false;
					showEnemy = false;
					gameState = STATE_GAME_OVER;
				}
			}

			
			if (enemy6Attacking) {
				enemy6Attacking = false;
				enemy6AttackTimer = 0;
			}
		}
		//  enemy7 specific handling
		if (i == 7) { // enemy7 (index 7)
			currentHealth -= 0.3f;
			if (currentHealth < 0) currentHealth = 0;
			invincibleTicks = INVINCIBLE_MAX_TICKS;

			if (currentHealth <= 0) {
				enemyAlive = false;
				showEnemy = false;
				gameState = STATE_GAME_OVER;
			}
		}
		//  enemy3 burst animation
		if (i == 4 && enemy3Alive) {  // index 4 = enemy3
			enemy3Alive = false;
			enemy3BurstActive = true;
			enemy3BurstFrame = 0;
			enemy3BurstDelay = 0;
		}

		//  enemy4b inverted trigger on collision
		if (i == 3 && enemy4bAlive && !enemy4bInverted) {  // index 3 = enemy4b
			enemy4bHealth--;
			if (enemy4bHealth <= 0 || enemy4bHits >= 3) {
				enemy4bInverted = true;
				enemy4bInvertedFrame = 0;
				enemy4bInvertedTimer = 0;
			}
		}

		// enemy5 collision (index 5)
		if (i == 5 && enemy5Alive) {
			// Make enemy5 stop attacking temporarily
			if (enemy5Attacking) {
				enemy5Attacking = false;
				enemy5AttackTimer = 0;
			}
		}

	}
	// SEPARATE ATTACK RANGE DETECTION FOR ENEMY6
	if (enemy6Alive && enemy6Attacking && currentLevel == 2) {
		float attackRangeX = 120.0f;
		float attackRangeY = 100.0f;

		float enemy6CenterX = enemy6.x - camX + 100;
		float enemy6CenterY = enemy6.y + 110;

		float doraCenterX = doraemon.x + 45;
		float doraCenterY = doraemon.y + 50;

		bool inAttackRangeX = abs(doraCenterX - enemy6CenterX) < attackRangeX;
		bool inAttackRangeY = abs(doraCenterY - enemy6CenterY) < attackRangeY;

		if (inAttackRangeX && inAttackRangeY && !doraemon.isBlinking) {
			doraemon.isBlinking = true;
			doraemon.blinkTimer = 0;
			doraemon.blinkCount = 0;

			if (invincibleTicks == 0) {
				currentHealth -= 0.2f;
				if (currentHealth < 0) currentHealth = 0;
				invincibleTicks = INVINCIBLE_MAX_TICKS / 3;

				if (currentHealth <= 0) {
					enemyAlive = false;
					showEnemy = false;
					gameState = STATE_GAME_OVER;
				}
			}
		}
	}

	// SEPARATE ATTACK RANGE DETECTION FOR ENEMY5 
	if (enemy5Alive && enemy5Attacking && currentLevel == 2) {
		// distance between Doraemon and enemy5 attack image
		float attackRangeX = 250.0f; 
		float attackRangeY = 150.0f;  

		//  (center of attack image)
		float enemy5CenterX = enemy5.x - camX + 100; 
		float enemy5CenterY = enemy5.y + 110;       

		// Get Doraemon position (center)
		float doraCenterX = doraemon.x + 45; 
		float doraCenterY = doraemon.y + 50; 

		// if Doraemon is within attack range 
		bool inAttackRangeX = abs(doraCenterX - enemy5CenterX) < attackRangeX;
		bool inAttackRangeY = abs(doraCenterY - enemy5CenterY) < attackRangeY;

		if (inAttackRangeX && inAttackRangeY && !doraemon.isBlinking) {
			doraemon.isBlinking = true;
			doraemon.blinkTimer = 0;
			doraemon.blinkCount = 0;
			printf("Doraemon BLINKING from enemy5 ATTACK RANGE (not collision)!\n");

			
			if (invincibleTicks == 0) {
				currentHealth -= 0.3f;
				if (currentHealth < 0) currentHealth = 0;
				invincibleTicks = INVINCIBLE_MAX_TICKS / 2; 
				printf("Doraemon took RANGE DAMAGE from enemy5 attack! Health: %.1f\n", currentHealth);

				if (currentHealth <= 0) {
					enemyAlive = false;
					showEnemy = false;
					gameState = STATE_GAME_OVER;
				}
			}
		}
	}

}

void updateDoraemonBlink() {
	if (doraemon.isBlinking) {
		doraemon.blinkTimer++;

		if (doraemon.blinkTimer >= 40) {  // adjust speed of blink
			doraemon.blinkTimer = 0;
			doraemon.blinkCount++;

			if (doraemon.blinkCount >= 2) { // 6 toggles = 3 full blinks
				doraemon.isBlinking = false;
			}
		}
	}
}

void playBulletSound() {

	mciSendString("stop bullet", NULL, 0, NULL);
	mciSendString("close bullet", NULL, 0, NULL);


	mciSendString("open \"Music\\enemy1B.mp3\" alias bullet", NULL, 0, NULL);
	mciSendString("play bullet", NULL, 0, NULL);
}
void updateBullet(float dt) {

	if (enemyJumping) return;


	if (!showEnemy) {
		for (int i = 0; i < MAX_BULLETS; i++) bulletActive[i] = false;
		enemyBulletTimer = 0;   // reset timer
		return;
	}


	if (enemyBulletTimer < BULLET_DELAY) {
		enemyBulletTimer += dt;
		
		return; 
	}

	if (invincibleTicks > 0) invincibleTicks--;

	for (int i = 0; i < MAX_BULLETS; i++) {
		// spawn bullet only after delay + enemyFrame==2
		if (!bulletActive[i] && enemyFrame == 2) {
			bulletX[i] = (enemyWorldX - 30) - (int)camX;
			bulletY[i] = enemyWorldY + 50;
			bulletActive[i] = true;
			if (currentLevel != 2) {
				playBulletSound();
			}

			
			break;
		}

		if (bulletActive[i]) {
			bulletX[i] -= bulletSpeed;

			int doraemonMidY = doraemon.y + 30;
			int doraemonMidHeight = 50;

			if (rectOverlap(doraemon.x, doraemonMidY, 90, doraemonMidHeight,
				(int)bulletX[i], (int)bulletY[i], 30, 15)) {
				if (invincibleTicks == 0) {
					currentHealth -= 0.3f;
					if (currentHealth < 0) currentHealth = 0;
					invincibleTicks = INVINCIBLE_MAX_TICKS;
					bulletActive[i] = false;

					// blink effect start
					doraemon.isBlinking = true;
					doraemon.blinkTimer = 0;
					doraemon.blinkCount = 0;

					if (currentHealth <= 0) {
						gameState = STATE_GAME_OVER;
						gameOverMusicPlaying = false;
						playGameOverMusic();
					}
				}
			}

			if (bulletX[i] < 0) {
				bulletActive[i] = false;
			}
		}
	}
}

//Level 1
void updateEnemyAnimation() {
	if (!showEnemy) return;

	enemyFrameDelay++;
	if (enemyFrameDelay >= maxEnemyFrameDelay) {
		enemyFrame = (enemyFrame + 1) % 4;
		enemyFrameDelay = 0;
	}
}

//Level 2
void updateLevel2EnemyAnimation() {
	if (!level2EnemyAlive) return;
	if (bossHitEffect) {
		return; 
	}
	level2EnemyFrameDelay++;
	if (level2EnemyFrameDelay >= maxLevel2FrameDelay) {
		level2EnemyFrameIndex = (level2EnemyFrameIndex + 1) % 6; // 6 frames
		level2EnemyFrameDelay = 0;
		
		if (level2EnemyFrameIndex == 5 && !dragonFireActive) {
			dragonFireActive = true;
			dragonFireX = level2EnemyX - (int)camX + 120;
			dragonFireY = level2EnemyY + 80;
			dragonFireTimer = dragonFireDuration;  // effect duration
			printf(" Dragon FIRE spawned at (%d,%d)\n", dragonFireX, dragonFireY);
		}
		level2EnemyFrameDelay = 0;
	}
	
}
void updateDragonFire() {
	if (dragonFireActive) {
		dragonFireX -= dragonFireSpeed;   

		dragonFireTimer--;
		if (dragonFireTimer <= 0 || dragonFireX < -dragonFireWidth) {
			dragonFireActive = false;
		}
	}
}
void drawDragonFire() {
	if (dragonFireActive) {
		iShowImage(dragonFireX, dragonFireY, dragonFireWidth, dragonFireHeight, dragonFireImage);
	}
}
void drawBullet() {
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (bulletActive[i]) {
			iShowImage((int)bulletX[i], (int)bulletY[i], 30, 30, bulletImage);
		}
	}
}

void updateLevel2EnemyMovement() {
	if (!level2EnemyAlive || !level2EnemyVisible) return;

	// Move enemy
	level2EnemyX += level2EnemySpeed * level2EnemyDir*2;

	// Check bounds
	if (level2EnemyX >= level2EnemyMaxX) {
		level2EnemyDir = -1; 
	}
	else if (level2EnemyX <= level2EnemyMinX) {
		level2EnemyDir = 1;  
	}
	if (level2EnemyVisible && level1MusicStarted) {
	  // music stop function
		level1MusicStarted = false;
	}
	// Animate walking
	updateLevel2EnemyAnimation();
}

void updateJumpEnemy() {
	if (enemyFrame == 0 && !enemyJumping) {  // e.1 image
		enemyJumping = true;
		enemyJumpVelocity = jumpStrength;   // constant speed
		enemyDirectionUp = true;
	}

	if (enemyJumping) {
		if (enemyDirectionUp) {
			enemyJumpOffsetY += enemyJumpVelocity;  // move up
			if (enemyJumpOffsetY >= maxJumpHeight) {
				enemyDirectionUp = false;           // reached top, now go down
			}
		}
		else {
			enemyJumpOffsetY -= enemyJumpVelocity;  // move down
			if (enemyJumpOffsetY <= 0) {
				enemyJumpOffsetY = 0;
				enemyJumping = false;              // back to ground
			}
		}
	}
}

//Level 1 Boss enemy
void drawEnemy() {
	if (currentLevel == 1){
		if (!showEnemy) return;

		int enemyX = enemyWorldX - (int)camX;
		int enemyY = enemyWorldY + (int)enemyJumpOffsetY;
		
		if (enemyX + 100 >= 0 && enemyX <= SCREEN_WIDTH){
		
		iShowImage(enemyX, enemyY, 100, 100, enemyImages[enemyFrame]);
		if (enemyHitEffect) {
			iShowImage(enemyX, enemyY, 100, 100, enemyHitImage);
		}
			drawBullet();
		}
	}
}
void updateBossHitEffect() {
	if (bossHitEffect) {
		bossHitTimer--;   
		if (bossHitTimer <= 0) {
			bossHitEffect = false;  // effect 
			bossHitTimer = 0;
		}
	}
}

void doraemonlevel2Enemycollision(){
	if (projectionActive) return;
	if (level2EnemyAlive && currentLevel == 2) {

		
		if (level2EnemyFrameIndex == 5) {

			float enemyCenterX = level2EnemyX - camX + 100;  
			float enemyCenterY = level2EnemyY + 110;         


			float doraCenterX = doraemon.x + 45;   
			float doraCenterY = doraemon.y + 50;   

		
			float attackRangeX = 60.0f;   
			float attackRangeY = 80.0f;   

			bool inAttackRangeX = fabs(doraCenterX - enemyCenterX) < attackRangeX;
			bool inAttackRangeY = fabs(doraCenterY - enemyCenterY) < attackRangeY;

			if (inAttackRangeX && inAttackRangeY && !doraemon.isBlinking) {
			
				doraemon.isBlinking = true;
				doraemon.blinkCount = 0;

				currentHealth -= 2;

				invincibleTicks = INVINCIBLE_MAX_TICKS / 2;  
			
				if (currentHealth <= 0) {
					currentHealth = 0;
					score += 100;
					gameState = STATE_GAME_OVER;
				}
			}
		}
	}
}
void updateEnemySize() {
	if (enemySmall) {
		enemySmallTimer--;
		if (enemySmallTimer <= 0) {
			enemySmall = false;  
		}
	}
}
void playLevel2EnemyMusic() {
	if (!level2MusicPlaying) {
		mciSendString("close dragon", NULL, 0, NULL);
		mciSendString("open \"Music\\dragon.mp3\" alias dragon", NULL, 0, NULL);
		mciSendString("play dragon repeat", NULL, 0, NULL); 
		level2MusicPlaying = true;
	}
}

void stopLevel2EnemyMusic() {
	if (level2MusicPlaying) {
		mciSendString("stop dragon", NULL, 0, NULL);
		mciSendString("close dragon", NULL, 0, NULL);
		level2MusicPlaying = false;
	}
}
//Level 2 Boss Enemy
void  drawLevel2Enemy() {
	if (currentLevel == 2){
		if (!level2EnemyAlive || !level2EnemyVisible) return;

		int screenX = level2EnemyX - (int)camX;
		int screenY = level2EnemyY;
		int enemyW = 400, enemyH = 300;

		printf("Drawing Level 2 enemy at screenX=%d (worldX=%d, camX=%.2f)\n",
			screenX, level2EnemyX, camX);
		if (projectionActive) {
			enemyW = 200;   
			enemyH = 150;
		}

		if (bossHitEffect) {
			// Bo
			iShowImage(screenX, screenY, enemyW, enemyH, level2EnemyImages[level2EnemyFrameIndex]);

			// effect 
			int effectW = 150, effectH = 150; // 
			int effectX = screenX + (enemyW - effectW) / 2;
			int effectY = screenY + (enemyH - effectH) / 2;

			iShowImage(effectX, effectY, effectW, effectH, bossHitImage);
		}
		else {
			
			iShowImage(screenX, screenY, enemyW, enemyH, level2EnemyImages[level2EnemyFrameIndex]);
		}
		if (level2EnemyFrameIndex == 5) { // L6 frame
			playLevel2EnemyMusic();
		}
		else {
			stopLevel2EnemyMusic();
		}
	}

}//ccccc

void updateEnemyMusic() {
	int enemyX = enemyWorldX - (int)camX;

	if (enemyX + 100 >= 0 && enemyX <= SCREEN_WIDTH) {

		if (!enemyMusicPlaying) {
			playEnemyMusic();
		}
		showEnemy = true;
	}
	else {
		// Enemy g
		if (showEnemy) {
			showEnemy = false;
			if (!bgMusicPlaying) {
				playBGMusic();
			}
			enemyMusicPlaying = false;
		}
	}
}

void checkBossEncounter() {
	if (showEnemy && enemyAlive && !screenLocked) {
		// if boss is on screen
		int bossScreenX = enemyWorldX - (int)camX;

		if (bossScreenX >= 0 && bossScreenX <= SCREEN_WIDTH) {
			// Boss is on screen LOCK THE SCREEN!
			screenLocked = true;
			lockStartX = worldX;  // current position
			lockEndX = LEVEL_WIDTH * TILE_SIZE;  // Can move right until end

			printf("BOSS ENCOUNTER! Screen locked at X: %.1f\n", lockStartX);
		}
	}
}

void checkBoss2Encounter() {
	if (level2EnemyVisible && level2EnemyAlive && !screenLocked) {
		// Check if boss is on screen
		int screenX = level2EnemyX - (int)camX;

		if (screenX >= 0 && screenX <= SCREEN_WIDTH) {
			// Boss is on screen - LOCK THE SCREEN!
			screenLocked = true;
			lockStartX = worldX;  // Lock at current position
			lockEndX = LEVEL_WIDTH * TILE_SIZE;  // Can move right until end

			printf("BOSS ENCOUNTER! Screen locked at X: %.1f\n", lockStartX);
		}
	}
}

void updateMusic()  {
	int enemyX = enemyWorldX - (int)camX;
	if (gameState == STATE_GAME_OVER) {
		if (!gameOverMusicPlaying) playGameOverMusic();
		return;
	}
	// Change:
	else if (gameState == STATE_GAME_COMPLETE ) {
		if (!level1MusicPlaying) playLevel1Music();
	}

	if (gameState == STATE_GAME) {
		if (enemyX + 100 >= 0 && enemyX <= SCREEN_WIDTH) {
			if (!enemyMusicPlaying) {
				playEnemyMusic();
			}
			showEnemy = true;
		}
		else {
			if (showEnemy) {
				showEnemy = false;
				if (!bgMusicPlaying) {
					playBGMusic();
				}
				enemyMusicPlaying = false;
			}
		}
	}
}
void fixedUpdate() {
	updateMusic();
}

void updateLoadingState() {
	if (gameState == STATE_LOADING1) {
		loadingTimer++;
		if (loadingTimer > 100) {
			gameState = STATE_LOADING2;
			loadingTimer = 0;
		}
	}

}

void updateButtonDisplay() {
	if (showStartButtonFullScreen) {
		buttonDisplayTimer++;
		if (buttonDisplayTimer >= BUTTON_DISPLAY_TIME) {
			showStartButtonFullScreen = false;
			// AFTER showing the button, start the storyline
			gameState = STATE_ENTER_NAME;
		}
		
	}
	if (showOptionButtonFullScreen) {
		optionButtonDisplayTimer++;
		if (optionButtonDisplayTimer >= OPTION_BUTTON_DISPLAY_TIME) {
			showOptionButtonFullScreen = false;
			gameState = STATE_OPTIONS;
		}
	}
	if (showCreditsButtonFullScreen) {
		creditsButtonDisplayTimer++;
		if (creditsButtonDisplayTimer >= CREDITS_BUTTON_DISPLAY_TIME) {
			showCreditsButtonFullScreen = false;
			gameState = STATE_CREDITS;
		}
	}
	if (showExitButtonFullScreen) {
		exitButtonDisplayTimer++;
		if (exitButtonDisplayTimer >= EXIT_BUTTON_DISPLAY_TIME) {
			showExitButtonFullScreen = false;
			gameState = STATE_EXIT;
		}
	}
}

void updateStoryline() {
	if (!showingStory) return;

	storyTimer++;
	if (storyTimer > storyDelay) {
		storyTimer = 0;
		storyIndex++;

	
		if (storyIndex >= TOTAL_STORY_IMAGES) {
			storyIndex = TOTAL_STORY_IMAGES - 1; // Stay on the last image
			
		}
	}
}


void iDraw() {
	iClear();


	if (gameState == STATE_STORYLINE && showingStory) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, storyImages[storyIndex]);
		return; 
	}

	
	switch (gameState) {
	case STATE_LOADING1:
	case STATE_LOADING2:
	case STATE_MAINMENU:
	case STATE_OPTIONS:
	case STATE_CONTROLS:
	case STATE_CREDITS:
	case STATE_EXIT:
		drawMenu();
		break;

	case STATE_STORYLINE:
		// T
		break;

	case STATE_GAME: {  
						 
						 updateJumpEnemy();
						 updateMovement();
						 updateAnimation();
						 updateSmoke();
						 updateWeaponSmoke();
						 if (ballActive) {
							 iShowImage((int)ballX, (int)ballY, BALL_SIZE, BALL_SIZE, ballImage);
						 }
						 float dt = 1.0f / 100.0f;   
						 updateBullet(dt);
						 drawDragonFire();
						 
						 
						 updateEnemyCollision();
						 doraemonlevel2Enemycollision();
						 updateDoraemonBlink();
						

						 if (bossHitEffect) {
							 bossHitTimer--;
							 if (bossHitTimer <= 0) {
								 bossHitEffect = false;
							 }
						 }
						 if (enemyHitEffect) {
							 enemyHitTimer--;
							 if (enemyHitTimer <= 0) {
								 enemyHitEffect = false;  
							 }
						 }

						 if (enemy1Flashed) {
							 enemy1FlashTimer--;
							 if (enemy1FlashTimer <= 0) {
								 enemy1Flashed = false;
							 }
						 }
						 if (enemy1bFlashed) {
							 enemy1bFlashTimer--;
							 if (enemy1bFlashTimer <= 0) {
								 enemy1bFlashed = false;
							 }
						 }

						 
						 drawGame();
						 drawHealthBar();
						 drawScoreBar();

						 if (showEnemy && enemyAlive) {
							 drawEnemyHealthBar(enemyHealth);
						 }
						 if (currentLevel == 2 && level2EnemyAlive) {
							 drawLevel2EnemyHealthBar();   // Level 2 Boss Enemy
						 }
						
						 if (currentLevel == 1) {
							 updateBullet(dt);
							 drawBullet();
							 break;   
						 }

						 break;   
	}   

	case STATE_ENTER_NAME:
		iSetColor(0, 0, 0);  // black background
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		iSetColor(255, 255, 255);
		iText(350, 400, "Enter Your Name:", GLUT_BITMAP_TIMES_ROMAN_24);
		iRectangle(350, 330, 330, 50);

		// Show typed name
		iText(360, 350, playerName, GLUT_BITMAP_TIMES_ROMAN_24);
		if (showNameWarning) {
			iText(352, 310, "Name must be at least 3 letters!", GLUT_BITMAP_HELVETICA_18);
		}

		iText(700, 30, "Press Space to Continue...", GLUT_BITMAP_HELVETICA_18);
		break;

	case STATE_GAME_OVER:
		drawGameOver();
		break;

	case STATE_GAME_COMPLETE:
		drawLevelComplete();
		break;
	}
}

void iMouseMove(int mx, int my)
{
	printf("Mx =%d MY =%d\n", mx, my);
	xe = mx;
	ye = my;
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	mouseX = mx;
	mouseY = SCREEN_HEIGHT - my; // Convert to screen coordinates
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		// --- MAIN MENU ---
		if (gameState == STATE_MAINMENU) {
			if (insideRect(mx, my, startTextRect)) {
				printf("Start button clicked! Showing full screen button.\n"); 
				showStartButtonFullScreen = true;  // start button image
				buttonDisplayTimer = 0;            // Reset timer
			}
			else if (insideRect(mx, my, optionTextRect)) {
				printf("Option button clicked! Showing full screen button.\n");
				showOptionButtonFullScreen = true;  //  option button image
				optionButtonDisplayTimer = 0;       // Reset timer
				
			}
			else if (insideRect(mx, my, creditsTextRect)) {
				printf("Credits button clicked! Showing full screen button.\n");
				showCreditsButtonFullScreen = true;
				creditsButtonDisplayTimer = 0;
			}
			else if (insideRect(mx, my, exitTextRect)) {
				printf("Exit button clicked! Showing full screen button.\n");
				showExitButtonFullScreen = true;
				exitButtonDisplayTimer = 0;
			}
			else if (insideRect(mx, my, creditsTextRect)) {
				gameState = STATE_CREDITS;
			}
			else if (insideRect(mx, my, exitTextRect)) {
				gameState = STATE_EXIT;
			}
		}
		// OPTIONS/CONTROLS/CREDITS MENU
		else if (gameState == STATE_OPTIONS) {
			if (insideRect(mx, my, backRect)) {
				gameState = STATE_MAINMENU;
			}
			else if (insideRect(mx, my, control1ClickRect)) {
				gameState = STATE_CONTROLS;   // switch to control2Img
			}
		}
		else if (gameState == STATE_CREDITS) {
			if (insideRect(mx, my, backRect1)) {
				gameState = STATE_MAINMENU;
			}
		}
		else if (gameState == STATE_CONTROLS) {
			if (insideRect(mx, my, backRect)) {
				gameState = STATE_MAINMENU;
			}
		}
		else if (gameState == STATE_GAME_COMPLETE) {
			saveCurrentPlayer();
			// Next Level button clicked
			if (insideRect(mx, my, nextLevelButton)) {
				currentLevel++;
				if (currentLevel >= MAX_LEVELS) {
					gameState = STATE_GAME_COMPLETE;
				}

				loadLevel(currentLevel);   // load new tilemap
				resetGame();               // reset Doraemon, enemies, etc.
				showingStory = false; // IMPORTANT: stop drawing story image
				showEnemy = false;
				resetDoracakesForLevel();
				gameState = STATE_GAME; 

				// back to gameplay
			
				level2EnemyVisible == true;
				// Level 2 music trigger
	
					playBGMusic();      
					level1MusicPlaying = true;
				
			}
			// Main Menu button 
			else if (insideRect(mx, my, mainMenuButton)) {
				gameState = STATE_MAINMENU;
			}
		}
		else if (gameState == STATE_GAME_OVER) {
			if (insideRect(mx, my, playAgainButton)) {
			
				gameState = STATE_GAME;
				resetGame();
				playBGMusic();
				level1MusicPlaying = true;
				currentHealth = 100.0f;
			}
			else if (insideRect(mx, my, exitGameButton))
				gameState = STATE_EXIT;
		}

	}
	

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
}
/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == '\r'){

	}
	if (gameState == STATE_ENTER_NAME) {
		if (key == ' ') {
			// Only continue if name has at least 3 characters
			if (nameLength >= 3) {
				gameState = STATE_STORYLINE;
				showingStory = true;
				storyIndex = 0; // start from first story image
			}
			else {
				showNameWarning = true;
			}
		}
		else if (key == '\b') { // BACKSPACE
			if (nameLength > 0) {
				playerName[--nameLength] = '\0';
			}
		}
		else {
			if (nameLength < 49 && key >= 32 && key <= 126) {
				playerName[nameLength++] = key;
				playerName[nameLength] = '\0';
			}
		}
	}
	if (key == 13) {
		if (gameState == STATE_LOADING2) {
			gameState = STATE_MAINMENU;
			playMenuMusic();
		}
		else if (gameState == STATE_GAME) {
			//  available smoke slot
			int availableSlot = -1;
			for (int i = 0; i < MAX_SMOKES; i++) {
				if (!smokeActive[i]) {
					availableSlot = i;
					break;
				}
			}

			if (availableSlot == -1) {
				availableSlot = 0; // Simple approach - replace the first one
			}

			// new smoke
			smokeActive[availableSlot] = true;
			playSmokeSound();

			if (doraemon.facingRight) {
				smokeX[availableSlot] = doraemon.x + 80;
				smokeDir[availableSlot] = 1;
			}
			else {
				smokeX[availableSlot] = doraemon.x - 30;
				smokeDir[availableSlot] = -1;
			}

			smokeY[availableSlot] = doraemon.y + 21;
			smokeScale[availableSlot] = 0.5f;
			smokeStartX[availableSlot] = smokeX[availableSlot];

			// Update active smoke count 
			if (availableSlot >= activeSmokes) {
				activeSmokes = availableSlot + 1;
			}
		}
	}

	if (gameState == STATE_GAME && key == 'm' && screenLocked && currentLevel == 2) { // 16 is the key code for Shift
		

		// If weapon is visible, show projection
		if (!lightWeaponVisible) {
			lightWeaponVisible = true;
			projectionActive = true;
			projectionTimer = PROJECTION_DURATION;

			//  projection position based on Doraemon's direction
			if (doraemon.facingRight) {
				projectionX = doraemon.x + 80;
			}
			else {
				projectionX = doraemon.x - 100;
			}
			projectionY = doraemon.y + 20;

		}
	}

	// Handle storyline advancement
	if (gameState == STATE_STORYLINE && key == ' ') {
		
		if (storyIndex == TOTAL_STORY_IMAGES - 1) {
			showingStory = false;
			resetGame();
			gameState = STATE_GAME;
			playBGMusic();
		}
		return;
	}



}


/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboardUp(unsigned char key) {
	if (key == GLUT_KEY_UP) {
		jumpHeld = false;   // release
	}
}

void iSpecialKeyboard(unsigned char key) {
	if (gameState != STATE_GAME) return;

	if (key == GLUT_KEY_RIGHT) {
		doraemon.velocityX = ACCELERATION * 4;
		doraemon.facingRight = true;
		frameDelay++;
		if (frameDelay >= maxFrameDelay) {
			doraemon.currentFrame = (doraemon.currentFrame + 1) % 2;
			frameDelay = 0;
		}
	}
	else if (key == GLUT_KEY_LEFT) {
		doraemon.velocityX = -ACCELERATION * 4;
		doraemon.facingRight = false;
		frameDelay++;
		if (frameDelay >= maxFrameDelay) {
			doraemon.currentFrame = (doraemon.currentFrame + 1) % 2;
			frameDelay = 0;
		}
	}
	else if (key == GLUT_KEY_UP&& isGrounded) {
		jumpBufferTimer = BUFFER_FRAMES;   
		jumpHeld = true;
		PlaySound(TEXT("Music\\jump.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	}
}



void updateEnemy1() {

	if (currentLevel == 1) {
		// enemy1 
		int enemyScreenX = enemy1.x - bgScrollX;
		if (enemyScreenX <= SCREEN_WIDTH) {
			enemy1.frameDelay++;
			if (enemy1.frameDelay >= 6) {
				enemy1.currentFrame = (enemy1.currentFrame + 1) % 5;
				enemy1.frameDelay = 0;
			}
			// Move left
			enemy1.x -= 2;
		}

		// enemy1b 
		int enemyScreenXb = enemy1b.x - bgScrollX;
		if (enemyScreenXb <= SCREEN_WIDTH) {
			enemy1b.frameDelay++;
			if (enemy1b.frameDelay >= 6) {
				enemy1b.currentFrame = (enemy1b.currentFrame + 1) % 5;
				enemy1b.frameDelay = 0;
			}
			// Move left
			enemy1b.x -= 2;
		}
	}
}

void updateEnemy2() {
	if (currentLevel == 1) {
		int enemyScreenX = enemy2.x - bgScrollX;

		
		if (enemyScreenX <= SCREEN_WIDTH) {
			enemy2.frameDelay++;
			if (enemy2.frameDelay >= 6) {
				enemy2.currentFrame = (enemy2.currentFrame + 1) % 4;
				enemy2.frameDelay = 0;
			}

			// Move left
			enemy2.x -= 2;
		}
	}
}

void updateEnemy3() {
	if (currentLevel == 1) {
		int enemyScreenX = enemy3.x - camX;

		if (enemyScreenX <= SCREEN_WIDTH) {
			enemy3.frameDelay++;
			if (enemy3.frameDelay >= 6) {
				enemy3.currentFrame = (enemy3.currentFrame + 1) % 4;
				enemy3.frameDelay = 0;
			}

			// Move enemy3 left
			enemy3.x -= 2;
		}
	}
}

void updateEnemy4() {
	if (!enemy4Alive) return;

	if (!enemy4Inverted) {
		// normal walking
		enemy4FrameDelay++;
		if (enemy4FrameDelay >= maxEnemy4FrameDelay) {
			enemy4Frame = (enemy4Frame + 1) % 4;
			enemy4FrameDelay = 0;
		}
		enemy4.x -= 2;  // move left
	}
	else {
		
		enemy4InvertedFrame++;
		if (enemy4InvertedFrame >= 3) enemy4InvertedFrame = 0; 

		
		enemy4InvertedTimer++;
		if (enemy4InvertedTimer >= enemy4InvertedDuration) {
			enemy4Alive = false;  // disappear after showing inverted images
		}
	}
}

void updateEnemy4b() {
	if (!enemy4bAlive) return;

	// Don't update if screen is locked (boss battle)
	if (screenLocked) return;

	if (!enemy4bInverted) {
		// Normal walking animation
		enemy4bFrameDelay++;
		if (enemy4bFrameDelay >= maxEnemy4FrameDelay) {
			enemy4bFrame = (enemy4bFrame + 1) % 4;
			enemy4bFrameDelay = 0;
		}

	
		if (enemy4bMovingRight) {
			enemy4b.x += 2;
			if (enemy4b.x >= enemy4bMaxX) {
				enemy4b.x = enemy4bMaxX;
				enemy4bMovingRight = false; // Change direction
			}
		}
		else {
			enemy4b.x += 2;
			if (enemy4b.x <= enemy4bMinX) {
				enemy4b.x = enemy4bMinX;
				enemy4bMovingRight = true; // Change direction
			}
		}
	}
	else {
		// Inverted (dying) animation
		enemy4bInvertedFrame++;
		if (enemy4bInvertedFrame >= 3) {
			enemy4bInvertedFrame = 0;  
		}

		// Count frames of inverted animation
		enemy4bInvertedTimer++;
		if (enemy4bInvertedTimer >= enemy4bInvertedDuration) {
			
			enemy4bAlive = false;
			enemy4bInverted = false;
			
		}
	}
}
void updateEnemy5() {
	if (!enemy5Alive || currentLevel != 2) return;

	//  flash effect after hit
	if (enemy5Flashed) {
		enemy5FlashTimer--;
		if (enemy5FlashTimer <= 0) {
			enemy5Flashed = false;
		}
		return; 
	}

	//  if Doraemon is near 
	int distanceToDoraemon = abs(enemy5.x - worldX);

	if ((distanceToDoraemon < 70 || worldX > enemy5.x) && !enemy5Attacking) {
		// Start attacking
		enemy5Attacking = true;
		enemy5AttackTimer = 0;
	}
	
	if (enemy5Attacking && distanceToDoraemon > 150) {
		enemy5Attacking = false;
		enemy5AttackTimer = 0;
		enemy5.facingRight = true;
		
	}

	if (enemy5Attacking) {
		
		enemy5AttackTimer++;
		if (enemy5AttackTimer >= ENEMY5_ATTACK_DURATION) {
			enemy5Attacking = false;
		}

		
		enemy5.frameDelay++;
		if (enemy5.frameDelay >= 8) {
			enemy5.currentFrame = (enemy5.currentFrame + 1) % 2;
			enemy5.frameDelay = 0;
		}
	}
	else {
		// Normal walking animation
		enemy5.frameDelay++;
		if (enemy5.frameDelay >= 10) {
			enemy5.currentFrame = (enemy5.currentFrame + 1) % 4; // 4 walk frames
			enemy5.frameDelay = 0;
			
		}
		
		if (enemy5.facingRight){
			enemy5.x += 2;
		}
		else{
			enemy5.x -= 2;  // move left
		}

	}

}
void updateEnemy6() {
	if (!enemy6Alive || currentLevel != 2) return;

	//  flash effect after hit
	if (enemy6Flashed) {
		enemy6FlashTimer--;
		if (enemy6FlashTimer <= 0) {
			enemy6Flashed = false;
		}
		return; 
	}

	//  if Doraemon is near 
	int distanceToDoraemon = abs(enemy6.x - worldX);

	if ((distanceToDoraemon < 50 || worldX > enemy6.x) && !enemy6Attacking) {
		// Start attacking
		enemy6Attacking = true;
		enemy6AttackTimer = 0;
	}
	// EXIT attack state if Doraemon moves too far away
	if (enemy6Attacking && distanceToDoraemon > 150) {
		enemy6Attacking = false;
		enemy6AttackTimer = 0;
		enemy6.facingRight = true;
	}

	if (enemy6Attacking) {
		// Handle attack animation
		enemy6AttackTimer++;
		if (enemy6AttackTimer >= ENEMY6_ATTACK_DURATION) {
			enemy6Attacking = false;
		}

		// Attack animation frame update - 4 attack frames
		enemy6.frameDelay++;
		if (enemy6.frameDelay >= 8) {
			enemy6.currentFrame = (enemy6.currentFrame + 1) % 4; // 4 attack frames
			enemy6.frameDelay = 0;
		}
	}
	else {
		// Normal walking animation - 4 walk frames
		enemy6.frameDelay++;
		if (enemy6.frameDelay >= 10) {
			enemy6.currentFrame = (enemy6.currentFrame + 1) % 4; // 4 walk frames
			enemy6.frameDelay = 0;
		}
		if (enemy6.facingRight){
			enemy6.x += 2;
		}
		else{
			enemy6.x -= 2;  // move left 
		}
		
	}
}
void updateEnemy7() {
	if (!enemy7Alive) return;

	// flash effect after hit
	if (enemy7Flashed) {
		enemy7FlashTimer--;
		if (enemy7FlashTimer <= 0) {
			enemy7Flashed = false;
		}
		return;
	}

	
	if (enemy7ThrowCooldown > 0) {
		enemy7ThrowCooldown--;
	}

	// Check if Doraemon is near 
	int distanceToDoraemon = abs(enemy7.x - worldX);


	if (distanceToDoraemon < 500 && !ballActive && enemy7ThrowCooldown <= 0) {
		
		ballActive = true;
		ballX = enemy7.x; // World X coordinate
		ballY = enemy7.y + 50; // World Y coordinate
		ballDirection = (worldX > enemy7.x) ? 1 : -1;
		enemy7ThrowCooldown = ENEMY7_THROW_COOLDOWN;
	}

	// Normal walking animation (always walking)
	enemy7.frameDelay++;
	if (enemy7.frameDelay >= 10) {
		enemy7.currentFrame = (enemy7.currentFrame + 1) % 5;
		enemy7.frameDelay = 0;
	}
	enemy7.x -= 2;  // move left

	
	enemy7.facingRight = (worldX > enemy7.x);
}
void updateProjection() {
	if (projectionActive) {
		projectionTimer--;
		if (projectionTimer <= 0) {
			projectionActive = false;
			lightWeaponVisible = false;
		}
	}
}
void updateBall() {
	if (!ballActive) return;

	// Deactivate ball if Doraemon has passed enemy7
	if (worldX > enemy7.x + 200) { 
		ballActive = false;
		return;
	}

	// Move the ball in WORLD coordinates
	ballX += ballSpeed * ballDirection;

	// Check if ball goes off screen 
	if (ballX < 0 || ballX > LEVEL_WIDTH * TILE_SIZE) {
		ballActive = false;
		return;
	}

	// Check collision with Doraemon 
	int ballScreenX = ballX - camX;
	int ballScreenY = ballY - camY;

	if (rectOverlap(ballScreenX, ballScreenY, BALL_SIZE, BALL_SIZE,
		doraemon.x, doraemon.y, 90, 100)) {
		ballActive = false;

		//  Doraemon blink and take damage
		if (!doraemon.isBlinking && invincibleTicks == 0) {
			doraemon.isBlinking = true;
			doraemon.blinkTimer = 0;
			doraemon.blinkCount = 0;

			currentHealth -= 0.3f;
			if (currentHealth < 0) currentHealth = 0;
			invincibleTicks = INVINCIBLE_MAX_TICKS;

			if (currentHealth <= 0) {
				gameState = STATE_GAME_OVER;
			}
		}
	}
}
void iUpdate() {
	updateCamera();
	updateLoadingState();
}
void updateAllEnemies() {
	updateEnemy1();
	updateEnemy2();
	updateEnemy3();
	updateEnemy4();
	updateEnemy4b();
	updateEnemy5();
	updateEnemy6();
	updateEnemy7(); 
	updateBall();
	updateEnemyAnimation();
    updateBossHitEffect();
     updateEnemySize();

	updateLevel2EnemyMovement();
	updateLevel2EnemyAnimation();
}
void updateTimer(){
	if (isFallingToDeath) {
		updateFallingDeath(); // Only update falling sequence
	}
	else {
		updateProjection();
		updateButtonDisplay();
		iUpdate();
		updatePhysics();
		updateStoryline();
		checkBossEncounter();
		checkBoss2Encounter();
	}
}



int main() {
	gameState = STATE_LOADING1;
	loadingTimer = 0;
	iSetTimer(16, updateTimer);
	iSetTimer(30, updateAllEnemies);
	iSetTimer(16, updateMusic);
	iSetTimer(6, updateLoadingState);

	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Doraemon Quest");
	initializeDoraemon();
	loadMenu();
	loadTiles();
	loadLevel(currentLevel);
	updateDragonFire();
	iStart();
	return 0;
}