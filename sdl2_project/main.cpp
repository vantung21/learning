#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

// Global constants for game settings
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 40;
const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;
const int UI_HEIGHT = 100;
const int DAY_DURATION_MS = 10000;
const int WILT_DAYS = 2; // Days after maturity to wilt
const int MAX_ENERGY = 10;

// Path for the save file
const std::string SAVE_FILE_PATH = "savegame.dat";

// --- Enums for game objects ---
enum TileType {
    GRASS,
    DIRT,
    PLANTED_CROP,
    HAS_ANIMAL
};

enum CropType {
    NO_CROP,
    WHEAT,
    CORN,
    TOMATO
};

enum AnimalType {
    NO_ANIMAL,
    COW,
    CHICKEN
};

// --- Crop Base Class (Inheritance & Polymorphism) ---
class Crop {
public:
    CropType cropType;
    int days_to_grow;
    int days_to_harvest;
    int harvest_value;
    int days_after_grown;
    
    // Virtual destructor is important for polymorphic classes
    virtual ~Crop() {}

    // Virtual methods for polymorphism
    virtual void updateGrowth() = 0;
    virtual bool isGrown() = 0;
    virtual bool isWilted() = 0;
    virtual SDL_Texture* getTexture() = 0;
    virtual std::string getProductName() = 0;
    virtual void saveState(std::ofstream& file) = 0;
    virtual void loadState(std::ifstream& file) = 0;
};

// --- WheatCrop Derived Class ---
class WheatCrop : public Crop {
private:
    SDL_Texture* texture_planted;
    SDL_Texture* texture_grown;
public:
    WheatCrop(SDL_Texture* planted, SDL_Texture* grown) {
        cropType = WHEAT;
        days_to_grow = 0;
        days_to_harvest = 2;
        harvest_value = 20;
        days_after_grown = 0;
        texture_planted = planted;
        texture_grown = grown;
    }

    ~WheatCrop() override {}

    void updateGrowth() override {
        if (!isGrown()) {
            days_to_grow++;
        } else if (!isWilted()) {
            days_after_grown++;
        }
    }

    bool isGrown() override {
        return days_to_grow >= days_to_harvest;
    }

    bool isWilted() override {
        return days_after_grown >= WILT_DAYS;
    }

    SDL_Texture* getTexture() override {
        if (isWilted()) {
            return texture_planted; // Use planted texture as wilted state for simplicity
        }
        if (isGrown()) {
            return texture_grown;
        }
        return texture_planted;
    }
    
    std::string getProductName() override {
        return "Lua";
    }

    void saveState(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&days_to_grow), sizeof(int));
        file.write(reinterpret_cast<const char*>(&days_after_grown), sizeof(int));
    }
    
    void loadState(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&days_to_grow), sizeof(int));
        file.read(reinterpret_cast<char*>(&days_after_grown), sizeof(int));
    }
};

// --- CornCrop Derived Class ---
class CornCrop : public Crop {
private:
    SDL_Texture* texture_planted;
    SDL_Texture* texture_grown;
public:
    CornCrop(SDL_Texture* planted, SDL_Texture* grown) {
        cropType = CORN;
        days_to_grow = 0;
        days_to_harvest = 3;
        harvest_value = 40;
        days_after_grown = 0;
        texture_planted = planted;
        texture_grown = grown;
    }
    
    ~CornCrop() override {}
    
    void updateGrowth() override {
        if (!isGrown()) {
            days_to_grow++;
        } else if (!isWilted()) {
            days_after_grown++;
        }
    }
    
    bool isGrown() override {
        return days_to_grow >= days_to_harvest;
    }

    bool isWilted() override {
        return days_after_grown >= WILT_DAYS;
    }
    
    SDL_Texture* getTexture() override {
        if (isWilted()) {
            return texture_planted; // Use planted texture as wilted state for simplicity
        }
        if (isGrown()) {
            return texture_grown;
        }
        return texture_planted;
    }
    
    std::string getProductName() override {
        return "Ngo";
    }

    void saveState(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&days_to_grow), sizeof(int));
        file.write(reinterpret_cast<const char*>(&days_after_grown), sizeof(int));
    }
    
    void loadState(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&days_to_grow), sizeof(int));
        file.read(reinterpret_cast<char*>(&days_after_grown), sizeof(int));
    }
};

// --- TomatoCrop Derived Class ---
class TomatoCrop : public Crop {
private:
    SDL_Texture* texture_planted;
    SDL_Texture* texture_grown;
public:
    TomatoCrop(SDL_Texture* planted, SDL_Texture* grown) {
        cropType = TOMATO;
        days_to_grow = 0;
        days_to_harvest = 4;
        harvest_value = 80;
        days_after_grown = 0;
        texture_planted = planted;
        texture_grown = grown;
    }
    
    ~TomatoCrop() override {}
    
    void updateGrowth() override {
        if (!isGrown()) {
            days_to_grow++;
        } else if (!isWilted()) {
            days_after_grown++;
        }
    }
    
