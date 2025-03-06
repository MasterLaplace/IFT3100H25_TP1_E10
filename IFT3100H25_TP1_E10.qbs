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
            'src/Canvas.cpp',
            'src/Canvas.hpp',
            'src/Controller.hpp',
            'src/Controller.cpp',
            'src/Controller.hpp',
            'src/DrawingTools.cpp',
            'src/DrawingTools.hpp',
            'src/HistogramUI.cpp',
            'src/HistogramUI.hpp',
            'src/Importation.cpp',
            'src/Importation.hpp',
            'src/Node.inl',
            'src/Node.hpp',
            'src/app/Application.cpp',
            'src/app/Application.hpp',
            'src/app/Renderer.cpp',
            'src/app/Renderer.hpp',
            'src/main.cpp',
            'src/plugin/camera/InteractiveCamera.hpp',
            'src/plugin/camera/MultiViewpoints.hpp',
            'src/plugin/camera/Occlusion.hpp',
            'src/plugin/camera/Portal.hpp',
            'src/plugin/camera/ProjectionModes.hpp',
            'src/plugin/classical-lighting/LightTypes.hpp',
            'src/plugin/classical-lighting/LightingModels.hpp',
            'src/plugin/classical-lighting/Materials.hpp',
            'src/plugin/classical-lighting/MultiLights.hpp',
            'src/plugin/classical-lighting/NonRealisticModel.hpp',
            'src/plugin/controller/Controller.hpp',
            'src/plugin/controller/Observer.hpp',
            'src/plugin/controller/Subject.hpp',
            'src/plugin/geometry/Animation.hpp',
            'src/plugin/geometry/BoundaryBox.hpp',
            'src/plugin/geometry/GeometricPrimitives.hpp',
            'src/plugin/geometry/Instance.hpp',
            'src/plugin/geometry/ObjModel.hpp',
            'src/plugin/geometry/geometry.hpp',
            'src/plugin/image/ColourSpaces.hpp',
            'src/plugin/image/ColourSpaces.inl',
            'src/plugin/image/Exporting.cpp',
            'src/plugin/image/Exporting.hpp',
            'src/plugin/image/Histogram.cpp',
            'src/plugin/image/Histogram.hpp',
            'src/plugin/image/Importing.hpp',
            'src/plugin/image/Sampling.hpp',
            'src/plugin/image/images.hpp',
            'src/plugin/modern-lighting/DeferredRendering.hpp',
            'src/plugin/modern-lighting/EnvironmentalLight.hpp',
            'src/plugin/modern-lighting/Metallicity.hpp',
            'src/plugin/modern-lighting/Microfacets.hpp',
            'src/plugin/modern-lighting/PBR.hpp',
            'src/plugin/primitive/Ellipse.cpp',
            'src/plugin/primitive/Ellipse.hpp',
            'src/plugin/primitive/Line2D.cpp',
            'src/plugin/primitive/Line2D.hpp',
            'src/plugin/primitive/Point2D.cpp',
            'src/plugin/primitive/Point2D.hpp',
            'src/plugin/primitive/Polygon.cpp',
            'src/plugin/primitive/Polygon.hpp',
            'src/plugin/primitive/Primitive.cpp',
            'src/plugin/primitive/Primitive.hpp',
            'src/plugin/primitive/Rectangle.cpp',
            'src/plugin/primitive/Rectangle.hpp',
            'src/plugin/primitive/primitives.hpp',
            'src/plugin/raytracing/GlobalLighting.hpp',
            'src/plugin/raytracing/Intersection.hpp',
            'src/plugin/raytracing/Reflection.hpp',
            'src/plugin/raytracing/Refraction.hpp',
            'src/plugin/raytracing/Shading.hpp',
            'src/plugin/states/DrawHistogramState.cpp',
            'src/plugin/states/DrawHistogramState.hpp',
            'src/plugin/states/DrawLineState.cpp',
            'src/plugin/states/DrawLineState.hpp',
            'src/plugin/states/DrawPointState.cpp',
            'src/plugin/states/DrawPointState.hpp',
            'src/plugin/states/DrawRectangleState.cpp',
            'src/plugin/states/DrawRectangleState.hpp',
            'src/plugin/states/SelectionState.cpp',
            'src/plugin/states/SelectionState.hpp',
            'src/plugin/states/State.hpp',
            'src/plugin/states/StateMachine.cpp',
            'src/plugin/states/StateMachine.hpp',
            'src/plugin/states/states.hpp',
            'src/plugin/texture/Cubemap.hpp',
            'src/plugin/texture/Filtering.hpp',
            'src/plugin/texture/ProceduralTexture.hpp',
            'src/plugin/texture/TextureCoordinates.hpp',
            'src/plugin/texture/ToneMapping.hpp',
            'src/plugin/topology/ParametricCurve.hpp',
            'src/plugin/topology/ParametricSurface.hpp',
            'src/plugin/topology/ReliefEffect.hpp',
            'src/plugin/topology/TessellationShader.hpp',
            'src/plugin/topology/Triangulation.hpp',
            'src/plugin/transformation/CoordinateSystem.hpp',
            'src/plugin/transformation/InteractiveTransformation.hpp',
            'src/plugin/transformation/MultiSelection.hpp',
            'src/plugin/transformation/SceneGraph.hpp',
            'src/plugin/transformation/history/Command.hpp',
            'src/plugin/transformation/history/Invoker.cpp',
            'src/plugin/transformation/history/Invoker.hpp',
            'src/plugin/transformation/history/Invoker.inl',
            'src/plugin/transformation/transformation.hpp',
            'src/plugin/vector-drawing/DrawingTools.hpp',
            'src/plugin/vector-drawing/DynamicSlider.hpp',
            'src/plugin/vector-drawing/Interface.hpp',
            'src/plugin/vector-drawing/VectorPrimitives.hpp',
            'src/plugin/vector-drawing/VectorShapes.hpp',
            'src/plugin/vector-drawing/vector_drawing.hpp',
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
