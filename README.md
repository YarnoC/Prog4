# Engine Specifications

## Github Repo
[The public git repository can be found here.](https://github.com/YarnoC/Prog4)

## About the engine
### Intro
Patterns such as the "Component pattern", "Game loop" and "update method" are naturally present in the project but also don't need a lot of justification. So i'll skip right over them to the more interesting bits.

### Flyweight
I employed the flyweight pattern in the SDL sound system implementation. Upon load, the sound system stores the sound file along with the file name and returns a pointer to that instance to any location trying to load that sound. This way the sound is only loaded once but can still be used in multiple places.

### Command pattern
I used the command pattern as an interface between (virtual) input and the entities in the game. As any system can issue and execute commands, it makes it very simple to have an enemy, here Coily, be controlled by either the second player via the input manager or by an AI system giving out commands.

### State

### Type object
