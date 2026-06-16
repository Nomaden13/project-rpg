#ifndef MAIN_H
#define MAIN_H

#include <memory>

typedef struct GameConfig {
    int screen_width;
    int screen_height;
    int target_fps;
    std::string game_name;
} GameConfig;

GameConfig config = {
    .screen_width = 1280,
    .screen_height = 720,
    .target_fps = 60,
    .game_name = "Rhythm Game"
};

class Game {
private:
    GameConfig config_;
    std::unique_ptr<Screen> current_screen_;
    bool on_transition_;
    bool trans_fade_out_;
    float trans_alpha_;

public:
    Game(GameConfig config);

    void UpdateDrawFrame();
    void UpdateTransition();
    void DrawTransition();

    void setCurrentScreen(std::unique_ptr<Screen> current_screen);
    std::string GetGameName();
    int GetScreenWidth();
    int GetScreenHeight();
    int GetTargetFPS();
};

class Screen {
public:
    virtual void UpdateScreen() = 0;
    virtual void DrawScreen() = 0;
    virtual int FinishScreen() = 0;
    virtual std::unique_ptr<Screen> getNextScreen() = 0;

    virtual ~Screen() = default;
};

class ScreenLogo : public Screen {
private:
    std::unique_ptr<Screen> next_screen_;
    int framesCounter;
    int finishScreen;
    int logoPositionX;
    int logoPositionY;

public:
    void UpdateScreen() override;
    void DrawScreen() override;
    int FinishScreen() override;

    std::unique_ptr<Screen> getNextScreen() override;

    ScreenLogo();
};

#endif
