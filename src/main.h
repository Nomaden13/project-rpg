#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <string>

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
protected:
    std::unique_ptr<Screen> next_screen_;
    int frames_counter_;
    int finish_screen_;
public:
    virtual void UpdateScreen() = 0;
    virtual void DrawScreen() = 0;
    virtual int FinishScreen() = 0;
    std::unique_ptr<Screen> getNextScreen();

    virtual ~Screen();
};

class ScreenLogo : public Screen {
private:
    int logo_position_x;
    int logo_position_y;
public:
    void UpdateScreen() override;
    void DrawScreen() override;
    int FinishScreen() override;

    ScreenLogo();
};

class ScreenGameplay : public Screen {
public:
    void UpdateScreen() override;
    void DrawScreen() override;
    int FinishScreen() override;

    ScreenGameplay();
};

#endif