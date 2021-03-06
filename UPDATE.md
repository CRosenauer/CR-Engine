# Update
 This file contains the changelogs for all (or most) of the
 updates to the CR-Engine. For a more general overview see
 repository notes.
 
# March, 7, 2020
 This has been a fairly sizeale update. In this update the
 following functionality has been added: sprite rotating,
 sprite stretching, sprite flipping, alpha textures, and
 dynamic display. As an additional note, I have also added
 a configuration file, "config.h" to allow for easy editing
 of specific engine features and constants.
 
 Starting with sprite rotating, stretching, and flipping;
 these pieces of functionality can only be used with textures
 labelled as sprites (enum CRE_RenderingFlag::RENDERINGFLAG_SPRITE
 in "texture.h").
 
 The entity and texture classes have been given functionality to set
 rotation angles, stretching scales, and flip flags. See "entity.h"
 and "texture.h" for more specifics.
 
 Rotation angles are meassured clockwise in degrees. Stretching scales
 are stored for both X direction scaling and Y direction scaling and
 can be changed independantly. Sprites cal be flipped by setting
 flip flags. For flips flags see enum CRE_FlipFlag.
 
 Display resolution, fullscreen mode, and aspect ratio handling
 can all be set during game runtime through an object of CRE_Video class.
 
 Display resolution can be set to whatever you want it to be. There are
 currently three fullscreen modes: fullscreen, borderless fullscreen,
 and windowed. Aspect ratio handling is used when the aspect ratio
 of the game rendering does not match the display aspect ratio.
 You can set the engine to scale or stretch the game's rendered image to fit
 the screen. Stretch to fit works slightly differently in windowed mode to
 remove black bars on the side of the window.
 
 The default values for all of these can be found in "config.h"
 
 This will likely be the last "major" update to the engine as things
 are nearing completion and the engine is slowly taking shape.
 That being said I still want to improve the engine by adding/altering
 functionality. A few examples are adding controller support, saving
 and loading keybindings from some ini file, decouping video rendering from
 game logic, and adding paralax background and foreground scrolling just
 to name a few.
 
# Feburary, 23, 2020
 In this update the rendering system has been changed slightly
 to (hopefully) optimize rendering and increase frame rates.
 Additionally, I have made some fixes to the script handler class.
 
 Starting with the rendering system; the render function in the video
 class now calculates which textures are currently within view of the
 viewport along with the portions of the textures that are within view
 of the viewport. The rendering system only draws from the portions
 of the textures that would be visible in the viewport and only
 draws to the portion of the texture that would appear on the viewport.
 
 In theory this should speed things up when drawing large textures,
 however it seems that drawing large textures is just really
 inefficient. In the future I will liekly optimize this further.
 
 As for the fixes to the script handler class; the interpretScripts
 function in the scriptHandler class was not functioning as intended
 in certain scenarios. These issues have been resolved and the
 scriptHandler class is fully functional to my knowledge.
 
 The next update will be working with the video rendering system
 to allow for dynamic display resolutions (with fixed rendering resolutions)
 along with texture scaling, rotating, and stretching.
 
