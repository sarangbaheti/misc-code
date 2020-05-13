/*
EngineAll.cpp
Written by Matthew Fisher

See EngineAll.h for a defintion of all files included here.
*/

//All source files include Main.h
#include "Main.h"

#include "EngineAll\Core\Stdhdr.cpp"
#include "EngineAll\Core\UnicodeString.cpp"
#include "EngineAll\Core\String.cpp"
#include "EngineAll\Core\OutputDataStream.cpp"
#include "EngineAll\Core\InputDataStream.cpp"

#include "EngineALl\Networking\Pipe.cpp"

#include "EngineAll\Math\RGBColor.cpp"
#include "EngineAll\Math\SpaceVector.cpp"
#include "EngineAll\Math\Line3D.cpp"
#include "EngineAll\Math\LineSegment2D.cpp"
#include "EngineAll\Math\LineSegment3D.cpp"
#include "EngineAll\Math\Plane.cpp"
#include "EngineAll\Math\Intersect.cpp"
#include "EngineAll\Math\Matrix4.cpp"

#include "EngineAll\Multithreading\Thread.cpp"

#include "EngineAll\Graphics Objects\ColorSpaces.cpp"
#include "EngineAll\Graphics Objects\Bitmap.cpp"
#include "EngineAll\Graphics Objects\ZBuffer.cpp"
#include "EngineAll\Graphics Objects\MatrixController.cpp"
#include "EngineAll\Graphics Objects\Camera.cpp"
#include "EngineAll\Graphics Objects\PrimitiveRender.cpp"
#include "EngineAll\Graphics Objects\MeshVertex.cpp"
#include "EngineAll\Graphics Objects\Clipper.cpp"
#include "EngineAll\Graphics Objects\Viewport.cpp"
#include "EngineAll\Graphics Objects\KDTree3.cpp"
#include "EngineAll\Graphics Objects\KDTreeN.cpp"
#include "EngineAll\Graphics Objects\PointSet.cpp"
#include "EngineAll\Graphics Objects\RayIntersectorBruteForce.cpp"
#include "EngineAll\Graphics Objects\RayIntersectorKDTree.cpp"

#include "EngineAll\Simple Mesh\BaseMesh.cpp"
#include "EngineAll\Simple Mesh\D3D9Mesh.cpp"
#include "EngineAll\Simple Mesh\D3D10Mesh.cpp"
#include "EngineAll\Simple Mesh\Mesh.cpp"

#include "EngineAll\Complex Mesh\Triangle.cpp"
#include "EngineAll\Complex Mesh\FullEdge.cpp"
#include "EngineAll\Complex Mesh\Vertex.cpp"
#include "EngineAll\Complex Mesh\ComplexMesh.cpp"

#include "EngineAll\D3DObjects\D3D9RenderTargetTexture.cpp"
#include "EngineAll\D3DObjects\D3D9RenderTargetSurface.cpp"
#include "EngineAll\D3DObjects\D3D9VertexDeclaration.cpp"
#include "EngineAll\D3DObjects\D3D9PixelShader.cpp"
#include "EngineAll\D3DObjects\D3D9VertexShader.cpp"
#include "EngineAll\D3DObjects\D3D9PersistentMesh.cpp"
#include "EngineAll\D3DObjects\D3D9Font.cpp"
#include "EngineAll\D3DObjects\D3D10Effect.cpp"

#include "EngineAll\Textures\BaseTexture.cpp"
#include "EngineAll\Textures\D3D9Texture.cpp"
#include "EngineAll\Textures\D3D10Texture.cpp"
#include "EngineAll\Textures\OpenGLTexture.cpp"
#include "EngineAll\Textures\GenericTexture.cpp"

#include "EngineAll\Graphics Devices\GraphicsDevice.cpp"
#include "EngineAll\Graphics Devices\D3D9GraphicsDevice.cpp"
#include "EngineAll\Graphics Devices\D3D10GraphicsDevice.cpp"
#include "EngineAll\Graphics Devices\OpenGLGraphicsDevice.cpp"
#include "EngineAll\Graphics Devices\SoftwareGraphicsDevice.cpp"

#include "EngineAll\Utility\MovieExporter.cpp"
#include "EngineAll\Utility\AudioCapture.cpp"
#include "EngineAll\Utility\VideoCompressor.cpp"
#include "EngineAll\Utility\Indicator.cpp"
#include "EngineAll\Utility\FileCollection.cpp"
#include "EngineAll\Utility\ParameterFile.cpp"
#include "EngineAll\Utility\UVAtlas.cpp"
#include "EngineAll\Utility\FrameTimer.cpp"
#include "EngineAll\Utility\Profiler.cpp"
#include "EngineAll\Utility\Directory.cpp"
#include "EngineAll\Utility\MenuInterface.cpp"
#include "EngineAll\Utility\Console.cpp"

#include "EngineAll\Windows Controller\InputManager.cpp"
#include "EngineAll\Windows Controller\EventHandler.cpp"
#include "EngineAll\Windows Controller\WindowManager.cpp"
#include "EngineAll\Windows Controller\WindowObjects.cpp"
