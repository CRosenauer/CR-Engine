# Update
 This file contains the changelogs for all (or most) of the
 updates to the CR-Engine. For a more general overview see
 repository notes.
 
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