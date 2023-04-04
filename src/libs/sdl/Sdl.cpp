/*
** EPITECH PROJECT, 2023
** Epitech_Arcade
** File description:
** Sdl
*/

#include "sdl/Sdl.hpp"
#include <algorithm>
#include <iostream>
#include "XDisplay.hpp"
#include <set>

extern "C" void *createDisplay()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("Error: SDL2: Failed to init SDL.");
    if (TTF_Init() < 0)
        throw std::runtime_error("Error: SDL2: Failed to init SDL_ttf.");
    return new Arcade::Graphics::Sdl::Sdl();
}

extern "C" void deleteDisplay(void *display)
{
    delete reinterpret_cast<Arcade::Graphics::Sdl::Sdl *>(display);
    Arcade::Graphics::Sdl::Sdl::unloadTextures();
    TTF_Quit();
    SDL_Quit();
}

std::map<std::string, std::unique_ptr<Arcade::Graphics::Sdl::Texture>> Arcade::Graphics::Sdl::Sdl::_textures = {};
const std::map<int, Arcade::Key> Arcade::Graphics::Sdl::Sdl::_keyMap = {
        {SDLK_UP, Arcade::Key::Up},
        {SDLK_DOWN, Arcade::Key::Down},
        {SDLK_LEFT, Arcade::Key::Left},
        {SDLK_RIGHT, Arcade::Key::Right},
        {SDLK_RETURN, Arcade::Key::Enter},
        {SDLK_KP_ENTER, Arcade::Key::Enter},
        {SDLK_SPACE, Arcade::Key::Space},
        {SDLK_a, Arcade::Key::A},
        {SDLK_b, Arcade::Key::B},
        {SDLK_c, Arcade::Key::C},
        {SDLK_d, Arcade::Key::D},
        {SDLK_e, Arcade::Key::E},
        {SDLK_f, Arcade::Key::F},
        {SDLK_g, Arcade::Key::G},
        {SDLK_h, Arcade::Key::H},
        {SDLK_i, Arcade::Key::I},
        {SDLK_j, Arcade::Key::J},
        {SDLK_k, Arcade::Key::K},
        {SDLK_l, Arcade::Key::L},
        {SDLK_m, Arcade::Key::M},
        {SDLK_n, Arcade::Key::N},
        {SDLK_o, Arcade::Key::O},
        {SDLK_p, Arcade::Key::P},
        {SDLK_q, Arcade::Key::Q},
        {SDLK_r, Arcade::Key::R},
        {SDLK_s, Arcade::Key::S},
        {SDLK_t, Arcade::Key::T},
        {SDLK_u, Arcade::Key::U},
        {SDLK_v, Arcade::Key::V},
        {SDLK_w, Arcade::Key::W},
        {SDLK_x, Arcade::Key::X},
        {SDLK_y, Arcade::Key::Y},
        {SDLK_z, Arcade::Key::Z},
        {SDLK_0, Arcade::Key::Num0},
        {SDLK_1, Arcade::Key::Num1},
        {SDLK_2, Arcade::Key::Num2},
        {SDLK_3, Arcade::Key::Num3},
        {SDLK_4, Arcade::Key::Num4},
        {SDLK_5, Arcade::Key::Num5},
        {SDLK_6, Arcade::Key::Num6},
        {SDLK_7, Arcade::Key::Num7},
        {SDLK_8, Arcade::Key::Num8},
        {SDLK_9, Arcade::Key::Num9},
        {SDLK_ESCAPE, Arcade::Key::Escape},
        {SDLK_F1, Arcade::Key::F1},
        {SDLK_F2, Arcade::Key::F2},
        {SDLK_F3, Arcade::Key::F3},
        {SDLK_F4, Arcade::Key::F4},
        {SDLK_F5, Arcade::Key::F5},
        {SDLK_F6, Arcade::Key::F6},
        {SDLK_F7, Arcade::Key::F7},
        {SDLK_F8, Arcade::Key::F8},
        {SDLK_F9, Arcade::Key::F9},
        {SDLK_F10, Arcade::Key::F10},
        {SDLK_F11, Arcade::Key::F11},
        {SDLK_F12, Arcade::Key::F12},
        {SDLK_F13, Arcade::Key::F13},
        {SDLK_F14, Arcade::Key::F14},
        {SDLK_F15, Arcade::Key::F15},
        {SDLK_BACKSPACE, Arcade::Key::Backspace},
        {SDLK_LCTRL, Arcade::Key::LControl},
        {SDLK_RCTRL, Arcade::Key::RControl},
};