    bool isGrown() override {
        return days_to_grow >= days_to_harvest;
    }

    bool isWilted() override {
        return days_after_grown >= WILT_DAYS;
    }
    
    SDL_Texture* getTexture() override {
        if (isWilted()) {
            return texture_planted; // Use planted texture as wilted state for simplicity
        }
        if (isGrown()) {
            return texture_grown;
        }
        return texture_planted;
    }
    
    std::string getProductName() override {
        return "CaChua";
    }

    void saveState(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&days_to_grow), sizeof(int));
        file.write(reinterpret_cast<const char*>(&days_after_grown), sizeof(int));
    }
    
    void loadState(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&days_to_grow), sizeof(int));
        file.read(reinterpret_cast<char*>(&days_after_grown), sizeof(int));
    }
};


// --- Animal Base Class (Inheritance & Polymorphism) ---
class Animal {
public:
    AnimalType animalType;
    int days_until_next_product;
    int days_since_fed;
    int food_cost_per_day;
    std::string product_name;
    int product_value;
    int product_interval;

    virtual ~Animal() {}
    
    virtual void update() = 0;
    virtual bool isReadyToHarvest() = 0;
    virtual bool needsFood() = 0;
    virtual void feed() = 0;
    virtual SDL_Texture* getTexture() = 0;
    virtual void saveState(std::ofstream& file) = 0;
    virtual void loadState(std::ifstream& file) = 0;
    virtual void reset() = 0;
};

// --- Cow Derived Class ---
class Cow : public Animal {
private:
    SDL_Texture* texture;
public:
    Cow(SDL_Texture* cow_texture) {
        animalType = COW;
        days_until_next_product = 0;
        days_since_fed = 0;
        food_cost_per_day = 2;
        product_name = "Sua";
        product_value = 50;
        product_interval = 3;
        texture = cow_texture;
    }
    
    ~Cow() override {}
    
    void update() override {
        days_since_fed++;
        if (days_since_fed >= 1 && days_until_next_product < product_interval) {
            days_until_next_product++;
        }
    }
    
    bool isReadyToHarvest() override {
        return days_until_next_product >= product_interval;
    }

    bool needsFood() override {
        return days_since_fed >= 1;
    }

    void feed() override {
        days_since_fed = 0;
    }
    
    SDL_Texture* getTexture() override {
        return texture;
    }
    
    void reset() override {
        days_until_next_product = 0;
    }
    
    void saveState(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&days_until_next_product), sizeof(int));
        file.write(reinterpret_cast<const char*>(&days_since_fed), sizeof(int));
    }
    
    void loadState(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&days_until_next_product), sizeof(int));
        file.read(reinterpret_cast<char*>(&days_since_fed), sizeof(int));
    }
};

// --- Chicken Derived Class ---
class Chicken : public Animal {
private:
    SDL_Texture* texture;
public:
    Chicken(SDL_Texture* chicken_texture) {
        animalType = CHICKEN;
        days_until_next_product = 0;
        days_since_fed = 0;
        food_cost_per_day = 1;
        product_name = "Trung";
        product_value = 25;
        product_interval = 2;
        texture = chicken_texture;
    }
    
    ~Chicken() override {}
    
    void update() override {
        days_since_fed++;
        if (days_since_fed >= 1 && days_until_next_product < product_interval) {
            days_until_next_product++;
        }
    }
    
    bool isReadyToHarvest() override {
        return days_until_next_product >= product_interval;
    }

    bool needsFood() override {
        return days_since_fed >= 1;
    }

    void feed() override {
        days_since_fed = 0;
    }
    
    SDL_Texture* getTexture() override {
        return texture;
    }
    
    void reset() override {
        days_until_next_product = 0;
    }
    
    void saveState(std::ofstream& file) override {
        file.write(reinterpret_cast<const char*>(&days_until_next_product), sizeof(int));
        file.write(reinterpret_cast<const char*>(&days_since_fed), sizeof(int));
    }
    
    void loadState(std::ifstream& file) override {
        file.read(reinterpret_cast<char*>(&days_until_next_product), sizeof(int));
        file.read(reinterpret_cast<char*>(&days_since_fed), sizeof(int));
    }
};

// --- Player Class ---
class Player {
public:
    int money;
    int level;
    int energy;
    std::map<std::string, int> storage;

    Player() : money(50), level(1), energy(MAX_ENERGY) {
        storage["Lua"] = 0;
        storage["Ngo"] = 0;
        storage["CaChua"] = 0;
        storage["Sua"] = 0;
        storage["Trung"] = 0;
        storage["ThucAnGiaSuc"] = 10;
        storage["HatLua"] = 5;
        storage["HatNgo"] = 0;
        storage["HatCaChua"] = 0;
        storage["Bo"] = 0;
        storage["Ga"] = 0;
    }
};

// --- Tile Class ---
class Tile {
public:
    TileType type;
    Crop* crop;
    Animal* animal;

    Tile() : type(GRASS), crop(nullptr), animal(nullptr) {}
    ~Tile() {
        delete crop;
        delete animal;
    }
};

