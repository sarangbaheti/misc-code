/*
EngineAll.h
Written by Matthew Fisher

Many objects are universal and don't need to change often.  The source for all such files
are included in this file.  Often this would be compiled into a single *.lib or *.dll,
but I prefer to keep all my source readily accessible.  Another advantage of this is that
it is simpler to compile a subset of the code that includes only desired functionality (and
thus avoids as many external dependencies as possible.)
*/

/****************************/
/*           Core           */
/****************************/
//These are generic objects and functions that have no specific place anywhere else

//Forward declarations for several classes/structures
#include "EngineAll\Core\ClassList.h"

//All #includes that are generic or written by other people
#include "EngineAll\Core\ExternalFiles.h"

//The Vector class contains dynamic arrays of a template type.  This is equivalent to the Standard Template 
//Library's vector class, but for various reasons I like to have my own.
#include "EngineAll\Core\Vector.h"

//Collection of useful constants, macros, and functions
#include "EngineAll\Core\Stdhdr.h"

//Generic 32-bit RGBA color structure.  This early include is needed by SpaceVector.
#include "EngineAll\Math\RGBColor.h"

//SpaceVector, which defines 2D, 3D and 4D vectors and rectangles.  This early include is needed by Grid.
#include "EngineAll\Math\SpaceVector.h"

//a Grid is a 2D array
#include "EngineAll\Core\Grid.h"

//Basic string class
#include "EngineAll\Core\String.h"
#include "EngineAll\Core\UnicodeString.h"

//OutputDataStream and InputDataStream are binary equivalents of ofstream and ifstream, respectively
#include "EngineAll\Core\OutputDataStream.h"
#include "EngineAll\Core\InputDataStream.h"

//definition of various key codes
#include "EngineAll\Core\KeyDefs.h"

/****************************/
/*      Multithreading      */
/****************************/
//Objects pretaining to creating applications that use multiple threads

//A mutex is an object that grants a thread exclusive access to a given section of code
#include "EngineAll\Multithreading\Mutex.h"

//A thread is a single unit of code execution
#include "EngineAll\Multithreading\Thread.h"

/****************************/
/*        Networking        */
/****************************/
//Objects pretaining to sending data between programs or computers

//A pipe is a connection between two programs, possibly on different computers
#include "EngineAll\Networking\Pipe.h"

/****************************/
/*           Math           */
/****************************/
//All mathematical structures and functions are here.

//standard geometric objects
#include "EngineAll\Math\Line3D.h"
#include "EngineAll\Math\LineSegment2D.h"
#include "EngineAll\Math\LineSegment3D.h"
#include "EngineAll\Math\Ray3D.h"
#include "EngineAll\Math\Plane.h"
#include "EngineAll\Math\Intersect.h"

//fixed size square matrix classes
#include "EngineAll\Math\Matrix4.h"

//Dense matrix class
#include "EngineAll\Victor\Eigensystems.h"
#include "EngineAll\Math\DenseMatrix.h"

//Sparse matrix class, used by LinearSolver
#include "EngineAll\Math\SparseMatrix.h"

//Linear optimizer.  Uses (bi-)conjugate gradient descent or TAUCS's cholesky solver.
#include "EngineAll\Math\LinearSolver.h"

#include "EngineAll\Math\PCA.h"

#include "EngineAll\Math\KMeansClustering.h"

/****************************/
/*     Graphics Objects     */
/****************************/
//These are structures specific to geometry and computer graphics rendering.

//Transformations between color spaces
#include "EngineAll\Graphics Objects\ColorSpaces.h"

//A bitmap class (a 2D array of RGBColor's)
#include "EngineAll\Graphics Objects\Bitmap.h"

//MatrixController manages the 3 transformations (world, view, projection) central to the graphics pipeline
#include "EngineAll\Graphics Objects\MatrixController.h"

//Camera represents a 3-D free floating camera.
#include "EngineAll\Graphics Objects\Camera.h"

//MeshVertex represents a single vertex in a mesh structure.
#include "EngineAll\Graphics Objects\MeshVertex.h"

//Viewport represents a rectangle on the screen used for rendering
#include "EngineAll\Graphics Objects\Viewport.h"

//General purpose nearest-neighbor structure
#include "EngineAll\Graphics Objects\KDTreeN.h"

//3D point nearest neighbor structure
#include "EngineAll\Graphics Objects\KDTree3.h"

//Ray and triangle mesh intersection structure
#include "EngineAll\Graphics Objects\RayIntersector.h"
#include "EngineAll\Graphics Objects\RayIntersectorBruteForce.h"
#include "EngineAll\Graphics Objects\RayIntersectorKDTree.h"

//collection of 3D points
#include "EngineAll\Graphics Objects\PointSet.h"

