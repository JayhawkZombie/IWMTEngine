//
// Created by Kurt Slagle on 12/31/24.
//

#pragma once

#include <fmt/format.h>
#include <fmt/color.h>
#include <SFML/Graphics.hpp>

inline constexpr auto fg_color_red         = fmt::fg(fmt::color::red);
inline constexpr auto bg_color_red         = fmt::bg(fmt::color::red);
inline constexpr auto fg_color_green       = fmt::fg(fmt::color::green);
inline constexpr auto bg_color_green       = fmt::bg(fmt::color::green);
inline constexpr auto fg_color_blue        = fmt::fg(fmt::color::blue);
inline constexpr auto bg_color_blue        = fmt::bg(fmt::color::blue);
inline constexpr auto fg_color_yellow      = fmt::fg(fmt::color::yellow);
inline constexpr auto bg_color_yellow      = fmt::bg(fmt::color::yellow);
inline constexpr auto fg_color_magenta     = fmt::fg(fmt::color::magenta);
inline constexpr auto bg_color_magenta     = fmt::bg(fmt::color::magenta);
inline constexpr auto fg_color_cyan        = fmt::fg(fmt::color::cyan);
inline constexpr auto bg_color_cyan        = fmt::bg(fmt::color::cyan);
inline constexpr auto fg_color_purple      = fmt::fg(fmt::color::purple);
inline constexpr auto bg_color_purple      = fmt::bg(fmt::color::purple);
inline constexpr auto fg_color_gold        = fmt::fg(fmt::color::gold);
inline constexpr auto bg_color_gold        = fmt::bg(fmt::color::gold);
inline constexpr auto fg_color_lavender    = fmt::fg(fmt::color::lavender_blush);
inline constexpr auto bg_color_lavender    = fmt::bg(fmt::color::lavender_blush);
inline constexpr auto fg_color_blue_violet = fmt::fg(fmt::color::blue_violet);
inline constexpr auto bg_color_blue_violet = fmt::bg(fmt::color::blue_violet);
inline constexpr auto fg_color_white       = fmt::fg(fmt::color::white);
inline constexpr auto bg_color_white       = fmt::bg(fmt::color::white);
inline constexpr auto fg_color_black       = fmt::fg(fmt::color::black);
inline constexpr auto bg_color_black       = fmt::bg(fmt::color::black);
inline constexpr auto fg_color_dark_red    = fmt::fg(fmt::color::dark_red);
inline constexpr auto bg_color_dark_red    = fmt::bg(fmt::color::dark_red);

#define FMT_DEBUG_LOG(...) fmt::print("{}", fmt::styled(##__VA_ARGS__, fg_color_cyan))

namespace sf {
    inline auto format_as(const sf::Vector2f &vec) {
        return fmt::format("({:4.2f},{:4.2f})",
                           fmt::styled(vec.x, fg_color_lavender),
                           fmt::styled(vec.y, fg_color_lavender));
    }

    inline auto format_as(const sf::FloatRect &rect) {
        return fmt::format("({:4.2f},{:4.2f},{:4.2f},{:4.2f})",
                           fmt::styled(rect.left, fg_color_lavender),
                           fmt::styled(rect.top, fg_color_lavender),
                           fmt::styled(rect.width, fg_color_lavender),
                           fmt::styled(rect.height, fg_color_lavender));
    }

    inline auto format_as(const sf::Vector2i &vec) {
        return fmt::format("({},{})", fmt::styled(vec.x, fg_color_lavender), fmt::styled(vec.y, fg_color_lavender));
    }

    inline auto format_as(const sf::Vector2u &vec) {
        return fmt::format("({},{})",
                           fmt::styled(vec.x, fg_color_blue_violet),
                           fmt::styled(vec.y, fg_color_blue_violet));
    }

    inline auto format_as(const sf::Color &color) {
        return fmt::format("({},{},{},{})",
                           color.r,
                           color.g,
                           color.b,
                           color.a
                          );
    }

    inline auto format_as(const sf::Mouse::Button &button) {
        return fmt::format("{}",
                           fmt::styled(fmt::underlying(button), fg_color_green));
    }

    inline auto format_as(const sf::Keyboard::Key &key) {
        return fmt::format("{}",
                           fmt::styled(fmt::underlying(key), fg_color_green));
    }

    inline auto format_as(const sf::Uint8 &value) {
        return fmt::format("{}", fmt::styled(value, fg_color_cyan));
    }

    inline auto format_as(const sf::Event::MouseButtonEvent &mbEvent) {
        return fmt::format("{} @ {}",
                           mbEvent.button,
                           sf::Vector2i(mbEvent.x, mbEvent.y));
    }

    inline auto format_as(const sf::Event::MouseMoveEvent &mmEvent) {
        return fmt::format("({},{})",
                           fmt::styled(mmEvent.x, fg_color_yellow),
                           fmt::styled(mmEvent.y, fg_color_yellow));
    }

    inline auto format_as(const sf::Event::SizeEvent &szEvent) {
        return fmt::format("({},{})",
                           fmt::styled(szEvent.width, fg_color_gold),
                           fmt::styled(szEvent.height, fg_color_gold));
    }

    inline auto format_as(const sf::Uint32 &uint) {
        return fmt::format("{}", fmt::styled(uint, fg_color_blue_violet));
    }

    inline auto format_as(const sf::Event::TextEvent &txtEvent) {
        return fmt::format("{}", fmt::styled(txtEvent.unicode, fg_color_blue_violet));
    }

    inline auto format_as(const sf::Event &event) {
        const auto event_str = fmt::underlying(event.type);
        if (event.type == sf::Event::KeyPressed) {
            return fmt::format("Key pressed: {}", event.key.code);
        } else if (event.type == sf::Event::KeyReleased) {
            return fmt::format("Key released: {}", event.key.code);
        } else if (event.type == sf::Event::MouseButtonPressed) {
            return fmt::format("Mouse pressed: {}",
                               event.mouseButton);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            return fmt::format("Mouse released: {}", event.mouseButton);
        } else if (event.type == sf::Event::Closed) {
            return fmt::format("Closed");
        } else if (event.type == sf::Event::MouseMoved) {
            return fmt::format("Mouse moved: {}", event.mouseMove);
        } else if (event.type == sf::Event::Resized) {
            return fmt::format("Resized: {}", event.size);
        } else if (event.type == sf::Event::TextEntered) {
            return fmt::format("Text entered: {}", event.text);
        }

        return fmt::format("Unknown event: {}", fmt::styled(event_str, fg_color_cyan));
    }
}