// --- Game Class ---
class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Player player;
    std::vector<std::vector<Tile>> farm_map;
    int current_day;
    Uint32 last_day_update;
    bool isShopOpen;
    bool isRunning;

    int cameraX;
    int cameraY;
    bool isPanning;
    int mouseStartX, mouseStartY;

    // Textures - All textures are loaded once here for performance
    SDL_Texture* grassTexture;
    SDL_Texture* dirtTexture;
    SDL_Texture* wheatPlantedTexture;
    SDL_Texture* wheatGrownTexture;
    SDL_Texture* cornPlantedTexture;
    SDL_Texture* cornGrownTexture;
    SDL_Texture* tomatoPlantedTexture;
    SDL_Texture* tomatoGrownTexture;
    SDL_Texture* cowTexture;
    SDL_Texture* chickenTexture;
    
public:
    Game() : window(nullptr), renderer(nullptr), font(nullptr), current_day(1), last_day_update(0), cameraX(0), cameraY(0), isPanning(false), isShopOpen(false), isRunning(true) {
        farm_map.resize(MAP_HEIGHT, std::vector<Tile>(MAP_WIDTH));
    }

    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0 || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) || TTF_Init() < 0) {
            std::cerr << "Initialization failed!" << std::endl;
            return false;
        }

        // Get native display size for full-screen mode
        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
            std::cerr << "SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
            return false;
        }
        SCREEN_WIDTH = dm.w;
        SCREEN_HEIGHT = dm.h;

        window = SDL_CreateWindow("Farm Manager PBL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!window || !renderer) {
            std::cerr << "Window or Renderer creation failed!" << std::endl;
            return false;
        }

        // Load all textures ONCE at the start for better performance
        grassTexture = IMG_LoadTexture(renderer, "grass.png");
        dirtTexture = IMG_LoadTexture(renderer, "dirt.png");
        wheatPlantedTexture = IMG_LoadTexture(renderer, "planted.png");
        wheatGrownTexture = IMG_LoadTexture(renderer, "grown.png");
        cornPlantedTexture = IMG_LoadTexture(renderer, "corn_planted.png");
        cornGrownTexture = IMG_LoadTexture(renderer, "corn_grown.png");
        tomatoPlantedTexture = IMG_LoadTexture(renderer, "tomato_planted.png");
        tomatoGrownTexture = IMG_LoadTexture(renderer, "tomato_grown.png");
        cowTexture = IMG_LoadTexture(renderer, "cow.png");
        chickenTexture = IMG_LoadTexture(renderer, "chicken.png");
        font = TTF_OpenFont("font.ttf", 24);

        if (!grassTexture || !dirtTexture || !wheatPlantedTexture || !wheatGrownTexture || !cornPlantedTexture || !cornGrownTexture || !tomatoPlantedTexture || !tomatoGrownTexture || !cowTexture || !chickenTexture || !font) {
            // Display an error message if any file is missing
            SDL_Color red = {255, 0, 0, 255};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            renderText("Loi: Thieu file hinh anh hoac font!", 100, 200, red);
            renderText("Vui long dat cac file sau vao cung thu muc voi file chuong trinh da bien dich:", 100, 250, red);
            renderText("grass.png, dirt.png, planted.png, grown.png, corn_planted.png, corn_grown.png, tomato_planted.png, tomato_grown.png, cow.png, chicken.png, font.ttf", 100, 280, red);
            SDL_RenderPresent(renderer);
            SDL_Delay(5000); // Wait 5 seconds for the user to read the message
            close(); // Clean up resources
            return false;
        }
        
        loadGame();
        last_day_update = SDL_GetTicks();
        return true;
    }

    void run() {
        while (isRunning) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    isRunning = false;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    handleMouseClick(event);
                }
                if (event.type == SDL_MOUSEBUTTONUP) {
                    handleMouseUp(event);
                }
                if (event.type == SDL_MOUSEMOTION) {
                    handleMouseMotion(event);
                }
            }
            update();
            render();
        }
        saveGame();
    }

    void close() {
        if (grassTexture) SDL_DestroyTexture(grassTexture);
        if (dirtTexture) SDL_DestroyTexture(dirtTexture);
        if (wheatPlantedTexture) SDL_DestroyTexture(wheatPlantedTexture);
        if (wheatGrownTexture) SDL_DestroyTexture(wheatGrownTexture);
        if (cornPlantedTexture) SDL_DestroyTexture(cornPlantedTexture);
        if (cornGrownTexture) SDL_DestroyTexture(cornGrownTexture);
        if (tomatoPlantedTexture) SDL_DestroyTexture(tomatoPlantedTexture);
        if (tomatoGrownTexture) SDL_DestroyTexture(tomatoGrownTexture);
        if (cowTexture) SDL_DestroyTexture(cowTexture);
        if (chickenTexture) SDL_DestroyTexture(chickenTexture);
        if (font) TTF_CloseFont(font);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

private:
    void renderText(const std::string& text, int x, int y, SDL_Color color) {
        if (!font) return;
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!textSurface) return;
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            SDL_FreeSurface(textSurface);
            return;
        }
        SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    
    void saveGame() {
        std::ofstream file(SAVE_FILE_PATH, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Could not open save file for writing!" << std::endl;
            return;
        }

        file.write(reinterpret_cast<const char*>(&player.money), sizeof(int));
        if (!file) { std::cerr << "Error writing player money!" << std::endl; file.close(); return; }
        file.write(reinterpret_cast<const char*>(&player.level), sizeof(int));
        if (!file) { std::cerr << "Error writing player level!" << std::endl; file.close(); return; }
        file.write(reinterpret_cast<const char*>(&player.energy), sizeof(int));
        if (!file) { std::cerr << "Error writing player energy!" << std::endl; file.close(); return; }
        file.write(reinterpret_cast<const char*>(&current_day), sizeof(int));
        if (!file) { std::cerr << "Error writing current day!" << std::endl; file.close(); return; }

        size_t storage_size = player.storage.size();
        file.write(reinterpret_cast<const char*>(&storage_size), sizeof(size_t));
        if (!file) { std::cerr << "Error writing storage size!" << std::endl; file.close(); return; }
        for (const auto& pair : player.storage) {
            size_t key_size = pair.first.size();
            file.write(reinterpret_cast<const char*>(&key_size), sizeof(size_t));
            if (!file) { std::cerr << "Error writing storage key size!" << std::endl; file.close(); return; }
            file.write(pair.first.c_str(), key_size);
            if (!file) { std::cerr << "Error writing storage key!" << std::endl; file.close(); return; }
            file.write(reinterpret_cast<const char*>(&pair.second), sizeof(int));
            if (!file) { std::cerr << "Error writing storage value!" << std::endl; file.close(); return; }
        }

        for (const auto& row : farm_map) {
            for (const auto& tile : row) {
                file.write(reinterpret_cast<const char*>(&tile.type), sizeof(TileType));
                if (!file) { std::cerr << "Error writing tile type!" << std::endl; file.close(); return; }
                if (tile.type == PLANTED_CROP && tile.crop) {
                    file.write(reinterpret_cast<const char*>(&tile.crop->cropType), sizeof(CropType));
                    if (!file) { std::cerr << "Error writing crop type!" << std::endl; file.close(); return; }
                    tile.crop->saveState(file);
                    if (!file) { std::cerr << "Error writing crop state!" << std::endl; file.close(); return; }
                } else if (tile.type == HAS_ANIMAL && tile.animal) {
                    file.write(reinterpret_cast<const char*>(&tile.animal->animalType), sizeof(AnimalType));
                    if (!file) { std::cerr << "Error writing animal type!" << std::endl; file.close(); return; }
                    tile.animal->saveState(file);
                    if (!file) { std::cerr << "Error writing animal state!" << std::endl; file.close(); return; }
                }
            }
        }
        file.close();
        std::cout << "Game saved successfully!" << std::endl;
    }

    void loadGame() {
        std::ifstream file(SAVE_FILE_PATH, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&player.money), sizeof(int));
            if (!file) { std::cerr << "Error reading player money!" << std::endl; file.close(); return; }
            file.read(reinterpret_cast<char*>(&player.level), sizeof(int));
            if (!file) { std::cerr << "Error reading player level!" << std::endl; file.close(); return; }
            file.read(reinterpret_cast<char*>(&player.energy), sizeof(int));
            if (!file) { std::cerr << "Error reading player energy!" << std::endl; file.close(); return; }
            file.read(reinterpret_cast<char*>(&current_day), sizeof(int));
            if (!file) { std::cerr << "Error reading current day!" << std::endl; file.close(); return; }

            size_t storage_size;
            file.read(reinterpret_cast<char*>(&storage_size), sizeof(size_t));
            if (!file) { std::cerr << "Error reading storage size!" << std::endl; file.close(); return; }
            player.storage.clear();
            for (size_t i = 0; i < storage_size; ++i) {
                size_t key_size;
                file.read(reinterpret_cast<char*>(&key_size), sizeof(size_t));
                if (!file) { std::cerr << "Error reading storage key size!" << std::endl; file.close(); return; }
                std::string key(key_size, '\0');
                file.read(&key[0], key_size);
                if (!file) { std::cerr << "Error reading storage key!" << std::endl; file.close(); return; }
                int value;
                file.read(reinterpret_cast<char*>(&value), sizeof(int));
                if (!file) { std::cerr << "Error reading storage value!" << std::endl; file.close(); return; }
                player.storage[key] = value;
            }

            for (auto& row : farm_map) {
                for (auto& tile : row) {
                    delete tile.crop;
                    tile.crop = nullptr;
                    delete tile.animal;
                    tile.animal = nullptr;

                    file.read(reinterpret_cast<char*>(&tile.type), sizeof(TileType));
                    if (!file) { std::cerr << "Error reading tile type!" << std::endl; file.close(); return; }
                    if (tile.type == PLANTED_CROP) {
                        CropType cropType;
                        file.read(reinterpret_cast<char*>(&cropType), sizeof(CropType));
                        if (!file) { std::cerr << "Error reading crop type!" << std::endl; file.close(); return; }
                        if (cropType == WHEAT) {
                            tile.crop = new WheatCrop(wheatPlantedTexture, wheatGrownTexture);
                        } else if (cropType == CORN) {
                            tile.crop = new CornCrop(cornPlantedTexture, cornGrownTexture);
                        } else if (cropType == TOMATO) {
                            tile.crop = new TomatoCrop(tomatoPlantedTexture, tomatoGrownTexture);
                        }
                        if (tile.crop) {
                            tile.crop->loadState(file);
                            if (!file) { std::cerr << "Error reading crop state!" << std::endl; file.close(); return; }
                        } else {
                            tile.type = GRASS; // Handle invalid crop type
                        }
                    } else if (tile.type == HAS_ANIMAL) {
                        AnimalType animalType;
                        file.read(reinterpret_cast<char*>(&animalType), sizeof(AnimalType));
                        if (!file) { std::cerr << "Error reading animal type!" << std::endl; file.close(); return; }
                        if (animalType == COW) {
                            tile.animal = new Cow(cowTexture);
                        } else if (animalType == CHICKEN) {
                            tile.animal = new Chicken(chickenTexture);
                        }
                        if (tile.animal) {
                            tile.animal->loadState(file);
                            if (!file) { std::cerr << "Error reading animal state!" << std::endl; file.close(); return; }
                        } else {
                            tile.type = GRASS; // Handle invalid animal type
                        }
                    }
                }
            }
            file.close();
            std::cout << "Game loaded successfully!" << std::endl;
        } else {
            std::cout << "No save file found. Starting new game." << std::endl;
        }
    }

    void handleMouseClick(SDL_Event& event) {
        if (event.button.button == SDL_BUTTON_RIGHT) {
            isPanning = true;
            SDL_GetMouseState(&mouseStartX, &mouseStartY);
            return;
        }

        if (event.button.button == SDL_BUTTON_LEFT) {
            // Check for UI clicks first
            if (event.button.y >= SCREEN_HEIGHT - UI_HEIGHT) {
                // Exit button
                SDL_Rect exitButton = {SCREEN_WIDTH - 110, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                if (event.button.x >= exitButton.x && event.button.x < exitButton.x + exitButton.w &&
                    event.button.y >= exitButton.y && event.button.y < exitButton.y + exitButton.h) {
                    isRunning = false;
                    return;
                }
                
                if (isShopOpen) {
                    // Close shop button
                    SDL_Rect closeButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                    if (event.button.x >= closeButton.x && event.button.x < closeButton.x + closeButton.w &&
                        event.button.y >= closeButton.y && event.button.y < closeButton.y + closeButton.h) {
                        isShopOpen = false;
                        return;
                    }
                    
                    // Check if buy wheat seeds button is clicked
                    SDL_Rect wheatBuyButton = {SCREEN_WIDTH - 440, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                    if (event.button.x >= wheatBuyButton.x && event.button.x < wheatBuyButton.x + wheatBuyButton.w &&
                        event.button.y >= wheatBuyButton.y && event.button.y < wheatBuyButton.y + wheatBuyButton.h) {
                        if (player.money >= 10) {
                            player.money -= 10;
                            player.storage["HatLua"] += 5;
                        }
                        return;
                    }
                    
                    // Check if buy corn seeds button is clicked
                    SDL_Rect cornBuyButton = {SCREEN_WIDTH - 440, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
                    if (event.button.x >= cornBuyButton.x && event.button.x < cornBuyButton.x + cornBuyButton.w &&
                        event.button.y >= cornBuyButton.y && event.button.y < cornBuyButton.y + cornBuyButton.h) {
                        if (player.money >= 20) {
                            player.money -= 20;
                            player.storage["HatNgo"] += 3;
                        }
                        return;
                    }

                    // Check if buy tomato seeds button is clicked
                    SDL_Rect tomatoBuyButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
                    if (event.button.x >= tomatoBuyButton.x && event.button.x < tomatoBuyButton.x + tomatoBuyButton.w &&
                        event.button.y >= tomatoBuyButton.y && event.button.y < tomatoBuyButton.y + tomatoBuyButton.h) {
                        if (player.money >= 40) {
                            player.money -= 40;
                            player.storage["HatCaChua"] += 3;
                        }
                        return;
                    }

                    // Check if buy cow button is clicked
                    SDL_Rect cowBuyButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
                    if (event.button.x >= cowBuyButton.x && event.button.x < cowBuyButton.x + cowBuyButton.w &&
                        event.button.y >= cowBuyButton.y && event.button.y < cowBuyButton.y + cowBuyButton.h) {
                        if (player.money >= 100) {
                            player.money -= 100;
                            player.storage["Bo"]++;
                        }
                        return;
                    }

                    // Check if buy chicken button is clicked
                    SDL_Rect chickenBuyButton = {SCREEN_WIDTH - 110, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
                    if (event.button.x >= chickenBuyButton.x && event.button.x < chickenBuyButton.x + chickenBuyButton.w &&
                        event.button.y >= chickenBuyButton.y && event.button.y < chickenBuyButton.y + chickenBuyButton.h) {
                        if (player.money >= 50) {
                            player.money -= 50;
                            player.storage["Ga"]++;
                        }
                        return;
                    }
                    
                    // Check if buy food button is clicked
                    SDL_Rect foodBuyButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                    if (event.button.x >= foodBuyButton.x && event.button.x < foodBuyButton.x + foodBuyButton.w &&
                        event.button.y >= foodBuyButton.y && event.button.y < foodBuyButton.y + foodBuyButton.h) {
                        if (player.money >= 5) {
                            player.money -= 5;
                            player.storage["ThucAnGiaSuc"] += 10;
                        }
                        return;
                    }

                } else { // Shop is NOT open
                    // Sell button
                    SDL_Rect sellButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                    if (event.button.x >= sellButton.x && event.button.x < sellButton.x + sellButton.w &&
                       event.button.y >= sellButton.y && event.button.y < sellButton.y + sellButton.h) {
                       // Sell all products for a simplified game loop
                       player.money += player.storage["Lua"] * 20;
                       player.storage["Lua"] = 0;
                       player.money += player.storage["Ngo"] * 40;
                       player.storage["Ngo"] = 0;
                       player.money += player.storage["CaChua"] * 80;
                       player.storage["CaChua"] = 0;
                       player.money += player.storage["Sua"] * 50;
                       player.storage["Sua"] = 0;
                       player.money += player.storage["Trung"] * 25;
                       player.storage["Trung"] = 0;
                       return;
                   }
                   
                    // Shop button
                    SDL_Rect shopButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
                    if (event.button.x >= shopButton.x && event.button.x < shopButton.x + shopButton.w &&
                        event.button.y >= shopButton.y && event.button.y < shopButton.y + shopButton.h) {
                        isShopOpen = true;
                        return;
                    }

                }
            } else if (!isShopOpen) { // Handle map clicks only if shop is not open and click is not in UI
                int tileX = (event.button.x + cameraX) / TILE_SIZE;
                int tileY = (event.button.y + cameraY) / TILE_SIZE;
                
                if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
                    Tile& clicked_tile = farm_map[tileY][tileX];
                    
                    if (clicked_tile.type == GRASS) {
                        if (player.energy > 0 && player.money >= 10) {
                            clicked_tile.type = DIRT;
                            player.money -= 10;
                            player.energy--;
                        }
                    } else if (clicked_tile.type == DIRT) {
                        if (player.energy > 0) {
                            if (player.storage["HatLua"] >= 1) {
                                clicked_tile.type = PLANTED_CROP;
                                clicked_tile.crop = new WheatCrop(wheatPlantedTexture, wheatGrownTexture);
                                player.storage["HatLua"] -= 1;
                                player.energy--;
                            } else if (player.storage["HatNgo"] >= 1) {
                                clicked_tile.type = PLANTED_CROP;
                                clicked_tile.crop = new CornCrop(cornPlantedTexture, cornGrownTexture);
                                player.storage["HatNgo"] -= 1;
                                player.energy--;
                            } else if (player.storage["HatCaChua"] >= 1) {
                                clicked_tile.type = PLANTED_CROP;
                                clicked_tile.crop = new TomatoCrop(tomatoPlantedTexture, tomatoGrownTexture);
                                player.storage["HatCaChua"] -= 1;
                                player.energy--;
                            } else if (player.storage["Bo"] >= 1) {
                                clicked_tile.type = HAS_ANIMAL;
                                clicked_tile.animal = new Cow(cowTexture);
                                player.storage["Bo"]--;
                                player.energy--;
                            } else if (player.storage["Ga"] >= 1) {
                                clicked_tile.type = HAS_ANIMAL;
                                clicked_tile.animal = new Chicken(chickenTexture);
                                player.storage["Ga"]--;
                                player.energy--;
                            }
                        }
                    } else if (clicked_tile.type == PLANTED_CROP && clicked_tile.crop && clicked_tile.crop->isGrown()) {
                        if (clicked_tile.crop->isWilted()) {
                            if (player.energy > 0) {
                                delete clicked_tile.crop;
                                clicked_tile.crop = nullptr;
                                clicked_tile.type = DIRT;
                                player.energy--;
                            }
                        } else if (player.energy > 0) {
                            player.storage[clicked_tile.crop->getProductName()]++;
                            delete clicked_tile.crop;
                            clicked_tile.crop = nullptr;
                            clicked_tile.type = DIRT;
                            player.energy--;
                        }
                    } else if (clicked_tile.type == HAS_ANIMAL && clicked_tile.animal) {
                        if (clicked_tile.animal->needsFood() && player.storage["ThucAnGiaSuc"] > 0 && player.energy > 0) {
                            clicked_tile.animal->feed();
                            player.storage["ThucAnGiaSuc"]--;
                            player.energy--;
                        } else if (clicked_tile.animal->isReadyToHarvest() && player.energy > 0) {
                            player.storage[clicked_tile.animal->product_name]++;
                            clicked_tile.animal->reset();
                            player.energy--;
                        }
                    }
                }
            }
        }
    }
    
    void handleMouseUp(SDL_Event& event) {
        if (event.button.button == SDL_BUTTON_RIGHT) {
            isPanning = false;
        }
    }
    
    void handleMouseMotion(SDL_Event& event) {
        if (isPanning) {
            int currentX, currentY;
            SDL_GetMouseState(&currentX, &currentY);
            
            cameraX -= (currentX - mouseStartX);
            cameraY -= (currentY - mouseStartY);
            
            if (cameraX < 0) cameraX = 0;
            if (cameraY < 0) cameraY = 0;
            if (cameraX > (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH) cameraX = (MAP_WIDTH * TILE_SIZE) - SCREEN_WIDTH;
            if (cameraY > (MAP_HEIGHT * TILE_SIZE) - (SCREEN_HEIGHT - UI_HEIGHT)) cameraY = (MAP_HEIGHT * TILE_SIZE) - (SCREEN_HEIGHT - UI_HEIGHT);
            
            mouseStartX = currentX;
            mouseStartY = currentY;
        }
    }

    void update() {
        if (SDL_GetTicks() - last_day_update >= DAY_DURATION_MS) {
            current_day++;
            last_day_update = SDL_GetTicks();
            player.energy = MAX_ENERGY;
            
            for (int y = 0; y < MAP_HEIGHT; ++y) {
                for (int x = 0; x < MAP_WIDTH; ++x) {
                    Tile& currentTile = farm_map[y][x];
                    if (currentTile.type == PLANTED_CROP && currentTile.crop) {
                        currentTile.crop->updateGrowth();
                    } else if (currentTile.type == HAS_ANIMAL && currentTile.animal) {
                        currentTile.animal->update();
                    }
                }
            }
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Calculate visible tile range to optimize rendering
        int startX = cameraX / TILE_SIZE;
        int startY = cameraY / TILE_SIZE;
        int endX = startX + (SCREEN_WIDTH / TILE_SIZE) + 2; // Add a buffer
        int endY = startY + ((SCREEN_HEIGHT - UI_HEIGHT) / TILE_SIZE) + 2;

        if (endX > MAP_WIDTH) endX = MAP_WIDTH;
        if (endY > MAP_HEIGHT) endY = MAP_HEIGHT;

        for (int y = startY; y < endY; ++y) {
            for (int x = startX; x < endX; ++x) {
                SDL_Rect tileRect = {x * TILE_SIZE - cameraX, y * TILE_SIZE - cameraY, TILE_SIZE, TILE_SIZE};
                
                SDL_Texture* currentTexture = nullptr;
                Tile& currentTile = farm_map[y][x];
                
                switch (currentTile.type) {
                    case GRASS: currentTexture = grassTexture; break;
                    case DIRT: currentTexture = dirtTexture; break;
                    case PLANTED_CROP:
                        if (currentTile.crop) {
                            currentTexture = currentTile.crop->getTexture();
                        }
                        break;
                    case HAS_ANIMAL:
                        if (currentTile.animal) {
                            currentTexture = currentTile.animal->getTexture();
                        }
                        break;
                }
                if (currentTexture) {
                    SDL_RenderCopy(renderer, currentTexture, nullptr, &tileRect);
                }
            }
        }

        // Render UI
        SDL_Rect uiRect = {0, SCREEN_HEIGHT - UI_HEIGHT, SCREEN_WIDTH, UI_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &uiRect);
        
        SDL_Color textColor = {255, 255, 255, 255};
        renderText("Tien: " + std::to_string(player.money), 10, SCREEN_HEIGHT - UI_HEIGHT + 5, textColor);
        renderText("Cap do: " + std::to_string(player.level), 10, SCREEN_HEIGHT - UI_HEIGHT + 30, textColor);
        renderText("Nang luong: " + std::to_string(player.energy) + "/" + std::to_string(MAX_ENERGY), 10, SCREEN_HEIGHT - UI_HEIGHT + 55, textColor);
        renderText("Ngay: " + std::to_string(current_day), 10, SCREEN_HEIGHT - UI_HEIGHT + 80, textColor);
        
        // Render Storage
        renderText("Kho chua:", 250, SCREEN_HEIGHT - UI_HEIGHT + 5, textColor);
        renderText("Hat Lua: " + std::to_string(player.storage["HatLua"]), 250, SCREEN_HEIGHT - UI_HEIGHT + 30, textColor);
        renderText("Hat Ngo: " + std::to_string(player.storage["HatNgo"]), 250, SCREEN_HEIGHT - UI_HEIGHT + 50, textColor);
        renderText("Hat Ca chua: " + std::to_string(player.storage["HatCaChua"]), 250, SCREEN_HEIGHT - UI_HEIGHT + 70, textColor);
        renderText("Thuc an: " + std::to_string(player.storage["ThucAnGiaSuc"]), 380, SCREEN_HEIGHT - UI_HEIGHT + 30, textColor);
        renderText("Bo: " + std::to_string(player.storage["Bo"]), 380, SCREEN_HEIGHT - UI_HEIGHT + 50, textColor);
        renderText("Ga: " + std::to_string(player.storage["Ga"]), 380, SCREEN_HEIGHT - UI_HEIGHT + 70, textColor);
        renderText("Lua: " + std::to_string(player.storage["Lua"]), 500, SCREEN_HEIGHT - UI_HEIGHT + 30, textColor);
        renderText("Ngo: " + std::to_string(player.storage["Ngo"]), 500, SCREEN_HEIGHT - UI_HEIGHT + 50, textColor);
        renderText("Ca chua: " + std::to_string(player.storage["CaChua"]), 500, SCREEN_HEIGHT - UI_HEIGHT + 70, textColor);
        renderText("Sua: " + std::to_string(player.storage["Sua"]), 600, SCREEN_HEIGHT - UI_HEIGHT + 30, textColor);
        renderText("Trung: " + std::to_string(player.storage["Trung"]), 600, SCREEN_HEIGHT - UI_HEIGHT + 50, textColor);
        
        // Render permanent buttons
        SDL_Rect exitButton = {SCREEN_WIDTH - 110, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderFillRect(renderer, &exitButton);
        renderText("Thoat", exitButton.x + 5, exitButton.y + 10, {0, 0, 0, 255});
        
        if (!isShopOpen) {
            SDL_Rect sellButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
            SDL_RenderFillRect(renderer, &sellButton);
            renderText("Ban het", sellButton.x + 5, sellButton.y + 10, {0, 0, 0, 255});
            
            SDL_Rect shopButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
            SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
            SDL_RenderFillRect(renderer, &shopButton);
            renderText("Cua hang", shopButton.x + 5, shopButton.y + 10, {0, 0, 0, 255});

        } else {
            // Render shop items
            SDL_Rect closeButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
            SDL_RenderFillRect(renderer, &closeButton);
            renderText("Dong", closeButton.x + 5, closeButton.y + 10, {0, 0, 0, 255});

            // Buy Wheat Seeds
            SDL_Rect wheatBuyButton = {SCREEN_WIDTH - 440, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
            SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
            SDL_RenderFillRect(renderer, &wheatBuyButton);
            renderText("Mua Lua", wheatBuyButton.x + 5, wheatBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(10)", wheatBuyButton.x + 30, wheatBuyButton.y + 20, {0, 0, 0, 255});
            
            // Buy Corn Seeds
            SDL_Rect cornBuyButton = {SCREEN_WIDTH - 440, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
            SDL_SetRenderDrawColor(renderer, 100, 150, 200, 255);
            SDL_RenderFillRect(renderer, &cornBuyButton);
            renderText("Mua Ngo", cornBuyButton.x + 5, cornBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(20)", cornBuyButton.x + 30, cornBuyButton.y + 20, {0, 0, 0, 255});

            // Buy Tomato Seeds
            SDL_Rect tomatoBuyButton = {SCREEN_WIDTH - 330, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
            SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
            SDL_RenderFillRect(renderer, &tomatoBuyButton);
            renderText("Mua Ca Chua", tomatoBuyButton.x + 5, tomatoBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(40)", tomatoBuyButton.x + 30, tomatoBuyButton.y + 20, {0, 0, 0, 255});

            // Buy Cow
            SDL_Rect cowBuyButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
            SDL_SetRenderDrawColor(renderer, 200, 150, 100, 255);
            SDL_RenderFillRect(renderer, &cowBuyButton);
            renderText("Mua Bo", cowBuyButton.x + 5, cowBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(100)", cowBuyButton.x + 25, cowBuyButton.y + 20, {0, 0, 0, 255});

            // Buy Chicken
            SDL_Rect chickenBuyButton = {SCREEN_WIDTH - 110, SCREEN_HEIGHT - UI_HEIGHT + 55, 100, 40};
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
            SDL_RenderFillRect(renderer, &chickenBuyButton);
            renderText("Mua Ga", chickenBuyButton.x + 5, chickenBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(50)", chickenBuyButton.x + 30, chickenBuyButton.y + 20, {0, 0, 0, 255});
            
            // Buy Food
            SDL_Rect foodBuyButton = {SCREEN_WIDTH - 220, SCREEN_HEIGHT - UI_HEIGHT + 10, 100, 40};
            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
            SDL_RenderFillRect(renderer, &foodBuyButton);
            renderText("Mua Thuc An", foodBuyButton.x + 5, foodBuyButton.y + 5, {0, 0, 0, 255});
            renderText("(5)", foodBuyButton.x + 30, foodBuyButton.y + 20, {0, 0, 0, 255});
        }
        
        SDL_RenderPresent(renderer);
    }
};

int main(int argc, char* argv[]) {
    Game farmGame;

    if (!farmGame.init()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    farmGame.run();
    farmGame.close();

    return 0;
}