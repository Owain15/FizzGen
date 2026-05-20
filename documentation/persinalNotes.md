Event system
. consider a buffered/ async event system, where events are stored in a queue and processed at a later time. this can help to decouple the event generation from the event handling, and can also help to improve performance by allowing events to be processed in batches.
. on button/click held keep track of how meany triggers are generated.

Logging lib
. spdlog, look into creating my own, "OJLogging"

initial rederer api opengl. 
. look into renderer for android use. vulken is most commonly used indesty wide.

Math lib
. cosider using directX lib, look into creating my own math library.

Premake
. look into premake, cmake, meson, and other build systems. premake

consider a Renderer cofig file to prepar solution for different architecturs. ie. ARM or X64.

Window Resize
. orthographic Camera, consider how to handle window resize events and adjust 
the camera accordingly. a.display a lager area. b. resize so the image renderd is the same but at the new window size.
c. wright both options and allow the user to choose which one they want to use. 

Diagnostics/ Profiling
. consider implementing a diagnostics or profiling system to help identify performance bottlenecks and optimize the engine
	- currntly a crude class in sandbox2D, code could be extracted and kep within FizGen, and expanded upon.
	- currently visulizing though chrom/tracer. could diagnostics be visualized though local code?
	- look int difernt styles of collecting data. more focused on collecting all data indefinatly