//A simple ZBuffer structure, for software rendering.  Stores the depth of each screen pixel.
#include "EngineAll\Graphics Objects\ZBuffer.h"

//Clipper is used to take an arbitrary polygon and clip it against the viewing frustrum.
#include "EngineAll\Graphics Objects\Clipper.h"

//Rendering functions for lines and polygons in software.  Not very efficent.
#include "EngineAll\Graphics Objects\PrimitiveRender.h"

/****************************/
/*     Machine Learning     */
/****************************/
#include "EngineAll\MachineLearning\BinaryClassifier.h"
#include "EngineAll\MachineLearning\BinaryClassifierBagged.h"
#include "EngineAll\MachineLearning\BinaryClassifierAdaBoost.h"
#include "EngineAll\MachineLearning\BinaryClassifierLogisticRegression.h"
#include "EngineAll\MachineLearning\BinaryClassifierSVM.h"
#include "EngineAll\MachineLearning\BinaryClassifierNaiveBayes.h"
#include "EngineAll\MachineLearning\BinaryClassifierMulticlass.h"
#include "EngineAll\MachineLearning\MulticlassClassifier.h"
#include "EngineAll\MachineLearning\MulticlassClassifierAdaBoostM1.h"
#include "EngineAll\MachineLearning\MulticlassClassifierPairwiseCoupling.h"
#include "EngineAll\MachineLearning\MulticlassClassifierOneVsAll.h"
#include "EngineAll\MachineLearning\MulticlassClassifierDecisionTree.h"
#include "EngineAll\MachineLearning\MulticlassClassifierNearestNeighborBruteForce.h"
#include "EngineAll\MachineLearning\MulticlassClassifierNearestNeighborANN.h"
#include "EngineAll\MachineLearning\MulticlassClassifierGenerator.h"
#include "EngineAll\MachineLearning\RegressionLearner.h"
#include "EngineAll\MachineLearning\RegressionLearnerBagged.h"
#include "EngineAll\MachineLearning\RegressionLearnerDecisionTree.h"
#include "EngineAll\MachineLearning\RegressionLearnerNearestNeighbor.h"
#include "EngineAll\MachineLearning\ClassifierDatasetTransformer.h"
#include "EngineAll\MachineLearning\ClassifierDatasetTransformerPCA.h"

/****************************/
/*  Simple Mesh Structures  */
/****************************/
//These files all center around creating and manipulating triangle meshes.
//These meshes are "simple" in that they contain no adjaceny information and are just an indexed vertex list.

//BaseMesh is an abstract mesh class that defines basic mesh functionality.  It also includes source for most
//of the manipulation (shape generation, file loading, etc.) that is possible under this generic structure.
#include "EngineAll\Simple Mesh\BaseMesh.h"

//D3D9Mesh is a DirectX 9 implementation of the BaseMesh class
#include "EngineAll\Simple Mesh\D3D9Mesh.h"

//D3D10Mesh is a DirectX 10 implementation of the BaseMesh class
#include "EngineAll\Simple Mesh\D3D10Mesh.h"

//Mesh is a standard C++ array instance of the BaseMesh class.  It's the only kind that can be used by OpenGL,
//but it will run fine under DirectX as well (if not as quickly as a D3D9Mesh.)
#include "EngineAll\Simple Mesh\Mesh.h"

/************************************/
/*     Complex Mesh Structures      */
/************************************/
//These files implement a complex (edge-based) mesh structure.

//definition of the Triangle structure
#include "EngineAll\Complex Mesh\Triangle.h"

//functions for an indivudial vertex
#include "EngineAll\Complex Mesh\Vertex.h"

//Edge-based functions
#include "EngineAll\Complex Mesh\FullEdge.h"

//ComplexMesh class encapsulates and stores arrays of all components in the edge-based data structure
#include "EngineAll\Complex Mesh\ComplexMesh.h"

/****************************/
/*           Textures       */
/****************************/
//These files all control rendering textured polygons through DirectX and OpenGL.

//BaseTexture is an abstract class that defines base-level texture functionality
#include "EngineAll\Textures\BaseTexture.h"

//DirectX implementations of BaseTexture
#include "EngineAll\Textures\D3D9Texture.h"
#include "EngineAll\Textures\D3D10Texture.h"

//OpenGL implementation of BaseTexture
#include "EngineAll\Textures\OpenGLTexture.h"

//Generic texture class that maps to either a DirectX or OpenGL texture based upon what the current window is using.
#include "EngineAll\Textures\GenericTexture.h"

/****************************/
/*     Direct3D Objects     */
/****************************/
//Objects that encapsulate shader and render-to-texture functionality in DirectX.

//Abstract class used for all resetable D3D9 graphics objects
#include "EngineAll\D3DObjects\D3D9Object.h"

//A texture that can be used as the render target
#include "EngineAll\D3DObjects\D3D9RenderTargetTexture.h"

