# Engine Specifications

## Github Repo
[The public git repository can be found here.](https://github.com/YarnoC/Prog4)

## About the engine
### Intro
Patterns such as the "Component pattern", "Game loop" and "update method" are naturally present in the project but also don't need a lot of justification. So i'll skip right over them to the more interesting bits.

### Flyweight
I employed the flyweight pattern in SDL sound system implementation. Upon load, the sound system stores the sound file along with the file name and returns a pointer to that instance to any location trying to load that sound. This way the sound is only loaded once but can still be used in multiple places.

### Command pattern
I used the command pattern as an interface between (virtual) input and the entities in the game. As any system can issue and execute commands, it makes it very simple to have an enemy, here Coily, be controlled by either the second player via the input manager or by an AI system giving out commands.

### State

### Type object

### Scenegraph
Despite not actually being a game design pattern, I'd like to talk about the scenegraph and how I used in my collision detection system for Q\*Bert. From all sources that I could find, it seems that Q\*Bert can only collide with enemies whilst they are both standing still on the same block. So I decided to make every entity on the map a child object of the block they were standing on. This way when landing on a new block, you only have to check whether that object has a child. This method only works for Q*Bert of course, so it's implemented as game logic instead of in the engine itself.