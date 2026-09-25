#include "Enemy.h"

#include <raylib.h>

#include <array>
#include <cmath>
#include <filesystem>
#include <string>

#include "Config.h"

namespace {
constexpr int kFrameWidth = 90;
constexpr int kFrameHeight = 90;
constexpr int kIdleStart = 0;
constexpr int kIdleCount = 4;
constexpr int kRunStart = 4;
constexpr int kRunCount = 10;
constexpr int kAttackStart = 14;
constexpr int kAttackCount = 8;
constexpr int kDeadStart = 22;
constexpr int kDeadCount = 7;

// 这类 sprite sheet 里，通常会有 1 帧透明占位/空白帧,
// 但它不属于真实动画帧，因此不计入 start/count。
// 真实分段是：4 idle + 10 run + 8 attack + 7 dead = 29 帧/方向。
struct Clip {
    int start;
    int count;
};

Clip GetClip(bool moving) {
    return moving ? Clip{kRunStart, kRunCount} : Clip{kIdleStart, kIdleCount};
}

int GetDirectionOffset(int totalFrames, bool facingRight) {
    if (facingRight) return 0;

    // 单向图：29 帧，不需要偏移；双向图：一般 58 帧，左右各 29 帧。
    if (totalFrames > 29 && totalFrames % 2 == 0) {
        return totalFrames / 2;
    }

    return 0;
}

std::filesystem::path FindProjectRoot() {
    std::filesystem::path dir = std::filesystem::current_path();
    for (int i = 0; i < 12; ++i) {
        if (std::filesystem::exists(dir / "assets" / "character") &&
            std::filesystem::exists(dir / "CMakeLists.txt")) {
            return dir;
        }
        std::filesystem::path parent = dir.parent_path();
        if (parent == dir) break;
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
        if (index < static_cast<int>(candidates.size()))
            candidates[index++] = value;
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
        if (texture.id != 0) return texture;
    }

    return {0, 0, 0, 0};
}
}  // namespace

Enemy::Enemy(double x, double y)
    : x(x + GetRandomValue(-50, 50)),
      y(y + GetRandomValue(-50, 50)),
      texture({0, 0, 0, 0}),
      frame(GetRandomValue(0, 3)),
      animationTime(0.0),
      isMoving(false),
      facingRight(true) {
    speed = 1.5 + GetRandomValue(0, 4) * 0.5;

    if (x < 0) x = 0;
    if (x > WindowWidth - CharacterSize) x = WindowWidth - CharacterSize;
    if (y < 0) y = 0;
    if (y > WindowLength - CharacterSize) y = WindowLength - CharacterSize;
}

void Enemy::LoadAssets() {
    if (texture.id != 0) return;

    std::array<std::string, 2> texturePaths = {
        "assets/character/Cap_guy_sprite_sheet.png",
        "assets/character/Machine_guy_sprite_sheet.png",
    };

    const int choice =
        GetRandomValue(0, static_cast<int>(texturePaths.size()) - 1);
    std::array<std::string, 2> chosenPaths = {
        texturePaths[choice],
        texturePaths[(choice + 1) % texturePaths.size()],
    };

    texture = TryLoadTextureFromCandidates(chosenPaths);
}

Enemy::~Enemy() {
    if (texture.id != 0) UnloadTexture(texture);
}

void Enemy::Draw() {
    if (texture.id == 0) {
        DrawRectangle(x, y, CharacterSize, CharacterSize, BLUE);
        return;
    }

    const int totalFrames = static_cast<int>(texture.width / kFrameWidth);
    const int directionOffset = GetDirectionOffset(totalFrames, facingRight);
    const Clip clip = GetClip(isMoving);
    const int frameIndex = frame % clip.count;
    const int sourceX =
        (directionOffset + clip.start + frameIndex) * kFrameWidth;
    const float spriteSize = static_cast<float>(CharacterSize);
    const float drawX = static_cast<float>(x - spriteSize * 0.5f);
    const float drawY = static_cast<float>(y - spriteSize * 0.5f);

    Rectangle source = {
        facingRight ? static_cast<float>(sourceX)
                    : static_cast<float>(sourceX + kFrameWidth),
        0.0f,
        facingRight ? static_cast<float>(kFrameWidth)
                    : -static_cast<float>(kFrameWidth),
        static_cast<float>(kFrameHeight),
    };

    Rectangle dest = {
        drawX,
        drawY,
        spriteSize,
        spriteSize,
    };

    DrawTexturePro(texture, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}

void Enemy::Update(double playerX, double playerY) {
    double dx = playerX - x;
    double dy = playerY - y;
    double dist = std::sqrt(dx * dx + dy * dy);

    isMoving = false;
    if (dist > 0.01) {
        x += speed * (dx / dist);
        y += speed * (dy / dist);
        isMoving = true;
        facingRight = dx >= 0;
    }

    animationTime += GetFrameTime();
    const Clip clip = GetClip(isMoving);
    if (animationTime > (isMoving ? 0.12 : 0.18)) {
        animationTime = 0.0;
        frame = (frame + 1) % clip.count;
    }
}

double Enemy::GetX() const { return x; }

double Enemy::GetY() const { return y; }

void Enemy::SetPosition(double newX, double newY) {
    x = newX;
    y = newY;
}