//A surface that can be used as the render target
#include "EngineAll\D3DObjects\D3D9RenderTargetSurface.h"

//Vertex decleration used for shaders
#include "EngineAll\D3DObjects\D3D9VertexDeclaration.h"

//Pixel shaders
#include "EngineAll\D3DObjects\D3D9PixelShader.h"

//Vertex shaders
#include "EngineAll\D3DObjects\D3D9VertexShader.h"

//Fonts
#include "EngineAll\D3DObjects\D3D9Font.h"

//Effects
#include "EngineAll\D3DObjects\D3D10Effect.h"

//D3D9Mesh that can reset itself with a RAM copy
#include "EngineAll\D3DObjects\D3D9PersistentMesh.h"

/****************************/
/*     Graphics Devices     */
/****************************/
//A graphics device controls the interaction between Windows and a graphics API.

//GraphicsDevice is the abstract class that contains functionality that all graphics devices must expose.
//any GraphicsDevice can do simple things like render meshes into the main rendering window and handle
//the world, view and projection transforms.
#include "EngineAll\Graphics Devices\GraphicsDevice.h"

//a D3D instance of GraphicsDevice
#include "EngineAll\Graphics Devices\D3D9GraphicsDevice.h"
#include "EngineAll\Graphics Devices\D3D10GraphicsDevice.h"

//a OpenGL instance of GraphicsDevice
#include "EngineAll\Graphics Devices\OpenGLGraphicsDevice.h"

//a software instance of GraphicsDevice
#include "EngineAll\Graphics Devices\SoftwareGraphicsDevice.h"

/****************************/
/*          Utility         */
/****************************/
//These simplify access to existing classes

//The frame timer reads the system time and maintains the frames per second counter.
#include "EngineAll\Utility\FrameTimer.h"

//MovieExporter manages screen capture and exports as a sequence of images for compilation
//into a movie.
#include "EngineAll\Utility\MovieExporter.h"

//AudioCapture captures the current line-out or line-in to an uncompressed audio stream
#include "EngineAll\Utility\AudioCapture.h"

//VideoCompressor takes a sequence of images and compressed them into a video file.
#include "EngineAll\Utility\VideoCompressor.h"

//the Indicator class rapidly renders spheres or cylinders between arbitrary points in three space
//by using stored mesh data and loading a new Matrix4 each time a cylinder or sphere needs "indicating."
//also can do basic viewing frustrum (camera) analysis or rendering.
#include "EngineAll\Utility\Indicator.h"

//A FileCollection stores a large number of files as a single file.  It is similar to a tar file in functionality.
#include "EngineAll\Utility\FileCollection.h"

//A directory manages the list of files and subdirectories in a given folder
#include "EngineAll\Utility\Directory.h"

//the Parameter class loads a paramater file as a simple set of "Parameter=Option" lines
#include "EngineAll\Utility\ParameterFile.h"

//UVAtlas uses D3D to generate a paramaterization of a mesh in the plane
#include "EngineAll\Utility\UVAtlas.h"

//Profiler is used to record the percent of time spent in code
#include "EngineAll\Utility\Profiler.h"

//MenuInterface streamlines adding a menu to a window
#include "EngineAll\Utility\MenuInterface.h"

//The Console namespace controls all access to the console
#include "EngineAll\Utility\Console.h"

/****************************/
/*            GUI           */
/****************************/
//These objects support overlaying user-interface objects like sliders or buttons onto the scene.

//Abstract class that all GUI elements use
#include "EngineAll\GUI\GUIElement.h"

//GUIController handles dispatching window events and rendering a set of GUIElement objects
#include "EngineAll\GUI\GUIController.h"

//A clickable button GUIElement
#include "EngineAll\GUI\GUIButton.h"

//A draggable slider GUIElement
#include "EngineAll\GUI\GUISlider.h"

/****************************/
/*    Windows Controllers   */
/****************************/
//These files handle the interaction between the application and Windows.  This includes files that contain
//WinMain and create the main application window.  There is also a frame timer and a screen capture mechanism.

//The input manager stores and controls access to keyboard and mouse data
#include "EngineAll\Windows Controller\InputManager.h"

//Creating a new window involves having a callback function, WndProc, that is called whenever Windows has
//an event to send to your window/application.  EventHandler contains the WndProc file as well as the global
//array of keys that tells which keys are current pressed/depressed.
#include "EngineAll\Windows Controller\EventHandler.h"

//WindowManager handles creating and managing the application's main window
#include "EngineAll\Windows Controller\WindowManager.h"

//A set of useful objects associated with each window (the graphics device, window manager, input manager, and
//frame timer.)
#include "EngineAll\Windows Controller\WindowObjects.h"

//Abstract class for an object which controls all rendering each frame.
#include "EngineAll\Windows Controller\FrameController.h"
