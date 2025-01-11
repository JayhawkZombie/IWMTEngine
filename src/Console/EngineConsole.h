#pragma once

#include <Engine/GameObject.h>
#include <Misc/UI.h>

#include <imgui.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>

class EngineConsole : public GameObject {
public:
    struct ConsoleEntry {
        // Max length for formatted string is 1024chars
        char buf[1024] = { '\0' };
        ImVec4 color = ImVec4(1.f, 1.f, 1.f, 1.f);

        void Draw() const
        {
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(buf);
            ImGui::PopStyleColor();
        }
    };

    ~EngineConsole() override;

    void SetPersistentFile(const std::string &filename);
    void SetPersistToFile(bool persist);
    void Tick(double delta) override;
    void Render(sf::RenderWindow &window) override;
    void SetOpen(bool open);
    [[nodiscard]] bool IsOpen() const;

    enum class LogLevel : int {
        Info = 0,
        Debug = 1,
        Warn = 2,
        Error = 3,
        Fatal = 4,
    };

    void AddLog(LogLevel level, const char *fmt, ...) IM_FMTARGS(3)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(level);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }

    void Debug(const char *fmt, ...) IM_FMTARGS(2)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(LogLevel::Debug);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }

    void Error(const char *fmt, ...) IM_FMTARGS(2)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(LogLevel::Error);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }

    void Warn(const char *fmt, ...) IM_FMTARGS(2)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(LogLevel::Warn);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }

    void Info(const char *fmt, ...) IM_FMTARGS(2)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(LogLevel::Info);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }
    int InputTextCallback(ImGuiInputTextCallbackData *data);

private:

    char m_inputBuf[256] = {'\0'};
    bool m_needsScroll = false;


    void WriteToPersistentFile();

    static ImVec4 GetColorForLogLevel(LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Info:
            {
                return ImGuiColors::InfoGray;
            }
            case LogLevel::Debug:
            {
                return ImGuiColors::DebugBlue;
            }
            case LogLevel::Warn:
            {
                return ImGuiColors::WarningYellow;
            }
            case LogLevel::Error:
            {
                return ImGuiColors::ErrorOrange;
            }
            case LogLevel::Fatal:
            {
                return ImGuiColors::FatalRed;
            }
            default:
            {
                return ImGuiColors::MutedMagenta;
            }

        }
    }

    void AddEntry(LogLevel level, const char *fmt, ...) IM_FMTARGS(3)
    {
        m_entries.emplace_back();
        auto &entry = m_entries.back();
        entry.color = GetColorForLogLevel(level);
        memset(entry.buf, '\0', 1024);
        va_list args;
        va_start(args, fmt);
        vsnprintf(entry.buf, IM_ARRAYSIZE(entry.buf), fmt, args);
        va_end(args);
        m_needsScroll = true;
    }

    void ClearConsole();
    void RenderLogsAndMessages();
    void RenderTerminal();

    std::vector<ConsoleEntry> m_entries;
    bool m_persistToFile = false;
    std::string m_persistentFilename;
    bool m_isOpen = true;
};
