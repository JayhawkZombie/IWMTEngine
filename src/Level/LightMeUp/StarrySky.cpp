#include "StarrySky.h"
#include <cmath>

StarrySky::StarrySky(size_t starsPerCell)
    : m_rng(std::random_device()())  // Initialize with random seed
    , m_backgroundColor(10, 10, 20)  // Dark blue-ish background
{
    generateStars(starsPerCell);
}

void StarrySky::generateStars(size_t starsPerCell) {
    // Create random distribution for star properties
    std::uniform_real_distribution<float> posDist(0.0f, 1.0f);  // Normalized positions
    std::uniform_real_distribution<float> brightnessDist(0.3f, 1.0f);  // Minimum brightness of 0.3
    std::uniform_real_distribution<float> sizeDist(1.0f, 2.0f);  // Star sizes between 1-2 pixels

    // Generate stars for each cell in the grid
    for (size_t i = 0; i < GRID_SIZE; ++i) {
        for (size_t j = 0; j < GRID_SIZE; ++j) {
            auto& cell = m_grid[i][j];
            cell.stars.clear();
            cell.stars.reserve(starsPerCell);
            cell.visibility = 1.0f;
            cell.color = sf::Color::White;  // Default to white stars

            for (size_t k = 0; k < starsPerCell; ++k) {
                Star star;
                star.position = sf::Vector2f(posDist(m_rng), posDist(m_rng));
                star.brightness = brightnessDist(m_rng);
                star.size = sizeDist(m_rng);
                cell.stars.push_back(star);
            }
        }
    }
}

float StarrySky::randomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_rng);
}

sf::Color StarrySky::getStarColor(const Star& star, const Cell& cell) const {
    // Blend the star's brightness with the cell's color and visibility
    float brightness = star.brightness * cell.visibility;
    return sf::Color(
        static_cast<uint8_t>(cell.color.r * brightness),
        static_cast<uint8_t>(cell.color.g * brightness),
        static_cast<uint8_t>(cell.color.b * brightness),
        255
    );
}

sf::Vector2f StarrySky::mapToRenderArea(const Star& star, const sf::FloatRect& cellBounds) const {
    return sf::Vector2f(
        cellBounds.left + star.position.x * cellBounds.width,
        cellBounds.top + star.position.y * cellBounds.height
    );
}

sf::FloatRect StarrySky::getCellBounds(size_t x, size_t y, const sf::FloatRect& totalArea) const {
    float cellWidth = totalArea.width / GRID_SIZE;
    float cellHeight = totalArea.height / GRID_SIZE;
    return sf::FloatRect(
        totalArea.left + x * cellWidth,
        totalArea.top + y * cellHeight,
        cellWidth,
        cellHeight
    );
}

void StarrySky::draw(sf::RenderTarget& target, const sf::FloatRect& renderArea) const {
    // Draw background
    sf::RectangleShape background(sf::Vector2f(renderArea.width, renderArea.height));
    background.setPosition(renderArea.left, renderArea.top);
    background.setFillColor(m_backgroundColor);
    target.draw(background);

    // Draw stars for each cell
    for (size_t i = 0; i < GRID_SIZE; ++i) {
        for (size_t j = 0; j < GRID_SIZE; ++j) {
            const auto& cell = m_grid[i][j];
            if (cell.visibility <= 0.0f) continue;  // Skip invisible cells

            sf::FloatRect cellBounds = getCellBounds(i, j, renderArea);
            for (const auto& star : cell.stars) {
                sf::CircleShape starShape(star.size);
                starShape.setPosition(mapToRenderArea(star, cellBounds));
                starShape.setFillColor(getStarColor(star, cell));
                target.draw(starShape);
            }
        }
    }
}

void StarrySky::update(float deltaTime) {
    // Add subtle twinkling effect
    for (auto& row : m_grid) {
        for (auto& cell : row) {
            for (auto& star : cell.stars) {
                float brightnessChange = randomFloat(-0.1f, 0.1f) * deltaTime;
                star.brightness = std::clamp(star.brightness + brightnessChange, 0.3f, 1.0f);
            }
        }
    }
}

void StarrySky::setCellVisibility(size_t x, size_t y, float visibility) {
    if (x < GRID_SIZE && y < GRID_SIZE) {
        m_grid[x][y].visibility = std::clamp(visibility, 0.0f, 1.0f);
    }
}

void StarrySky::setCellColor(size_t x, size_t y, const sf::Color& color) {
    if (x < GRID_SIZE && y < GRID_SIZE) {
        m_grid[x][y].color = color;
    }
}

float StarrySky::getCellVisibility(size_t x, size_t y) const {
    if (x < GRID_SIZE && y < GRID_SIZE) {
        return m_grid[x][y].visibility;
    }
    return 0.0f;
}

sf::Color StarrySky::getCellColor(size_t x, size_t y) const {
    if (x < GRID_SIZE && y < GRID_SIZE) {
        return m_grid[x][y].color;
    }
    return sf::Color::White;
}

size_t StarrySky::getTotalStars() const {
    size_t total = 0;
    for (const auto& row : m_grid) {
        for (const auto& cell : row) {
            total += cell.stars.size();
        }
    }
    return total;
} 