#include "Player.h"

#include <raylib.h>

#include <algorithm>
#include <array>
#include <filesystem>
#include <string>

#include "Config.h"

namespace {
constexpr int kSpriteFrameWidth = 90;
constexpr int kSpriteFrameHeight = 90;
constexpr int kIdleFrameCount = 6;
constexpr int kRunFrameCount = 8;
constexpr int kAttackFrameCount = 7;
constexpr int kDeadFrameCount = 8;

struct AnimationClip {
    int startIndex;
    int frameCount;
};

AnimationClip GetAnimationClip(bool moving) {
    if (moving) return {kIdleFrameCount, kRunFrameCount};
    return {0, kIdleFrameCount};
}

std::filesystem::path FindProjectRoot() {
    std::filesystem::path dir = std::filesystem::current_path();

    for (int i = 0; i < 12; ++i) {
        if (std::filesystem::exists(dir / "assets" / "character") &&
            std::filesystem::exists(dir / "CMakeLists.txt")) {
            return dir;
        }

        std::filesystem::path parent = dir.parent_path();
        if (parent == dir) {
            break;
        }
        dir = parent;
    }

    return std::filesystem::current_path();
}

Texture2D TryLoadTextureFromCandidates(
    const std::array<std::string, 2>& paths) {
    const std::filesystem::path projectRoot = FindProjectRoot();
    std::array<std::string, 12> candidates = {};
    int index = 0;

    auto pushCandidate = [&](const std::string& value) {
        if (index < static_cast<int>(candidates.size())) {
            candidates[index++] = value;
        }
    };

    for (const auto& rel : paths) {
        pushCandidate((projectRoot / rel).string());
        pushCandidate((projectRoot / ".." / rel).string());
        pushCandidate((projectRoot / "assets" / "character" /
                       std::filesystem::path(rel).filename())
                          .string());
    }

    for (const auto& candidate : candidates) {
        if (candidate.empty()) continue;
        const std::filesystem::path filePath(candidate);
        if (!std::filesystem::exists(filePath)) continue;

        const Texture2D texture = LoadTexture(filePath.string().c_str());
        if (texture.id != 0) {
            return texture;
        }
    }

    return {0, 0, 0, 0};
}
}  // namespace

Player::Player(double x, double y)
    : x(x),
      y(y),
      texture({0, 0, 0, 0}),
      frame(0),
      animationTime(0.0),
      isMoving(false),
      facingRight(true) {
    speed = 5;
}

void Player::LoadAssets() {
    if (texture.id != 0) {
        return;
    }

    std::array<std::string, 2> texturePaths = {
        "assets/character/Cap_guy_sprite_sheet.png",
        "assets/character/Machine_guy_sprite_sheet.png",
    };

    texture = TryLoadTextureFromCandidates(texturePaths);
}

Player::~Player() {
    if (texture.id != 0) {
        UnloadTexture(texture);
    }
}

void Player::Update() {
    double previousX = x;
    bool moved = false;

    if (IsKeyDown(KEY_A)) {
        x -= speed;
        moved = true;
        facingRight = false;
    }
    if (IsKeyDown(KEY_D)) {
        x += speed;
        moved = true;
        facingRight = true;
    }
    if (IsKeyDown(KEY_W)) {
        y -= speed;
        moved = true;
    }
    if (IsKeyDown(KEY_S)) {
        y += speed;
        moved = true;
    }
    if (0 > x) x = 0;
    if (x > WindowWidth - CharacterSize) x = WindowWidth - CharacterSize;
    if (0 > y) y = 0;
    if (y > WindowLength - CharacterSize) y = WindowLength - CharacterSize;

    isMoving = moved || (x != previousX);

    animationTime += GetFrameTime();
    const AnimationClip clip = GetAnimationClip(isMoving);
    if (animationTime > (isMoving ? 0.12 : 0.18)) {
        animationTime = 0.0;
        frame = (frame + 1) % clip.frameCount;
    }
}

void Player::Draw() {
    if (texture.id == 0) {
        DrawRectangle(x, y, CharacterSize, CharacterSize, RED);
        return;
    }

    const int totalFrames = static_cast<int>(texture.width / kSpriteFrameWidth);
    const int directionOffset = (totalFrames > 29 && !facingRight) ? 29 : 0;
    const AnimationClip clip = GetAnimationClip(isMoving);
    const int frameIndex = frame % clip.frameCount;
    const int sheetIndex = directionOffset + clip.startIndex + frameIndex;
    const float sourceX = static_cast<float>(sheetIndex * kSpriteFrameWidth);

    const float spriteSize = static_cast<float>(CharacterSize);
    const float drawX = static_cast<float>(x - spriteSize * 0.5f);
    const float drawY = static_cast<float>(y - spriteSize * 0.5f);

    Rectangle source = {
        facingRight ? sourceX : sourceX + static_cast<float>(kSpriteFrameWidth),
        0.0f,
        facingRight ? static_cast<float>(kSpriteFrameWidth)
                    : -static_cast<float>(kSpriteFrameWidth),
        static_cast<float>(kSpriteFrameHeight),
    };

    Rectangle dest = {
        drawX,
        drawY,
        spriteSize,
        spriteSize,
    };

    DrawTexturePro(texture, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}

double Player::GetX() const { return x; }

double Player::GetY() const { return y; }

void Player::SetPosition(double newX, double newY) {
    x = newX;
    y = newY;
}