Arcade::Graphics::Sdl::Sdl::Sdl():
        _window{1280, 832},
        _globalFont("assets/arial.ttf", 20),
        _boldGlobalFont("assets/arial.ttf", 25, true),
        _gameOverFont("assets/arial.ttf", 40, true),
        _menuBackground()
{
    _menuBackgroundTexture = std::move(std::make_unique<Texture>("assets/menubg.png", _window.getRenderer()));
    _menuBackground.setTexture(*_menuBackgroundTexture);

    // Set titles
    _graphTitle = std::make_unique<Text>(_window.getRenderer(),
                                         &_boldGlobalFont,
                                         "Graphical libraries",
                                         SDL_Color{255, 255, 255, 255});
    _gameTitle = std::make_unique<Text>(_window.getRenderer(),
                                        &_boldGlobalFont,
                                        "Games",
                                        SDL_Color{255, 255, 255, 255});
    _controlsTitle = std::make_unique<Text>(_window.getRenderer(),
                                            &_boldGlobalFont,
                                            "Controls",
                                            SDL_Color{255, 255, 255, 255});
    _scoreText = std::make_unique<Text>(_window.getRenderer(),
                                            &_boldGlobalFont,
                                            "Score",
                                            SDL_Color{255, 255, 255, 255});
    _gameOverText = std::make_unique<Text>(_window.getRenderer(),
                                            &_gameOverFont,
                                            "GAME OVER",
                                            SDL_Color{255, 0, 0, 255});
    _graphTitle->setPosition({537, 317});
    _gameTitle->setPosition({970, 317});
    _controlsTitle->setPosition({190, 317});
}

Arcade::Graphics::Sdl::Sdl::~Sdl() = default;

void Arcade::Graphics::Sdl::Sdl::renderMenu(const std::vector<std::string> &games, const std::vector<std::string> &graphics,
                                            int selectedGame, int selectedGraph,
                                            const ControlMap &controls, const std::string &username, const std::string &bestScoreUsername, int bestScore)
{
    if (graphics != _graphNames || games != _gameNames || controls != _controls)
        createMenus(games, graphics, controls);

    _window.clear();

    _window.draw(_menuBackground);
    drawMenuTitlesAndBg();
    drawMenuItems(selectedGame, selectedGraph);

    // Draw username
    Text usernameText(_window.getRenderer(), &_globalFont, "Username: " + username,
                      SDL_Color{255, 255, 255, 255});
    usernameText.setPosition({10, 10});
    _window.draw(usernameText);

    // Draw best score
    Text bestScoreText(_window.getRenderer(), &_globalFont, "Best score : " + bestScoreUsername + " : " + std::to_string(bestScore),
                      SDL_Color{255, 255, 255, 255});
    bestScoreText.setPosition({10, 40});
    _window.draw(bestScoreText);

    // Display
    _window.display();
}

void Arcade::Graphics::Sdl::Sdl::createMenus(const std::vector<std::string> &games, const std::vector<std::string> &graphics, const ControlMap &controls)
{
    // Set graph items
    _graphItems.clear();
    for (std::size_t i = 0; i < graphics.size(); i++) {
        _graphItems.push_back(
                std::make_unique<Text>(_window.getRenderer(), &_globalFont, simplifyName(graphics[i]), SDL_Color{255, 255, 255, 255}));
        _graphItems.back()->setPosition({550, 375 + i * 40});
    }

    // Set game items
    _gameItems.clear();
    for (std::size_t i = 0; i < games.size(); i++) {
        _gameItems.push_back(
                std::make_unique<Text>(_window.getRenderer(), &_globalFont, simplifyName(games[i]), SDL_Color{255, 255, 255, 255}));
        _gameItems.back()->setPosition({925, 375 + i * 40});
    }

    // Set controls items
    _controlsItems.clear();
    std::size_t i = 0;
    for (const auto &control : controls) {
        _controlsItems.push_back(
                std::make_unique<Text>(_window.getRenderer(), &_globalFont, control.first + " : " + control.second, SDL_Color{255, 255, 255, 255}));
        _controlsItems.back()->setPosition({110, 375 + i * 40});
        i++;
    }

    // Update cache data
    _graphNames = graphics;
    _gameNames = games;
    _controls = controls;
}

void Arcade::Graphics::Sdl::Sdl::drawMenuItems(int selectedGame, int selectedGraph)
{
    // Set color of selected item if not in game
    for (std::size_t i = 0; i < _graphItems.size(); i++) {
        if (i == static_cast<std::size_t>(selectedGraph))
            _graphItems[i]->setColor({255, 0, 0, 255}); // Red
        else
            _graphItems[i]->setColor({255, 255, 255, 255}); // White
        _window.draw(*_graphItems[i]);
    }
    // Set color of selected item if in game
    for (std::size_t i = 0; i < _gameItems.size(); i++) {
        if (i == static_cast<std::size_t>(selectedGame))
            _gameItems[i]->setColor({255, 0, 0, 255}); // Red
        else
            _gameItems[i]->setColor({255, 255, 255, 255}); // White
        _window.draw(*_gameItems[i]);
    }

    // Draw controls
    for (const auto &control : _controlsItems)
        _window.draw(*control);
}

