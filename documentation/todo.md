 -- FizzGen -- 

----------------
Summery
----------------
.complete game engin baised apon the game engine corse by "the cherno". youtude.com


GameEnginePlaylist 
[26/123] "static lib"  

----------------
Current Support
----------------
    
    Platform
     []windows X64
     []widows ARM64
    
    Renderer
     []OpenGL

    Math Libuary
     []glm

    Logging Sysetem
     []spdlog

----------------
Overview
----------------

.Entery Point
    []

.Application Layer
    []

.Display Layer

    .Inputs
     []
    .Events
     []

.Renderer
    []

.Render API
    []

.Debugging Support
    []

.Scripting Layer
    []

.Memory Systems
    []

.Event System
   [] Application Events
        [] App Tick Events
        [] App Update Events
        [] App Render Events

    [] Mouse Events
        [] Mouse Button Events
        []Mouse Position Events
        [] Mouse Move Events
        [] Mouse Scroll Events
    
    [] Keyboard Events
        [] Key Press Events
        [] Key Release Events
        [] Key Repeat Events
    
    [] Window Events
        [] Window Close Events
        [] Window Resize Events
        [] Window Focus Events
        [] Window Lost Focus Events
        [] Window Moved Events

.ECS (Entity Component System)
    []

.Physics System
    []

.File I/O
    []

.VSF (Virtual File System)
    []

.Build System
    []
    .Hotspot ability

----------------
render architecture
----------------

    ------------
    render API (API platform specific)
    ------------
    .render context
    .swap chain
    .frame buffer
    .vertex buffer
    .index buffer
    .texture
    .shader
    .states
    .pipeline
    .render pass
    .command buffer

    ------------
    Renderer (API platform agnostic) abstraction
    ------------
    .2D renderer
        
    .3D renderer

    .scene graph

    .sorting

    .culling

    .materrials

    .LOD (Level of Detail)

    .animation

    .camera

    .vfx

    .post fx system

----------------
current renderer support
----------------
    []OpenGL
    
    .future renderer support
    
    []vulken
    []directX 12

-----------------
    
        