# Feburary, 19, 2020
 In this update the event handlering system was overhauled
 to allow for more robust events and scripting, along with
 logical scripting.
 
 Event have been overhauled and now include 4 generic data
 unions which can hold a void ptr, function ptr (that takes arguements
 (void ptr, void ptr), or 32-bit piece of other data.
 
 Additionally, the list of event types has been expanded to
 include logical events, background/foreground events,
 logical events, and more. This list of event types will
 be updated further in the future. Information on event types
 can be found in "event.h"
 
 Event handler has been moved to it's own set of files,
 "eventHandler.h" and "eventHandler.cpp". The functionality
 of the event handler remains unchanged.
 
 There are currently some frame rate issues. Next update I
 will look into these issues and see what I can optimize.
 
# Feburary, 11, 2020
 In this update background and foregrounds functionality
 has been added via the "ground" class and related data
 structs in "grounds.h" and "ground.cpp". Additionally,
 functionality has been added for easy background and 
 foreground loading and removal. Foregrounds and backgrounds
 are stored in two vectors: foreground and background.
 
 There are four main rendering methods for foregrounds
 and backgrounds, all of which can be found in the enum
 RENDERIN_FLAG in "renderingFlags.hpp": RENDERINGFLAG_BACKGROUND,
 RENDERINGFLAG_FOREGROUND, RENDERINGFLAG_STATIC_BACKGROUND, and
 RENDERINGFLAG_STATIC_FOREGROUND. The video system renders
 graphics in specific order based on the rendering flag.
 From drawn first to drawn last: RENDERINGFLAG_STATIC_BACKGROUND,
 RENDERINGFLAG_BACKGROUND, RENDERINGFLAG_ENTITY, RENDERINGFLAG_FOREGROUND,
 and RENDERINGFLAG_STATIC_FOREGROUND. Additionally, static foregrounds
 and static backgrounds are not rendered relative to the
 view port position in the game context. As such, static
 foregrounds can be used for displaying HUDS or menus.
 
 When developing for the CR-Engine you will likely not need
 to use the grounds class directly and will rely on passing
 ground data to the implementation functions.
 
 There are two main components to ground data:
 the union groundImageData, and the struct groundData.
 These two user defined data types contain all data used
 for storing and conveying grounds data.
 
 groundImageData contains a pointer to textureData and a
 pointer to animation. This union stores relavent image
 data to be loaded to a ground object.
 
 groundData is implemented similarly to a singly linked list
 frame and contains several piece of information:
 an image type specifier, imageType; a pointer to
 groundImageData, data;, an animation looping flag, animFlag;
 a rendering type flag, flag; an integer representing the
 depth of ground data, depth; and finally a pointer to the
 next groundData struct to load, next.
 
 groundData structs are intended to be stringed together  singly
 linked lists where the member pointer in groundData, next
 points to the next piece of groundData to load.
 
 Both groundData and groundImageData are inteneded to be
 stored as const structs to prevent using working memory for
 storing image data.
 
 There are five main implementation functions for handling
 foregrounds and backgrounds: setGround, loadGround, 
 resetGround, updateGround, and groundsEmpty.
 
 setGround and loadGround have similar functionality. They
 both take a groundData struct as arguements and generate ground objects
 in the foreground and background vectors based on the
 passed groundData. The main difference between these two
 functions is that setGrounds removes all current foreground
 and background data before loading the passed groundData
 while loadGrounds just loads the passed groundData.
 
 resetGround removes all or part of the current foreground
 and background data depending on which version of the
 overloaded function is currently used. The two overloaded
 versions of resetGround take no arguements, or a RENDERING_FLAG.
 The no arguements version resets all foreground and background
 data while the RENDERING_FLAG version removes all foreground or
 background data of the passed flag.
 
 updateGrounds updates the animation for all currently loaded
 foregrounds and backgrounds. This function is only called by
 the video system but can be called by the user for any
 particular reason.
 
 Finally, groundsEmpty returns a boolean variables for if the
 foreground and background vectors are empty.
 
 As a final note, the grounds system is fully functional but 
 some functionality will be added in the future. In particular,
 depth-based rendering priority is not currently implemented.
 Additionally, in the future I want to add some way to
 remove specific foregrounds and backgrounds that are
 currently loaded.

 The next update is aready underway and focuses on re-tooling
 the event and scripting systems to provide more robust form
 of scripting and event passing. Ideally the next update will
 make it such that most processes in the CR-Engine occurs
 from passing specific events.
 
# January, 25, 2020
 In this update a few new things have been added. Firstly,
 Entities are now rendered based on their z position, or
 depth, textures have added implementation for making
 proper use of their dynamic memory portion, and only
 entities that are on screen will be rendered to the frame.
 
 Starting with entities being rendered based on their z
 positon. You can think of an entities z position being how
 much they pop out of the screen. As such entities with a
 higher z position will be rendered on top of entities with
 a lower z position. An additional part to add that
 rendering flags have been added for static foreground and
 background textures (foreground and background textures
 that don't change position with a moving view port). These
 rendering flags have not been completely implemented and
 will be further expanded upon in a later update.
 
 The texture class now has a copy constructor and
 overloaded assignment operator to prevent issues with the
 dynamically allocated member SDL_Texture.
 
 Finally a bit of logic has been added to the render
 function to only draw entities that would show on screen.
 This change should not have any visual impact but in
 theory speeds up the rendering time as the engine no
 longer renders entities that wouldn't show on screen anyways.
 
 For the next update I will likely add implementation to
 background and foreground textures, and may also implement
 custom binding readings.
 
# January, 23, 2020
 Very small update today. I have fixed another memory leak
 in the CR-Engine. This time it appears that there are no
 other memory leaks in the game. The leak occured in the
 function getFilePath(string, RESOURCE_PATH). The function
 would allocate a char*
 but never deallocated it after determining the path of the
 passed resource. This issue has been fixed and now there
 are no memory leaks to my knowledge.
 
# January, 15, 2020 (Again)
 Smaller update for the last part of today. Texture data
 and entity data have been implemented.

 Texture data is stored as a struct, textureData. This
 struct contains four members: string path, SDL_Rect source,
 int xOffset, and int yOffset. path is the name of the 
 texture to be loaded. Not that you do not need to specify
 the file path as the name suggests, CR-Engine
 automatically handles pathing. source is the rectangle of
 the image which CR-Engine will draw from. In most cases
 this will be {0, 0, width, height} where width and height
 are the width and high of the texture image respectively.
 xOffset and yOffset have a similar purpose. They represent
 where the upper left corner of the image will be located
 when the image is draw to the screen relative to the
 entity's position which contains the texture. xOffset
 represents the number of pixels left of the entity's x
 position and the yOffset represents the number of pixels
 above the entity's y position.

 The framework for entity data has been implemented but
 will need to be expanded based on a game specific needs.
 the entityData structure contains two members, int
 entityType, and a union called componentData which
 may contain information that regards one specific type of
 entity. entityType tells the game logic which member
 struct of the union componentData to read. The union
 componentData should contain several structures which
 contain data to specific types of entities (player, fireball, etc).

 With this new member to the entity class a few new
 functions have been added to access and mutate the entityData
 structure. entity::setEntityType(unsigned int) sets
 data.entityData to the passed integer. entity::getEntityType()
 returns the current entity type (found in entity.data.entityType).

 Functions to access and mutate the union in entity.data
 have not been added yet as I don't know how I want to
 implement these functions yet.

 Additionally there may be another memory leak in the engine.
 I'm not entirely sure if there is as memory usage slowly
 increases and decreases throughout runtime. Next update
 I will attempt to detect if there is a memory leak and if
 so fix it.
 
# January, 15, 2020
 In this update only a couple of things have been changed.
 The memory leak in the engine has been fixed, and input
 information has been relocated to a more suitible file.
 
 The memory leak was located to be in texture::loadTexture(
 string, SDL_Rect, SDL_Rect). The leak occured because I
 had assumed that the SDL function, SDL_CreateTextureFromSurface
 did not allocate any new memory. This assumption was incorrect
 and as such every time the engine loaded a new texture (say from
 an animation) memory would leak. To fix this error the previous
 texture is freed before a new texture is loaded.
 
 Input information, such as the number of inputs and the input
 array have been reloacted from the CREngine files to the input
 class. Additionally, the input array is no longer implemented
 using heap memory, but rather stack memory. The input array is
 accessed by using the function input::getUserInput(__int8[]).
 The user inputs will be copied to the passed array and no
 value is returned.
 
 For the next update I plan on implementing internal entity data
 for game logic use, and to re-implement texture data into a
 structure containing the texture path, string, source, etc
 (basically all the information that the texture class reads
 to load a texture).
 
# January, 11, 2020
 In this update event and script handling were implemented
 and tested. These proccesses are handled by the classes
 "eventHandler" and "scriptHandler" respectively.
 
 Events are passed with an internal structure, "CRE_Event."
 CRE_Events have four internal pieces of data: int
 eventType, int data1, int data2, and unsigned int
 entityID.
 
 CRE_Events have been modelled after SDL_Events
 with the removal of unnecessary information and with the
 replacement of void pointers data1 and data2 with regular
 integers. The removal of void pointers was done to allowed
 events to be stored easily in the program for use with
 scripting (as opposed to storing them in working memory).
 
 eventType tells the event handler what type of event this
 and how the internal data should be used. Some current
 events include CRE_EVENT_QUIT, CRE_TEST_PRINT,
 CRE_ENTITY_MOVE, and CRE_ENTITY_SET_POS. All of these
 event codes have been defined under enum CREEventCode in
 "event.h". During game development the programmer will
 likely need to define events as they build the game to
 suit their own game's specific needs.
 
 data1 and data2 are general purpose integers to store
 information that the event handler may need to process
 the event. In the case of CRE_EVENT_ENTITY_POS_MOVE, the
 event handler reads the data1 and data2 integers for x 
 and y positions to move a specific entity.
 
 entityID is the ID of the entity the event will be
 affecting (if applicible). The lowest entity ID and entity
 should have is 1, as such if an event does not effect a
 specific entity set the entityID to NULL or 0.
 
 Events may be stored in the program as const structs or
 may be created as needed. Regardless, when passing an
 event through the event handler make sure the event has
 an entityID assigned to it.
 
 Scripts function similarly to animations and by extension
 linked lists. Scripts are stored in the structure "script"
 and contain four pieces of information: a CRE_Event event,
 int frameCount, unsigned int entityID, and a const script*
 nextScript.
 
 event is the event that is queued to the event handler
 when the script is loaded into memory. frameCount is the
 number of frames that the script handler will delay before
 loading the next event in the script. For the case of
 frameCount = 0 the next event will be played instantly
 after the current script is loaded. entityID is a
 reference ID to have the script occur to a specific
 entity, much like how event entityID's function. The
 script's entityID will be automatically assigned to all
 events in the script. Finally, nextScript is a const
 pointer to the next script frame used in the script.
 
 The class eventHandler has two main function: void
 queueEvent(CRE_Event e, unsigned int ID), and bool
 interpretEvents(). queueEvent queues the passed event
 with a given ID for an entity which the event will
 effect. interpretEvents is called near the end of a given
 tick, before audio is played and graphics are drawn.
 internpretEvents processes all events queued this tick
 and applies them to the given entity(s). interpretEvents
 will return false if a quit event is passed, in which
 case the game loop exits and begins the cleanup and
 shutdown procedure. In all other cases interpretEvents
 returns true.
 
 The class scriptHandler also has two main functions: void
 loadScript(script eScript, unsigned int ID), and void 
 processScripts(). loadScript works very similarly to
 eventHandler's loadEvent, it loads a script into
 scriptHandler's internal linked list passing the script's
 internal event. processScripts iterates through the
 scriptHandler's internal linked list, queueing script's
 who's frame count is 0 and decrementing the frame count
 of all other scripts.
 
 Updates in the near future will include a change of how
 texture data is contained, will change the entityBlock
 from a fixed array to a vector to allow for easier entity
 management in larger games, and will alter how foreground
 and background images are established and process to allow
 for easier background and foreground usage along with
 foreground and background that don't rely on viewport
 positioning (like HUDs).
 
 Additionally, I have discovered a memory leak in
 video::render() which I intend to attend to fix in the next
 update.
 
# January, 1, 2020
 Happy new year!
 
 In this update I've mostly added a framework for creating
 and implementing scripts. Scripts in this sense are a
 sequence of commands that effect a specific entity.
 Scripts in the CR-Engine work similarly to a list list;
 in each script contains an ID for referencing specific
 entities based on ID, an SDL event to be queued on a given
 frame, an integer to determine how many frames delay there
 will be between two given events in a script, and a
 pointer to the next script container in the script.
 
 A frame count of 0 frames means that the next script
 containers event will be queued right after the current
 script event is queued. 
 
 If the pointer to the next script is NULL then there is no
 "next" script to play.
 
 If the script's internal reference ID is NULL then a
 specific entity will not be effected by the event. This
 may be used in passing events like "pause game" or
 "kill player" that would effect more than one entity.
 Entity ID's should not be set in the internal SDL event's
 void pointers as the as the ID needed may be indetermined
 until game run time, such as determining which enemines
 are hit by a given hitbox in a beat 'em up game.
 
 Scripts should be made in rom memory during game
 development and be passed through to the script handler
 class during run time.
 
 Now that that's all out of the way lets delve into how
 scripts are handled in this iteration of the CR-Engine.
 
 Scripts are loaded and interpreted by the class
 scriptHandler. This class loads scripts via the function
 loadScript, and for queueing the events in loaded scripts
 via the function processScripts.
 
 loadScript take two arguements: a script, eScripts and and
 an unsigned integer, ID. The script is loaded to the
 scriptHandler object's internal script linked list and the
 loaded scripts entity referency ID is replaced with the
 passed reference ID. The loaded script's event is then
 loaded to SDL's internal event queue. It should be noted
 that script's events are only played when the script is
 loaded to the script handler. Each frame the script is
 altered afterwards either by decrementing the frame count
 or by replacing the current script frame with the next
 script frame.
 
 proccesScripts should be called near the end of each frame
 before video rendering and audio handling and takes no
 arguements. The function cycles through each stored script
 frame. For each loaded script frame, if the script's
 internal frame counter is 0 the next script is loaded (if
 any) and the next scripts event is queued, otherwise the
 frame count is decremented.
 
 Please note that the current scripting functions still
 need to be tested. Scripting implementation may change
 drastically in the near future, so if you are for some
 reason using this engine to make a game, well first don't,
 you're shooting yourself in the foot, and secondly wait a
 bit for me to validate script handling before using this
 code.
 
 
# December, 29, 2019
 Allot of new things have been included. Firstly, a frame
 cap of 60 FPS has been implemented. Testing for this
 feature is still in the works.
 
 The framework for applying animations to entities has also
 been implemented and tested. Included in this update is 
 test animation of an orange circle that spells out th
 letters "LUL". The graphical files for this test have been
 included. Prior texture drawing has been retained and can
 still be used along side animations.
 
 The implementation of graphics rendering and texture
 retrieval from entities has been altered slightly to fix
 bugs in animation handling.
 
 Entities are now assigned an internal ID number that is
 used by the the video handler for rendering and in the
 future will be used in internal game events for entity
 referencing and verification. This ID number is
 automatically set upon entity initialization and
 re-initialization via constructors. Entities also have an
 internal definition variable. This definition variable
 is set to false upon initialization and the function
 void entity::define() must be used for external handlers
 to be able to interact with the entity.
 
 Entities no longer need to be pushed to the video
 rendering queue. Instead entities have been given an
 internal flag for if said entity should be rendered as a
 sprite, foreground image, or background image. When the
 video handler is called to render it will load every
 defined entity to the rendering queues depending on the
 entity's internal flags.
 
 On a lesser note, the input bus, entity block, video handler
 and audio handler have been redefined in certain files as an
 extern variable rather than passing addresses and assigning
 them to pointers.