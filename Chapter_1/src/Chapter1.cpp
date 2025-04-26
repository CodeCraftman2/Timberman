#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main()
{
    // Step 1: Create a video mode object (resolution)
    VideoMode vm(1920, 1080);

    // Step 2: Create and open the window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    // Step 3: Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Step 4: Load a graphic into the texture
    if (!textureBackground.loadFromFile("../graphics/background.jpg"))
    {
        // If loading the texture fails, print an error and exit
        std::cerr << "Error: Could not load background image!" << std::endl;
        return -1;
    }

    // Step 5: Create a sprite for the background
    Sprite spriteBackground;

    // Step 6: Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Step 7: Set the position of the sprite to cover the screen (top-left corner)
    spriteBackground.setPosition(0, 0);

    // Game loop
    while (window.isOpen())
    {
        // Step 8: Event handling (user input)
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                // Close the window if the user presses the Escape key or closes the window
                window.close();
            }
        }

        // Step 9: Clear the previous frame
        window.clear();

        // Step 10: Draw the background sprite
        window.draw(spriteBackground);

        // Step 11: Display the current frame (swap buffers)
        window.display();
    }

    return 0;
}

