
#ifndef MINESWEEPER_GRAPHICSETTINGS_H
#define MINESWEEPER_GRAPHICSETTINGS_H


class GraphicSettings
{
public:
    GraphicSettings();


    void saveToFile(const std::string path);

    void loadFromFile(const std::string path);

    //Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;
    std::map<std::string, int> keybinds;
};


#endif //MINESWEEPER_GRAPHICSETTINGS_H
