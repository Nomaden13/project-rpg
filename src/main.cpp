#include "raylib.h"
#include "main.h"
#include <string>
#include <memory>

int main(int argc, char *argv[]) {
    Game game(config);

    InitWindow(game.GetScreenWidth(),game.GetScreenHeight(), game.GetGameName().c_str());
    SetTargetFPS(game.GetTargetFPS());
    
    game.setCurrentScreen(std::make_unique<ScreenLogo>());
    while (!WindowShouldClose()) {
        game.UpdateDrawFrame();
    }

    CloseWindow();
    
    return 0;
}

Game::Game(GameConfig config) {
    config_ = config;
    on_transition_ = false;
}

void Game::UpdateTransition() {
    if (trans_fade_out_) {
        trans_alpha_ -= 0.05f;

        if (static_cast<int>(trans_alpha_) <= 0) {
            trans_alpha_ = 0.0f;
            trans_fade_out_ = false;
            on_transition_ = false;
        }
    } else {
        trans_alpha_ += 0.05f;

        if (static_cast<int>(trans_alpha_) >= 1) {
            trans_alpha_ = 1.0f;

            std::unique_ptr<Screen> next_screen = current_screen_->getNextScreen();
            current_screen_.reset();
            
            if (current_screen_ == nullptr) {
                current_screen_ = std::move(next_screen);
            }

            trans_fade_out_ = true;
        }
    }
}

void Game::DrawTransition() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, trans_alpha_));
}

void Game::UpdateDrawFrame() {
    if (on_transition_) {
        UpdateTransition();
    } else {
        current_screen_->UpdateScreen();

        if (current_screen_->FinishScreen()) {
            trans_alpha_ = 0.0f;
            trans_fade_out_ = false;
            on_transition_ = true;
        }
    }

    BeginDrawing();
        ClearBackground(RAYWHITE);

        current_screen_->DrawScreen();
        
        if (on_transition_) {
            DrawTransition();
        }

    EndDrawing();
}

void Game::setCurrentScreen(std::unique_ptr<Screen> current_screen) {
    current_screen_ = std::move(current_screen);
}

std::string Game::GetGameName() {
    return config_.game_name;
}

int Game::GetScreenWidth() {
    return config_.screen_width;
}

int Game::GetScreenHeight() {
    return config_.screen_height;
}

int Game::GetTargetFPS() {
    return config_.target_fps;
}

Screen::~Screen() = default;

std::unique_ptr<Screen> Screen::getNextScreen() {
    return std::move(next_screen_);
}