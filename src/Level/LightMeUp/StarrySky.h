#ifndef STARRYSKY_H
#define STARRYSKY_H

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <array>

class StarrySky {
public:
    static constexpr size_t GRID_SIZE = 8;
    static constexpr size_t STARS_PER_CELL = 10;  // Default stars per grid cell

    struct Star {
        sf::Vector2f position;  // Position is normalized within its cell (0-1)
        float brightness;       // 0.0 to 1.0
        float size;            // radius in pixels
    };

    struct Cell {
        std::vector<Star> stars;
        float visibility{1.0f};  // Control factor for star visibility in this cell
        sf::Color color{sf::Color::White};  // Color of stars in this cell
    };

    StarrySky(size_t starsPerCell = STARS_PER_CELL);
    
    void generateStars(size_t starsPerCell);
    void draw(sf::RenderTarget& target, const sf::FloatRect& renderArea) const;
    void update(float deltaTime);
    
    // Grid control
    void setCellVisibility(size_t x, size_t y, float visibility);
    void setCellColor(size_t x, size_t y, const sf::Color& color);
    float getCellVisibility(size_t x, size_t y) const;
    sf::Color getCellColor(size_t x, size_t y) const;
    
    // Getters and setters
    size_t getTotalStars() const;
    void setStarsPerCell(size_t starsPerCell) { generateStars(starsPerCell); }
    
    // Background color control
    void setBackgroundColor(const sf::Color& color) { m_backgroundColor = color; }
    const sf::Color& getBackgroundColor() const { return m_backgroundColor; }

private:
    using GridArray = std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE>;
    GridArray m_grid;
    std::mt19937 m_rng;  // Mersenne Twister random number generator
    sf::Color m_backgroundColor;  // Background color for the starry sky
    
    // Helper functions
    float randomFloat(float min, float max);
    sf::Color getStarColor(const Star& star, const Cell& cell) const;
    sf::Vector2f mapToRenderArea(const Star& star, const sf::FloatRect& cellBounds) const;
    sf::FloatRect getCellBounds(size_t x, size_t y, const sf::FloatRect& totalArea) const;
};

#endif // STARRYSKY_H 