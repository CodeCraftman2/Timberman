#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main()
{
    // Initialize random seed once
    srand((unsigned int)time(0));

    // Step 1: Create a video mode object (resolution)
    VideoMode vm(1920, 1080);

    // Step 2: Create and open the window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    // Step 3: Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Step 4: Load a graphic into the texture
    if (!textureBackground.loadFromFile("../graphics/background.png"))
    {
        std::cerr << "Error: Could not load background image!" << std::endl;
        return -1;
    }

    // Step 5: Create a sprite for the background
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Step 13: Standing Tree
    Texture textureTree;
    if (!textureTree.loadFromFile("../graphics/tree.png"))
    {
        std::cerr << "Error: Could not load tree image!" << std::endl;
        return -1;
    }

    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);  // Adjust position to be inside the screen
				    // Taking tree in center from x-axis


    // Debugging: Print the size of the tree texture
    std::cout << "Tree texture size: " << textureTree.getSize().x << "x" << textureTree.getSize().y << std::endl;
	
    // Step 14: Adding Bee
    Texture textureBee;
    if (!textureBee.loadFromFile("../graphics/bee.png"))
    {
        std::cerr << "Error: Could not load bee image!" << std::endl;
        return -1;
    }

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    // Is the bee currently moving?
    bool beeActive = false;

    // How fast can the bee fly
    float beeSpeed = 0.05f; // Adjusted speed

    // Debugging: Print the size of the bee texture
    std::cout << "The bee size: " << textureBee.getSize().x << "x" << textureBee.getSize().y << std::endl;

    //Step 15: Creating cloud class for 3 cloud object
    Texture textureCloud;
    if (!textureCloud.loadFromFile("../graphics/cloud.png"))
    {
	    std::cerr << "Error: Could not load cloud image!" << std::endl;
	    return -1;
    }

    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    //Creating cloud on screen

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    //Speed of cloud
    float cloud1Speed = 0.05f; // Adjusted speed
    float cloud2Speed = 0.05f; // Adjusted speed
    float cloud3Speed = 0.05f; // Adjusted speed

    // Step 18: Moving Bee
    Clock clock;

    // Game loop
    while (window.isOpen())
    {
        // Step 8: Event handling (user input)
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
        }

        // Measure time
        Time dt = clock.restart();

        // Update the bee
        if (!beeActive)
        {
            // Bee's Speed
            beeSpeed = (rand() % 200) + 200;

            // Bee's position
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        else
        {
            // Move the bee
            spriteBee.setPosition(
                spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                spriteBee.getPosition().y
            );

            // Check if bee has reached the left hand edge
            if (spriteBee.getPosition().x < -100)
            {
                // Reset the bee
                beeActive = false;
            }
        }

	// Step 19: Creating cloud
	// Moving the 3 Clouds
	// Manage the clouds
	
	// Cloud 1
	if (!cloud1Active)
	
	{
		// How fast is the cloud
		srand((int)time(0) * 10);
		cloud1Speed = (rand() % 200);
	
		// How high is the cloud
		srand((int)time(0) * 10);
		float height = (rand() % 150);
		spriteCloud1.setPosition(-200, height);
		cloud1Active = true;
	
	}
	
	else
	{
	spriteCloud1.setPosition( spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),spriteCloud1.getPosition().y);

	// Has the cloud reached the right hand edge of the screen?

	if (spriteCloud1.getPosition().x > 1920)
	{

	// Set it up ready to be a whole new cloud next frame
	
		cloud1Active = false;
	}
	}

	        // Cloud 2
        if (!cloud2Active)

        {
                // How fast is the cloud
		srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                // How high is the cloud
		srand((int)time(0) * 20);
                float height = (rand() % 150);
                spriteCloud2.setPosition(-150, height);
                cloud2Active = true;

        }

        else
        {
        spriteCloud2.setPosition( spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),spriteCloud2.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?

        if (spriteCloud2.getPosition().x > 1920)
        {

        // Set it up ready to be a whole new cloud next frame

                cloud2Active = false;
        }

        }

	        // Cloud 3
        if (!cloud3Active)

        {
                // How fast is the cloud
		srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                // How high is the cloud
		srand((int)time(0) *30);
                float height = (rand() % 150);
                spriteCloud3.setPosition(-200, height);
                cloud3Active = true;

        }

        else
        {
        spriteCloud3.setPosition( spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),spriteCloud3.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?

        if (spriteCloud3.getPosition().x > 1920)
        {

        // Set it up ready to be a whole new cloud next frame

                cloud3Active = false;
        }

        }



        // Step 9: Clear the previous frame
        window.clear();

        // Step 10: Draw the background sprite
        window.draw(spriteBackground);

        // Step 11: Draw the tree sprite
        window.draw(spriteTree);

	// Step 16: Draw the bee sprite
	window.draw(spriteBee);

	// Step 17: Draw 3 Cloud sprite
	window.draw(spriteCloud1);
	window.draw(spriteCloud2);
	window.draw(spriteCloud3);

        // Step 12: Display the current frame (swap buffers)
        window.display();
    }

    return 0;
}