void Arcade::Graphics::Sdl::Sdl::drawMenuTitlesAndBg()
{
    // Draw rectangles
    _window.draw(RectangleShape{{248, 475}, {887, 291}, Black}); // Game
    _window.draw(RectangleShape{{248, 475}, {516, 291}, Black}); // Graph
    _window.draw(RectangleShape{{248 + 70, 475}, {80, 291}, Black}); // Controls

    // Draw menu titles
    _window.draw(*_graphTitle);
    _window.drawLine({532, 350}, {532 + 219, 350}, White);

    _window.draw(*_gameTitle);
    _window.drawLine({901 + 45, 350}, {901 + 219 - 45, 350}, White);

    _window.draw(*_controlsTitle);
    _window.drawLine({161 + 40 - 35, 350}, {161 - 40 + 219 - 35, 350}, White);
}

void Arcade::Graphics::Sdl::Sdl::drawInfoPanel(Arcade::IGameData &gameData)
{
    double cellSize = calculateCellSize(gameData.getMapSize().first, gameData.getMapSize().second);

    if (_infoPanelTitle.get() == nullptr) {
        _infoPanelTitle = std::make_unique<Text>(_window.getRenderer(),
                                                &_boldGlobalFont,
                                                gameData.getGameName(),
                                                SDL_Color{255, 255, 255, 255});
        _infoPanelTitle->getRawTexture();
        _infoPanelTitle->setPosition({(gameData.getMapSize().second * cellSize + 1280) / 2
        - _infoPanelTitle->getSize().first / 2, 25});
    }

    // Draw scores
    _window.draw(*_infoPanelTitle);
    for (int i = 0; auto &score : gameData.getScores()) {
        _scoreText->setText(score.first + ": " + std::to_string(score.second));
        _scoreText->setPosition({gameData.getMapSize().second * cellSize + 40, 100  + i * 50});
        _window.draw(*_scoreText);
        i++;
    }

    // Draw controls
    for (int i = 0; auto &control : gameData.getControls()) {
        _scoreText->setText(control.first + ": " + control.second);
        _scoreText->setPosition({(0.3 + gameData.getMapSize().second) * cellSize + 90, 500  + i * 40});
        _window.draw(*_scoreText);
        i++;
    }

    if (gameData.isGameOver()) {
        _infoPanelTitle->getRawTexture();
        _gameOverText->setPosition({((0.25 + gameData.getMapSize().second) * cellSize + 1280) / 2
        - _gameOverText->getSize().first / 2, 330});
        _window.draw(*_gameOverText);
    }
}

void Arcade::Graphics::Sdl::Sdl::render(IGameData &gameData)
{
    double cellSize = calculateCellSize(gameData.getMapSize().first, gameData.getMapSize().second);
    Texture *t;
    std::string texturePath;
    Sprite s;
    SpriteSize pos, size;

    _window.clear();
    // Draw entities
    for (auto &entity: gameData.getEntities()) {
        // Get texture
        texturePath = Sdl::texturePath(*entity, gameData.getGameName());
        if (_textures.find(texturePath) == _textures.end() || _textures[texturePath].get() == nullptr)
            _textures[texturePath] = std::make_unique<Texture>(texturePath, _window.getRenderer());
        t = _textures[texturePath].get();

        // Position sprite
        s.setTexture(*t);
        size = entity->getSize();
        s.setSize({size.first * cellSize, size.second * cellSize});

        // Draw it
        std::vector<std::pair<float, float>> positions = entity->getPosition();
        for (auto &pos : positions) {
            s.setPosition({pos.first * cellSize, pos.second * cellSize});
            _window.draw(s);
        }
    }
    drawInfoPanel(gameData);
    _window.display();
}

double Arcade::Graphics::Sdl::Sdl::calculateCellSize(int width, int height)
{
    double cellSizeX = 1280.0 / width;
    double cellSizeY = 832.0 / height;

    return std::min(cellSizeX, cellSizeY);
}

std::string Arcade::Graphics::Sdl::Sdl::texturePath(const IEntity &entity, const std::string &gameName)
{
    return "assets/" + gameName + "/sdl/" + entity.getTexture();
}

std::string Arcade::Graphics::Sdl::Sdl::simplifyName(const std::string &name)
{
    static const std::size_t maxSize = std::string("arcade_centipede.so").size();

    if (name.size() <= maxSize)
        return name;
    return name.substr(0, maxSize - 3) + "...";
}

void Arcade::Graphics::Sdl::Sdl::unloadTextures()
{
    _textures.clear();
}

std::vector<Arcade::Key> Arcade::Graphics::Sdl::Sdl::getPressedKeys()
{
    SDL_Event ev;
    static std::set<Key> pressedKeysSet;
    bool isToCheck;

    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT)
            pressedKeysSet.insert(Arcade::Key::Escape);
        isToCheck = (ev.type == SDL_KEYDOWN || ev.type == SDL_KEYUP) && _keyMap.find(ev.key.keysym.sym) != _keyMap.end();
        if (ev.type == SDL_KEYDOWN && isToCheck) {
            pressedKeysSet.insert(_keyMap.at(ev.key.keysym.sym));
        }
        else if (ev.type == SDL_KEYUP && isToCheck) {
            pressedKeysSet.erase(_keyMap.at(ev.key.keysym.sym));
        }
    }

    std::vector<Key> pressedKeys;
    for (auto &i: pressedKeysSet)
        pressedKeys.push_back(i);
    return pressedKeys;
}
