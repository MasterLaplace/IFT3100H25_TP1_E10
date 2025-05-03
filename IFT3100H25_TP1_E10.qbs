import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "ThirdParty/of_v0.12.0_linux64gcc6_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "ThirdParty/of_v0.12.0_linux64gcc6_release"

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            'src/AppGui.cpp',
            'src/AppGui.hpp',
            'src/Camera.cpp',
            'src/Camera.hpp',
            'src/Canvas.cpp',
            'src/Canvas.hpp',
            'src/Canvas3D.cpp',
            'src/Canvas3D.hpp',
            'src/Controller.cpp',
            'src/Controller.hpp',
            'src/CurveUI.cpp',
            'src/CurveUI.hpp',
            'src/HistogramUI.cpp',
            'src/HistogramUI.hpp',
            'src/MappingScene.cpp',
            'src/MappingScene.hpp',
            'src/Node.hpp',
            'src/Node.inl',
            'src/PBRScene.cpp',
            'src/PBRScene.hpp',
            'src/RaytracingScene.cpp',
            'src/RaytracingScene.hpp',
            'src/TriangulationUI.cpp',
            'src/TriangulationUI.hpp',
            'src/app/Application.cpp',
            'src/app/Application.hpp',
            'src/app/Renderer.cpp',
            'src/app/Renderer.hpp',
            'src/main.cpp',
            'src/plugin/geometry/Animation.hpp',
            'src/plugin/geometry/BoundaryBox.cpp',
            'src/plugin/geometry/BoundaryBox.hpp',
            'src/plugin/geometry/GeometricPrimitives.hpp',
            'src/plugin/geometry/Instance.hpp',
            'src/plugin/geometry/geometry.hpp',
            'src/plugin/image/ColourSpaces.cpp',
            'src/plugin/image/ColourSpaces.hpp',
            'src/plugin/image/Exporting.cpp',
            'src/plugin/image/Exporting.hpp',
            'src/plugin/image/Histogram.cpp',
            'src/plugin/image/Histogram.hpp',
            'src/plugin/image/Image.cpp',
            'src/plugin/image/Image.hpp',
            'src/plugin/image/Importing.cpp',
            'src/plugin/image/Importing.hpp',
            'src/plugin/image/ResourceManager.cpp',
            'src/plugin/image/ResourceManager.hpp',
            'src/plugin/image/Sampling.hpp',
            'src/plugin/image/ToneMapping.cpp',
            'src/plugin/image/ToneMapping.hpp',
            'src/plugin/image/images.hpp',
            'src/plugin/light/Light.cpp',
            'src/plugin/light/Light.hpp',
            'src/plugin/light/light_header.hpp',
            'src/plugin/primitive/Box.cpp',
            'src/plugin/primitive/Box.hpp',
            'src/plugin/primitive/Ellipse.cpp',
            'src/plugin/primitive/Ellipse.hpp',
            'src/plugin/primitive/Ellipsoid.cpp',
            'src/plugin/primitive/Ellipsoid.hpp',
            'src/plugin/primitive/Line2D.cpp',
            'src/plugin/primitive/Line2D.hpp',
            'src/plugin/primitive/ObjModel.cpp',
            'src/plugin/primitive/ObjModel.hpp',
            'src/plugin/primitive/Point2D.cpp',
            'src/plugin/primitive/Point2D.hpp',
            'src/plugin/primitive/Polygon.cpp',
            'src/plugin/primitive/Polygon.hpp',
            'src/plugin/primitive/Primitive.hpp',
            'src/plugin/primitive/PrimitiveConcepts.hpp',
            'src/plugin/primitive/Rectangle.cpp',
            'src/plugin/primitive/Rectangle.hpp',
            'src/plugin/primitive/primitives.hpp',
            'src/plugin/raytracing/Raytracing.hpp',
            'src/plugin/shape/Shape.hpp',
            'src/plugin/states/DrawBoxState.cpp',
            'src/plugin/states/DrawBoxState.hpp',
            'src/plugin/states/DrawCoonsState.cpp',
            'src/plugin/states/DrawCoonsState.hpp',
            'src/plugin/states/DrawEllipseState.cpp',
            'src/plugin/states/DrawEllipseState.hpp',
            'src/plugin/states/DrawEllipsoidState.cpp',
            'src/plugin/states/DrawEllipsoidState.hpp',
            'src/plugin/states/DrawHistogramState.cpp',
            'src/plugin/states/DrawHistogramState.hpp',
            'src/plugin/states/DrawLineState.cpp',
            'src/plugin/states/DrawLineState.hpp',
            'src/plugin/states/DrawPointState.cpp',
            'src/plugin/states/DrawPointState.hpp',
            'src/plugin/states/DrawPolygonState.cpp',
            'src/plugin/states/DrawPolygonState.hpp',
            'src/plugin/states/DrawRectangleState.cpp',
            'src/plugin/states/DrawRectangleState.hpp',
            'src/plugin/states/SelectionState.cpp',
            'src/plugin/states/SelectionState.hpp',
            'src/plugin/states/State.hpp',
            'src/plugin/states/StateMachine.cpp',
            'src/plugin/states/StateMachine.hpp',
            'src/plugin/states/states.hpp',
            'src/plugin/texture/Skybox.cpp',
            'src/plugin/texture/Skybox.hpp',
            'src/plugin/texture/texture.hpp',
            'src/plugin/topology/BezierQuadratique.cpp',
            'src/plugin/topology/BezierQuadratique.hpp',
            'src/plugin/topology/CatmullRom.cpp',
            'src/plugin/topology/CatmullRom.hpp',
            'src/plugin/topology/Coons.cpp',
            'src/plugin/topology/Coons.hpp',
            'src/plugin/topology/Delauney.cpp',
            'src/plugin/topology/Delauney.hpp',
            'src/plugin/topology/ShaserLoader.hpp',
            'src/plugin/topology/TessellationShader.hpp',
            'src/plugin/topology/topology.hpp',
            'src/plugin/transformation/CoordinateSystem.hpp',
            'src/plugin/transformation/InteractiveTransformation.hpp',
            'src/plugin/transformation/MultiSelection.hpp',
            'src/plugin/transformation/SceneGraph.hpp',
            'src/plugin/transformation/history/Command.hpp',
            'src/plugin/transformation/history/Invoker.cpp',
            'src/plugin/transformation/history/Invoker.hpp',
            'src/plugin/transformation/history/Invoker.inl',
            'src/plugin/transformation/transformation.hpp',
        ]

        of.addons: [
            'ofxAssimpModelLoader',
            'ofxGui',
            'ofxImGui',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
                                // will compile OF only once for all your projects
                                // otherwise compiled per project with qbs
    

    property bool precompileOfMain: false  // precompile ofMain.h
                                           // faster to recompile when including ofMain.h 
                                           // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
